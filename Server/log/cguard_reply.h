/********************************************************************
created:	2019-05-07

author:		chensong

level:		网络层

purpose:	网络数据的收发
*********************************************************************/


#ifndef _C_GUARD_REPLY_H_
#define _C_GUARD_REPLY_H_
#include "clog.h"
#include <google/protobuf/message_lite.h>
#include "cwan_session.h"
namespace chen {
	class cguard_reply
	{
	public:
		cguard_reply(uint16 msg_id, const ::google::protobuf::MessageLite& msg, cwan_session* session_ptr)
			: m_msg_id(msg_id)
			, m_message(msg)
			, m_session_ptr(session_ptr) {  }
		~cguard_reply();
	private:
		uint16									m_msg_id;
		const ::google::protobuf::MessageLite&	m_message; 
		cwan_session*							m_session_ptr;

	};



#define CGUARD_REPLY(MSG_ID, SESSION) M##MSG_ID  reply;\
        cguard_reply guard_reply(MSG_ID,  reply, SESSION); 
}

#endif // _C_GUARD_REPLY_H_