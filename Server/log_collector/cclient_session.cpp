#include "cclient_session.h"
#include "clog.h"
#include "cclient.h"
#include "clog_collector_server.h"
#include "cclient_msg/MsgID.pb.h"
//#include "cclient_msg/AgentWebRtc.pb.h"
#include "cclient_msg/EnumDefine.pb.h"
//#include "cclient_msg/DongleAuth.pb.h"
//#include "cclient_msg/Rte.pb.h"
#include "crobot_msg_header.h"
#include "Log.pb.h"
//#include "ccfg.h"
namespace chen {
	cclient_session::cclient_session()
		: m_session_id(0)
		, m_status(ELSS_None)
		/*, m_player(NULL)*/
		, m_reconnect_timer(0)
		, m_timestamp_second(0)
		//, m_cloud_reandering_stop_cb(nullptr)
		/*, m_gpu_index(20)
		, m_send_rte_info(::time(NULL))*/
		//, m_cloud_reandering_gpu_index_cb(nullptr)
		/*, m_count_beart_head(0)*/
		/*, m_crypto_flag(false)
		, m_crypto()
		, m_encrypt_byte_ptr(NULL)*/
	{
		//handler_login
		 m_client_handler_map.insert(std::make_pair(S2C_Login, &cclient_session::handler_login));
		//m_client_handler_map.insert(std::make_pair(S2C_EncryptKey, &cclient_session::handler_rte_encrypt));
		//m_client_handler_map.insert(std::make_pair(S2C_RteInfo, &cclient_session::handler_rte_info));
		//m_encrypt_byte_ptr = new unsigned char[1024 * 30];
	//	m_client_handler_map.insert(std::make_pair(S2C_WebRtcCommand, &cclient_session::handler_webrtc_command));
		 m_client_handler_map.insert(std::make_pair(S2C_HeatBeat, &cclient_session::handler_heatbeat));
	//	m_client_handler_map.insert(std::make_pair(S2C_GraphicsOffsetsUpdate, &cclient_session::handler_graphics_offsets_update));
	}
	cclient_session::~cclient_session()
	{
	}
	bool cclient_session::init()
	{
		m_session_id = INVALID_SESSION_ID;

		/*m_player = new cplayer();
		if (!m_player)
		{
		ERROR_EX_LOG(" new player failed ");
		return false;
		}*/
		//m_status = ELSS_Connecting;
		/*if (!m_mediasoup_mgr.init())
		{
			return false;
		}
		
		 m_mediasoup_mgr.startup("", 11, "", "", 4);*/
		return true;
		//return true;

		//return true;
	}
	void cclient_session::destroy()
	{
		//m_mediasoup_mgr.destroy();
	}
	bool cclient_session::send_msg(uint16_t msg_id, const void* pMsgPtr, uint32 size)
	{
		//std::string message ((char *)pMsgPtr, size);
		 //encrypt(message.c_str(), (void*)message.data(), message.length());
		return s_lan_client.send_msg(m_session_id, msg_id, pMsgPtr, size);
	}

	bool cclient_session::send_msg(uint16_t msg_id, const ::google::protobuf::MessageLite& msg)
	{
		//std::string message(msg.SerializeAsString());
		//encrypt(message.c_str(), (void*)message.data(), message.length());
		return s_lan_client.send_msg(m_session_id, msg_id, msg.SerializeAsString().c_str(), msg.ByteSize());
	}
	
	 
	
	void cclient_session::update(uint32 elapse)
	{
		//ERROR_EX_LOG("m_timestamp_second = %u,  m_status = %d", m_timestamp_second, m_status.load());
		m_timestamp_second += elapse;
		if (m_timestamp_second > 60 * 1500)
		{
			
			//++m_count_beart_head;
			//ERROR_EX_LOG("m_count_beart_head = %llu", m_count_beart_head);
			//ERROR_EX_LOG("timstamp = %d, beart_heart = %lu, timer = %d", m_timestamp_second, g_cfg.get_uint32(ECI_Beart_Heart), g_timer_mgr.get_second_timestamp());
			//ccmd_param param;
			//csend_msgc2s::send_beatheart(param, this);
			//MC2S_HeatBeat reply;
			 static  const  char * heatbeat = "beatbeat";
			send_msg(C2S_HeatBeat, heatbeat, 0);
			m_timestamp_second = m_timestamp_second - (60 * 1500);
		}
		//if (m_send_rte_info + 60 < ::time(NULL))
		{
			//g_agent_client.send_rte_info();
		//	m_send_rte_info = ::time(NULL) + 60;
			//MC2S_LogDataUpdate log_data;
			//log_data.set_log_data("chensong\n");
			//send_msg(C2S_LogDataUpdate, log_data );
		}
	}
	bool cclient_session::is_used()
	{
		return m_status.load() == ELSS_Conencted;
	}

	void cclient_session::on_disconnect()
	{
		m_session_id = INVALID_SESSION_ID;
		m_status = ELSS_Closed; 
	}

	 
	void cclient_session::handle_msg(uint16_t msg_id, const void* msg_ptr, uint32_t msg_size)
	{
		M_CLIEINT_HANDLER_MAP::iterator iter =  m_client_handler_map.find(msg_id);
		if (iter == m_client_handler_map.end())
		{
			WARNING_EX_LOG("not find msg_id = %u", msg_id);
			return;
		}
		
		return (this->*(iter->second))(msg_ptr, msg_size);
		
	}

	 

}