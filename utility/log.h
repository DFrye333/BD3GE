#ifndef LOG_H
#define LOG_H

#include <ctime>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../system/constants.h"

namespace BD3GE
{
	// Logs all output to log files, and standard streams if appropriate.
	class Log
	{
		public:

					Log();
					Log(std::string custom_log_directory);
					~Log();
			void	write(std::string entry, BD3GE::LOG_OUTPUT output);

		private:

			std::ofstream	m_log_stream;
	};
}

#endif // LOG_H
