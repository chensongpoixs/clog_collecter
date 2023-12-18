/***********************************************************************************************
created: 		2022-02-27

author:			chensong

purpose:		�����
************************************************************************************************/


#ifndef _C_ASYNC_LOG_QUEUE__H_
#define _C_ASYNC_LOG_QUEUE__H_
#include "cnoncopytable.h"
#include "cnet_type.h"
#include "clog_collector.h"
#include "clog_color.h"
#include <list>
#include <mutex>
namespace chen {


#pragma pack(push,1)
	struct clog_collector_item
	{
		int				timestamp;
		signed char		level;
		unsigned int	size;
		//char			buf[1];
		char* buffer;
	};
#pragma pack(pop)

	class casync_log_queue : public cnoncopytable
	{
	private:
		typedef	std::mutex									clock_type;
		typedef std::lock_guard<clock_type>					clock_guard;
	public:
		explicit casync_log_queue()
			:m_level_log(ELogCollectorLevel_None)
			, m_color_ptr(NULL)
			, m_show_screen(false)
			, m_log_item()
			, m_log_buf(NULL)
		{}
		virtual ~casync_log_queue(){}


	public:
		bool init(  bool show_screen = false);
		void update(uint32 uDataTime);
		void destroy();
	public:
		void append_fix(ELogCollectorLevelType level, const void* str, unsigned int len);
		void append_var(ELogCollectorLevelType level, const char* format, va_list ap);

		void set_level(ELogCollectorLevelType level);

		ELogCollectorLevelType get_level()  const { return m_level_log; }

	private:
		void			_handler_log_item(const clog_collector_item* log_item_ptr);

		clog_collector_item*   _get_new_buf();

	private:
		ELogCollectorLevelType					m_level_log;
		clog_color*								m_color_ptr;
		bool									m_show_screen;
		clock_type								m_log_lock;
		std::list<clog_collector_item*>			m_log_item;
		char* m_log_buf;
	};
}



#endif // _C_ASYNC_LOG_QUEUE__H_