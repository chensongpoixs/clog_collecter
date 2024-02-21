#include "clog_collector_c.h"


#if _DEBUG
#pragma comment(lib, "log_collectord.lib")
#else
#pragma comment(lib, "log_collector.lib")
#endif 

int main(int argc, char* argv[])
{
	c_init("127.0.0.1", 8000, 5);


	Sleep(1);




	 
	
	c_send_core("core.dump");
	return 0;
}