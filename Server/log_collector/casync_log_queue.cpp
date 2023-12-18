/***********************************************************************************************
created: 		2022-02-27

author:			chensong

purpose:		�����
************************************************************************************************/
#include "casync_log_queue.h"
#include "clog_collector.h"
#include "clog_color.h"
#include "cclient_session.h"
#include "ctime_api.h"
#include "ctime_const.h"
#include "Log.pb.h"
#include <sstream>
#include "cclient_msg/MsgID.pb.h"
namespace chen {


	static const unsigned int LOG_ITEM_SIZE = sizeof(clog_collector_item);
	static const unsigned int LOG_BUF_MAX_SIZE = 1024 * 1024;


	struct clog_collector_name_color
	{
		const char* name;
		ELogColorType color;
	}

	static const g_log_collector_name_colors[] =
	{
		{ "",		ELCT_White },
		{ "system", ELCT_Blue },
		{ "fatal",  ELCT_Red },
		{ "error",  ELCT_Pink },
		{ "warn",	ELCT_Yellow },
		{ "info",	ELCT_White },
		{ "debug",	ELCT_Green },
	};

	bool casync_log_queue::init(bool show_screen)
	{
		m_color_ptr = new clog_color();
		m_show_screen = show_screen;

		m_log_buf = new char[LOG_BUF_MAX_SIZE];
		return true;
	}

	void casync_log_queue::update(uint32 uDataTime)
	{
		clog_collector_item* item_ptr = NULL;
		if (!s_agent_client_session.is_used())
		{
			// TODO@chensong 20231218 判断队列中数据缓存大小

			while (m_log_item.size() > 3000)
			{
				{
					clock_guard lock(m_log_lock);
					item_ptr = m_log_item.front();
					m_log_item.pop_front();
				}
				if (item_ptr)
				{ 
					delete item_ptr;
					item_ptr = NULL;
				}
			}


			return;
		}
		
		while (!m_log_item.empty())
		{
			{
				clock_guard lock(m_log_lock);
				item_ptr = m_log_item.front();
				m_log_item.pop_front();
			}
			_handler_log_item(item_ptr);
			if (item_ptr)
			{
				delete item_ptr;
			}
			item_ptr = NULL;
		}
	}

	void casync_log_queue::destroy()
	{
		if (m_color_ptr)
		{
			delete m_color_ptr;
			m_color_ptr = NULL;
		}
		
		clock_guard lock(m_log_lock);
		while (!m_log_item.empty())
		{
			delete m_log_item.front();
			m_log_item.pop_front();
		}
		if (m_log_buf)
		{
			delete m_log_buf;
			m_log_buf = NULL;
		}
	}

	void casync_log_queue::append_fix(ELogCollectorLevelType level, const void* str, unsigned int len)
	{
		if (level < ELogCollectorLevel_None || level > ELogCollectorLevel_Num || m_level_log < level)
		{
		 	return;
		}
		 
		//static const unsigned int max_size = 1024;
		//m_lock.lock();
		//char * buf = new char[LOG_BUF_MAX_SIZE];
		//memset(m_log_buf, 0x00, LOG_BUF_MAX_SIZE);
		//uint32 cnt = vsnprintf(m_log_buf, LOG_BUF_MAX_SIZE, format, ap);

		if (len < 0 || !m_log_buf)
		{
			//delete[] buf;
			return;
		}

		clock_guard lock(m_log_lock);
		
		clog_collector_item* log_item_ptr = _get_new_buf();
		if (!log_item_ptr)
		{
			//delete[] buf;
			return;
		}
		log_item_ptr->buffer = new char[len];
		if (!log_item_ptr->buffer)
		{
			delete log_item_ptr;
			return;
		}

		log_item_ptr->size = len;
		log_item_ptr->level = level;
		log_item_ptr->timestamp = static_cast<int>(ctime_base_api::get_gmt());

		memcpy(log_item_ptr->buffer, str, len);

		m_log_item.push_back(log_item_ptr);
		 
	}

	void casync_log_queue::append_var(ELogCollectorLevelType level, const char* format, va_list ap)
	{
		if (level < ELogCollectorLevel_None || level > ELogCollectorLevel_Num || m_level_log < level)
		{ 
		 	return;
		}
		if (!m_log_buf)
		{
			return;
		 }
		//static const unsigned int max_size = 1024;
		
		clock_guard lock(m_log_lock);
		//char * buf = new char[LOG_BUF_MAX_SIZE];
		memset(m_log_buf, 0x00, LOG_BUF_MAX_SIZE);
		int32 cnt = vsnprintf(m_log_buf, LOG_BUF_MAX_SIZE, format, ap);

		if (cnt < 0)
		{ 
			return;
		}

		//�õ�һ���µ�log
		clog_collector_item* log_item_ptr = _get_new_buf();
		if (!log_item_ptr)
		{ 
			return;
		}
		log_item_ptr->buffer = new char[cnt];
		if (!log_item_ptr->buffer)
		{
			delete log_item_ptr;
			 
			return;
		}

		log_item_ptr->size = cnt;
		log_item_ptr->level = level;
		log_item_ptr->timestamp = static_cast<int>(ctime_base_api::get_gmt());

		memcpy(log_item_ptr->buffer, m_log_buf, cnt);

		m_log_item.push_back(log_item_ptr);
	}

	void casync_log_queue::set_level(ELogCollectorLevelType level)
	{
		if (level < ELogCollectorLevel_None || level > ELogCollectorLevel_Num)
		{
			return;
		}
		m_level_log = level;
	}

	void casync_log_queue::_handler_log_item(const clog_collector_item* log_item_ptr)
	{
		if (!log_item_ptr)
		{
			return;
		}
		if (m_show_screen && m_color_ptr)
		{
			m_color_ptr->set_color(g_log_collector_name_colors[log_item_ptr->level].color);
		}
		MC2S_LogDataUpdate log_data;
		std::stringstream   log_stream;
		//log_data.set_log_data("chensong\n");
		//send_msg(C2S_LogDataUpdate, log_data);
		if (!(log_item_ptr->level == ELogCollectorLevel_Info || log_item_ptr->level == ELogCollectorLevel_System))
		{

			char dateTime[ASCII_DATETIME_LEN] = { 0 };
			ctime_base_api::time64_datetime_format(log_item_ptr->timestamp, dateTime, '-', ' ', ':');

			//log_stream 
			//if (m_fd.is_open())
			//{
			log_stream << '[' << dateTime << "][" << g_log_collector_name_colors[log_item_ptr->level].name << "]";
			//}
			if (m_show_screen)
			{
				std::cout << '[' << dateTime << "][" << g_log_collector_name_colors[log_item_ptr->level].name << "]";

			}
		}

		 
		log_stream.write(log_item_ptr->buffer, log_item_ptr->size);
		log_stream.write("\n", 1);
		log_data.set_log_data(log_stream.str());
		if (s_agent_client_session.is_used())
		{
			s_agent_client_session.send_msg(C2S_LogDataUpdate, log_data);
		}
		if (m_show_screen)
		{
			std::cout.write(log_item_ptr->buffer, log_item_ptr->size);
			std::cout.write("\n", 1);
			std::cout.flush();
		}
	}

	clog_collector_item* casync_log_queue::_get_new_buf()
	{
		clog_collector_item* log_item_ptr = new clog_collector_item();
		if (!log_item_ptr)
		{
			return NULL;
		}
		return log_item_ptr;
	}

}


