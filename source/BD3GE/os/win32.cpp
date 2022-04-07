#include "win32.h"

namespace BD3GE {
	std::map<int, Input::KEY_CODE> WinAPI::key_code_map = {
		{ VK_BACK, Input::KEY_CODE::BACKSPACE },
		{ VK_TAB, Input::KEY_CODE::TAB },
		{ VK_ESCAPE, Input::KEY_CODE::ESCAPE },
		{ VK_SPACE, Input::KEY_CODE::SPACE },
		{ VK_OEM_7, Input::KEY_CODE::QUOTE },
		{ VK_OEM_COMMA, Input::KEY_CODE::COMMA },
		{ VK_OEM_MINUS, Input::KEY_CODE::MINUS },
		{ VK_OEM_PERIOD, Input::KEY_CODE::PERIOD },
		{ VK_OEM_2, Input::KEY_CODE::SLASH },
		{ 0x30, Input::KEY_CODE::NUM_0 },
		{ 0x31, Input::KEY_CODE::NUM_1 },
		{ 0x32, Input::KEY_CODE::NUM_2 },
		{ 0x33, Input::KEY_CODE::NUM_3 },
		{ 0x34, Input::KEY_CODE::NUM_4 },
		{ 0x35, Input::KEY_CODE::NUM_5 },
		{ 0x36, Input::KEY_CODE::NUM_6 },
		{ 0x37, Input::KEY_CODE::NUM_7 },
		{ 0x38, Input::KEY_CODE::NUM_8 },
		{ 0x39, Input::KEY_CODE::NUM_9 },
		{ VK_OEM_1, Input::KEY_CODE::SEMICOLON },
		{ VK_OEM_PLUS, Input::KEY_CODE::EQUAL },
		{ VK_OEM_4, Input::KEY_CODE::BRACKETLEFT },
		{ VK_OEM_5, Input::KEY_CODE::BACKSLASH },
		{ VK_OEM_6, Input::KEY_CODE::BRACKETRIGHT },
		{ VK_OEM_3, Input::KEY_CODE::GRAVE },
		{ 0x41, Input::KEY_CODE::A },
		{ 0x42, Input::KEY_CODE::B },
		{ 0x43, Input::KEY_CODE::C },
		{ 0x44, Input::KEY_CODE::D },
		{ 0x45, Input::KEY_CODE::E },
		{ 0x46, Input::KEY_CODE::F },
		{ 0x47, Input::KEY_CODE::G },
		{ 0x48, Input::KEY_CODE::H },
		{ 0x49, Input::KEY_CODE::I },
		{ 0x4A, Input::KEY_CODE::J },
		{ 0x4B, Input::KEY_CODE::K },
		{ 0x4C, Input::KEY_CODE::L },
		{ 0x4D, Input::KEY_CODE::M },
		{ 0x4E, Input::KEY_CODE::N },
		{ 0x4F, Input::KEY_CODE::O },
		{ 0x50, Input::KEY_CODE::P },
		{ 0x51, Input::KEY_CODE::Q },
		{ 0x52, Input::KEY_CODE::R },
		{ 0x53, Input::KEY_CODE::S },
		{ 0x54, Input::KEY_CODE::T },
		{ 0x55, Input::KEY_CODE::U },
		{ 0x56, Input::KEY_CODE::V },
		{ 0x57, Input::KEY_CODE::W },
		{ 0x58, Input::KEY_CODE::X },
		{ 0x59, Input::KEY_CODE::Y },
		{ 0x5A, Input::KEY_CODE::Z },
		{ VK_RETURN, Input::KEY_CODE::RETURN },
		{ VK_SNAPSHOT, Input::KEY_CODE::PRINTSCREEN },
		{ VK_SCROLL, Input::KEY_CODE::SCROLLLOCK },
		{ VK_PAUSE, Input::KEY_CODE::PAUSE },
		{ VK_INSERT, Input::KEY_CODE::INSERT },
		{ VK_HOME, Input::KEY_CODE::HOME },
		{ VK_PRIOR, Input::KEY_CODE::PAGEUP },
		{ VK_DELETE, Input::KEY_CODE::DEL },
		{ VK_END, Input::KEY_CODE::END },
		{ VK_NEXT, Input::KEY_CODE::PAGEDOWN },
		{ VK_UP, Input::KEY_CODE::UP },
		{ VK_LEFT, Input::KEY_CODE::LEFT },
		{ VK_DOWN, Input::KEY_CODE::DOWN },
		{ VK_RIGHT, Input::KEY_CODE::RIGHT },
		{ VK_SHIFT, Input::KEY_CODE::SHIFT },
		{ VK_LMENU, Input::KEY_CODE::ALTL },
		{ VK_RMENU, Input::KEY_CODE::ALTR },
		{ VK_LWIN, Input::KEY_CODE::SUPERL },
		{ VK_CAPITAL, Input::KEY_CODE::CAPSLOCK },
		{ VK_NUMLOCK, Input::KEY_CODE::NUMLOCK },
		{ VK_F1, Input::KEY_CODE::F1 },
		{ VK_F2, Input::KEY_CODE::F2 },
		{ VK_F3, Input::KEY_CODE::F3 },
		{ VK_F4, Input::KEY_CODE::F4 },
		{ VK_F5, Input::KEY_CODE::F5 },
		{ VK_F6, Input::KEY_CODE::F6 },
		{ VK_F7, Input::KEY_CODE::F7 },
		{ VK_F8, Input::KEY_CODE::F8 },
		{ VK_F9, Input::KEY_CODE::F9 },
		{ VK_F10, Input::KEY_CODE::F10 },
		{ VK_F11, Input::KEY_CODE::F11 },
		{ VK_F12, Input::KEY_CODE::F12 },
		{ VK_F13, Input::KEY_CODE::F13 },
		{ VK_F14, Input::KEY_CODE::F14 },
		{ VK_F15, Input::KEY_CODE::F15 },
		{ VK_F16, Input::KEY_CODE::F16 },
		{ VK_F17, Input::KEY_CODE::F17 },
		{ VK_F18, Input::KEY_CODE::F18 },
		{ VK_F19, Input::KEY_CODE::F19 },
		{ VK_F20, Input::KEY_CODE::F20 },
		{ VK_F21, Input::KEY_CODE::F21 },
		{ VK_F22, Input::KEY_CODE::F22 },
		{ VK_F23, Input::KEY_CODE::F23 },
		{ VK_F24, Input::KEY_CODE::F24 },
		{ VK_DIVIDE, Input::KEY_CODE::KP_DIVIDE },
		{ VK_MULTIPLY, Input::KEY_CODE::KP_MULTIPLY },
		{ VK_SUBTRACT, Input::KEY_CODE::KP_SUBTRACT },
		{ VK_ADD, Input::KEY_CODE::KP_ADD },
		{ VK_RETURN, Input::KEY_CODE::KP_ENTER },
		{ VK_DECIMAL, Input::KEY_CODE::KP_DECIMAL },
		{ VK_NUMPAD0, Input::KEY_CODE::KP_0 },
		{ VK_NUMPAD1, Input::KEY_CODE::KP_1 },
		{ VK_NUMPAD2, Input::KEY_CODE::KP_2 },
		{ VK_NUMPAD3, Input::KEY_CODE::KP_3 },
		{ VK_NUMPAD4, Input::KEY_CODE::KP_4 },
		{ VK_NUMPAD5, Input::KEY_CODE::KP_5 },
		{ VK_NUMPAD6, Input::KEY_CODE::KP_6 },
		{ VK_NUMPAD7, Input::KEY_CODE::KP_7 },
		{ VK_NUMPAD8, Input::KEY_CODE::KP_8 },
		{ VK_NUMPAD9, Input::KEY_CODE::KP_9 },
		{ VK_LBUTTON, Input::KEY_CODE::MOUSE_LEFTBUTTON },
		{ VK_RBUTTON, Input::KEY_CODE::MOUSE_RIGHTBUTTON },
		{ VK_MBUTTON, Input::KEY_CODE::MOUSE_MIDDLEBUTTON },
		{ VK_XBUTTON1, Input::KEY_CODE::MOUSE_X1BUTTON },
		{ VK_XBUTTON2, Input::KEY_CODE::MOUSE_X2BUTTON },
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

		BD3GE::Input::InputEvent input_event = {};
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
			case WM_LBUTTONDOWN: input_event.key_state_map.insert({ Input::KEY_CODE::MOUSE_LEFTBUTTON, true }); break;
			case WM_RBUTTONDOWN: input_event.key_state_map.insert({ Input::KEY_CODE::MOUSE_RIGHTBUTTON, true }); break;
			case WM_MBUTTONDOWN: input_event.key_state_map.insert({ Input::KEY_CODE::MOUSE_MIDDLEBUTTON, true }); break;
			case WM_XBUTTONDOWN:
				// TODO: Add support for context-awareness (i.e. knowing if other buttons are being used as this event comes in).
				//std::cout << std::hex << GET_KEYSTATE_WPARAM(w_param) << std::endl;
				input_event.key_state_map.insert({ GET_XBUTTON_WPARAM(w_param) == XBUTTON1 ? Input::KEY_CODE::MOUSE_X1BUTTON : Input::KEY_CODE::MOUSE_X2BUTTON, true }); break;
			case WM_LBUTTONUP: input_event.key_state_map.insert({ Input::KEY_CODE::MOUSE_LEFTBUTTON, false }); break;
			case WM_RBUTTONUP: input_event.key_state_map.insert({ Input::KEY_CODE::MOUSE_RIGHTBUTTON, false }); break;
			case WM_MBUTTONUP: input_event.key_state_map.insert({ Input::KEY_CODE::MOUSE_MIDDLEBUTTON, false }); break;
			case WM_XBUTTONUP:
				// TODO: Add support for context-awareness (i.e. knowing if other buttons are being used as this event comes in).
				//std::cout << std::hex << GET_KEYSTATE_WPARAM(w_param) << std::endl;
				input_event.key_state_map.insert({ GET_XBUTTON_WPARAM(w_param) == XBUTTON1 ? Input::KEY_CODE::MOUSE_X1BUTTON : Input::KEY_CODE::MOUSE_X2BUTTON, false }); break;
			case WM_MOUSEWHEEL: input_event.key_state_map.insert({ GET_WHEEL_DELTA_WPARAM(w_param) > 0 ? Input::KEY_CODE::MOUSE_WHEELUP : Input::KEY_CODE::MOUSE_WHEELDOWN, true }); break;
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

	WinAPIWindow::WinAPIWindow(BD3GE::WinAPIWindow::WinAPIEntryArgs* winAPIEntryArgs) {
		std::string windowClassName = "BD3GEWindowClass";
		wchar_t g_szClassName[32];
		BD3GE::WinAPI::to_utf16(windowClassName, g_szClassName);

		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = winAPIEntryArgs->instance;
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

		unsigned int config_window_width = ConfigManager::get_config_value_int("window_width");
		unsigned int config_window_height = ConfigManager::get_config_value_int("window_height");
		std::string config_window_title = ConfigManager::get_config_value_string("window_title");

		wchar_t window_title[256];
		BD3GE::WinAPI::to_utf16(config_window_title.size() > 0 ? config_window_title : BD3GE::DEFAULT_WINDOW_TITLE, window_title);

		window_proc_data = new BD3GE::WinAPIWindow::WindowProcData;
		window_proc_data->window = this;

		window_handle = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			g_szClassName,
			window_title,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			config_window_width > 0 ? config_window_width : BD3GE::DEFAULT_WINDOW_WIDTH,
			config_window_height > 0 ? config_window_height : BD3GE::DEFAULT_WINDOW_HEIGHT,
			NULL, NULL, winAPIEntryArgs->instance,
			window_proc_data
		);

		if (window_handle == nullptr) {
			BD3GE::WinAPI::display_message_box(window_handle, "Error!", "Window Creation Failed!");
			return;
		}

		ShowWindow(window_handle, winAPIEntryArgs->command_show);
		UpdateWindow(window_handle);

		std::cout << "Command line arguments: ";
		std::cout << winAPIEntryArgs->command_line << std::endl;

		/*std::string command_line = std::string(winAPIEntryArgs->command_line);
		unsigned short split_index = command_line.find(' ');
		int width = atoi(command_line.substr(0, split_index).c_str());
		int height = atoi(command_line.substr(split_index).c_str());
		BD3GE::WinAPI::resize_window(window_handle, width, height);*/
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

	void WinAPIWindow::push_input_event(Input::InputEvent input_event) {
		input_queue.push(input_event);
	}

	Message<Input::InputEvent> WinAPIWindow::pull_input_event() {
		Message<Input::InputEvent> input_message = Message<Input::InputEvent>();

		if (!input_queue.empty()) {
			input_message = input_queue.front();
			input_queue.pop();
		}

		return input_message;
	}

	void WinAPIWindow::push_reshape_event(Window::ReshapeEvent reshape_event) {
		reshape_queue.push(reshape_event);
	}

	Message<Window::ReshapeEvent> WinAPIWindow::pull_reshape_event() {
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

	WinAPITimer::WinAPITimer(std::string name) : WinAPITimer(name, 0) {}

	WinAPITimer::WinAPITimer(std::string name, uint64_t timer_frequency_Hz) : Timer(name, timer_frequency_Hz) {}

	void WinAPITimer::start() {
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		system_frequency_Hz = frequency.QuadPart;

		start_stamp = get_current_timestamp();
		lap_stamp = start_stamp;

		is_running = true;
	}

	void WinAPITimer::pause() {
		fresh_pause_duration = get_current_timestamp();

		is_running = false;
	}

	void WinAPITimer::unpause() {
		fresh_pause_duration = get_current_timestamp() - fresh_pause_duration;
		total_pause_duration += fresh_pause_duration;

		is_running = true;
	}

	void WinAPITimer::toggle_pause() {
		is_running = !is_running;
	}

	uint64_t WinAPITimer::elapsed() {
		return get_current_timestamp() - total_pause_duration - start_stamp;
	}

	bool WinAPITimer::is_due() {
		bool is_due = false;

		if (is_running && timer_frequency_Hz > 0) {
			uint64_t current_stamp = get_current_timestamp();
			uint64_t elapsed_since_last_check = current_stamp - lap_stamp;
			if (fresh_pause_duration > 0) {
				elapsed_since_last_check -= fresh_pause_duration;
				fresh_pause_duration = 0;
			}

			if (elapsed_since_last_check >= ((1.0f / timer_frequency_Hz) * 1000)) {
				lap_stamp = current_stamp;
				is_due = true;
			}
		}

		return is_due;
	}

	uint64_t WinAPITimer::get_current_timestamp() {
		LARGE_INTEGER current_timestamp;
		QueryPerformanceCounter(&current_timestamp);
		return (current_timestamp.QuadPart * 1000) / system_frequency_Hz;
	}
}