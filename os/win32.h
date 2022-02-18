#ifndef BD3GE_WIN32_H
#define BD3GE_WIN32_H

#include <map>
#include <string>

#include <Windows.h>

#include "../system/constants.h"
#include "../utility/timer.h"
#include "../system/window.h"

namespace BD3GE {
	class WinAPI {
		public:
			static int get_quantity_utf16_characters(std::string input);
			static void to_utf16(std::string input, LPWSTR output);
			static void to_utf16(std::string input, LPWSTR output, int length);
			static void display_message_box(HWND window_handle, std::string caption, std::string message);
			static void resize_window(HWND window_handle, int width, int height);

			static std::map<int, BD3GE::KEY_CODE> key_code_map;
	};

	class WinAPIWindow : public Window {
		public:

			struct WinAPIEntryArgs {
				HINSTANCE hInstance;
				HINSTANCE hPrevInstance;
				LPSTR lpCmdLine;
				int nCmdShow;
			};

			struct WindowProcData {
				WinAPIWindow* window;
			};

			WinAPIWindow(WinAPIEntryArgs winAPIEntryArgs);
			~WinAPIWindow();
			bool											get_window_exists() override;
			void											set_window_exists(bool does_window_exist) override;
			void											message_listener() override;
			void											swap_buffers() override;
			void											push_input_event(Window::InputEvent input_event) override;
			Message<Window::InputEvent>						pull_input_event() override;
			void											push_reshape_event(Window::ReshapeEvent reshape_event) override;
			Message<Window::ReshapeEvent>					pull_reshape_event() override;
			void											set_mouse_cursor_visibility(bool shouldBeVisible) override;

		private:

			BD3GE::WinAPIWindow::WindowProcData*			window_proc_data;
			HWND											window_handle;
			HDC												display_context;
	};

	class WinAPITimer : public Timer {
		public:

			WinAPITimer(std::string name, uint64_t timer_frequency_Hz);
			~WinAPITimer();
			void start();
			bool is_due();

		private:

			std::string			name;
			bool				is_running;
			uint64_t			timer_frequency_Hz;
			uint64_t			system_frequency_Hz;
			uint64_t			start_stamp;
	};
}

#endif // BD3GE_WIN32_H