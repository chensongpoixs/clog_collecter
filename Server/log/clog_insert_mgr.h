/***********************************************************************************************
created: 		2019-05-06

author:			chensong

purpose:		clog_insert_mgr
************************************************************************************************/


#ifndef _C_LOG_INSERT_MGR_H_
#define _C_LOG_INSERT_MGR_H_
#include "clog_insert_data.h"
#include "clog_insert_base.h"
#include <list>
#include "cnet_type.h" 
#include <memory>
namespace chen {
	//extern cmem_pool g_log_pool;
	class clog_insert_mgr 
	{
	private:
		typedef std::list<clog_insert_base*>			csave_list;
	public:
		clog_insert_mgr(int32 tick_save_num = 100, int32 save_interval = 1000);
		~clog_insert_mgr();
	public:
		bool init();
		void update(uint32 elapse);
		void shutdown_save();

		template<typename _Ty>
		void	add(const _Ty&data)
		{
			void *p = ::malloc(sizeof(clog_insert_data<_Ty>));
			if (!p)
			{
				return;
			}
			clog_insert_data<_Ty>* q = new(p) clog_insert_data<_Ty>(data);
			m_save_list.push_back(q);
		}
		uint32 get_size() const { return static_cast<uint32>(m_save_list.size()); }
		int32	get_tick_save_num() const { return m_tick_save_num; }
	private:
		void _tick_save(bool flag_shut);
	private:
		csave_list		m_save_list;
		int32			m_tick_save_num;
		int32			m_save_interval;
		int32			m_tick_time;
	};

	bool all_log_mgr_init();
	void all_log_mgr_update(uint32 elapse);
	void all_log_mgr_shutdown_save();
	void all_log_mgr_show_info();
	void all_log_mgr_destroy();

	extern clog_insert_mgr g_log_conllector_info_mgr;
	

}// !namespace chen

#endif // !#define _C_LOG_INSERT_MGR_H_
