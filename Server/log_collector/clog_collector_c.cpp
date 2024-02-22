/***********************************************************************************************
created: 		2023-12-15

author:			chensong

purpose:		�����
************************************************************************************************/

#include "clog_collector_c.h"
#include "clog_collector.h"
#include "cutil.h"
bool   cpp_init(const char* ip, uint32_t port, uint32_t client_type)
{
	return c_init(ip, port, client_type);;
}

bool   cpp_send_core(const char* core_file_path )
{
	return c_send_core(core_file_path);;
}

void cpp_destroy()
{
	c_destroy();
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
	//static FILE* out_file = fopen("chensong.txt", "wb+");
	FILE* read_file = fopen(core_file_path, "rb");
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
	 
	//core_dump_data.resize(size );
	size_t read_size = 0;
	size_t re_l = size;
	
	while (read_size < size)
	{
		char buffer[4096] = { 0 };
		size_t size_r = ::fread((void*)(&buffer[0] /*+ read_size*/), 1, 4096, read_file);
		//printf("[core_dump_data.max_size() = %u][read_size = %u]size_r = %u[size = %u]\n", core_dump_data.max_size(), read_size, size_r, size);
		if (size_r <= 0)
		{
			//Sleep(1);
			//fclose(out_file_ptr);
			//out_file_ptr = NULL;
			break;
		}
		core_dump_data.append(std::string(&buffer[0], size_r));
		//memcpy((void *)(core_dump_data.data() + read_size), &buffer[0], size_r);
		//fwrite(&buffer[0], 1, size_r, out_file_ptr);
		//fflush(out_file_ptr);
		re_l - size_r;
		read_size += size_r;
		//::fseek(read_file, size_r, SEEK_CUR);
	}
	 
	/*std::string ddd = chen::cutil::get_hex_str(core_dump_data.c_str(), 1024);
	::fwrite(ddd.data(), 1, ddd.size(), out_file);
	fflush(out_file);*/
	//fclose(out_file);
	if (read_file)
	{
		::fclose(read_file);
		read_file = NULL;
	}

	{
		//static int32_t count = 1;
		//std::string file_core_name = "test_" + std::to_string(count++) + "chensong.zip";
		//FILE* out_file_ptr = fopen(file_core_name.c_str(), "wb+");
		// if (out_file_ptr)
		{
			// msg.SerializeAsString().c_str(), msg.ByteSize()
			 
			//MC2S_CoreFileUpdate msg1; \
				//	if (msg1.ParsePartialFromArray(ddd.c_str(), ddd.size()))
				//	{  
				//		fwrite(msg1.core_dump().c_str(), 1, msg1.core_dump().size(), out_file_ptr);
				//	}
				//	else
				//	{
				//		// parse faile
				//		printf("parse failed !!!\n");
				//	}
			//size_t write_l = 0;
			//size_t write_size = 0;
			//size_t w_size = size;
			//while (write_size < size)
			//{
			//	size_t www = 1024;
			//	if (w_size < 1024)
			//	{
			//		www = w_size;
			//	}
			//	write_l = fwrite(core_dump_data.c_str()+ write_size, 1, www, out_file_ptr);
			//	if (write_l <= 0)
			//	{
			//		break;
			//	}
			//	write_size += write_l;
			//	w_size -= write_l;
			//	::fseek(out_file_ptr, write_l, SEEK_CUR);
			//}
			//
			////fflush(out_file_ptr);
			//fclose(out_file_ptr);
			//printf("---> [%s](%u)(write_size = %u)\n", file_core_name.c_str(), size, write_size);
			//out_file_ptr = NULL;
		}
	
	}

	std::string core_file_name = core_name(core_file_path);
	bool ret = chen::LOG_COLLECTOR::send_core_dump(core_file_name.c_str(), core_dump_data);;

	 return ret;
}


void c_destroy()
{
	chen::LOG_COLLECTOR::destroy();
}
