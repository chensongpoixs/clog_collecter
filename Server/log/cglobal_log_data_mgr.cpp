/***********************************************************************************************
created: 		2019-05-06

author:			chensong

purpose:		cglobal_log_data_mgr
************************************************************************************************/

#include "cglobal_log_data_mgr.h"
#include "clog_insert_mgr.h"

namespace chen {


	cglobal_log_data_mgr g_global_log_data_mgr;

	bool cglobal_log_data_mgr::init()
	{
		return all_log_mgr_init();
	}

	void cglobal_log_data_mgr::update(uint32 uDateTime)
	{
		if (m_log_conllectors.empty())
		{
			return;
		}
		save();
		all_log_mgr_update(uDateTime);
	}

	void cglobal_log_data_mgr::destroy()
	{
		save();
		  all_log_mgr_shutdown_save();
		  all_log_mgr_show_info();
		  all_log_mgr_destroy();
	}

	void cglobal_log_data_mgr::push(const clog_collector& log_collector)
	{
		clock_guard lock(m_lock);
		m_log_conllectors.push_back(log_collector);
	}

	void cglobal_log_data_mgr::save()
	{ 
		while (!m_log_conllectors.empty())
		{
			{
				clock_guard lock(m_lock);
				if (m_log_conllectors.empty())
				{
					break;
				} 
				g_log_conllector_info_mgr.add(m_log_conllectors.front());
				m_log_conllectors.pop_front();
			} 
		}
	}

}