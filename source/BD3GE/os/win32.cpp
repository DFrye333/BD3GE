#include "win32.h"

namespace BD3GE {
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
			case WM_KEYDOWN: input_event.key_state_map.insert({ w_param, true }); break;
			case WM_KEYUP: input_event.key_state_map.insert({ w_param, false }); break;
			case WM_LBUTTONDOWN: input_event.key_state_map.insert({ VK_LBUTTON, true }); break;
			case WM_RBUTTONDOWN: input_event.key_state_map.insert({ VK_RBUTTON, true }); break;
			case WM_MBUTTONDOWN: input_event.key_state_map.insert({ VK_MBUTTON, true }); break;
			case WM_XBUTTONDOWN:
				// TODO: Add support for context-awareness (i.e. knowing if other buttons are being used as this event comes in).
				//std::cout << std::hex << GET_KEYSTATE_WPARAM(w_param) << std::endl;
				input_event.key_state_map.insert({ GET_XBUTTON_WPARAM(w_param) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2, true }); break;
			case WM_LBUTTONUP: input_event.key_state_map.insert({ VK_LBUTTON, false }); break;
			case WM_RBUTTONUP: input_event.key_state_map.insert({ VK_RBUTTON, false }); break;
			case WM_MBUTTONUP: input_event.key_state_map.insert({ VK_MBUTTON, false }); break;
			case WM_XBUTTONUP:
				// TODO: Add support for context-awareness (i.e. knowing if other buttons are being used as this event comes in).
				//std::cout << std::hex << GET_KEYSTATE_WPARAM(w_param) << std::endl;
				input_event.key_state_map.insert({ GET_XBUTTON_WPARAM(w_param) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2, false }); break;
			case WM_MOUSEWHEEL: input_event.mouse_wheel_delta = GET_WHEEL_DELTA_WPARAM(w_param); break;
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

	Message<Window::InputEvent> WinAPIWindow::pull_input_event() {
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