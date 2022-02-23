#include "log.h"

namespace BD3GE {
	// Construct a log that writes to a custom logging location.
	// TODO: Need to ensure that the log directory and file and be created and written to, from scratch.
	Log::Log(std::string logFilePath) {
		log.open((logFilePath + DEFAULT_LOG_FILE).c_str(), std::ios::out);
	}

	Log::~Log() {
		log.close();
	}

	// Write a string entry to the log file and the appropriate standard stream, specifying the entry as an error, informative, or otherwise.
	void Log::write(BD3GE::LOG_TYPE loggingMode, std::string entry) {
		char log_time_formatted[32];
		time_t log_time = time(NULL);

		strftime(log_time_formatted, 32, "[%F %T]", localtime(&log_time));

		switch (loggingMode) {
			case BD3GE::LOG_TYPE::INFO:
				log << log_time_formatted << " " << LOG_PRINT_INFORMATION << entry << std::endl;
				std::cout << log_time_formatted << " " << LOG_PRINT_INFORMATION << entry << std::endl;

				break;
			case BD3GE::LOG_TYPE::ERR:
				log << log_time_formatted << " " << LOG_PRINT_ERROR << entry << std::endl;
				std::cerr << log_time_formatted << " " << LOG_PRINT_ERROR << entry << std::endl;

				break;
		}
	}
}