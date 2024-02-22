//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
////#include "clog_collector_server.h"
//#include "clog_collector.h"
//#include <thread>
//#include <chrono>
//
//#include <csignal>
//#if _DEBUG
//#pragma comment(lib, "log_collectord.lib")
//#else
//#pragma comment(lib, "log_collector.lib")
//#endif 
//bool test_stoped = false;
//void Stop(int i)
//{
//	test_stoped = true;
//	chen::LOG_COLLECTOR::destroy();
//	//s_log_collector_server.stop();
//}
//
//void RegisterSignal()
//{
//	signal(SIGINT, Stop);
//	signal(SIGTERM, Stop);
//
//}
//
//
//int main(int argc, char* argv[])
//{
//	RegisterSignal();
//	test_stoped = false;
//	//const char* config_filename = "client.cfg";
//	////chen::check_file(config_filename);
//	//if (argc > 1)
//	//{
//	//	config_filename = argv[1];
//	//}
//	//const char* log_path = "./log";
//	//if (argc > 2)
//	//{
//	//	log_path = argv[2];
//	//}
//
//	//const char* wan_ip = "192.168.1.175";
//	//const uint16_t wan_port = 8000;
//
//	chen::LOG_COLLECTOR::init(argv[1], std::atoi(argv[2]), std::atoi(argv[3]));
//
//
//	for (int i = 0; i < 100; ++i)
//	{
//		std::thread([] {
//			while (!test_stoped)
//			{
//				using namespace chen;
//
//				LOG_COLLECTOR_WARN << 3 << "chensdsfdong" << "pppppp--->";
//				ERROR_EX_LOG_COLLECTOR("chendfdssong");
//				std::this_thread::sleep_for(std::chrono::microseconds(100));
//			}
//			}).detach();
//	}
//
//
//
//	FILE* read_file = fopen("test.dump", "r");
//
//	// 数据的大小
//		// 移动到文件末尾
//	::fseek(read_file, 0, SEEK_END);
//	// 获取当前位置，即文件大小
//	uint32_t size = ::ftell(read_file);
//	::fseek(read_file, 0, SEEK_SET);
//
//
//	std::string core_dump_data;
//	core_dump_data.resize(size + 1);
//	size_t read_size = ::fread((void*)core_dump_data.data(), 1, size, read_file);
//
//
//	if (read_file)
//	{
//		::fclose(read_file);
//		read_file = NULL;
//	}
//	
//	while (!test_stoped)
//	{
//		using namespace chen;
//
//		LOG_COLLECTOR_WARN << 3 << "chensong" << "pppppp--->";
//		ERROR_EX_LOG_COLLECTOR("chensong");
//		static uint32_t core_count = 9;
//		std::string core_file_name = "test_" + std::to_string(++core_count) + ".dump";
//		LOG_COLLECTOR::send_core_dump(core_file_name.c_str(), core_dump_data.c_str());
//
//		//LOG_COLLECTOR_SYSTEM()// << "chensong--->";
//		std::this_thread::sleep_for(std::chrono::seconds(10));
//	}
//	/*bool init = s_log_collector_server.init(wan_ip, wan_port);
//
//	 
//
//	s_log_collector_server.Loop();
//	 
//
//	s_log_collector_server.destroy();*/
//	 
//
//	return EXIT_SUCCESS;
//}
//
//int   ffffmain(int argc, char* argv[])
//{
//
//	 
//	/*cdongle_auth_mgr auth_mgr;
//	auth_mgr.set_register_result( result);
//	auth_mgr.set_register_rte_info_callback(  rte_info);
//	auth_mgr.connect("127.0.0.1", 8300);
//
//	while (1)
//	{
//		Sleep(10);
//	}
//	auth_mgr.set_register_result(NULL);
//	auth_mgr.set_register_rte_info_callback(NULL);
//	auth_mgr.stop();*/
//	/*/chen::g_agent_client.init("127.0.0.1", 8300);
//	/chen::g_agent_client.Loop();
//	/chen::g_agent_client.destroy();*/
//   //
//	return 0;
//}