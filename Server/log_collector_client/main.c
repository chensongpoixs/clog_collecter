#include "clog_collector_c.h"
#include <stdio.h>

//#if _DEBUG
//#pragma comment(lib, "log_collectord.lib")
//#else
#pragma comment(lib, "log_collector.lib")
//#endif 

int main(int argc, char* argv[])
{
	c_init("127.0.0.1", 8000, 5);


	//Sleep(1000);


	//while (1)
	{
		//Sleep(1000);
		c_send_core("../dump_20240221184304.zip");
		printf("send\n");
		//Sleep(1000);
	}
	c_destroy();
	/*while (1)
	{
		Sleep(10);
	}*/
	return 0;
}