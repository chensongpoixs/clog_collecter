#include "cserver_cfg.h"
#include "clog.h"
//#include "../wversion/build_version.h"
//#include "cmd5.h"

namespace chen {

	bool cserver_cfg::init(uint16 values_count, const char* config_filename)
	{
		//SYSTEM_LOG("svn version = %d", BUILD_SVN_REVERSION);
		if (false == cconfig::init(values_count, config_filename))
		{
			ERROR_EX_LOG("init config, set values count error, values_count = %u", values_count);
			return false;
		}

		/*if (!open_file(config_filename))
		{
			ERROR_EX_LOG("open config file error, %s", config_filename);
			return false;
		}*/

		//ip port
		//gateway
		set_string(ECI_WanIp, "wan_ip", "127.0.0.1");
		set_uint32(ECI_WanPort, "wan_port", 8000);
		 
	 

		//common
		set_string(ECI_ResPath, "res_path", "../../../res/");

		// [-11, 11]
		set_int32(ECI_TimeZone, "time_zone", 8);
		set_int32(ECI_TimeAdjust, "time_adjust", 0);
		//单位秒
		set_uint32(ECI_HeartBeat, "heart_beat", 120 * 1000);
		 
		set_uint32(ECI_LogLevel, "log_level", ELogLevel_Num);

		 

		//db log
		set_string(ECI_LogDbHost, "log_db_host", "127.0.0.1");
		set_string(ECI_LogDbUser, "log_db_user", "root");
		set_string(ECI_LogDbPsd, "log_db_psd", ""); //20211013
		set_string(ECI_LogDbName, "log_db_name", "global_log");
		set_uint32(ECI_LogDbPort, "log_db_port", 3306);

		 
		//Wan
		set_uint32(ECI_WanClientMaxNum, "wan_client_max_num", 64);
		//单位 B
		set_uint32(ECI_WanMaxRecvSize, "wan_max_recv_size", 1024);
		//单位 B
		set_uint32(ECI_WanInputBufSize, "wan_input_buf_size", 10 * 1024);
		//单位 B
		set_uint32(ECI_WanOutputBufSize, "wan_output_buf_size", 20 * 1024);
		//单位 MB
		set_uint32(ECI_WanOutputPoolSize, "wan_output_pool_size", 10);
		set_uint32(ECI_WanMemPoolSize, "wan_mem_pool_size", 20 * 1024);
 
		if (!_check())
		{
			return false;
		}

		//_post_process();

		if (!init_more())
		{
			return false;
		}
		//���ñ���ֵ
		load_cfg_file();
		//close_file();

		return true;
	}

	/*void cserver_cfg::destroy()
	{
		cconfig::destroy();
	}*/

	/*std::string cserver_cfg::get_server_pass(uint32 server_id) const
	{
		cMD5 md5;
		md5.update(&server_id, sizeof(server_id));
		md5.update(get_string(ECI_Sign));
		return md5.toString();
	}*/

	bool cserver_cfg::_check()
	{
		int time_zone = get_int32(ECI_TimeZone);
		if (time_zone < -11 || time_zone > 11)
		{
			ERROR_EX_LOG("invliad time zone [-11, 11], now is %d", time_zone);
			return false;
		}
		return true;
	}

	/*void cserver_cfg::_post_process()
	{
		_set_db(m_game_db_cfg, ECI_GameDbHost);
		_set_db(m_global_db_cfg, ECI_GlobalDbHost);
		_set_db(m_log_db_cfg, ECI_LogDbHost);
	}*/
	/*void cserver_cfg::_set_db(wdb_cfg& cfg, uint16 start_index)
	{
		cfg.m_host = get_string(start_index++);
		cfg.m_user = get_string(start_index++);
		cfg.m_passwd = get_string(start_index++);
		cfg.m_db_name = get_string(start_index++);
		cfg.m_port = get_uint32(start_index++);
		cfg.m_time_zone = get_int32(ECI_TimeZone);
	}*/
} // namespace chen
