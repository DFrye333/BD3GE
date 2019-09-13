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

namespace BD3GE
{
	// Logs all output to log files, and standard streams if appropriate.
	class Log
	{
		public:

					Log(std::string custom_log_directory = DEFAULT_SYSTEM_DIRECTORY + DEFAULT_LOG_DIRECTORY);
					~Log();
			void	write(BD3GE::LOG_TYPE outputMode, std::string entry);

		private:

			std::ofstream	m_log_stream;
	};
}

#endif // BD3GE_LOG_H
