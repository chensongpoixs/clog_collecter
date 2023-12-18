#include <iostream>
#include "clog_collector_server.h"



#include <csignal>
void Stop(int i)
{

	chen::g_log_collector_server.stop();
}

void RegisterSignal()
{
	signal(SIGINT, Stop);
	signal(SIGTERM, Stop);

}


int main(int argc, char* argv[])
{
	RegisterSignal();

	//const char* config_filename = "client.cfg";
	////chen::check_file(config_filename);
	//if (argc > 1)
	//{
	//	config_filename = argv[1];
	//}
	//const char* log_path = "./log";
	//if (argc > 2)
	//{
	//	log_path = argv[2];
	//}

	const char* wan_ip = "192.168.1.175";
	const uint16_t wan_port = 8000;


	bool init = chen::g_log_collector_server.init(wan_ip, wan_port);

	 

	chen::g_log_collector_server.Loop();
	 

	chen::g_log_collector_server.destroy();
	 

	return EXIT_SUCCESS;
}

int   ffmain(int argc, char* argv[])
{

	 
	/*cdongle_auth_mgr auth_mgr;
	auth_mgr.set_register_result( result);
	auth_mgr.set_register_rte_info_callback(  rte_info);
	auth_mgr.connect("127.0.0.1", 8300);

	while (1)
	{
		Sleep(10);
	}
	auth_mgr.set_register_result(NULL);
	auth_mgr.set_register_rte_info_callback(NULL);
	auth_mgr.stop();*/
	/*/chen::g_agent_client.init("127.0.0.1", 8300);
	/chen::g_agent_client.Loop();
	/chen::g_agent_client.destroy();*/
   //
	return 0;
}