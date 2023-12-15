/********************************************************************
created:	2019-08-12

author:		chensong

purpose:	cdb_cfg
*********************************************************************/


#ifndef _C_DB_CFG_H_
#define _C_DB_CFG_H_
#include "cnet_type.h"
#include <string>
namespace chen {
	struct cdb_cfg
	{
		cdb_cfg(void);
		cdb_cfg(const std::string& host, const std::string& user, const std::string& db_name, const std::string& passwd
			, uint32 port, int32 time_zone, int32 auto_commit);

		std::string m_host;
		std::string m_user;
		std::string m_db_name;
		std::string m_passwd;
		uint32		m_port;
		int32		m_time_zone;// [-11,+12]
		int32		m_auto_commit;
	};

	enum ESqlErrorType
	{
		ESqlError_CanIgnore, 
		ESqlError_ShutDown,
	};
}// namespace chen

#endif // !#define _C_DB_CFG_H_
