#ifndef BD3GE_WIN32_H
#define BD3GE_WIN32_H

#include <string>

#include <Windows.h>

namespace BD3GE {
	class Win32 {
		public:
			static int getQuantityUTF16Characters(std::string input);
			static void toUTF16(std::string input, LPWSTR output);
			static void toUTF16(std::string input, LPWSTR output, int length);
			static void displayMessageBox(std::string caption, std::string message);
	};
}

#endif // BD3GE_WIN32_H