#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE dll_instance, DWORD reason, LPVOID reserved) {
	switch (reason) {
		case DLL_PROCESS_ATTACH:
			return true;
			break;
	}
}