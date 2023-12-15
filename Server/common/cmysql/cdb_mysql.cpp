/********************************************************************
created:	2019-08-13

author:		chensong

purpose:	cdb_mysql
输赢不重要，答案对你们有什么意义才重要。

光阴者，百代之过客也，唯有奋力奔跑，方能生风起时，是时代造英雄，英雄存在于时代。或许世人道你轻狂，可你本就年少啊。 看护好，自己的理想和激情。


我可能会遇到很多的人，听他们讲好2多的故事，我来写成故事或编成歌，用我学来的各种乐器演奏它。
然后还可能在一个国家遇到一个心仪我的姑娘，她可能会被我帅气的外表捕获，又会被我深邃的内涵吸引，在某个下雨的夜晚，她会全身淋透然后要在我狭小的住处换身上的湿衣服。
3小时候后她告诉我她其实是这个国家的公主，她愿意向父皇求婚。我不得已告诉她我是穿越而来的男主角，我始终要回到自己的世界。
然后我的身影慢慢消失，我看到她眼里的泪水，心里却没有任何痛苦，我才知道，原来我的心被丢掉了，我游历全世界的原因，就是要找回自己的本心。
于是我开始有意寻找各种各样失去心的人，我变成一块砖头，一颗树，一滴水，一朵白云，去听大家为什么会失去自己的本心。
我发现，刚出生的宝宝，本心还在，慢慢的，他们的本心就会消失，收到了各种黑暗之光的侵蚀。
从一次争论，到嫉妒和悲愤，还有委屈和痛苦，我看到一只只无形的手，把他们的本心扯碎，蒙蔽，偷走，再也回不到主人都身边。
我叫他本心猎手。他可能是和宇宙同在的级别 但是我并不害怕，我仔细回忆自己平淡的一生 寻找本心猎手的痕迹。
沿着自己的回忆，一个个的场景忽闪而过，最后发现，我的本心，在我写代码的时候，会回来。
安静，淡然，代码就是我的一切，写代码就是我本心回归的最好方式，我还没找到本心猎手，但我相信，顺着这个线索，我一定能顺藤摸瓜，把他揪出来。
*********************************************************************/

#include "cdb_mysql.h"
#include "csql_mgr.h"
#include "cdb_query_result.h"
#include "clog.h"
#include <sstream>
 
namespace chen {


	static const uint32 MAX_SQL_LENGTH = 1024 * 1024; // 1M


	int cdb_mysql::m_count = 0;
	bool cdb_mysql::m_inited = false;
	cdb_mysql::cdb_mysql()
		: m_mysql(NULL)
		, m_prepare_disconnect(false)
		, m_disconnect_fn(NULL)
	{
		if (!m_inited)
		{
			mysql_library_init(-1, NULL, NULL);
			m_inited = true;
			++m_count;
		}
	}
	cdb_mysql::~cdb_mysql()
	{
		shut_down();
		--m_count;
		if (0 == m_count)
		{
			mysql_library_end();
		}
	}
	
