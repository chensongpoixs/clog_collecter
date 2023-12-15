/********************************************************************
created:	2019-08-13

author:		chensong

purpose:	cdb_version


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


#define _CRT_SECURE_NO_WARNINGS
#include "cdb_version.h"
#include <algorithm>
#include <sstream>
 #include "clog.h"
#include "cdb_query_result.h"
 
namespace chen {
	cdb_version::cdb_version()
		: m_inited(false)
	{
	}
	cdb_version::~cdb_version()
	{
		destroy();
	}
	bool cdb_version::init()
	{
		if (m_inited) 
		{
			return true;
		}

		{
			cversions& auth = m_versions[EDT_Log];
			auth.push_back(1); 
		} 
		m_inited = true;
		return true;
	}
	void cdb_version::destroy()
	{
	}
	bool cdb_version::check_db_version(cdb_mysql & db, EDb_type type, bool auto_update, const std::string & update_path)
	{
		if (!valid_type(type))
		{
			return false;
		}

		// ²éÑ¯µ±Ç°Êý¾Ý¿â°æ±¾ºÅ
		int32 version = get_db_version(db);

		if (version <= 0)
		{
			return false;
		}

		const cversions& versions = m_versions[type];

		int latest_version = get_latest_db_version(versions);
		NORMAL_EX_LOG("version = %d, latest_version = %d", version, latest_version);
		//LLOG_ERROR << "version = " << version << ", latest_version = " << latest_version;
		if (version == latest_version)
		{
			return true;
		}

		if (!auto_update || update_path.empty())
		{
			ERROR_EX_LOG("%s version = %d need update to version = %d", db.get_db_name().c_str(), version, latest_version);
			//LLOG_ERROR << db.get_db_name().c_str() << " version = " << version << ", need update to version = " << latest_version;
			return false;
		}

		cversions::const_iterator it = std::find(versions.begin(), versions.end(), version);
		if (it == versions.end())
		{
			ERROR_EX_LOG("%s version = %d invalid, need update to version = %d", db.get_db_name().c_str(), version, latest_version);
			//LLOG_ERROR << db.get_db_name().c_str() << " version = " << version << "invalid , need update to version = " << latest_version;
			return false;
		}
		++it;
		if (it == versions.end())
		{
			ERROR_EX_LOG("%s version = %d invalid, need update to version = %d", db.get_db_name().c_str(), version, latest_version);
			//LLOG_ERROR << db.get_db_name().c_str() << " version = " << version << "invalid , need update to version = " << latest_version;
			return false;
		}

		std::string base_path(update_path);
		base_path.append("sql/update/");
		if (type == EDT_Log)
		{
			base_path.append("log");
		}
		else
		{
			ERROR_EX_LOG("unknow db type = %d", type);
			//LLOG_ERROR << "unknow db type =" << type;
			return false;
		}
		base_path.append(1, '/');

		SYSTEM_LOG("auto update begin, %s version = %d ==> %d", db.get_db_name().c_str(), version, latest_version);
		//LLOG_SYSTEM << "auto update begin, " << db.get_db_name().c_str() << " version =" << version << "===> " << latest_version;
		std::stringstream ss;
		uint32 last_version = version;
		for (; it != versions.end(); ++it)
		{
			ss.clear();
			ss.str("");
			ss << base_path << *it << ".sql";

			SYSTEM_LOG("%s version = %d, target version = %d, execute sql_file = %s", db.get_db_name().c_str(), last_version, *it, ss.str().c_str());
			//LLOG_SYSTEM << db.get_db_name().c_str() << " version =" << last_version << ", target version = " << *it << ", execute sql_file =  " << ss.str().c_str();
			if (!execute_sql_file(db, ss.str()))
			{
				return false;
			}
			last_version = *it;
		}

		version = get_db_version(db);
		if (version != latest_version)
		{
			return false;
		}

		return true;
	}
	int32 cdb_version::get_db_version(cdb_mysql & db)
	{
		std::stringstream sql;
		sql << "SELECT `version` FROM `t_version`;";

		cdb_query_result result;

		if (!db.send_query(result, sql.str()))
		{
			ERROR_EX_LOG("%s query sql error, sql = %s", db.get_db_name().c_str(), sql.str().c_str());
			//LLOG_ERROR << db.get_db_name().c_str() << " query sql error, sql = " << sql.str().c_str();
			return -1;
		}

		result.next_row();

		if (0 == result.get_row_count())
		{
			ERROR_EX_LOG("%s has no version data", db.get_db_name().c_str());
			//LLOG_ERROR << db.get_db_name().c_str() << " has no version data";
			return -1;
		}

		int32 version = result.get_int32(0);

		if (version <= 0)
		{
			ERROR_EX_LOG("%s version = %d invalid", db.get_db_name().c_str(), version);
			//LLOG_ERROR << db.get_db_name().c_str() << " version = " << version << " invalid";
			return -1;
		}

		return version;
	}
	bool cdb_version::valid_type(EDb_type type)
	{
		if (type < 0 || type >= EDT_MAX)
		{
			ERROR_EX_LOG("invalid type %d", type);
			//LLOG_ERROR << "invalid type " << type;
			return false;
		}
		return true;
	}
	int32 cdb_version::get_latest_db_version(const cversions & versions)
	{
		if (versions.empty())
		{
			return 0;
		}

		return versions[versions.size() - 1];
	}
	bool cdb_version::execute_sql_file(cdb_mysql & db, const std::string & sql_file)
	{
		FILE* file_ptr = ::fopen(sql_file.c_str(), "rb");

		if (NULL == file_ptr)
		{
			ERROR_EX_LOG("sql_file = %s open error", sql_file.c_str());
			//LLOG_ERROR << "sql_file = " << sql_file.c_str() << " open error";
			return false;
		}

		long cur = ftell(file_ptr);
		fseek(file_ptr, 0, SEEK_END);

		long end = ftell(file_ptr);
		fseek(file_ptr, cur, SEEK_SET);

		char* data_ptr = new char[end + 1];

		if (!data_ptr)
		{
			ERROR_EX_LOG("alloc memory error");
			//LLOG_ERROR << "alloc memory error";
			fclose(file_ptr);
			return false;
		}

		// ¼ÓÈë»»ÐÐ·û
		fread(data_ptr, 1, end, file_ptr);
		data_ptr[end] = 0x0a;
		long i = 0;

		// utf8
		if (end >= 3 && static_cast<unsigned char>(data_ptr[0]) == 0xEF &&
			static_cast<unsigned char>(data_ptr[1]) == 0xBB &&
			static_cast<unsigned char>(data_ptr[2]) == 0xBF)
		{
			i += 3;      // Skip utf-8 bom
		}

		long index = i;

		for (; i <= end; ++i)
		{
			if (data_ptr[i] == ';')
			{
				if (i > index)
				{
					if (!db.excute(data_ptr + index, i - index))
					{
						fclose(file_ptr);
						delete[] data_ptr;
						return false;
					}
				}

				index = i + 1;
			}
		}

		fclose(file_ptr);
		delete[]data_ptr;

		return true;
	}
} // namespace chen
