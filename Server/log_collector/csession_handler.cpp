/***********************************************************************************************
created: 		2022-02-27

author:			chensong

purpose:		�����
************************************************************************************************/
#include "cclient_session.h"
#include "cclient_msg/Log.pb.h"
#include "cclient.h"
#include "MsgID.pb.h"

namespace chen {

	void cclient_session::send_login()
	{
		MC2S_Login msg;
		send_msg(C2S_Login, msg);
	}
}