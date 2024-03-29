#ifndef BD3GE_LOG_H
#define BD3GE_LOG_H

#include <ctime>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
#include <direct.h>
#endif

#include "../system/constants.h"

namespace BD3GE {
	// TODO: Make this static?
	// Logs all output to log files, and standard streams if appropriate.
	class Log {
		public:
			enum class TYPE {
				INFO,
				ERR,
			};

					Log(std::string log_file_path = DEFAULT_RELATIVE_SYSTEM_DIRECTORY + DEFAULT_LOG_DIRECTORY + DEFAULT_LOG_FILE);
					~Log();
			void	write(Log::TYPE logging_mode, std::string entry);

		private:

			std::ofstream	log_stream;
	};
}

#endif // BD3GE_LOG_H