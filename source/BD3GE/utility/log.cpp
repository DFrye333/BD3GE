#include "log.h"

namespace BD3GE {
	// TODO: Need to ensure that the log directory and file and be created and written to, from scratch.
	// Construct a log that writes to a custom logging location.
	Log::Log(std::string log_file_path) {
		log_stream.open((log_file_path + DEFAULT_LOG_FILE).c_str(), std::ios::out);
	}

	Log::~Log() {
		log_stream.close();
	}

	// Write a string entry to the log file and the appropriate standard stream, specifying the entry as an error, informative, or otherwise.
	void Log::write(Log::TYPE logging_mode, std::string entry) {
		char log_time_formatted[32];
		time_t log_time = time(NULL);

		strftime(log_time_formatted, 32, "[%F %T]", localtime(&log_time));

		switch (logging_mode) {
			case Log::TYPE::INFO:
				log_stream << log_time_formatted << " " << LOG_PRINT_INFORMATION << entry << std::endl;
				std::cout << log_time_formatted << " " << LOG_PRINT_INFORMATION << entry << std::endl;

				break;
			case Log::TYPE::ERR:
				log_stream << log_time_formatted << " " << LOG_PRINT_ERROR << entry << std::endl;
				std::cerr << log_time_formatted << " " << LOG_PRINT_ERROR << entry << std::endl;

				break;
		}
	}
}