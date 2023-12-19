/***********************************************************************************************
			created: 		2019-05-13
			author:			chensong
			purpose:		msg_dipatch
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
************************************************************************************************/
#include "casync_write_file.h"
#include "ccfg.h"
#include "ctime_mgr.h"
#include "ctime_api.h"
#include <boost/filesystem.hpp>
#include "cglobal_log_data_mgr.h"
namespace chen {




	casync_write_file::~casync_write_file()
	{
	}

	bool casync_write_file::init(const char* remote_ip, int32 client_type)
	{
		m_remote_ip = remote_ip;
		m_client_type = client_type;
		m_log_path = g_cfg.get_string(ECI_LogCollectorPath);
		m_cur_log_file_rows = 0;
		m_log_file_rows = g_cfg.get_uint32(ECI_LogCollectorRows);
		m_stoped = false;
		m_thread = std::thread(&casync_write_file::_work_pthread, this);
		return true;
	}

	void casync_write_file::update(uint32 uDeltaTime)
	{
	}

	void casync_write_file::destroy()
	{
		m_stoped = true;
		m_condition.notify_all();
		if (m_thread.joinable())
		{
			m_thread.join();
		}
		m_client_type = 0;
		m_log_lists.clear();
		m_remote_ip.clear();
		if (m_log_file_ptr)
		{
			::fflush(m_log_file_ptr);
			::fclose(m_log_file_ptr);
			m_log_file_ptr = NULL;
		}
		m_cur_log_file_rows = 0;
	}

	void casync_write_file::push(const MC2S_LogDataUpdate& msg)
	{
		clock_guard lock(m_log_lists_lock);
		m_log_lists.push_back(msg);
		{
			m_condition.notify_one();
		}
	}

	void casync_write_file::_work_pthread()
	{
		m_cur_log_file_rows = 0;
		 MC2S_LogDataUpdate log_data;
		while (!m_stoped || !m_log_lists.empty())
		{
			{
				std::unique_lock<std::mutex> lock(m_log_lists_lock);
				m_condition.wait(lock, [this]() {return m_log_lists.size() > 0 || m_stoped; });
			} 
			while (!m_log_lists.empty())
			{
				{
					clock_guard lock{ m_log_lists_lock };
					log_data = m_log_lists.front();
					m_log_lists.pop_front();
				}
				_handler_check_log_file();
				_handler_write_log(log_data); 
			}
			if (m_log_file_ptr)
			{
				::fflush(m_log_file_ptr);;
			}
		}
	}

	void casync_write_file::_handler_check_log_file()
	{
		uint32 day_time = ctime_base_api::get_today_stamp_time64(0);
		if (!m_log_file_ptr || m_cur_log_file_rows > m_log_file_rows || day_time > m_day_time)
		{
			m_day_time = day_time;
			m_cur_log_file_rows = 0;
			// create log name [20231216]/[ip client_type timestamp]
			char buff[ASCII_DATETIME_LEN] = {0};
			chen::ctime_base_api::time64_datetime_format(::time(NULL), buff, 0, 0, -1);
			std::string log_name_path = m_log_path +"/" + buff + "/" + m_remote_ip + "/";


			//检查目录是否存在, 不存在则创建
			boost::filesystem::path log_path(log_name_path);
			if (!boost::filesystem::exists(log_path))
			{
				boost::system::error_code ec;
				boost::filesystem::create_directories(log_path, ec);
			}
			//[生成文件加上毫秒数]
			char buffer[ASCII_DATETIME_LEN] = { 0 };
			chen::ctime_base_api::time64_datetime_format(::time(NULL), buffer, 0, 0, 0);
			std::string log_name =   std::to_string(m_client_type) + "_" + buffer + std::to_string(ctime_base_api::get_time_ms())+ ".log";
			
			
			log_name_path += log_name;

			if (m_log_file_ptr)
			{
				::fflush(m_log_file_ptr);
				::fclose(m_log_file_ptr);
				m_log_file_ptr = NULL;
			}

			m_log_file_ptr = ::fopen(log_name_path.c_str(), "wb+");
			if (!m_log_file_ptr)
			{
				WARNING_EX_LOG("not create file(%s) failed !!!", log_name_path.c_str());
				return;
			}
			clog_collector collector;
			collector.address = m_remote_ip;
			collector.client_type = m_client_type;
			collector.timestamp = ::time(NULL);
			collector.log_file_name = std::string(buff) + "/" + m_remote_ip  + "/" + log_name;
			g_global_log_data_mgr.push(collector);
		}

		 
	}

	void casync_write_file::_handler_write_log(const MC2S_LogDataUpdate& msg)
	{
		if (!m_log_file_ptr)
		{
			WARNING_EX_LOG("log file ptr == null !!! [remote_ip = %s][client_type = %u]", m_remote_ip.c_str(), m_client_type);
			return;
		}
		::fwrite(msg.log_data().c_str(), msg.log_data().length(), 1, m_log_file_ptr);
		//::fflush(m_log_file_ptr);


	}

}