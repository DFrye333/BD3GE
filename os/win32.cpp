#include "win32.h"

namespace BD3GE {
	int Win32::getQuantityUTF16Characters(std::string input) {
		return MultiByteToWideChar(CP_ACP, 0, input.c_str(), -1, nullptr, 0);
	}

	void Win32::toUTF16(std::string input, LPWSTR output) {
		toUTF16(input, output, 4096);
	}

	void Win32::toUTF16(std::string input, LPWSTR output, int length) {
		MultiByteToWideChar(CP_ACP, 0, input.c_str(), -1, output, length);
	}

	void Win32::displayMessageBox(std::string caption, std::string message) {
		wchar_t caption_utf16[256];
		wchar_t message_utf16[4096];
		
		toUTF16(caption, caption_utf16, 256);
		toUTF16(message, message_utf16, 4096);

		MessageBox(NULL, message_utf16, caption_utf16, MB_ICONEXCLAMATION | MB_OK);
	}
}