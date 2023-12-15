/********************************************************************
created:	2019-08-13

author:		chensong

purpose:	cdb_mysql
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


#ifndef _C_DB_MYSQL_H_
#define _C_DB_MYSQL_H_
#include "cdb_util.h"
#include "cdb_cfg.h"
#include "cdb_out_info.h"
namespace chen {
	class csql_mgr;
	class cdb_query_result;


	typedef void(*mysql_on_disconnect)(void);
	class cdb_mysql 
	{
	public:
		cdb_mysql();
		~cdb_mysql();
	public:
		bool init(const cdb_cfg& db_cfg, const std::string& name);

		bool connect(const cdb_cfg& db_cfg);
		void destroy();
		void shut_down();

		bool send_query(cdb_query_result& query_result, const char* query, uint32 len);
		bool send_query(cdb_query_result& query_result, const std::string& query);
		bool send_query(cdb_query_result& query_result, const csql_mgr& query);



		bool excute(const char* query, uint32 len, ESqlErrorType error_type = ESqlError_ShutDown, bool flag_error = false);
		bool excute(const std::string& query, ESqlErrorType error_type = ESqlError_ShutDown);
		bool excute(const csql_mgr& query, ESqlErrorType error_type = ESqlError_ShutDown);


//		bool spell_blob_str(const char* blob, uint32 len, char* out_blob, uint32& out_len);


		void register_disconnect_fn(mysql_on_disconnect fn) { m_disconnect_fn = fn; }

		const std::string& get_db_name() const { return m_cfg.m_db_name; }

	private:
		bool	_connect( );
		bool	_excute_query(const char * query, uint32 len);
		void	_sql_error_prompt(const char * query, uint32 len);
		
		void	_out_info(const char * query, unsigned int len);
		void	_mysql_error();
		
	private:
		cdb_mysql(const cdb_mysql&);
		cdb_mysql & operator=(const cdb_mysql&);
	private:
		cdb_cfg						m_cfg;
		cdb_out_info				m_out_info;
		MYSQL*						m_mysql;
		bool						m_prepare_disconnect;
		mysql_on_disconnect			m_disconnect_fn;
		std::string					m_name;
		static	int					m_count;
		static bool					m_inited;
	};
} // namespace chen

#endif// !#define _C_DB_MYSQL_H_