#ifndef BD3GE_CONFIG_MANAGER_H
#define BD3GE_CONFIG_MANAGER_H

#include <ios>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "../os/win32.h"
#include "../system/constants.h"
#include "../system/api.h"

namespace BD3GE {
	class BD3GE_API ConfigManager {
		public:

			enum class CONFIG_TYPE {
				STRING,
				FLOAT,
				INTEGER,
				BOOLEAN
			};

			static void load_config();
			static void save_config();
			static std::string get_config_value_string(const std::string config_key);
			static float get_config_value_float(const std::string config_key);
			static int get_config_value_int(const std::string config_key);
			static bool get_config_value_bool(const std::string config_key);
			static void set_config_value_string(const std::string config_key, std::string config_value);
			static void set_config_value_float(const std::string config_key, float config_value);
			static void set_config_value_int(const std::string config_key, int config_value);
			static void set_config_value_bool(const std::string config_key, bool config_value);

		private:

			static void set_config_value(const std::string config_key, CONFIG_TYPE config_type);
			static void read_config_file_line(std::string config_file_line);
			static void write_config_file_line(std::string config_key);

			static std::string config_file_path;
			static std::ifstream config_file_read_handle;
			static std::ofstream config_file_write_handle;
			static std::map<std::string, std::string> config_strings;
			static std::map<std::string, float> config_floats;
			static std::map<std::string, int> config_ints;
			static std::map<std::string, bool> config_bools;
			static std::map<std::string, CONFIG_TYPE> config_types;
			static std::vector<std::string> config_order;
	};
}

#endif // BD3GE_CONFIG_MANAGER_H