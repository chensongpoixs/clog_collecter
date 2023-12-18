/***********************************************************************************************
created: 		2022-02-27

author:			chensong

purpose:		�����
************************************************************************************************/
#include "cclient_session.h"
#include "cclient_msg/Log.pb.h"
#include "cclient.h"
#include "MsgID.pb.h"
#include "crobot_msg_header.h"
#include "clog_collector_server.h"
namespace chen {

	void cclient_session::send_login()
	{
		MC2S_Login msg;
		send_msg(C2S_Login, msg);
	}


	void cclient_session::handler_heatbeat(const void* msg_ptr, uint32_t msg_size)
	{

	}
	void cclient_session::handler_login(const void* msg_ptr, uint32_t msg_size)
	{
		PRASE_CLIENT_MSG(msg_ptr, S2C_Login, msg_size);
		s_log_collector_server.set_level(static_cast<ELogCollectorLevelType>( msg.log_level()));
	}
}