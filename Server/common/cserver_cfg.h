#ifndef _C_SERVER_CONFIG_H_
#define _C_SERVER_CONFIG_H_

#include "cconfig.h"
//#include "cdb_cfg.h"

namespace chen {

	enum EServerConfigIndex
	{
		ECI_WanIp,								// ����ip
		ECI_WanPort,							// �����˿�
		   
		//common
		ECI_ResPath,
		ECI_TimeZone,
		ECI_TimeAdjust,
		ECI_HeartBeat, 
		ECI_LogLevel,
		  
		//db config log
		ECI_LogDbHost,
		ECI_LogDbUser,
		ECI_LogDbPsd,
		ECI_LogDbName,
		ECI_LogDbPort,
		 
		//wan
		ECI_WanClientMaxNum,				// ��������ͻ�������
		ECI_WanMaxRecvSize,					// ������������Ϣ��С
		ECI_WanInputBufSize,				// �������ջ�������С
		ECI_WanOutputBufSize,				// �������ͻ�������С
		ECI_WanOutputPoolSize,				// ����������Ϣ�ڴ�ش�С
		ECI_WanMemPoolSize, 
	 

		ECI_ServerMax,//db config																																																																																		ECI_ServerMax,
	};

	class cserver_cfg : public cconfig
	{
	public:
		//void destroy();

		/*const cdb_cfg& get_game_db_cfg() const { return m_game_db_cfg; }
		const cdb_cfg& get_global_db_cfg() const { return m_global_db_cfg; }
		std::string get_server_pass(uint32 server_id) const;
		const cdb_cfg& get_log_db_cfg() const { return m_log_db_cfg; }
*/
	protected:
		bool init(uint16 values_count, const char* config_filename);
		virtual bool init_more() { return true; }

	private:
		bool _check();
		//void _post_process();

	protected:
		//void _set_db(cdb_cfg& cfg, uint16 start_index);

	private:
		/*cdb_cfg m_game_db_cfg;
		cdb_cfg m_global_db_cfg;
		cdb_cfg m_log_db_cfg;*/
	};

} // namespace chen

#endif // _NSHARED_NCONFIG_H_
