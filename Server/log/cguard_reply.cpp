/********************************************************************
created:	2019-05-07

author:		chensong

level:		网络层

purpose:	网络数据的收发
*********************************************************************/

#include "cguard_reply.h"
#include "cwan_server.h"
namespace chen
{
	cguard_reply::~cguard_reply()
	{
		//g_wan_server.send_msg(m_session_ptr->get_session_id(), m_msg_id, m_message.SerializeAsString().c_str(), m_message.SizeByte());
	}

}