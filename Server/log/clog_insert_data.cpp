/***********************************************************************************************
created: 		2019-05-06

author:			chensong

purpose:		clog_insert_data
************************************************************************************************/
#include "clog_insert_data.h"
 
#include "cglobal_log_data_mgr.h"
 
namespace chen {
	template<>
	void clog_insert_data<clog_collector>::make_begin_sql(csql_mgr & sql) const
	{
		sql << "INSERT INTO  `t_log_collector_info`(  `client_type`, `address`, `timestamp`, `log_file_name`)  VALUES";
	}
	 
	///

	template<>
	void clog_insert_data<clog_collector>::make_insert_sql(csql_mgr & sql) const
	{
		 
		sql << "( " << m_msg.client_type  << ", '" << m_msg.address  << "', " << m_msg.timestamp << 
			", '" << m_msg.log_file_name << "' )" ;
	}
	
} // namespace chen
