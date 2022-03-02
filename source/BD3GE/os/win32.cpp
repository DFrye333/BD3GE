#include "win32.h"

namespace BD3GE {
	std::map<int, BD3GE::KEY_CODE> WinAPI::key_code_map = {
		{ VK_BACK, BD3GE::KEY_CODE::BACKSPACE },
		{ VK_TAB, BD3GE::KEY_CODE::TAB },
		{ VK_ESCAPE, BD3GE::KEY_CODE::ESCAPE },
		{ VK_SPACE, BD3GE::KEY_CODE::SPACE },
		{ VK_OEM_7, BD3GE::KEY_CODE::QUOTE },
		{ VK_OEM_COMMA, BD3GE::KEY_CODE::COMMA },
		{ VK_OEM_MINUS, BD3GE::KEY_CODE::MINUS },
		{ VK_OEM_PERIOD, BD3GE::KEY_CODE::PERIOD },
		{ VK_OEM_2, BD3GE::KEY_CODE::SLASH },
		{ 0x30, BD3GE::KEY_CODE::NUM_0 },
		{ 0x31, BD3GE::KEY_CODE::NUM_1 },
		{ 0x32, BD3GE::KEY_CODE::NUM_2 },
		{ 0x33, BD3GE::KEY_CODE::NUM_3 },
		{ 0x34, BD3GE::KEY_CODE::NUM_4 },
		{ 0x35, BD3GE::KEY_CODE::NUM_5 },
		{ 0x36, BD3GE::KEY_CODE::NUM_6 },
		{ 0x37, BD3GE::KEY_CODE::NUM_7 },
		{ 0x38, BD3GE::KEY_CODE::NUM_8 },
		{ 0x39, BD3GE::KEY_CODE::NUM_9 },
		{ VK_OEM_1, BD3GE::KEY_CODE::SEMICOLON },
		{ VK_OEM_PLUS, BD3GE::KEY_CODE::EQUAL },
		{ VK_OEM_4, BD3GE::KEY_CODE::BRACKETLEFT },
		{ VK_OEM_5, BD3GE::KEY_CODE::BACKSLASH },
		{ VK_OEM_6, BD3GE::KEY_CODE::BRACKETRIGHT },
		{ VK_OEM_3, BD3GE::KEY_CODE::GRAVE },
		{ 0x41, BD3GE::KEY_CODE::A },
		{ 0x42, BD3GE::KEY_CODE::B },
		{ 0x43, BD3GE::KEY_CODE::C },
		{ 0x44, BD3GE::KEY_CODE::D },
		{ 0x45, BD3GE::KEY_CODE::E },
		{ 0x46, BD3GE::KEY_CODE::F },
		{ 0x47, BD3GE::KEY_CODE::G },
		{ 0x48, BD3GE::KEY_CODE::H },
		{ 0x49, BD3GE::KEY_CODE::I },
		{ 0x4A, BD3GE::KEY_CODE::J },
		{ 0x4B, BD3GE::KEY_CODE::K },
		{ 0x4C, BD3GE::KEY_CODE::L },
		{ 0x4D, BD3GE::KEY_CODE::M },
		{ 0x4E, BD3GE::KEY_CODE::N },
		{ 0x4F, BD3GE::KEY_CODE::O },
		{ 0x50, BD3GE::KEY_CODE::P },
		{ 0x51, BD3GE::KEY_CODE::Q },
		{ 0x52, BD3GE::KEY_CODE::R },
		{ 0x53, BD3GE::KEY_CODE::S },
		{ 0x54, BD3GE::KEY_CODE::T },
		{ 0x55, BD3GE::KEY_CODE::U },
		{ 0x56, BD3GE::KEY_CODE::V },
		{ 0x57, BD3GE::KEY_CODE::W },
		{ 0x58, BD3GE::KEY_CODE::X },
		{ 0x59, BD3GE::KEY_CODE::Y },
		{ 0x5A, BD3GE::KEY_CODE::Z },
		{ VK_RETURN, BD3GE::KEY_CODE::RETURN },
		{ VK_SNAPSHOT, BD3GE::KEY_CODE::PRINTSCREEN },
		{ VK_SCROLL, BD3GE::KEY_CODE::SCROLLLOCK },
		{ VK_PAUSE, BD3GE::KEY_CODE::PAUSE },
		{ VK_INSERT, BD3GE::KEY_CODE::INSERT },
		{ VK_HOME, BD3GE::KEY_CODE::HOME },
		{ VK_PRIOR, BD3GE::KEY_CODE::PAGEUP },
		{ VK_DELETE, BD3GE::KEY_CODE::DEL },
		{ VK_END, BD3GE::KEY_CODE::END },
		{ VK_NEXT, BD3GE::KEY_CODE::PAGEDOWN },
		{ VK_UP, BD3GE::KEY_CODE::UP },
		{ VK_LEFT, BD3GE::KEY_CODE::LEFT },
		{ VK_DOWN, BD3GE::KEY_CODE::DOWN },
		{ VK_RIGHT, BD3GE::KEY_CODE::RIGHT },
		{ VK_SHIFT, BD3GE::KEY_CODE::SHIFT },
		{ VK_LMENU, BD3GE::KEY_CODE::ALTL },
		{ VK_RMENU, BD3GE::KEY_CODE::ALTR },
		{ VK_LWIN, BD3GE::KEY_CODE::SUPERL },
		{ VK_CAPITAL, BD3GE::KEY_CODE::CAPSLOCK },
		{ VK_NUMLOCK, BD3GE::KEY_CODE::NUMLOCK },
		{ VK_F1, BD3GE::KEY_CODE::F1 },
		{ VK_F2, BD3GE::KEY_CODE::F2 },
		{ VK_F3, BD3GE::KEY_CODE::F3 },
		{ VK_F4, BD3GE::KEY_CODE::F4 },
		{ VK_F5, BD3GE::KEY_CODE::F5 },
		{ VK_F6, BD3GE::KEY_CODE::F6 },
		{ VK_F7, BD3GE::KEY_CODE::F7 },
		{ VK_F8, BD3GE::KEY_CODE::F8 },
		{ VK_F9, BD3GE::KEY_CODE::F9 },
		{ VK_F10, BD3GE::KEY_CODE::F10 },
		{ VK_F11, BD3GE::KEY_CODE::F11 },
		{ VK_F12, BD3GE::KEY_CODE::F12 },
		{ VK_F13, BD3GE::KEY_CODE::F13 },
		{ VK_F14, BD3GE::KEY_CODE::F14 },
		{ VK_F15, BD3GE::KEY_CODE::F15 },
		{ VK_F16, BD3GE::KEY_CODE::F16 },
		{ VK_F17, BD3GE::KEY_CODE::F17 },
		{ VK_F18, BD3GE::KEY_CODE::F18 },
		{ VK_F19, BD3GE::KEY_CODE::F19 },
		{ VK_F20, BD3GE::KEY_CODE::F20 },
		{ VK_F21, BD3GE::KEY_CODE::F21 },
		{ VK_F22, BD3GE::KEY_CODE::F22 },
		{ VK_F23, BD3GE::KEY_CODE::F23 },
		{ VK_F24, BD3GE::KEY_CODE::F24 },
		{ VK_DIVIDE, BD3GE::KEY_CODE::KP_DIVIDE },
		{ VK_MULTIPLY, BD3GE::KEY_CODE::KP_MULTIPLY },
		{ VK_SUBTRACT, BD3GE::KEY_CODE::KP_SUBTRACT },
		{ VK_ADD, BD3GE::KEY_CODE::KP_ADD },
		{ VK_RETURN, BD3GE::KEY_CODE::KP_ENTER },
		{ VK_DECIMAL, BD3GE::KEY_CODE::KP_DECIMAL },
		{ VK_NUMPAD0, BD3GE::KEY_CODE::KP_0 },
		{ VK_NUMPAD1, BD3GE::KEY_CODE::KP_1 },
		{ VK_NUMPAD2, BD3GE::KEY_CODE::KP_2 },
		{ VK_NUMPAD3, BD3GE::KEY_CODE::KP_3 },
		{ VK_NUMPAD4, BD3GE::KEY_CODE::KP_4 },
		{ VK_NUMPAD5, BD3GE::KEY_CODE::KP_5 },
		{ VK_NUMPAD6, BD3GE::KEY_CODE::KP_6 },
		{ VK_NUMPAD7, BD3GE::KEY_CODE::KP_7 },
		{ VK_NUMPAD8, BD3GE::KEY_CODE::KP_8 },
		{ VK_NUMPAD9, BD3GE::KEY_CODE::KP_9 },
		{ VK_LBUTTON, BD3GE::KEY_CODE::MOUSE_LEFTBUTTON },
		{ VK_RBUTTON, BD3GE::KEY_CODE::MOUSE_RIGHTBUTTON },
		{ VK_MBUTTON, BD3GE::KEY_CODE::MOUSE_MIDDLEBUTTON },
		{ VK_XBUTTON1, BD3GE::KEY_CODE::MOUSE_X1BUTTON },
		{ VK_XBUTTON2, BD3GE::KEY_CODE::MOUSE_X2BUTTON },
	};

