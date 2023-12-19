/***********************************************************************************************
created: 		2023-12-15

author:			chensong

purpose:		�����
************************************************************************************************/

#include "clog_collector.h"
#include "cdigit2str.h"
#include "cclient.h"
#include "clog_collector_server.h"
#include "cclient_session.h"

namespace chen {
	static bool g_log_server_stoped = false;

	clog_collector::clog_collector()
		:m_len(0)
		, m_level(ELogCollectorLevel_None)
	{
	}
	clog_collector::clog_collector(ELogCollectorLevelType level)
		: m_len(0)
		, m_level(level)
	{
	}
	clog_collector::clog_collector(ELogCollectorLevelType level, const char* func, int line)
		: m_len(0)
		, m_level(level)
	{
		*this << '[' << func << ':' << line << "] ";
	}
	bool clog_collector::init(const char* ip, uint16_t port, uint32_t client_type, bool show_screen)
	{
		//g_log_ptr = new casync_log();
		//if (!g_log_ptr)
		//{
		//	std::cout << " alloc casync_log new fail " << std::endl;
		//	return false;
		//}
		//if (!g_log_ptr->init(path, name, ext, true))
		//{
		//	std::cout << "log init error " << std::endl;
		//	return false;
		//}
		if (g_log_server_stoped)
		{
			return true;
		}
		s_agent_client_session.set_client_type(client_type);
		if (!s_log_collector_server.init(ip, port, show_screen))
		{
			return false;
		}
		g_log_server_stoped = true;
		std::thread([&] {
			s_log_collector_server.Loop();
			s_log_collector_server.destroy();
			g_log_server_stoped = false;
			}).detach();
		return true;;
	}
	void clog_collector::fix_log(ELogCollectorLevelType level, const void* p, int len)
	{
		s_log_collector_server.append_fix(level, p, len);
		//if (g_log_ptr && len > 0 /*&& m_level <= g_log_ptr->get_level()*/)
		//{
		//	g_log_ptr->append_fix(level, p, len);
		//}
	}
	void clog_collector::var_log(ELogCollectorLevelType level, const char* format, ...)
	{
		if (s_log_collector_server.get_level() < level)
		{
			return;
		}
		
		 va_list argptr;
		 va_start(argptr, format);
		 s_log_collector_server.append_var(level, format, argptr);
		 va_end(argptr);
		 
	}
	 
	void clog_collector::destroy()
	{
		s_log_collector_server.stop();
		//s_log_collector_server.destroy();
	}
	clog_collector& clog_collector::operator<<(bool value)
	{
		// TODO: �ڴ˴����� return ���
		if (value)
		{
			return *this << '1';
		}
		else
		{
			return *this << '0';
		}
	}
	clog_collector& clog_collector::operator<<(char value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			m_data[m_len++] = value;
		}
		return *this;
	}
	clog_collector& clog_collector::operator<<(signed char value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			m_data[m_len++] = value;
		}
		//return *this;
		return *this;
	}
	clog_collector& clog_collector::operator<<(unsigned char value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			m_data[m_len++] = value;
		}
		return *this;
	}
	clog_collector& clog_collector::operator<<(signed short value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			m_len += digit2str_dec(m_data + m_len, EBuf_Size - m_len, value);
		}
		return *this;
	}
	clog_collector& clog_collector::operator<<(unsigned short value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			m_len += digit2str_dec(m_data + m_len, EBuf_Size - m_len, value);
		}
		return *this;
	}
	clog_collector& clog_collector::operator<<(signed int value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			m_len += digit2str_dec(m_data + m_len, EBuf_Size - m_len, value);
		}
		return *this;
	}
	clog_collector& clog_collector::operator<<(unsigned int value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			m_len += digit2str_dec(m_data + m_len, EBuf_Size - m_len, value);
		}
		return *this;
	}
	clog_collector& clog_collector::operator<<(signed long value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			m_len += digit2str_dec(m_data + m_len, EBuf_Size - m_len, value);
		}
		return *this;
	}
	clog_collector& clog_collector::operator<<(unsigned long value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			m_len += digit2str_dec(m_data + m_len, EBuf_Size - m_len, value);
		}
		return *this;
	}
	clog_collector& clog_collector::operator<<(signed long long value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			m_len += digit2str_dec(m_data + m_len, EBuf_Size - m_len, value);
		}
		return *this;
	}
	clog_collector& clog_collector::operator<<(unsigned long long value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			m_len += digit2str_dec(m_data + m_len, EBuf_Size - m_len, value);
		}
		return *this;
	}
	clog_collector& clog_collector::operator<<(const char* value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			//m_data[m_len++] = value;
			if (!memcpy(m_data + m_len, value, strlen(value)))
			{
				return *this;
			}
			m_len += static_cast<int32>(strlen(value));
		}
		return *this;
	}
	
	clog_collector& clog_collector::operator<<(const std::string& value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			//m_data[m_len++] = value;
			//m_len += digit2str_dec(m_data + m_len, EBuf_Size - m_len, value);
			/*m_len += */
			if (!memcpy(m_data + m_len, value.c_str(), value.length()))
			{
				return *this;
			}
			m_len += static_cast<int32>(value.length());
		}
		return *this;
	}
	clog_collector& clog_collector::operator<<(float value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			//m_data[m_len++] = value;
			m_len += digit2str_dec(m_data + m_len, EBuf_Size - m_len, value);
		}
		return *this;
	}
	clog_collector& clog_collector::operator<<(double value)
	{
		// TODO: �ڴ˴����� return ���
		if (m_len < EBuf_Size)
		{
			/*m_data[m_len++] =*/ m_len += digit2str_dec(m_data + m_len, EBuf_Size - m_len, value);
		}
		return *this;
	}
	clog_collector::~clog_collector()
	{
		s_log_collector_server.append_fix(m_level, m_data, m_len);
		//if (g_log_ptr && m_len > 0 /*&& m_level <= g_log_ptr->get_level()*/)
		//{
		//	g_log_ptr->append_fix(m_level, m_data, m_len);
		//}
	}

}