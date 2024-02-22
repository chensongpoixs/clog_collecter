/********************************************************************
created:	2019-05-07

author:		chensong

level:		ÍøÂç²ã

purpose:	ÍøÂçÊý¾ÝµÄÊÕ·¢


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
#include "cwan_session.h"
#include "cguard_reply.h"
#include "cutil.h"
#include "crobot_msg_header.h"
#include "cglobal_db.h"
#include "cdb_query_result.h"
namespace chen {


	void	cwan_session::handler_client_login(const void* ptr, uint32 msg_size)
	{
		PRASE_CLIENT_MSG(ptr, C2S_Login, msg_size);
		CGUARD_REPLY(S2C_Login, m_session_id);
		m_async_write_file.init(m_remote_ip.c_str(), msg.client_type());
		//////////////////////////
		//// 查询数据中数据
		enum EField
		{
			EF_log_level = 0,
		};

		 g_sql_mgr.reset();
		 g_sql_mgr << "SELECT    `log_level`  FROM `t_user_log_collector_info`  WHERE `address` = '" << m_remote_ip << "' and `client_type` = " << msg.client_type() << " ";
		
		 cdb_query_result query_result;


		if (!g_global_log_db.send_query(query_result, g_sql_mgr))
		{
			WARNING_EX_LOG("g_global_log_db.send_query error !!!   [msg.client_type()  = %u][address = %s]", msg.client_type() , m_remote_ip.c_str());
			//err.assign("sql query error");
			//;reply.set_result(EEC_DongleAuthDb);
			return;
		}

		if (!query_result.next_row())
		{
			WARNING_EX_LOG("not find  [msg.client_type()  = %u][address = %s]", msg.client_type(), m_remote_ip.c_str());

			{
				//insert into tableName (colunm1,colunm2,...) value(value1,value2,...);
				// insert sql 
				g_sql_mgr.reset();
				g_sql_mgr << "INSERT  INTO t_user_log_collector_info(`client_type`, `address` ) value(" << msg.client_type() << ", '" << m_remote_ip << "') ";
				//g_sql_mgr.back(1);
				//LLOG_SYSTEM << "sql = " << g_sql_mgr.get_buf();
				g_global_log_db.excute(g_sql_mgr, ESqlError_CanIgnore);
				g_sql_mgr.reset();
			}
			//err.assign("order not found");
			//reply.set_result(EEC_DongleAuthNotAppid);
			return;
		}

		const uint32 log_level = query_result.get_uint32(EF_log_level);
		reply.set_log_level(log_level);
		//const char* default_project_id = query_result.get_col_value(EF_default_project_id);
		//if (default_project_id != msg.projectid())
		//{
		//	WARNING_EX_LOG("[appid = %s][client project_id = %s ==> db default_project_id = %s] !!!", msg.appid().c_str(), msg.projectid().c_str(), default_project_id);
		//	reply.set_result(EEC_DongLeAuthLoadDefaultProject);
		//	return;
		//}


		
	}
	void    cwan_session::handler_client_log_data_update(const void* ptr, uint32 msg_size)
	{
		PRASE_CLIENT_MSG(ptr, C2S_LogDataUpdate, msg_size);
		m_async_write_file.push(msg);
	}

	void	cwan_session::handler_client_core_dump_file(const void* ptr, uint32 msg_size)
	{
		if (true)
		{
			PRASE_CLIENT_MSG(ptr, C2S_CoreFileUpdate, msg_size);
			{
				
				//NORMAL_EX_LOG("[%s]", cutil::get_hex_str(msg.core_dump().c_str(), 1024).c_str());
				FILE* out_file_ptr = fopen(msg.core_name().c_str(), "wb+");
				if (!out_file_ptr)
				{
					WARNING_EX_LOG("core file not open  [%s] failed !!! ", msg.core_name().c_str());
					return;
				}




				size_t write_size = ::fwrite(msg.core_dump().c_str(), 1, msg.core_dump().size(), out_file_ptr);
				::fflush(out_file_ptr);
				::fclose(out_file_ptr);
				out_file_ptr = NULL;
				NORMAL_EX_LOG("core file   open  [write_size = %u][%s] write core  OK !!! ", write_size, msg.core_name().c_str());
			}
		}
		else
		{
			//PRASE_CLIENT_MSG(ptr, C2S_CoreFileUpdate, msg_size);
			{
				NORMAL_EX_LOG("--[%s]", cutil::get_hex_str(static_cast<const void  *>((char *)(ptr) + (msg_size - 80)), 80).c_str());
				//NORMAL_EX_LOG("[%s]", cutil::get_hex_str(msg.core_dump().c_str(), 1024).c_str());
				FILE* out_file_ptr = fopen("chensong.zip", "wb+");
				if (!out_file_ptr)
				{
					WARNING_EX_LOG("core file not open  failed !!! ",  );
					return;
				}
				size_t write_size_l = 0;
				while (write_size_l < msg_size)
				{
					size_t write_size = ::fwrite((const void *)((char *)ptr + write_size_l), 1, 4096, out_file_ptr);
					if (write_size <= 0)
					{
						break;
					}
					
					::fflush(out_file_ptr);
					write_size_l += write_size;
				}
				
				::fclose(out_file_ptr);
				out_file_ptr = NULL;
				NORMAL_EX_LOG("core file   open  [write_size = %u] write core  OK !!! ", write_size_l);
			}
		}
		//m_async_write_file.push(msg);
	}


	void    cwan_session::handler_client_heatbeat(const void* ptr, uint32 msg_size)
	{
		m_heart_beart = ::time(NULL);
	}
}