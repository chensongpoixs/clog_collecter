/***********************************************************************************************
created: 		2019-05-06

author:			chensong

purpose:		clog_insert_base
************************************************************************************************/


#ifndef _C_LOG_INSERT_BASE_H_
#define _C_LOG_INSERT_BASE_H_
#include "cnet_type.h"
namespace chen {
	class csql_mgr;
	class clog_insert_base
	{
	public:
		virtual ~clog_insert_base() {}
		virtual void make_begin_sql(csql_mgr& sql) const = 0;
		virtual void make_insert_sql(csql_mgr& sql) const = 0;
		virtual void destroy() = 0;
	};
}// namespace

#endif // !#define _C_LOG_INSERT_BASE_H_