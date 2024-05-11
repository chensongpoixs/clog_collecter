/***********************************************************************************************
created: 		2023-12-15

author:			chensong

purpose:		�����
************************************************************************************************/

#include "clog_collector_c.h"
#include "clog_collector.h"
#include "cutil.h"
bool   cpp_init(const char* ip, uint32_t port, uint32_t client_type)
{
	return c_init(ip, port, client_type);;
}

bool   cpp_send_core(const char* core_file_path )
{
	return c_send_core(core_file_path);;
}

void cpp_destroy()
{
	c_destroy();
}

int   c_init(const char* ip, uint32_t port, uint32_t client_type)
{
	return chen::LOG_COLLECTOR::init(ip, port, client_type);;
}



int   c_send_core(const char* core_file_path )
{ 
	bool ret = chen::LOG_COLLECTOR::send_core_dump(core_file_path);;

	 return ret;
}


void c_destroy()
{
	chen::LOG_COLLECTOR::destroy();
}