	int WinAPI::get_quantity_utf16_characters(std::string input) {
		return MultiByteToWideChar(CP_ACP, 0, input.c_str(), -1, nullptr, 0);
	}

	void WinAPI::to_utf16(std::string input, LPWSTR output) {
		to_utf16(input, output, 4096);
	}

	void WinAPI::to_utf16(std::string input, LPWSTR output, int length) {
		MultiByteToWideChar(CP_ACP, 0, input.c_str(), -1, output, length);
	}

	void WinAPI::display_message_box(HWND window_handle, std::string caption, std::string message) {
		wchar_t caption_utf16[256];
		wchar_t message_utf16[4096];
		
		to_utf16(caption, caption_utf16, 256);
		to_utf16(message, message_utf16, 4096);

		MessageBox(window_handle, message_utf16, caption_utf16, MB_ICONEXCLAMATION | MB_OK);
	}

	void WinAPI::resize_window(HWND window_handle, int width, int height) {
		MoveWindow(window_handle, 0, 0, width, height, true);
	}

	std::string WinAPI::get_environment_variable(std::string environment_variable_name) {
		char* environment_variable = getenv(environment_variable_name.c_str());
		return std::string(environment_variable);
	}

	bool WinAPI::make_directory(std::string directory_path, std::string& result) {
		WIN32_FILE_ATTRIBUTE_DATA file_attributes = {};
		if (does_directory_exist(directory_path, &file_attributes)) {
			result = file_attributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? "Directory already exists at path: " + directory_path : result = "File already exists at path: " + directory_path;
			return false;
		}

		int result_code = _mkdir(directory_path.c_str());
		result = (result_code == 0 ? "Directory creation success at: " : "Directory creation failure at: ") + directory_path;

		return result_code == 0;
	}

