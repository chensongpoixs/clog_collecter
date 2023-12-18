/***********************************************************************************************
created: 		2022-02-27

author:			chensong

purpose:		网络层
************************************************************************************************/


#ifndef _C_CLIENT_H_
#define _C_CLIENT_H_
#include "cnoncopytable.h"
#include "cnet_mgr.h"
#include <atomic>

namespace chen {
	class cclient :private cnoncopytable
	{
	public:
		explicit cclient();
		~cclient();
	public:
		bool init();
		void destroy();
	public:
		bool startup();
	public:
		void update(uint32 elapse);
		void shutdown();
	public:
		void on_connect(uint32 session_id, uint32 para, const char* buf);
		void on_msg_receive(uint32 session_id, uint16 msg_id, const void* p, uint32 size);
		void on_disconnect(uint32 session_id);
	private:
		bool connect_to_log( );
	public:
		bool send_msg(uint32 session_id, uint16 msg_id, const void* p, uint32 size);
		 
 
	public:
		/**
		* 关闭指定连接
		* @param session_id	连接id
		*/
		void close();
	 
	 
	private:
		cnet_mgr*					m_net_ptr;
		bool						m_stoped;
		 
		uint32						m_update_timer;
	};

	extern cclient	g_lan_client;
	extern std::string g_ip;
	extern uint16_t g_port;
}

#endif // _C_DEVICE_CLIENT_H_