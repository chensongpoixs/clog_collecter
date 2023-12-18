/***********************************************************************************************
created: 		2019-04-30

author:			chensong

purpose:		wan_server
 

输赢不重要，答案对你们有什么意义才重要。

光阴者，百代之过客也，唯有奋力奔跑，方能生风起时，是时代造英雄，英雄存在于时代。或许世人道你轻狂，可你本就年少啊。 看护好，自己的理想和激情。


我可能会遇到很多的人，听他们讲好2多的故事，我来写成故事或编成歌，用我学来的各种乐器演奏它。
然后还可能在一个国家遇到一个心仪我的姑娘，她可能会被我帅气的外表捕获，又会被我深邃的内涵吸引，在某个下雨的夜晚，她会全身淋透然后要在我狭小的住处换身上的湿衣服。
3小时候后她告诉我她其实是这个国家的公主，她愿意向父皇求婚。我不得已告诉她我是穿越而来的男主角，我始终要回到自己的世界。
然后我的身影慢慢消失，我看到她眼里的泪水，心里却没有任何痛苦，我才知道，原来我的心被丢掉了，我游历全世界的原因，就是要找回自己的本心。
于是我开始有意寻找各种各样失去心的人，我变成一块砖头，一颗树，一滴水，一朵白云，去听大家为什么会失去自己的本心。
我发现，刚出生的宝宝，本心还在，慢慢的，他们的本心就会消失，收到了各种黑暗之光的侵蚀。
从一次争论，到嫉妒和悲愤，还有委屈和痛苦，我看到一只只无形的手，把他们的本心扯碎，蒙蔽，偷走，再也回不到主人都身边。
我叫他本心猎手。他可能是和宇宙同在的级别 但是我并不害怕，我仔细回忆自己平淡的一生 寻找本心猎手的痕迹。
沿着自己的回忆，一个个的场景忽闪而过，最后发现，我的本心，在我写代码的时候，会回来。
安静，淡然，代码就是我的一切，写代码就是我本心回归的最好方式，我还没找到本心猎手，但我相信，顺着这个线索，我一定能顺藤摸瓜，把他揪出来。
*********************************************************************/
#include "cwan_server.h"
#include "clog.h"
#include "ccfg.h"
#include "cclient_msg/MsgID.pb.h"
//#include "crobot_msg_header.h" 
#include "cmsg_base_id.h" 
#include "cwan_session.h"
#include "cmsg_dispatch.h"
#include "clog.h"

#include "cserver_cfg.h"
#include <clog.h>
namespace chen {
	 
	cwan_server   g_wan_server;
	 
