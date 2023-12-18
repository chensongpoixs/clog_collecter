
/***********************************************************************************************
created: 		2019-05-10
author:			chensong
purpose:		robot
************************************************************************************************/

#ifndef _C_LOG_COLLECTOR_SERVER_H_
#define _C_LOG_COLLECTOR_SERVER_H_

#include "cnoncopytable.h"
#include <thread>
#include "clog_collector.h"
#include <vector>
#include <mutex>
#include "casync_log_queue.h"
#include "csingleton.h"
namespace chen {
	class clog_collector_server : private cnoncopytable
	{
	public:
		explicit clog_collector_server();
		~clog_collector_server();
	public:
		bool init(const char* ip, uint16_t port, bool show_screen = false);
		void Loop();
		void destroy();
		static void stop();
 
 
	public:


		void append_fix(ELogCollectorLevelType level, const void* str, unsigned int len);
		void append_var(ELogCollectorLevelType level, const char* format, va_list ap);

		void set_level(ELogCollectorLevelType level);
		ELogCollectorLevelType get_level() const;
	public:
	//	void result_dongle_auth(int32_t result, const char *  data);

	//	void send_rte_info();
	public:
		//void  register_result(set_rte_info_result_callback callback);
		//void  register_send_rte_info(set_rte_info_callback callback);
	private:
		 
		static volatile bool								m_stoped; 
		casync_log_queue									m_async_log_queue;
	};
	 #define s_log_collector_server   chen::csingleton<chen::clog_collector_server>::get_instance()
	//extern clog_collector_server g_log_collector_server;
} //namespace chen 

#endif // !#define _C_LOG_COLLECTOR_SERVER_H_