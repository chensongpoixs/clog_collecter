/***********************************************************************************************
created: 		2019-05-10
author:			chensong
purpose:		robot_client
************************************************************************************************/

#include "cclient.h"
#include "clog.h"
 
#include "cnet_msg_header.h"
#include "cclient_session.h"
 
#include "cclient_msg/MsgID.pb.h"
#include <iostream>
#include "clog_collector_server.h"
namespace  chen {
	
	std::string g_ip;
	uint16_t g_port;
	//cclient	g_lan_client;
	cclient::cclient()
		:m_net_ptr(NULL)
		, m_stoped(false)
		, m_update_timer(0)
		//, m_aysnc_log_queue()
	{
	}
	cclient::~cclient()
	{
	}
	bool cclient::init( )
	{
		m_net_ptr = cnet_mgr::construct();
		if (!m_net_ptr)
		{
			ERROR_EX_LOG("new cnet_mgr fail");
			return false;
		}
		s_agent_client_session.set_reconnect_timer(0);
		const uint32 recv_buf_size = 1024 * 10;
		const uint32 send_buf_size = 1024 * 30;
		const uint32 mem_pool_size = 60;
		if (!m_net_ptr->init("dongle_auth_client", 1, 1, send_buf_size, recv_buf_size, mem_pool_size))
		{
			return false;
		}

		m_net_ptr->set_connect_callback(
			std::bind(&cclient::on_connect, this, std::placeholders::_1, std::placeholders::_2
				, std::placeholders::_3)
		);

		m_net_ptr->set_msg_callback(
			std::bind(&cclient::on_msg_receive, this, std::placeholders::_1, std::placeholders::_2
				, std::placeholders::_3, std::placeholders::_4)
		);

		m_net_ptr->set_disconnect_callback(
			std::bind(&cclient::on_disconnect, this, std::placeholders::_1)
		);

		m_net_ptr->set_max_msg_size(recv_buf_size);
		
		return true;
	}
	void cclient::destroy()
	{
		if (m_net_ptr)
		{
			m_net_ptr->destroy();
			cnet_mgr::destroy(m_net_ptr);
		}

		s_agent_client_session.destroy();
		/*if (m_session_ptr)
		{
			for (uint32_t i = 0; i < m_max_client_session_num; ++i)
			{
				m_session_ptr[i].destroy();
			}
			delete[]	m_session_ptr;
			m_session_ptr = NULL;
		}*/
	}
	bool cclient::startup()
	{
		if (!m_net_ptr->startup(1, "", 0))
		{
			return false;
		}

		return true;

	}
	void cclient::update(uint32 elapse)
	{
		m_net_ptr->process_msg();
		 
		ELanSessionStatus status =  s_agent_client_session.get_status();
		NORMAL_EX_LOG("s_agent_client_session status= %u [reconnect_timer = %u]", status, s_agent_client_session.get_reconnect_timer());
		switch (status)
		{
		case ELSS_None:
				 
			s_agent_client_session.sub_reconnect_timer(elapse);
			if (s_agent_client_session.get_reconnect_timer() < 0)
			{
				connect_to_log();
			}
			break;
			 
		case ELSS_Connecting:
			break;
		case ELSS_Conencted:
		//case ELSS_Loading:
			s_agent_client_session.update(elapse);
			break;
		case ELSS_Gameing:
			s_agent_client_session.update(elapse);
			break;
		case ELSS_Closed:
			ERROR_EX_LOG("s_agent_client_session   m_status = %d", status);
			s_agent_client_session.set_status(ELSS_Closed, ELSS_None);
				
			s_agent_client_session.set_reconnect_timer(10000);
			break;
		default:
			break;
		}
		
	}
	void cclient::shutdown()
	{
		if (m_net_ptr)
		{
			m_net_ptr->shutdown();
		}
	}
	void cclient::on_connect(uint32 session_id, uint32 para, const char* buf)
	{
		ERROR_EX_LOG("session = %lu", session_id);
		if (para)
		{
			WARNING_EX_LOG("connect failed !!! para = %u", para);
			s_agent_client_session.set_status(ELSS_Connecting, ELSS_Closed);
		}
		else
		{
			NORMAL_LOG("connect agent ok session_id = %u!!!", session_id);
			s_agent_client_session.init();
			s_agent_client_session.on_connect(session_id);
			s_agent_client_session.set_status(ELSS_Connecting, ELSS_Conencted);
			s_agent_client_session.send_login();
		}
		 
	}
	void cclient::on_msg_receive(uint32 session_id, uint16 msg_id, const void* p, uint32 size)
	{
		ERROR_EX_LOG("session = %lu,msg_id = %lu, size = %lu", session_id, msg_id, size);
		
		if (!s_agent_client_session.is_connected())
		{
			ERROR_LOG("[%s] this session not connected!,   session_id = %u", __FUNCTION__,  session_id);
			return;
		}
		
		s_agent_client_session.handle_msg(msg_id, p, size); 
	}
	void cclient::on_disconnect(uint32 session_id)
	{
		ERROR_EX_LOG("session = %lu", session_id);
		//const uint32_t index = get_session_index(session_id);
		//// ×¢ÏúÁ¬½Ó
		//if (!index_valid(index))
		//{
		//	ERROR_LOG("[%s] invalid session index, index = %u, session id = %u", __FUNCTION__, index, session_id);
		//	return;
		//}

		//csession* session_ptr = &m_session_ptr[index];
		ELanSessionStatus status = s_agent_client_session.get_status();
		switch (status)
		{
		case ELSS_Connecting:
			SYSTEM_LOG("connecting failed" );
			break;
		case ELSS_Conencted:
			SYSTEM_LOG("disconnect with login after connected " );
			break;
		case ELSS_Gameing:
			SYSTEM_LOG("disconnect with game when gaming " );
			break;
		default:
			ERROR_LOG("[%s] invalid session status %d ", __FUNCTION__, status );
			return;
		}
		s_agent_client_session.on_disconnect();
	}
	bool cclient::connect_to_log( )
	{
		const std::string& ip = g_ip;
		uint16 port = g_port;
		SYSTEM_LOG("connect %s:%d ", ip.c_str(), port );
		if (!s_agent_client_session.set_status(ELSS_None, ELSS_Connecting))
		{
			ERROR_LOG("%s, set status to ELSS_LoginConnecting failed ", __FUNCTION__ );
			return false;
		}

		if (!m_net_ptr->connect_to(0, ip.c_str(), port))
		{
			ERROR_LOG("[%s] connect error!, ip = %s, port = %d", __FUNCTION__, ip.c_str(), port);
			s_agent_client_session.set_status(ELSS_Connecting, ELSS_Closed);
			return false;
		}
		//s_agent_client_session.init();
		//m_net_ptr->connect_to(index, ip.c_str(), port);
		return true;
	}
	bool cclient::send_msg(uint32 session_id, uint16 msg_id, const void* p, uint32 size)
	{
		if (!m_net_ptr->send_msg(session_id, msg_id, p, size))
		{
			WARNING_LOG("send session_id = %lu", session_id);
		}
		return true;
	}

	
	void cclient::close( )
	{
		m_net_ptr->close(s_agent_client_session.get_session_id());
	}

	 
} // namespace  chen