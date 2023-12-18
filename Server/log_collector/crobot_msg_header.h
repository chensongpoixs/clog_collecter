/***********************************************************************************************
created: 		2019-05-19

author:			chensong

purpose:		robot_msg_header
************************************************************************************************/


#ifndef _C_ROBOT_MSG_HEADER_H_
#define _C_ROBOT_MSG_HEADER_H_
#include "clog.h"
#include <google/protobuf/message_lite.h>
namespace chen {
#define PRASE_CLIENT_MSG(MSG_PTR, MSG_ID, MSG_SIZE) \
	M##MSG_ID msg; \
	if (false == msg.ParsePartialFromArray(MSG_PTR, MSG_SIZE)) \
	{ ERROR_EX_LOG("ParsePartialFromArray error, msg id = %s", #MSG_ID); return; } 

}//namespace chen

#endif // !#define _C_ROBOT_MSG_HEADER_H_