	bool cdb_mysql::init(const cdb_cfg & db_cfg, const std::string & name)
	{
		m_cfg = db_cfg;
		m_name = name;

		if (!_connect())
		{
			return false;
		}
		return m_out_info.init(name);
	}
	bool cdb_mysql::connect(const cdb_cfg & db_cfg)
	{
		if (m_mysql)
		{
			mysql_close(m_mysql);
			m_mysql = NULL;
		}

		m_cfg = db_cfg;

		if (!_connect())
		{
			return false;
		}

		return true;
	}
	void cdb_mysql::destroy()
	{
	}
	void cdb_mysql::shut_down()
	{
		if (m_mysql)
		{
			mysql_close(m_mysql);
			m_mysql = NULL;
		}
		m_out_info.close();
	}
	bool cdb_mysql::send_query(cdb_query_result & query_result, const char * query, uint32 len)
	{
		if (m_prepare_disconnect)
		{
			return false;
		}

		if (_excute_query(query, len))
		{
			MYSQL_RES*	mysql_res = mysql_store_result(m_mysql);
			query_result.connect(mysql_res);

			return true;
		}
		else
		{
			_sql_error_prompt(query, len);
			_out_info(query, len);
			return false;
		}
	}
	bool cdb_mysql::send_query(cdb_query_result & query_result, const std::string & query)
	{
		return send_query(query_result, query.c_str(), static_cast<uint32>(query.length()));;
	}
	bool cdb_mysql::send_query(cdb_query_result & query_result, const csql_mgr & query)
	{
		if (query.has_error())
		{
			return false;
		}
		return send_query(query_result, query.get_buf(), query.get_size());
	}
	bool cdb_mysql::excute(const char * query, uint32 len, ESqlErrorType error_type, bool flag_error)
	{
		if (m_prepare_disconnect)
		{
			_out_info(query, len);
			return true;
		}

		if (flag_error || !_excute_query(query, len))
		{
			bool is_fist = false;
			if (error_type == ESqlError_ShutDown && m_prepare_disconnect == false)
			{
				is_fist = true;
				m_prepare_disconnect = true;
			}
			_out_info(query, len);
			_sql_error_prompt(query, len);
			if (is_fist && NULL != m_disconnect_fn)
			{
				m_disconnect_fn();
			}
			if (error_type == ESqlError_ShutDown)
			{
				return true;
			}
			return false;
		}
		return true;
	}
	bool cdb_mysql::excute(const std::string & query, ESqlErrorType error_type)
	{
		return excute(query.c_str(), (uint32)query.length(), error_type);;
	}
	bool cdb_mysql::excute(const csql_mgr & query, ESqlErrorType error_type)
	{
		return excute(query.get_buf(), query.get_size(), error_type, query.has_error());
	}
	bool cdb_mysql::_connect( )
	{
		m_mysql = mysql_init(NULL);
		if (!m_mysql)
		{
			ERROR_EX_LOG("Could not initialize Mysql connection");
			//LLOG_ERROR << "Could not initialize Mysql connection";
			return false;
		}

		mysql_options(m_mysql, MYSQL_SET_CHARSET_NAME, "utf8");
		bool is_reconnect = true;
		mysql_options(m_mysql, MYSQL_OPT_RECONNECT, &is_reconnect);

		m_mysql = mysql_real_connect(m_mysql, m_cfg.m_host.c_str(), m_cfg.m_user.c_str(), m_cfg.m_passwd.c_str(), m_cfg.m_db_name.c_str(), m_cfg.m_port
			, NULL, 0);

		if (m_mysql)
		{
			
			if (mysql_autocommit(m_mysql, m_cfg.m_auto_commit))
			{
				ERROR_EX_LOG("autocommit not set to %d", m_cfg.m_auto_commit);
				//LLOG_ERROR << "autocommit not set to " << m_cfg.m_auto_commit;
			}

			//mysql_query(m_mysql, "SET NAMES utf8");
			mysql_query(m_mysql, "SET NAMES utf8");

			if (m_cfg.m_time_zone >= -11 && m_cfg.m_time_zone <= 12)
			{
				std::stringstream sql;
				sql << "set time_zone = '";
				if (m_cfg.m_time_zone >= 0)
				{
					sql << "+";
				}

				sql << m_cfg.m_time_zone << ":00'";
				if (!excute(sql.str()))
				{
					return false;
				}
			}
			else if (m_cfg.m_time_zone != -12)
			{
				ERROR_EX_LOG("time_zone = %d, error!", m_cfg.m_time_zone);
				//LLOG_ERROR << "time_zone = " << m_cfg.m_time_zone << ", error!";
				return false;
			}
		}
		else
		{
			ERROR_EX_LOG("failed to connect to mysql [ip = %s][port = %u][db_name = %s][password = %s]", m_cfg.m_host.c_str(), m_cfg.m_port, m_cfg.m_db_name.c_str(), m_cfg.m_passwd.c_str());
			//LLOG_ERROR << "failed to connect to mysql";
			return false;
		}

		return true;
	}
	bool cdb_mysql::_excute_query(const char * query, uint32 len)
	{
		if (0 == len || len > MAX_SQL_LENGTH)
		{
			ERROR_EX_LOG("bad sql length = %u", len );
			//LLOG_ERROR << "bad sql length " << len;
			return false;
		}

		uint32 result = mysql_real_query(m_mysql, query, len);
		if (0 != result)
		{
			ERROR_EX_LOG("mysql_real_query error, code = %u\n", result);
			//printf("mysql_real_query error, code = %u\n", result);
			//LLOG_ERROR << "mysql_real_query error, code = " << result;
		}
		return (0 == result);
	}
	void cdb_mysql::_sql_error_prompt(const char * query, uint32 len)
	{
		
		uint32 can_print_len = 0;
		for (uint32 i = 0; i < len; ++i)
		{
			if (isprint((unsigned char)(query[i])))
			{
				++can_print_len;
			}
			else
			{
				break;
			}
		}
		//FIX_LOG(ELogLevel_Warn, query, can_print_len);
	}
	void cdb_mysql::_out_info(const char * query, unsigned int len)
	{
		EOutInfoType type = m_prepare_disconnect ? EOIType_SqlNoExe : EOIType_SqlError;
		m_out_info.log_error_sql(type, query, len);
	}
	void cdb_mysql::_mysql_error()
	{
	}
} // namespace chen
