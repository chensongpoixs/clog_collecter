#include <iostream>

#include <cstdio>
#include <cstdlib>
//#include "cauth.h"
#include "log.h"

#include <csignal>
void Stop(int i)
{

	chen::g_log.stop();
}

void RegisterSignal()
{
	signal(SIGINT, Stop);
	signal(SIGTERM, Stop);

}


int main(int argc, char* argv[])
{
	RegisterSignal();

	const char* config_filename = "server.cfg";
	//chen::check_file(config_filename);
	if (argc > 1)
	{
		config_filename = argv[1];
	}
	const char* log_path = "./log";
	if (argc > 2)
	{
		log_path = argv[2];
	}

	bool init = chen::g_log.init(log_path, config_filename);

	if (init)
	{
		init = chen::g_log.Loop();
	}

	chen::g_log.destroy();
	if (!init)
	{
		return 1;
	}

	return EXIT_SUCCESS;
}