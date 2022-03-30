#include "config_manager.h"

namespace BD3GE {
	std::string ConfigManager::config_file_path;
	std::ifstream ConfigManager::config_file_read_handle;
	std::ofstream ConfigManager::config_file_write_handle;
	std::map<std::string, std::string> ConfigManager::config_strings;
	std::map<std::string, float> ConfigManager::config_floats;
	std::map<std::string, int> ConfigManager::config_ints;
	std::map<std::string, bool> ConfigManager::config_bools;

	void ConfigManager::load_config() {
#ifdef __linux__
#elif _WIN32
		set_config_value_string(
			"system_directory_path",
			WinAPI::get_environment_variable("LOCALAPPDATA") + "/" + DEFAULT_RELATIVE_SYSTEM_DIRECTORY
		);
#endif

		std::string system_directory_path = get_config_value_string("system_directory_path");
		config_file_path = system_directory_path + DEFAULT_CONFIG_FILE;

		config_file_read_handle.open(config_file_path, std::ios::in);
		if (config_file_read_handle.is_open()) {
			std::string current_line;
			while (std::getline(config_file_read_handle, current_line)) {
				read_config_file_line(current_line);
			}
		}
		config_file_read_handle.close();
	}

	std::string ConfigManager::get_config_value_string(const std::string config_key) {
		return config_strings.contains(config_key) ? config_strings[config_key] : "";
	}

	float ConfigManager::get_config_value_float(const std::string config_key) {
		return config_floats.contains(config_key) ? config_floats[config_key] : 0.0f;
	}

	int ConfigManager::get_config_value_int(const std::string config_key) {
		return config_ints.contains(config_key) ? config_ints[config_key] : 0;
	}

	bool ConfigManager::get_config_value_bool(const std::string config_key) {
		return config_bools.contains(config_key) ? config_bools[config_key] : false;
	}

	void ConfigManager::set_config_value_string(const std::string config_key, std::string config_value) {
		config_strings[config_key] = config_value;
	}

	void ConfigManager::set_config_value_float(const std::string config_key, float config_value) {
		config_floats[config_key] = config_value;
	}

	void ConfigManager::set_config_value_int(const std::string config_key, int config_value) {
		config_ints[config_key] = config_value;
	}

	void ConfigManager::set_config_value_bool(const std::string config_key, bool config_value) {
		config_bools[config_key] = config_value;
	}

	void ConfigManager::read_config_file_line(std::string config_file_line) {
		size_t split_position = config_file_line.find_first_of(" ", 0);

		std::string config_key = config_file_line.substr(0, split_position);

		std::string untrimmed_config_string_value = config_file_line.substr(split_position + 1);
		std::string config_string_value = untrimmed_config_string_value.substr(untrimmed_config_string_value.find_first_not_of(" \n\r\t"));
		if (config_string_value.size() > 1 && config_string_value[0] == '"' && config_string_value[config_string_value.size() - 1] == '"') {
			set_config_value_string(config_key, config_string_value.substr(1, config_string_value.size() - 2));
		} else if (config_string_value == "true" || config_string_value == "false") {
			set_config_value_bool(config_key, config_string_value == "true");
		} else if (config_string_value.find_first_of('.') != std::string::npos) {
			set_config_value_float(config_key, std::stof(config_string_value, nullptr));
		} else {
			set_config_value_int(config_key, std::stoi(config_string_value, nullptr, 10));
		}
	}
}