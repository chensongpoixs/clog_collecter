/***********************************************************************************************
created: 		2019-05-01

author:			chensong

purpose:		ccfg

*************************************************************************************************/
#include "log.h"
#include "clog.h"
#include "ccfg.h"
#include "ctime_mgr.h"
#include "ctime_api.h" 
#include "cwan_server.h"
#include "ctime_elapse.h"
#include "clib_util.h"
#include "cdb_mysql.h"
#include "csql_mgr.h"
#include "cdb_version.h" 
#include "cglobal_db.h" 
#include "cmsg_dispatch.h"
namespace chen {
	log		g_log;
	log::log()
		: m_stoped(false)
	{
	}
	log::~log()
	{
	}
	bool log::init(const char* log_path, const char* config_file)
	{
		printf("Log init ...\n");
		if (!LOG::init(log_path, "log"))
		{
			return false;
		}
		SYSTEM_LOG("config init ...");
		if (!g_cfg.init(config_file))
		{
			return false;
		}
		LOG::set_level(static_cast<ELogLevelType>(g_cfg.get_uint32(ECI_LogLevel)));
		ctime_base_api::set_time_zone(g_cfg.get_int32(ECI_TimeZone));
		ctime_base_api::set_time_adjust(g_cfg.get_int32(ECI_TimeAdjust));

		if (!g_timer_mgr.init())
		{
			return false;
		}

		/*SYSTEM_LOG(" auth server init ...");
		if (!g_dongle_auth_mgr.init())
		{
			return false;
		}
		SYSTEM_LOG("rte logic mgr init ...");
		if (!g_rte_logic_mgr.init())
		{
			return false;
		}*/
		SYSTEM_LOG("mysql init ...");
		// 4. mysql
		if (!g_sql_mgr.init())
		{
			return false;
		}

		if (!s_db_version_mgr.init())
		{
			return false;
		}


		cdb_cfg  global_dongle_auth_db_cfg(g_cfg.get_string(ECI_LogDbHost).c_str(), g_cfg.get_string(ECI_LogDbUser).c_str(),
			g_cfg.get_string(ECI_LogDbName).c_str(), g_cfg.get_string(ECI_LogDbPsd).c_str(), g_cfg.get_int32(ECI_LogDbPort), g_cfg.get_int32(ECI_TimeZone), 1);
		if (!g_global_log_db.init(global_dongle_auth_db_cfg, g_cfg.get_string(ECI_LogDbName).c_str()))
		{
			ERROR_EX_LOG("g_global_dongle_auth_db.init!!!!");
			return false;
		}

		if (!s_db_version_mgr.check_db_version(g_global_log_db, cdb_version::EDT_Log, true, g_cfg.get_string(ECI_ResPath)))
		{
			return false;
		}

		//g_sql_mgr.reset(&g_global_dongle_auth_db);
		cdb_cfg  global_pass_db_cfg(g_cfg.get_string(ECI_LogDbHost).c_str(), g_cfg.get_string(ECI_LogDbUser).c_str(),
			g_cfg.get_string(ECI_LogDbName).c_str(), g_cfg.get_string(ECI_LogDbPsd).c_str(), g_cfg.get_int32(ECI_LogDbPort), g_cfg.get_int32(ECI_TimeZone), 1);
		if (!g_global_log_db.init(global_pass_db_cfg, g_cfg.get_string(ECI_LogDbName).c_str()))
		{
			ERROR_EX_LOG("g_global_pass_db.init!!!!");
			return false;
		}

		SYSTEM_LOG("db ok");
		SYSTEM_LOG("msg server dispath init ...");;
		if (!g_msg_dispatch.init())
		{
			return false;
		}
		SYSTEM_LOG("wan server  init ...");
		if (!g_wan_server.init())
		{
			return false;
		}
		SYSTEM_LOG("wan server  startup ...");
		if (!g_wan_server.startup())
		{
			return false;
		}
		SYSTEM_LOG(" Dongle Auth  server init ok");

		return true;
	}
	bool log::Loop()
	{
		static const uint32 TICK_TIME = 100;
		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½È´ï¿½ï¿½ï¿½Ê¼ï¿½ï¿½ï¿½ï¿½ï¿½
		//NORMAL_EX_LOG("");
		ctime_elapse time_elapse;
		uint32 uDelta = 0;
		while (!m_stoped)
		{
			uDelta += time_elapse.get_elapse();
			//	NORMAL_EX_LOG("");
	//			g_game_client.update(uDelta);
			//g_rte_logic_mgr.upadte(uDelta);
			//g_dongle_auth_mgr.update(uDelta);
			g_wan_server.update(uDelta);



			uDelta = time_elapse.get_elapse();

			if (uDelta < TICK_TIME)
			{
				csleep(TICK_TIME - uDelta);
			}
		}

		SYSTEM_LOG("Leave main loop");

		return true;
	}
	void log::destroy()
	{
		g_msg_dispatch.destroy();

		g_wan_server.shutdown();
		g_wan_server.destroy();
		SYSTEM_LOG("g_wan_server Destroy OK!");

		//g_rte_logic_mgr.destroy();
		//SYSTEM_LOG("rtc logic destroy OK !!!");
		//g_dongle_auth_mgr.destroy();
		//SYSTEM_LOG("dongle atuh destroy OK !!!");
		//g_global_dongle_auth_db.destroy();
		//SYSTEM_LOG("g_global_dongle_auth_db destroy  OK !!!");

		g_global_log_db.destroy();
		SYSTEM_LOG("g_global_log_db destroy  OK !!!");

		g_sql_mgr.destroy();
		SYSTEM_LOG("g_sql_mgr destroy OK  !!!");

		g_cfg.destroy();
		LOG::destroy();
		printf(" Dongle Auth server Destroy End\n");
	}
	void log::stop()
	{
		m_stoped = true;
	}
}