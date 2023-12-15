/********************************************************************
created:	2019-08-13

author:		chensong

purpose:	cdb_query_result

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

#include "cdb_query_result.h"
#include <string>
namespace chen {
	cdb_query_result::cdb_query_result()
	{
		_init(NULL);
	}
	cdb_query_result::~cdb_query_result()
	{
		_un_connect();
	}
	void cdb_query_result::connect(MYSQL_RES * mysql_res)
	{
		_un_connect();
		_init(mysql_res);
	}
	bool cdb_query_result::next_row(void)
	{
		if (!m_mysql_res)
		{
			return false;
		}
		m_cur_row = mysql_fetch_row(m_mysql_res);
		if (!m_mysql_res)
		{
			return false;
		}
		if (!m_rows || !m_fieldes)
		{
			return false;
		}

		if (NULL == m_cur_row[0])
		{
			return false;
		}
		m_lengths = mysql_fetch_lengths(m_mysql_res);
		if (!m_lengths)
		{
			return false;
		}
		return true;
	}
	const char * cdb_query_result::get_col_value(uint32 col) const
	{
		if (is_valid_col(col))
		{
			return m_cur_row[col];
		}
		return NULL;
	}
	char * cdb_query_result::get_blob(uint32 col, uint32 & len) const
	{
		if (!m_mysql_res || !m_cur_row || !m_fieldes)
		{
			return NULL;
		}
		if (!is_valid_col(col))
		{
			return NULL;
		}
		len = m_lengths[col];
		return m_cur_row[len];
	}
	void cdb_query_result::parse_string(uint32 col, std::string * str_ptr) const
	{
		if (!str_ptr)
		{
			return;
		}
		if (!m_mysql_res || !m_cur_row || !m_fieldes)
			return;

		if (!is_valid_col(col))
			return;

		if (!m_cur_row[col] || 0 == m_lengths[col])
		{
			return;
		}

		str_ptr->assign(static_cast<const char *>(m_cur_row[col]), static_cast<std::string::size_type>(m_lengths[col]));

	}
	bool cdb_query_result::get_bool(uint32 col) const
	{
		if (m_cur_row[col])
		{
			return (0 != atoi(m_cur_row[col]));
		}
		return false;
	}
	int8 cdb_query_result::get_int8(uint32 col) const
	{
		if (m_cur_row[col])
		{
			return static_cast<int8>(atol(m_cur_row[col]));
		}
		return 0;
	}
	uint8 cdb_query_result::get_uint8(uint32 col) const
	{
		if (m_cur_row[col])
		{
			return static_cast<uint8>(strtoul(m_cur_row[col], NULL, 10));
		}
		return 0;
	}
	int16 cdb_query_result::get_int16(uint32 col) const
	{
		if (m_cur_row[col])
		{
			return static_cast<int16>(atoi(m_cur_row[col]));
		}
		return 0;
	}
	uint16 cdb_query_result::get_uint16(uint32 col) const
	{
		if (m_cur_row[col])
		{
			return static_cast<uint16>(strtoul(m_cur_row[col], NULL, 10));
		}
		return 0;
	}
	int32 cdb_query_result::get_int32(uint32 col) const
	{
		if (m_cur_row[col])
		{
			return static_cast<int32>(atoi(m_cur_row[col]));
		}
		return 0;
	}
	uint32 cdb_query_result::get_uint32(uint32 col) const
	{
		if (m_cur_row[col])
		{
			return static_cast<uint32>(strtoul(m_cur_row[col], NULL, 10));
		}
		return 0;
	}
	int64 cdb_query_result::get_int64(uint32 col) const
	{
		if (m_cur_row[col])
		{
			return static_cast<int64>(strtoll(m_cur_row[col], NULL, 10));
		}
		return 0;
	}
	uint64 cdb_query_result::get_uint64(uint32 col) const
	{
		if (m_cur_row[col])
		{
			return static_cast<uint64>(strtoull(m_cur_row[col], NULL, 10));
		}
		return 0;
	}
	float cdb_query_result::get_float(uint32 col) const
	{
		if (m_cur_row[col])
		{
			return static_cast<float>(atof(m_cur_row[col]));
		}
		return 0.0f;
	}
	bool cdb_query_result::is_valid_col(uint32 col) const
	{
		return (col<m_cols);
		//return false;
	}
	void cdb_query_result::_init(MYSQL_RES * mysql_res)
	{
		m_cur_row = NULL;
		m_mysql_res = mysql_res;

		if (m_mysql_res)
		{
			m_fieldes = mysql_fetch_fields(m_mysql_res);
			m_cols = static_cast<uint32>(mysql_num_fields(m_mysql_res));
			m_rows = static_cast<uint32>(mysql_num_rows(m_mysql_res));
		}
		else
		{
			m_cols = 0;
			m_rows = 0;
			m_fieldes = NULL;
		}
	}
	void cdb_query_result::_un_connect(void)
	{
		if (m_mysql_res)
		{
			mysql_free_result(m_mysql_res);
			m_mysql_res = NULL;
		}

		_init(NULL);
	}
} // namespace chen