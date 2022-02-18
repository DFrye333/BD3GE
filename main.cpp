#include "game/game.h"

#ifdef __linux__

int main() {
	BD3GE::Game game();
	game.startup();
	game.run();

	return 0;
}

#elif _WIN32

#include <Windows.h>

#include "os/win32.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#ifndef NDEBUG
	if (AttachConsole(GetCurrentProcessId()) || AllocConsole()) {
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}
#endif

	BD3GE::WinAPIWindow::WinAPIEntryArgs winAPIEntryArgs;
	winAPIEntryArgs.hInstance = hInstance;
	winAPIEntryArgs.hPrevInstance = hPrevInstance;
	winAPIEntryArgs.lpCmdLine = lpCmdLine;
	winAPIEntryArgs.nCmdShow = nCmdShow;
	BD3GE::Window* window = new BD3GE::WinAPIWindow(winAPIEntryArgs);

	BD3GE::Game game(window);
	game.run();

	return EXIT_SUCCESS;
}

#endif