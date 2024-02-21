/***********************************************************************************************
created: 		2023-12-15

author:			chensong

purpose:		�����
************************************************************************************************/


#ifndef _C_LOG_COLLECTOR_C_H_
#define _C_LOG_COLLECTOR_C_H_

#include <stdint.h>
#ifdef _MSC_VER
#include <Windows.h>
#define DLLIMPORT   __declspec(dllimport)
//#define DLLIMPORT
#elif defined(__GNUC__) ||defined(__APPLE__)
#define DLLIMPORT
#else
// å…¶ä»–ä¸æ”¯æŒçš„ç¼–è¯‘å™¨éœ€è¦è‡ªå·±å®žçŽ°è¿™ä¸ªæ–¹æ³•
#error unexpected c complier (msc/gcc), Need to implement this method for demangle
#endif



#ifdef __cplusplus


 
bool DLLIMPORT  cpp_init(const char *ip, uint32_t port, uint32_t client_type); 


bool DLLIMPORT cpp_send_core(const  char* core_file_name );
 
 
extern "C" {

#endif

 
	int DLLIMPORT  c_init(const char* ip, uint32_t port, uint32_t client_type);

	int DLLIMPORT c_send_core(const  char* core_file_path );
	 
#ifdef __cplusplus

}
#endif 


#endif // _C_LOG_COLLECTOR_C_H_