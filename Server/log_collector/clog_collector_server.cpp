 
/***********************************************************************************************
created: 		2019-05-10
author:			chensong
purpose:		robot
************************************************************************************************/

#include "clog_collector_server.h"
 
#include "clog.h"
 
#include "cconfig.h"
#include "cclient.h"
#include <signal.h>
//#include "cmsg_dispatch.h"
 
//#include "cgm_command.h"
#include <chrono>
#include "cnet_msg_header.h"
//#include "cstr2digit.h"
//#include "ctest_case_global_mgr.h"
#include "../common/build_version.h"
#include "cclient_session.h"
#include "cclient_msg/MsgID.pb.h"
//#include "cclient_msg/AgentWebRtc.pb.h"
#include "cclient_msg/EnumDefine.pb.h"
//#include "cclient_msg/Rte.pb.h"


namespace chen {
	clog_collector_server g_log_collector_server;
	const uint32_t TICK_TIME = 200;
	volatile bool clog_collector_server::m_stoped = false;
	clog_collector_server::clog_collector_server() 
	{
	}
	clog_collector_server::~clog_collector_server()
	{
	}
	bool clog_collector_server::init(const char *ip, uint16_t port)
	{
		g_ip = ip;
		g_port = port;
		LOG::init("./log", "log_collector");
		if (false == g_lan_client.init())
		{
			ERROR_LOG("[%s] client init error!", __FUNCTION__);
			return false;
		}
		SYSTEM_LOG("client init success!");

		
	
		if (false == g_lan_client.startup())
		{
			ERROR_LOG("[%s] client start error!", __FUNCTION__);
			return false;
		}

		SYSTEM_LOG("client startup success!");

	
		return true;
	}
	void clog_collector_server::Loop()
	{
		using namespace std::chrono;

		uint32_t elapse = 0;
		steady_clock::time_point cur_time;
		steady_clock::time_point pre_time = steady_clock::now();
		steady_clock::duration dur;
		milliseconds ms;

		while (!m_stoped)
		{
			cur_time = steady_clock::now();
			dur = cur_time - pre_time;
			ms = duration_cast<milliseconds>(dur);
			elapse = static_cast<uint32_t>(ms.count());
			pre_time = cur_time;

			g_lan_client.update(elapse);
		//	g_timer_mgr.update(elapse);
			/*g_login_mgr.update(elapse);
			g_friend_circle_http_mgr.update(elapse);
			g_test_case_mgr.update(elapse);*/
			//ERROR_EX_LOG("elapse = %d, timer = %d", elapse , g_timer_mgr.get_second_timestamp());
			cur_time = steady_clock::now();

			dur = cur_time - pre_time;
			ms = duration_cast<milliseconds>(dur);
			elapse = static_cast<uint32_t>(ms.count());
			if (elapse < TICK_TIME)
			{
				std::this_thread::sleep_for(milliseconds(TICK_TIME - elapse));
			}
		}
		 
		 
	}
	void clog_collector_server::destroy()
	{
		 
		// WAN�ر�
		g_lan_client.shutdown();
		SYSTEM_LOG("client shutdown!");
		 
	 

		// wan session ����
		g_lan_client.destroy();
		SYSTEM_LOG("client destroy!");

 
 
			// �����ļ��˳�
		//g_cfg.destroy();
		//SYSTEM_LOG("config destroy!");
		// log�˳�

		LOG::destroy();
	}
	void clog_collector_server::stop()
	{
		m_stoped = true;
	}

	/*void clog_collector_client::result_dongle_auth(int32_t result, const char* data)
	{
		std::lock_guard<std::mutex> lock(m_callback_mutex);
		if (m_callback_ptr)
		{
			m_callback_ptr(result, data);
		}
	}*/

	//void clog_collector_client::send_rte_info()
	//{
		/*if(s_agent_client_session.is_used())
		{
			std::lock_guard<std::mutex> lock(m_rte_info_mutex);
			if (m_rte_info_callback_ptr)
			{
				 RteInfo rte_info;
				uint32_t result = m_rte_info_callback_ptr(rte_info);
				if (result == 0)
				{
					 MC2S_RteInfo rteinfo;
					rteinfo.set_appid(rte_info.appid);
					rteinfo.set_projectid(rte_info.projectid);
					for (size_t i = 0; i < rte_info.pois.size(); ++i)
					{
						Poi* poi = rteinfo.add_pois();
						if (poi)
						{
							poi->set_id(rte_info.pois[i].id);
							for (const std::string& v : rte_info.pois[i].tags)
							{
								poi->add_tags(v);
							}
						}
					}

					for (size_t i = 0; i < rte_info.effects.size(); ++i)
					{
						Effect* effects = rteinfo.add_effects();
						if (effects)
						{
							effects->set_id(rte_info.effects[i].id);
							for (const std::string& v : rte_info.effects[i].tags)
							{
								effects->add_tags(v);
							}
						}
					}

					for (size_t i = 0; i < rte_info.pathBrowers.size(); ++i)
					{
						PathBrower* pathbrower = rteinfo.add_pathbrowers();
						if (pathbrower)
						{
							pathbrower->set_id(rte_info.pathBrowers[i].id);
							for (const std::string& v : rte_info.pathBrowers[i].tags)
							{
								pathbrower->add_tags(v);
							}
						}
					}
					for (size_t i = 0; i < rte_info.virualcameras.size(); ++i)
					{
						virualCamera* virualcamera = rteinfo.add_virualcamera();
						if (virualcamera)
						{
							virualcamera->set_id(rte_info.virualcameras[i].id);
							virualcamera->set_videotrack(rte_info.virualcameras[i].isVideoTrack);
							for (const std::string& v : rte_info.virualcameras[i].tags)
							{
								virualcamera->add_tags(v);
							}
						}
					}

					for (size_t i = 0; i < rte_info.videopannels.size(); ++i)
					{
						videoPannel* videopannel = rteinfo.add_videopannels();
						if (videopannel)
						{
							videopannel->set_id(rte_info.videopannels[i].id);
							videopannel->set_videochannel(rte_info.videopannels[i].videoChannel);
							videopannel->set_videofusion(rte_info.videopannels[i].isVideoFusion);
							for (const std::string& v : rte_info.videopannels[i].tags)
							{
								videopannel->add_tags(v);
							}
						}
					}

					if (s_agent_client_session.is_connected())
					{
						s_agent_client_session.send_msg(C2S_RteInfo, rteinfo);
					}
				}
				else
				{
					WARNING_EX_LOG("callback rteinfo result = %u", result);
				}
			 }
		}*/
	//}

	/*void clog_collector_client::register_result(set_rte_info_result_callback callback)
	{
		std::lock_guard<std::mutex> lock(m_callback_mutex);
		m_callback_ptr = callback;
	}
	void  clog_collector_client::register_send_rte_info(set_rte_info_callback callback)
	{
		std::lock_guard<std::mutex> lock(m_rte_info_mutex);
		m_rte_info_callback_ptr = callback;
	}*/

	 
}//namespace chen 
 
