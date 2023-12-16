/***********************************************************************************************
created: 		2019-05-06

author:			chensong

purpose:		cglobal_log_data_mgr
************************************************************************************************/

#ifndef _C_GLOBAL_LOG_DATA_MGR_H_
#define _C_GLOBAL_LOG_DATA_MGR_H_

#include "cnet_type.h"
#include <mutex>
#include <string>
#include <list>
namespace chen {



	struct clog_collector
	{
		uint32 client_type;
		std::string address;
		uint64      timestamp;
		std::string log_file_name;

		clog_collector()
			: client_type(0)
			, address("")
			, timestamp(0)
			, log_file_name("") {}
	};

	class cglobal_log_data_mgr
	{
	private:
		typedef		std::mutex						clock_type;
		typedef		std::lock_guard<clock_type>		clock_guard;
	public:
		explicit cglobal_log_data_mgr() {}
		virtual ~cglobal_log_data_mgr(){}
	public:

		bool init();
		void update(uint32 uDateTime);
		void destroy();



	public:

		void push(const clog_collector& log_conllector);


	public:


		void save();
	private:
		clock_type						m_lock;
		std::list<clog_collector>		m_log_conllectors;
	};

	extern cglobal_log_data_mgr g_global_log_data_mgr;
}


#endif // _C_GLOBAL_LOG_DATA_MGR_H_