	bool WinAPI::does_directory_exist(std::string directory_path) {
		WIN32_FILE_ATTRIBUTE_DATA file_attributes = {};
		return does_directory_exist(directory_path, &file_attributes);
	}

	bool WinAPI::does_directory_exist(std::string directory_path, WIN32_FILE_ATTRIBUTE_DATA* file_attributes) {
		if (0 == get_file_info(directory_path, file_attributes)) {
			// TODO: Handle errors.
			//DWORD error = GetLastError();
			//return "";
		}

		unsigned long long path_creation_time = (unsigned long long)((unsigned long long)(file_attributes->ftCreationTime.dwHighDateTime) << 8 * sizeof(unsigned long) | file_attributes->ftCreationTime.dwLowDateTime);
		return 0 != path_creation_time;
	}

	BOOL WinAPI::get_file_info(std::string& absolute_file_path, WIN32_FILE_ATTRIBUTE_DATA* file_attributes) {
		wchar_t absolute_file_path_utf16[260];
		to_utf16(absolute_file_path, absolute_file_path_utf16);
		return GetFileAttributesEx(absolute_file_path_utf16, GET_FILEEX_INFO_LEVELS::GetFileExInfoStandard, file_attributes);
	}

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT message_code, WPARAM w_param, LPARAM l_param) {
		BD3GE::WinAPIWindow::WindowProcData* data = nullptr;
		LONG_PTR data_long_ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (data_long_ptr != 0) {
			data = reinterpret_cast<BD3GE::WinAPIWindow::WindowProcData*>(data_long_ptr);
		}

		BD3GE::Window::InputEvent input_event = {};
		switch (message_code) {
			case WM_CREATE:
				{
					CREATESTRUCT* data_creation = reinterpret_cast<CREATESTRUCT*>(l_param);
					data = reinterpret_cast<BD3GE::WinAPIWindow::WindowProcData*>(data_creation->lpCreateParams);
					SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)data);

					HDC display_context = GetDC(hwnd);

					PIXELFORMATDESCRIPTOR pixel_format_descriptor = {};
					pixel_format_descriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
					pixel_format_descriptor.nVersion = 1;
					pixel_format_descriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
					pixel_format_descriptor.iPixelType = PFD_TYPE_RGBA;
					pixel_format_descriptor.cColorBits = 8;
					pixel_format_descriptor.cDepthBits = 24;
					pixel_format_descriptor.cAccumBits = 0;
					pixel_format_descriptor.cStencilBits = 0;

					int pixel_format = ChoosePixelFormat(display_context, &pixel_format_descriptor);
					SetPixelFormat(display_context, pixel_format, &pixel_format_descriptor);

					HGLRC render_context = wglCreateContext(display_context);
					wglMakeCurrent(display_context, render_context);

					ReleaseDC(hwnd, display_context);
				}

				data->window->set_window_exists(true);

				break;
			case WM_PAINT:
				PAINTSTRUCT paint_struct;
				BeginPaint(hwnd, &paint_struct);
				EndPaint(hwnd, &paint_struct);
				break;
			case WM_KEYDOWN: input_event.key_state_map.insert({ WinAPI::key_code_map[w_param], true }); break;
			case WM_KEYUP: input_event.key_state_map.insert({ WinAPI::key_code_map[w_param], false }); break;
			case WM_LBUTTONDOWN: input_event.key_state_map.insert({ BD3GE::KEY_CODE::MOUSE_LEFTBUTTON, true }); break;
			case WM_RBUTTONDOWN: input_event.key_state_map.insert({ BD3GE::KEY_CODE::MOUSE_RIGHTBUTTON, true }); break;
			case WM_MBUTTONDOWN: input_event.key_state_map.insert({ BD3GE::KEY_CODE::MOUSE_MIDDLEBUTTON, true }); break;
			case WM_XBUTTONDOWN:
				// TODO: Add support for context-awareness (i.e. knowing if other buttons are being used as this event comes in).
				//std::cout << std::hex << GET_KEYSTATE_WPARAM(w_param) << std::endl;
				input_event.key_state_map.insert({ GET_XBUTTON_WPARAM(w_param) == XBUTTON1 ? BD3GE::KEY_CODE::MOUSE_X1BUTTON : BD3GE::KEY_CODE::MOUSE_X2BUTTON, true }); break;
			case WM_LBUTTONUP: input_event.key_state_map.insert({ BD3GE::KEY_CODE::MOUSE_LEFTBUTTON, false }); break;
			case WM_RBUTTONUP: input_event.key_state_map.insert({ BD3GE::KEY_CODE::MOUSE_RIGHTBUTTON, false }); break;
			case WM_MBUTTONUP: input_event.key_state_map.insert({ BD3GE::KEY_CODE::MOUSE_MIDDLEBUTTON, false }); break;
			case WM_XBUTTONUP:
				// TODO: Add support for context-awareness (i.e. knowing if other buttons are being used as this event comes in).
				//std::cout << std::hex << GET_KEYSTATE_WPARAM(w_param) << std::endl;
				input_event.key_state_map.insert({ GET_XBUTTON_WPARAM(w_param) == XBUTTON1 ? BD3GE::KEY_CODE::MOUSE_X1BUTTON : BD3GE::KEY_CODE::MOUSE_X2BUTTON, false }); break;
			case WM_MOUSEWHEEL: input_event.key_state_map.insert({ GET_WHEEL_DELTA_WPARAM(w_param) > 0 ? BD3GE::KEY_CODE::MOUSE_WHEELUP : BD3GE::KEY_CODE::MOUSE_WHEELDOWN, true }); break;
			case WM_MOUSEMOVE:
				{
					input_event.mouse_position.first = LOWORD(l_param); // X
					input_event.mouse_position.second = HIWORD(l_param); // Y

					// Clamps cursor within the window.
					RECT window;
					GetWindowRect(hwnd, &window);
					POINT cursor;
					GetCursorPos(&cursor);
					short MARGIN = 200;
					short TITLE_BAR_HEIGHT = 50;
					if (cursor.x < window.left + MARGIN) { SetCursorPos(window.right - MARGIN, cursor.y); }
					if (cursor.x > window.right - MARGIN) { SetCursorPos(window.left + MARGIN, cursor.y); }
					if (cursor.y < window.top + MARGIN + TITLE_BAR_HEIGHT) { SetCursorPos(cursor.x, window.bottom - MARGIN); }
					if (cursor.y > window.bottom - MARGIN) { SetCursorPos(cursor.x, window.top + MARGIN + TITLE_BAR_HEIGHT); }
				}
				break;
			case WM_SIZE:
				{
					BD3GE::Window::ReshapeEvent reshape_event = {};
					reshape_event.width = LOWORD(l_param);
					reshape_event.height = HIWORD(l_param);

					data->window->push_reshape_event(reshape_event);
					break;
				}
			case WM_CLOSE: DestroyWindow(hwnd); break;
			case WM_DESTROY: PostQuitMessage(0); data->window->set_window_exists(false); break;
			default: return DefWindowProc(hwnd, message_code, w_param, l_param);
		}

		data->window->push_input_event(input_event);

		return EXIT_SUCCESS;
	}

	WinAPIWindow::WinAPIWindow(BD3GE::WinAPIWindow::WinAPIEntryArgs winAPIEntryArgs) {
		std::string windowClassName = "BD3GEWindowClass";
		wchar_t g_szClassName[32];
		BD3GE::WinAPI::to_utf16(windowClassName, g_szClassName);

		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = winAPIEntryArgs.hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = g_szClassName;
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wc)) {
			BD3GE::WinAPI::display_message_box(window_handle, "Error!", "Window Registration Failed!");
			return;
		}

		wchar_t window_title[256];
		BD3GE::WinAPI::to_utf16(BD3GE::WINDOW_TITLE, window_title);

		window_proc_data = new BD3GE::WinAPIWindow::WindowProcData;
		window_proc_data->window = this;

		window_handle = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			g_szClassName,
			window_title,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, BD3GE::WINDOW_WIDTH, BD3GE::WINDOW_HEIGHT,
			NULL, NULL, winAPIEntryArgs.hInstance,
			window_proc_data
		);

		if (window_handle == nullptr) {
			BD3GE::WinAPI::display_message_box(window_handle, "Error!", "Window Creation Failed!");
			return;
		}

		ShowWindow(window_handle, winAPIEntryArgs.nCmdShow);
		UpdateWindow(window_handle);

		std::cout << "Command line arguments: ";
		std::cout << winAPIEntryArgs.lpCmdLine << std::endl;
	}

	WinAPIWindow::~WinAPIWindow() {}

	bool WinAPIWindow::get_window_exists() {
		return does_window_exist;
	}

	void WinAPIWindow::set_window_exists(bool does_window_exist) {
		this->does_window_exist = does_window_exist;
	}

	void WinAPIWindow::message_listener(void) {
		MSG msg;
		if (PeekMessage(&msg, window_handle, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WinAPIWindow::swap_buffers(void) {
		display_context = GetDC(window_handle);
		SwapBuffers(display_context);
		ReleaseDC(window_handle, display_context);
	}

	void WinAPIWindow::push_input_event(Window::InputEvent input_event) {
		input_queue.push(input_event);
	}

	Message<Window::InputEvent> WinAPIWindow::pull_input_event(void) {
		Message<Window::InputEvent> input_message = Message<Window::InputEvent>();

		if (!input_queue.empty()) {
			input_message = input_queue.front();
			input_queue.pop();
		}

		return input_message;
	}

	void WinAPIWindow::push_reshape_event(Window::ReshapeEvent reshape_event) {
		reshape_queue.push(reshape_event);
	}

	Message<Window::ReshapeEvent> WinAPIWindow::pull_reshape_event(void) {
		Message<Window::ReshapeEvent> reshape_message = Message<Window::ReshapeEvent>();

		if (!reshape_queue.empty()) {
			reshape_message = reshape_queue.front();
			reshape_queue.pop();
		}

		return reshape_message;
	}

	void WinAPIWindow::set_mouse_cursor_visibility(bool should_be_visible) {
		CURSORINFO mouseCursorInfo = {};
		mouseCursorInfo.cbSize = sizeof(CURSORINFO);
		GetCursorInfo(&mouseCursorInfo);
		if (should_be_visible && !(mouseCursorInfo.flags & CURSOR_SHOWING)) {
			ShowCursor(true);
		}
		else if (!should_be_visible && (mouseCursorInfo.flags & CURSOR_SHOWING)) {
			ShowCursor(false);
		}
	}

	WinAPITimer::WinAPITimer(std::string name, uint64_t timer_frequency_Hz) {
		this->name = name;
		this->timer_frequency_Hz = timer_frequency_Hz;
	}

	WinAPITimer::~WinAPITimer() {}

	void WinAPITimer::start() {
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		system_frequency_Hz = frequency.QuadPart;

		LARGE_INTEGER current_count;
		QueryPerformanceCounter(&current_count);

		start_stamp = (current_count.QuadPart * 1000) / system_frequency_Hz;

		is_running = true;
	}

	bool WinAPITimer::is_due() {
		bool is_due = false;

		if (is_running) {
			LARGE_INTEGER current_count;
			QueryPerformanceCounter(&current_count);
			uint64_t current_stamp = (current_count.QuadPart * 1000) / system_frequency_Hz;

			if ((current_stamp - start_stamp) >= ((1.0f / timer_frequency_Hz) * 1000)) {
				start_stamp = current_stamp;
				is_due = true;
			}
		}

		return is_due;
	}
}