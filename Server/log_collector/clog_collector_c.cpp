/***********************************************************************************************
created: 		2023-12-15

author:			chensong

purpose:		�����
************************************************************************************************/

#include "clog_collector_c.h"
#include "clog_collector.h"

bool   cpp_init(const char* ip, uint32_t port, uint32_t client_type)
{
	return c_init(ip, port, client_type);;
}

bool   cpp_send_core(const char* core_file_path )
{
	return c_send_core(core_file_path);;
}

int   c_init(const char* ip, uint32_t port, uint32_t client_type)
{
	return chen::LOG_COLLECTOR::init(ip, port, client_type);;
}

std::string core_name(const std::string & path)
{
	int32_t index = -1;
	for (uint32_t i = 0; i < path.length(); ++i)
	{
		if (path.at(i) == '/' || path.at(i) == '\\')
		{
			index = i;
		}
	}
	return path.substr(index+1, path.length());
}

int   c_send_core(const char* core_file_path )
{
	FILE* read_file = fopen(core_file_path, "r");
	if (!read_file)
	{
		return false;
	}
	// 数据的大小
		// 移动到文件末尾
	::fseek(read_file, 0, SEEK_END);
	// 获取当前位置，即文件大小
	uint32_t size = ::ftell(read_file);
	::fseek(read_file, 0, SEEK_SET);


	std::string core_dump_data;
	core_dump_data.resize(size + 1);
	size_t read_size = ::fread((void*)core_dump_data.data(), 1, size, read_file);


	if (read_file)
	{
		::fclose(read_file);
		read_file = NULL;
	}

	std::string core_file_name = core_name(core_file_path);


	return chen::LOG_COLLECTOR::send_core_dump(core_file_name.c_str(), core_dump_data.c_str());;
}