	cwan_server::cwan_server()
		: m_net_ptr(NULL)
		, m_stoped(false)
		, m_max_session_num(0u)
		, m_session_ptr(NULL)
		, m_update_timer(0) 
	{
	}
	cwan_server::~cwan_server()
	{
	}
	bool cwan_server::init()
	{
		m_net_ptr = cnet_mgr::construct();
		if (!m_net_ptr)
		{
			ERROR_EX_LOG("new cnet_mgr fail");
			return false;
		}
		m_max_session_num = g_cfg.get_uint32(ECI_LogClientMaxNum);
		uint32 client_session_num = 0;
		 
		m_max_session_num += client_session_num;
		const uint32 recv_buf_size = g_cfg.get_uint32(ECI_LogInputBufSize);
		const uint32 send_buf_size = g_cfg.get_uint32(ECI_LogOutputBufSize);
		const uint32 pool_size = g_cfg.get_uint32(ECI_LogMemPoolSize);
		if (!m_net_ptr->init("log", client_session_num, m_max_session_num, send_buf_size, recv_buf_size, pool_size))
		{
			return false;
		}

		m_net_ptr->set_connect_callback(
			std::bind(&cwan_server::on_connect, this, std::placeholders::_1, std::placeholders::_2
				, std::placeholders::_3)
		);

		m_net_ptr->set_msg_callback(
			std::bind(&cwan_server::on_msg_receive, this, std::placeholders::_1, std::placeholders::_2
				, std::placeholders::_3, std::placeholders::_4)
		);

		m_net_ptr->set_disconnect_callback(
			std::bind(&cwan_server::on_disconnect, this, std::placeholders::_1)
		);

		m_net_ptr->set_wan();
		m_net_ptr->set_max_msg_size(recv_buf_size);
		m_session_ptr = new cwan_session[m_max_session_num];
		if (!m_session_ptr)
		{
			ERROR_EX_LOG("new faild session max num =%lu", m_max_session_num);
			return false;
		}

		for (uint32 i = 0; i < m_max_session_num; ++i)
		{
			m_session_ptr[i].init();
		}
		// m_encrypt_byte_ptr = new unsigned char[recv_buf_size];
		// if (!m_encrypt_byte_ptr)
		// {
		// 	ERROR_EX_LOG("alloc encrypt byte failed !!!!");
		// 	return false;
		// }


		return true;
	}
	void cwan_server::destroy()
	{
		if (m_session_ptr)
		{
			for (uint32 i = 0; i < m_max_session_num; ++i)
			{
				m_session_ptr[i].destroy();
			}
			delete[] m_session_ptr;
			m_session_ptr = NULL;
		}
		if (m_net_ptr)
		{
			m_net_ptr->destroy();
			if (m_net_ptr)
			{
				cnet_mgr::destroy(m_net_ptr);
				m_net_ptr = NULL;
			}

		}
		
		m_max_session_num = 0;
	}
	bool cwan_server::startup()
	{
		if (!m_net_ptr)
		{
			return false;
		}
		if (!m_net_ptr->startup(1, g_cfg.get_string(ECI_LogIp).c_str(), g_cfg.get_uint32(ECI_LogPort)))
		{
			return false;
		} 
		return true;
	}
	void cwan_server::update(uint32 uDeltaTime)
	{
		static const uint32 UPDATE_TIMER = 15 * 1000;

		m_net_ptr->process_msg();

		m_update_timer += uDeltaTime;

		if (m_update_timer >= UPDATE_TIMER)
		{
			m_update_timer -= UPDATE_TIMER;

			for (uint32 i = 0; i < m_max_session_num; ++i)
			{
				if (m_session_ptr[i].is_used())
				{
					m_session_ptr[i].update(UPDATE_TIMER);
				}
			}
			if (m_net_ptr)
			{
				//m_net_ptr->show_info();
			}
		}

	}
	void cwan_server::shutdown()
	{
		if (m_net_ptr)
		{
			m_net_ptr->shutdown();
		}
	}
	void cwan_server::on_connect(uint32 session_id, uint32 para, const char * buf)
	{
		//if (para)
		uint32 index = get_session_index(session_id);
		
		if (m_session_ptr[index].is_used())
		{
			WARNING_EX_LOG("session_id = %u, used !!!", index);
			return;
		}
		m_session_ptr[index].set_used();
		m_session_ptr[index].set_session_id(session_id);
		m_session_ptr[index].set_remote_ip(buf);
		//m_session_ptr[index].build_encrypt_key();
		//m_session_ptr[index
		NORMAL_EX_LOG("session_id = %lu", session_id);
	}
	void cwan_server::on_msg_receive(uint32 session_id, uint16 msg_id, const void * p, uint32 size)
	{
		uint32 index = get_session_index(session_id);
		
		if (!m_session_ptr[index].is_used())
		{
			WARNING_EX_LOG("session_id = %u, not  used !!!", session_id);
			return;
		}
		NORMAL_EX_LOG("session_id = %lu, msg_id =%lu,  size = %lu", session_id, msg_id,   size);
		cmsg_handler* handler_ptr = g_msg_dispatch.get_msg_handler(msg_id);
		if (!handler_ptr)
		{
			WARNING_EX_LOG("[session_id = %u]not find [msg_id = %u]", session_id, msg_id);
			return;
		}
		if (!handler_ptr->handler)
		{
			WARNING_EX_LOG("[session_id = %u][msg_id = %u][not register]", session_id, msg_id);
			return;
		}
		++handler_ptr->handle_count;
		 
		 (m_session_ptr[index].*(handler_ptr->handler)) (p, size);
		 
		 
	}
	void cwan_server::on_disconnect(uint32 session_id)
	{
		uint32 index = get_session_index(session_id);
		 
		if (!m_session_ptr[index].is_used())
		{
			WARNING_EX_LOG("session_id = %u, used !!!", session_id  );
			return;
		}
		m_session_ptr[index].disconnect();
		WARNING_EX_LOG("session_id = %lu", session_id );
	}

	void cwan_server::send_msg(uint32 session_id, uint16 msg_id, const void * p, uint32 size)
	{
		if (!m_net_ptr->send_msg(session_id, msg_id, p, size))
		{
			WARNING_EX_LOG("send session_id = %lu, msg_id = %u", session_id, msg_id);
		}
	}

	 

	cwan_session * cwan_server::get_session(uint32 index)
	{
		if (!index_valid(index))
		{
			ERROR_EX_LOG("[%s] invalid session index, index = %u", __FUNCTION__, index);
			return NULL;
		}

		return &(m_session_ptr[index]);
	}

	cwan_session * cwan_server::get_session(uint32 index, uint32 session_id)
	{
		if (!index_valid(index))
		{
			ERROR_EX_LOG("[%s] invalid session index, index = %u, session id = %u", __FUNCTION__, index, session_id);
			return NULL;
		}

		if (m_session_ptr[index].get_session_id() != session_id)
		{
			return NULL;
		}


		return &(m_session_ptr[index]);
	}

	void cwan_server::close(uint32 session_id)
	{
		if (m_net_ptr)
		{
			m_net_ptr->close(session_id);
			//m_session_ptr[session_id].close();
		}
	}

	 

}//namespace chen 