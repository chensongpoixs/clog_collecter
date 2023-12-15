﻿/********************************************************************
created:	2019-03-24

author:		chensong

purpose:	csql_mgr
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
#ifndef _C_SQL_MGR_H_
#define _C_SQL_MGR_H_
//#include "cnoncopyable.h"
#include "cnet_type.h"
#include "cdigit2str.h"
#include <string>
#include "csingleton.h"
namespace chen {
	class cdb_mysql;
	class csql_mgr /*:public cnoncopyable*/
	{
	public:
		explicit csql_mgr();
		virtual ~csql_mgr();
	public:
	public:
		bool init();
		void destroy();

	public:
		const char* get_buf() const { return m_buf; }

		uint32 get_size() const { return m_pos; }

		bool has_error() const { return m_error; }

		bool no_error() const { return !has_error(); }

		void reset();

		void reset(cdb_mysql* db_ptr);


		void write(const void* buf, uint32 len);

		void write(uint32 pos, const void* buf, uint32 len);

		void skip(uint32 len);

		void back(uint32 len);

	//public:
	//	// write master 
	//	bool  write_master_data(const std::string & data);
	//
	public:
		csql_mgr& operator<<(char value);

		csql_mgr& operator<<(bool value);

		csql_mgr& operator<<(signed char value);

		csql_mgr& operator<<(unsigned char value);

		csql_mgr& operator<<(signed short value);

		csql_mgr& operator<<(unsigned short value);

		csql_mgr& operator<<(signed int value);

		csql_mgr& operator<<(unsigned int value);

		csql_mgr& operator<<(signed long value);

		csql_mgr& operator<<(unsigned long value);

		csql_mgr& operator<<(signed long long value);

		csql_mgr& operator<<(unsigned long long value);

		csql_mgr& operator<<(float value);
		csql_mgr& operator<<(double value);
		//must be zero end string, not write the end 0
		csql_mgr& operator<<(const char* c_str);

		csql_mgr& operator<<(const std::string& value);
	private:
		csql_mgr(const csql_mgr&);
		csql_mgr& operator=(const csql_mgr&);
	private:
		char*						m_buf;
		char*						m_temp_buf;
		uint32						m_buf_size;
		uint32						m_pos;
		bool						m_error;
		cdb_mysql*					m_db_ptr;
	};
	//extern csql_mgr	g_sql_mgr;
	//#define   cw_redis_mgr                     csingleton<csql_mgr>::get_instance()
} // !namespace chen


#endif // _C_SQL_MGR_H_