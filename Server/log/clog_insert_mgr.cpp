/***********************************************************************************************
created: 		2019-05-06

author:			chensong

purpose:		clog_insert_mgr
************************************************************************************************/

#include "clog_insert_mgr.h"
//#include "clog.h"
#include "cglobal_db.h"
#include "cmysql/cdb_cfg.h" 
#include "cnet_type.h"
//#include "common/cmem_pool.h" 
#include "ccfg.h"
#include "cglobal_log_data_mgr.h"
 
namespace chen {
	//cmem_pool	g_log_pool(false);
	clog_insert_mgr::clog_insert_mgr(int32 tick_save_num , int32 save_interval )
		: m_tick_save_num(tick_save_num)
		, m_save_interval(save_interval)
		, m_tick_time(0)
	{
	}

	clog_insert_mgr::~clog_insert_mgr()
	{
	}

	bool clog_insert_mgr::init()
	{
		return true;
	}

	void clog_insert_mgr::update(uint32 elapse)
	{
		if (!m_save_list.empty())
		{
			m_tick_time += elapse;
			if (m_tick_time >= m_save_interval)
			{
				m_tick_time = 0;
				_tick_save(false);
			}
		}
	}

	void clog_insert_mgr::shutdown_save()
	{
		if (!m_save_list.empty())
		{
			_tick_save(true);
		}
	}

	void clog_insert_mgr::_tick_save(bool flag_shut)
	{
		csave_list::iterator it = m_save_list.begin();
		g_sql_mgr.reset();
		for (int32 count = 0; it != m_save_list.end(); ++it, ++count)
		{
			clog_insert_base* save_item_ptr = *it;

			if (g_sql_mgr.get_size() == 0)
			{
				save_item_ptr->make_begin_sql(g_sql_mgr);
			}
			save_item_ptr->make_insert_sql(g_sql_mgr);
			g_sql_mgr << ',';

			save_item_ptr->destroy();
			::free(save_item_ptr);
			//g_log_pool.free(save_item_ptr);
			if (count >= m_tick_save_num)
			{
				g_sql_mgr.back(1);
				//LLOG_SYSTEM << "sql = " << g_sql_mgr.get_buf();
				g_global_log_db.excute(g_sql_mgr, ESqlError_CanIgnore);
				g_sql_mgr.reset();

				if (!flag_shut)
				{
					++it;
					break;
				}
				count = 0;
			}
		}
		if (g_sql_mgr.get_size() > 0)
		{
			g_sql_mgr.back(1);
			//LLOG_SYSTEM << "sql = " << g_sql_mgr.get_buf();
			g_global_log_db.excute(g_sql_mgr, ESqlError_CanIgnore);
		}
		
		m_save_list.erase(m_save_list.begin(), it);
	}
	
	static bool check_sql_buf(uint32 sql_len, uint32 num)
	{
		
		//g_sql_mgr.reset();
		g_sql_mgr.skip(sql_len * num);
		if (g_sql_mgr.has_error())
		{
			
			return false;
		}
		return true;
	}

	clog_insert_mgr g_log_conllector_info_mgr(500, 0);
 
	bool all_log_mgr_init()
	{
		


		{
			 
			 

			clog_collector collector;
			collector.client_type =0x0FFFFFFF;
			collector.timestamp = 0x0FFFFFFF;
			collector.address = "333.333.333.333";
			collector.log_file_name = "23432432432432/23/4324/32/4/32/32/4/32/432/lsdflkdj.log";
			g_sql_mgr.reset();
			clog_insert_data<clog_collector> insert_data(collector);
			insert_data.make_begin_sql(g_sql_mgr);
			insert_data.make_insert_sql(g_sql_mgr);
			if (!check_sql_buf(g_sql_mgr.get_size(), 500))
			{
				ERROR_EX_LOG( "[collector write too length!!]");
				return false;
			}
		}

		
		
	//	g_log_pool.set_max_block(g_cfg.get_uint32(ECI_LogPoolSize));
		return true;
	}

	void all_log_mgr_update(uint32 elapse)
	{
		g_log_conllector_info_mgr.update(elapse);
		
		

	}

	void all_log_mgr_shutdown_save()
	{
		g_log_conllector_info_mgr.shutdown_save();
		
		all_log_mgr_destroy();
	}

	void all_log_mgr_show_info()
	{
		
	}

	void all_log_mgr_destroy()
	{
		//g_log_pool.gc();
		//g_log_pool.show_info();
		//g_log_pool.destroy();
	}

	
}// namespace chen

