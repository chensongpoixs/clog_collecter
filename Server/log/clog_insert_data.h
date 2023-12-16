/***********************************************************************************************
created: 		2019-05-06

author:			chensong

purpose:		clog_insert_data
************************************************************************************************/


#ifndef _C_LOG_INSERT_DATA_H_
#define _C_LOG_INSERT_DATA_H_
#include "cmysql/csql_mgr.h"
#include "clog_insert_base.h"
 
namespace chen {
	
	class csql_mgr;
	template<typename _Ty>
	class clog_insert_data : public clog_insert_base
	{
	public:
		clog_insert_data() {}
		clog_insert_data(const _Ty &data) :m_msg(data) {}
		virtual ~clog_insert_data() {}

	public:
		
		virtual void make_begin_sql(csql_mgr& sql) const;
		virtual void make_insert_sql(csql_mgr& sql) const ;
		virtual void destroy() { this->~clog_insert_data(); }
	private:
		_Ty		m_msg;
	};
	
}// namespace chen

#endif // !#define _C_LOG_INSERT_BASE_H_