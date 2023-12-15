/***********************************************************************************************
created: 		2019-05-01

author:			chensong

purpose:		ccfg

*************************************************************************************************/


#ifndef _LOG_H_
#define _LOG_H_
#include "cnoncopytable.h"
namespace chen {
	class log : private cnoncopytable
	{
	public:
		explicit log();
		virtual ~log();

	public:
		bool init(const char* log_path, const char* config_file);
		bool Loop();
		void destroy();
		void stop();

	private:

		volatile bool m_stoped;
	};


	extern log		g_log;

}

#endif // _C_DONGLE_AUTH_H_