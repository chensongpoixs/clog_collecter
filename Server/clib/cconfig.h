/***********************************************************************************************
created: 		2019-04-27

author:			chensong

purpose:		config
************************************************************************************************/
#ifndef _C_CONFIG_H_
#define _C_CONFIG_H_
#include "cnoncopytable.h"
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include "cnet_type.h"
namespace chen {
	class ccfg_file : private cnoncopytable
	{
	private:
		typedef std::unordered_map<std::string, std::string>	CCONFIG_MAP;
	public:
		ccfg_file();
		~ccfg_file();
	public:
		bool init(const char * file_name);
		void destroy();
	private:
		bool _parser_line(const std::string &line, std::string& key, std::string& value);
		bool _is_space(char c);
		bool _iscommentchar(char c);
		void _trim(std::string & str);
	public:
		bool   is_key(const std::string &key)const;
		std::string get_value(const std::string& key);
	private:
		void _insert_data(const std::string& key, const std::string &value);
	private:
		CCONFIG_MAP								m_config_map;
	};
	class cconfig : private cnoncopytable
	{
	public:
		explicit cconfig();
		virtual ~cconfig();

	public:
		virtual	bool init(int64 values_count, const char * file_name);
		virtual void destroy();
	public:
		void set_string(int32 index, const std::string key, std::string value);
		void set_int32(int32 index, const std::string key, int32 value);
		void set_uint32(int32 index, const std::string key, uint32 value);
		void set_string(int32 index, int32, const char * key, const char * value);
		void set_int32(int32 index, const char * key, int32 value);
		void set_uint32(int32 index, const char * key, uint32 value);


	public:
		std::string get_string(int64 index)const;
		int32 get_int32(int64 index)const;
		uint32 get_uint32(int64 index)const;
	public:
		void load_cfg_file();
	private:
		enum EValueType {
			EDataTypeNULL = 1,
			EDataTypeint,
			EDataTypeuint32,
			EDataTypeString,
		};
		typedef struct cnode {
			std::string m_name;
			EValueType	m_type;
			union
			{
				int32	m_int32;
				uint32	m_uint32;
				//uint64	m_uint64;
			};
			std::string m_data;

			cnode()
				: m_name("")
                , m_type(EDataTypeNULL)
                , m_data("")

			{
				//m_name.clear(); m_data.clear(); m_type = EDataTypeNULL;
			}
			~cnode()
			{
				m_name.clear(); m_data.clear(); m_type = EDataTypeNULL;

			}
			void init(const std::string& name, EValueType type)
			{
				m_name = name;
				m_type = type;
			}
		}cnode;

        cnode*			m_configs;
		int64           m_values_size;
		ccfg_file		m_cfg_file;
	};
}//namespace chen

#endif //!#define _C_CONFIG_H_

