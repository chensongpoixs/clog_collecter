/***********************************************************************************************
created: 		2022-02-27

author:			chensong

purpose:		�����
************************************************************************************************/


#ifndef _C_CLIENT_SESSION_H_
#define _C_CLIENT_SESSION_H_
#include <atomic>
#include "cnoncopytable.h"
#include "cnet_define.h"
#include "cnet_type.h"
#include "csingleton.h"
#include <google/protobuf/message_lite.h>
 
#include "cclient_msg/EnumDefine.pb.h"
#include "ccrypto.h"
namespace chen {
	enum ELanSessionStatus
	{
		ELSS_None = 0, 
		ELSS_Connecting,	//����������Ϸ������
		ELSS_Conencted,		//��������Ϸ������
		ELSS_Gameing,		//��ʼ��Ϸ
		ELSS_Closed,
		ELSS_Max,
	};
	class cclient_session : private cnoncopytable
	{
	private:


		typedef void(cclient_session::* client_handler_type)(const void* msg_ptr, uint32_t size);
		typedef std::map<uint16_t, client_handler_type>			M_CLIEINT_HANDLER_MAP;
		static const uint32 INVALID_SESSION_ID = 0XFFFFFFFF;
	public:
		explicit cclient_session();
		~cclient_session();
	public:
		bool init();
		void update(uint32 elapse);
		void destroy();

	public:
		bool send_msg(uint16_t msg_id, const void* pMsgPtr, uint32 size);
		bool send_msg(uint16_t msg_id, const ::google::protobuf::MessageLite& msg);

	 
	public:

		void handler_heatbeat(const void * msg_ptr, uint32_t msg_size);

		void handler_login(const void * msg_ptr, uint32_t msg_size);
	public:
		void send_login();
	public:
		bool is_used();
		bool set_status(ELanSessionStatus old_stauts, ELanSessionStatus new_stauts) { return m_status.compare_exchange_strong(old_stauts, new_stauts); }

		//void set_status(ELanSessionStatus status);
		uint32_t	get_session_id() const { return m_session_id; }
		ELanSessionStatus get_status() const { return m_status.load(); }
		void on_connect(uint32 session_id) { m_session_id = session_id; }
		bool   is_connected() const { return m_session_id != INVALID_SESSION_ID; }
		void  on_disconnect();

		void set_client_type(int32 client_type) { m_client_type = client_type; }

		const std::string & get_task_id() const { return m_task_id; }
		const std::string & get_collection_id() const { return m_collection_id; }
	 
		uint32	get_used_gpu_index() const { return m_gpu_index; }
	public:
		 
		void set_reconnect_timer(int value) { m_reconnect_timer = value; }
		void sub_reconnect_timer(int value) { m_reconnect_timer -= value; }
		int get_reconnect_timer() const { return m_reconnect_timer; }

	public:
		void handle_msg(uint16_t msg_id, const void* msg_ptr, uint32_t msg_size);
	private:
		//void _send_mediasoupstatusupdate(const std::string& taskid, EMediasoupType mediasoup_type, int32 result = 0);
	private:
		volatile	uint32						m_session_id;
		std::atomic<ELanSessionStatus>			m_status; // status
		int32									m_reconnect_timer;
		uint32									m_timestamp_second;
		//cmediasoup::cmediasoup_mgr				m_mediasoup_mgr;
		M_CLIEINT_HANDLER_MAP					m_client_handler_map;
		std::string									m_task_id;
		//cloud_rendering::cloud_rendering_stop_cb	m_cloud_reandering_stop_cb;
		
		std::string								m_collection_id;
		uint32									m_gpu_index; 
		time_t									m_send_rte_info;
		uint32									m_client_type;
 
	};


#define s_agent_client_session   chen::csingleton<chen::cclient_session>::get_instance()
}

#endif // _C_CLIENT_SESSION_H_