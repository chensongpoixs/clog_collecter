/********************************************************************
created:	2019-03-24

author:		chensong

purpose:	sql_mgr
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

#include "csql_mgr.h"
//#include "clog.h"
#include <cstring>
//#include "credis_cfg.h"
#include "clog.h"
namespace chen {
	//csql_mgr	g_sql_mgr;
	static const int BLOB_BUF_SIZE = 2 * 1024 * 1024;

	csql_mgr::csql_mgr()
		: m_buf(NULL)
		, m_temp_buf(NULL)
		, m_buf_size(0)
		, m_pos(0)
		, m_error(false)
		, m_db_ptr(NULL)
	{
	}

	csql_mgr::~csql_mgr()
	{
		destroy();
	}

	bool csql_mgr::init()
	{
		
		m_buf = new char[BLOB_BUF_SIZE];
		if (!m_buf)
		{
		 	ERROR_EX_LOG("new m_buf failed!");
			 
			return false;
		}

		m_temp_buf = new char[BLOB_BUF_SIZE];
		if (!m_temp_buf)
		{
			 ERROR_EX_LOG("new m_serialize_buf failed!");
			 
			return false;
		}
		memset(m_buf, 0, BLOB_BUF_SIZE);
		memset(m_temp_buf, 0, BLOB_BUF_SIZE);

		m_buf_size = BLOB_BUF_SIZE;

		return true;
	}

	void csql_mgr::destroy()
	{
		if (m_buf)
		{
			delete[] m_buf;
			m_buf = NULL;
		}
		if (m_temp_buf)
		{
			delete[] m_temp_buf;
			m_temp_buf = NULL;
		}

		m_buf_size = 0;
		m_pos = 0;
		m_error = false;
	}

	void csql_mgr::reset()
	{
		m_pos = 0;
		m_error = false;
	}

	void csql_mgr::reset(cdb_mysql* db_ptr)
	{
		reset();
		m_db_ptr = db_ptr;
	}

	void csql_mgr::write(const void * buf, uint32 len)
	{
		if (!m_error && m_pos + len <= m_buf_size)
		{
			memcpy(m_buf + m_pos, buf, len);
			m_pos += len;
			return;
		}
		m_error = true;
	}

	void csql_mgr::write(uint32 pos, const void * buf, uint32 len)
	{
		if (!m_error && pos + len <= m_buf_size)
		{
			memcpy(m_buf + pos, buf, len);
			return;
		}
		m_error = true;
	}

	void csql_mgr::skip(uint32 len)
	{
		if (!m_error && m_pos + len <= m_buf_size)
		{
			m_pos += len;
			return;
		}
		m_error = true;
	}

	void csql_mgr::back(uint32 len)
	{
		if (!m_error && m_pos >= len)
		{
			m_pos -= len;
			return;
		}
		m_error = true;
	}

	/*bool csql_mgr::write_master_data(const std::string & data)
	{
		if (!m_redis_master_ptr)
		{
			return false;
		}
		if (!m_redis_master_ptr->hmsethash(data))
		{
			return false;
		}
		return true;
	}*/

	csql_mgr & csql_mgr::operator<<(char value)
	{
		if (has_error())
		{
			return *this;
		}
		if (m_pos < m_buf_size)
		{
			m_buf[m_pos++] = value;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	csql_mgr & csql_mgr::operator<<(bool value)
	{
		if (value)
		{
			return *this << '1';
		}
		else
		{
			return *this << '0';
		}
	}

	csql_mgr & csql_mgr::operator<<(signed char value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	csql_mgr & csql_mgr::operator<<(unsigned char value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	csql_mgr & csql_mgr::operator<<(signed short value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	csql_mgr & csql_mgr::operator<<(unsigned short value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	csql_mgr & csql_mgr::operator<<(signed int value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	csql_mgr & csql_mgr::operator<<(unsigned int value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	csql_mgr & csql_mgr::operator<<(signed long value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	csql_mgr & csql_mgr::operator<<(unsigned long value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	csql_mgr & csql_mgr::operator<<(signed long long value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	csql_mgr & csql_mgr::operator<<(unsigned long long value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	csql_mgr & csql_mgr::operator<<(float value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec<float>(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	csql_mgr & csql_mgr::operator<<(double value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec<double>(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	csql_mgr & csql_mgr::operator<<(const char * c_str)
	{
		// TODO: insert return statement here
		write(c_str, static_cast<uint32>(strlen(c_str)));
		return *this;
	}

	csql_mgr & csql_mgr::operator<<(const std::string & value)
	{
		// TODO: insert return statement here
		write(value.c_str(), static_cast<uint32>(value.length()));
		return *this;
	}

}