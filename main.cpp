#include "system/game.h"

#ifdef __linux__

int main() {
	BD3GE::Game game();
	game.startup();
	game.run();
	game.shutdown();

	return 0;
}

#elif _WIN32

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if (AttachConsole(GetCurrentProcessId()) || AllocConsole()) {
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}

	BD3GE::WinAPIWindow::WinAPIEntryArgs winAPIEntryArgs;
	winAPIEntryArgs.hInstance = hInstance;
	winAPIEntryArgs.hPrevInstance = hPrevInstance;
	winAPIEntryArgs.lpCmdLine = lpCmdLine;
	winAPIEntryArgs.nCmdShow = nCmdShow;

	BD3GE::Game game(new BD3GE::WinAPIWindow(winAPIEntryArgs));
	game.run();
	game.shutdown();

	return 0;
}

#endif