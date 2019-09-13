#include "log.h"

namespace BD3GE
{
	/*
	 * 	Log class
	 */

	// Construct a log that writes to a custom logging location.
	Log::Log(std::string custom_log_directory)
	{
		DIR* custom_log_directory_stream = opendir(custom_log_directory.c_str());
		if (!custom_log_directory_stream)
		{
// TODO: Ugly! Create a class to handle filesystem stuff.
#ifdef __linux__
			if (-1 == mkdir(custom_log_directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH))
#elif _WIN32
			if (-1 == _mkdir(custom_log_directory.c_str()))
#endif
			{
				std::cerr << LOG_PRINT_ERROR << "Log directory creation failure." << std::endl;
			}
		}

		m_log_stream.open((custom_log_directory + DEFAULT_LOG_FILE).c_str(), std::ios::out);

		closedir(custom_log_directory_stream);
	}

	// Destruct the logger by closing the log file.
	Log::~Log()
	{
		m_log_stream.close();
	}

	// Write a string entry to the log file and the appropriate standard stream, specifying the entry as an error, informative, or otherwise.
	void Log::write(BD3GE::LOG_TYPE loggingMode, std::string entry)
	{
		char log_time_formatted[32];
		time_t log_time = time(NULL);

		strftime(log_time_formatted, 32, "[%F %T]", localtime(&log_time));

		switch (loggingMode)
		{
			case BD3GE::LOG_TYPE::INFO:
			{
				m_log_stream << log_time_formatted << " " << LOG_PRINT_INFORMATION << entry << std::endl;
				std::cout << log_time_formatted << " " << LOG_PRINT_INFORMATION << entry << std::endl;

				break;
			}

			case BD3GE::LOG_TYPE::ERR:
			{
				m_log_stream << log_time_formatted << " " << LOG_PRINT_ERROR << entry << std::endl;
				std::cerr << log_time_formatted << " " << LOG_PRINT_ERROR << entry << std::endl;

				break;
			}
		}
	}
}