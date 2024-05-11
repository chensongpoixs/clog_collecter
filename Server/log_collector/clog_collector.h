/***********************************************************************************************
created: 		2023-12-15

author:			chensong

purpose:		�����
************************************************************************************************/


#ifndef _C_LOG_COLLECTOR_H_
#define _C_LOG_COLLECTOR_H_
#include <cstdint>
#include <string>
#if defined(_MSC_VER)
#include <Windows.h>

#define FUNCTION __FUNCTION__


//#define DLLIMPORT __declspec(dllimport)

#elif defined(__GNUC__)

#define FUNCTION __PRETTY_FUNCTION__

#define DLLIMPORT

#else
#pragma error "unknow platform!!!"

#endif

namespace chen {

	enum   ELogCollectorLevelType
	{
		ELogCollectorLevel_None = 0,
		ELogCollectorLevel_System,
		ELogCollectorLevel_Fatal,
		ELogCollectorLevel_Error,
		ELogCollectorLevel_Warn,
		ELogCollectorLevel_Info,
		ELogCollectorLevel_Debug,
		ELogCollectorLevel_Num,
	};


	class /*__declspec(dllimport)*/  clog_collector /*: private cnoncopytable*/
	{
	private:
		enum { EBuf_Size = 1024 };
	public:

		explicit clog_collector();
		explicit clog_collector(ELogCollectorLevelType level );
		explicit clog_collector(ELogCollectorLevelType level, const char* func, int line);
		/*virtual*/ ~clog_collector();
	public:
		/*
		*   ip : 日志服务的ip地址
		*   port : 日志服务的端口
		*   show_screen: 是否屏幕显示
		*/
		static bool  init(const char * ip, uint16_t port, uint32_t client_type = 0, bool show_screen = false);
		static void fix_log(ELogCollectorLevelType level, const void* p, int len);
		static void var_log(ELogCollectorLevelType level, const char* format, ...);
		

		static bool send_core_dump(const char * core_file_path);
		//static void set_level(ELogCollectorLevelType level);
		static void destroy();
	private:
		//void _pthread_work();
	public:
		clog_collector& operator<<(bool);
		clog_collector& operator<<(char);

		clog_collector& operator<<(signed char);
		clog_collector& operator<<(unsigned char);

		clog_collector& operator<<(signed short);
		clog_collector& operator<<(unsigned short);

		clog_collector& operator<<(signed int);
		clog_collector& operator<<(unsigned int);

		clog_collector& operator<<(signed long);
		clog_collector& operator<<(unsigned long);

		clog_collector& operator<<(signed long long);
		clog_collector& operator<<(unsigned long long);

		clog_collector& operator<<(const char*);
		//clog_collector& operator<<(const char[]);
		clog_collector& operator<<(const std::string&);

		clog_collector& operator<<(float);
		clog_collector& operator<<(double);
	private:
		//clog_collector(clog_collector&&);
	//	clog_collector(const clog_collector&);
		//clog_collector &operator =(clog_collector &&);
		//clog_collector& operator=(const clog_collector&);
	private:
		char m_data[EBuf_Size] = {0};
		int  m_len;
		ELogCollectorLevelType m_level;


	};



#define LOG_COLLECTOR clog_collector

 




	//��׼log ��ʱ��ǰ׺
#define LOG_COLLECTOR_SYSTEM LOG_COLLECTOR(ELogCollectorLevel_System)
#define LOG_COLLECTOR_FATAL  LOG_COLLECTOR(ELogCollectorLevel_Fatal, FUNCTION, __LINE__)
#define LOG_COLLECTOR_ERROR  LOG_COLLECTOR(ELogCollectorLevel_Error, FUNCTION, __LINE__)
#define LOG_COLLECTOR_WARN   LOG_COLLECTOR(ELogCollectorLevel_Warn, FUNCTION, __LINE__)
#define LOG_COLLECTOR_INFO   LOG_COLLECTOR(ELogCollectorLevel_Info)
#define LOG_COLLECTOR_DEBUG  LOG_COLLECTOR(ELogCollectorLevel_Debug)

#define FIX_LOG_COLLECTOR LOG_COLLECTOR::fix_log
#define VAR_LOG_COLLECTOR LOG_COLLECTOR::var_log

#define NORMAL_LOG_COLLECTOR(format, ...)		VAR_LOG_COLLECTOR(ELogCollectorLevel_Info, format, ##__VA_ARGS__)
#define ERROR_LOG_COLLECTOR(format, ...)		VAR_LOG_COLLECTOR(ELogCollectorLevel_Error, format, ##__VA_ARGS__)
#define WARNING_LOG_COLLECTOR(format, ...)	VAR_LOG_COLLECTOR(ELogCollectorLevel_Warn, format, ##__VA_ARGS__)
#define SYSTEM_LOG_COLLECTOR(format, ...)		VAR_LOG_COLLECTOR(ELogCollectorLevel_System , format, ##__VA_ARGS__)
#define DEBUG_LOG_COLLECTOR(format, ...)		VAR_LOG_COLLECTOR(ELogCollectorLevel_Debug, format, ##__VA_ARGS__)

#define NORMAL_EX_LOG_COLLECTOR(format, ...)	NORMAL_LOG_COLLECTOR  ("[%s][%d]" format, FUNCTION, __LINE__, ##__VA_ARGS__)
#define ERROR_EX_LOG_COLLECTOR(format, ...)	ERROR_LOG_COLLECTOR  ("[%s][%d]" format, FUNCTION, __LINE__, ##__VA_ARGS__)
#define WARNING_EX_LOG_COLLECTOR(format, ...)	WARNING_LOG_COLLECTOR("[%s][%d]" format, FUNCTION, __LINE__, ##__VA_ARGS__)


}

#endif // _C_LOG_COLLECTION_H_