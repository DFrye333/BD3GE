#ifndef BD3GE_WIN32_H
#define BD3GE_WIN32_H

#include <map>
#include <string>

#include <Windows.h>
#include <direct.h>

#include "../management/config_manager.h"
#include "../system/api.h"
#include "../system/constants.h"
#include "../system/window.h"
#include "../utility/timer.h"

namespace BD3GE {
	class WinAPI {
		public:
			static int get_quantity_utf16_characters(std::string input);
			static void to_utf16(std::string input, LPWSTR output);
			static void to_utf16(std::string input, LPWSTR output, int length);
			static void display_message_box(HWND window_handle, std::string caption, std::string message);
			static void resize_window(HWND window_handle, int width, int height);
			static std::string get_environment_variable(std::string environment_variable_name);
			static bool make_directory(std::string directory_path, std::string& result);
			static bool does_directory_exist(std::string directory_path);
			static bool does_directory_exist(std::string directory_path, WIN32_FILE_ATTRIBUTE_DATA* file_attributes);
			static BOOL get_file_info(std::string& absolute_file_path, WIN32_FILE_ATTRIBUTE_DATA* file_attributes);
	};

	extern "C" class BD3GE_API WinAPIWindow : public Window {
		public:

			struct WinAPIEntryArgs : public EntryArgs {
				HINSTANCE instance;
				HINSTANCE previous_instance;
				LPSTR command_line;
				int command_show;
			};

			struct WindowProcData {
				WinAPIWindow* window;
			};

			WinAPIWindow(WinAPIEntryArgs* winAPIEntryArgs);
			~WinAPIWindow();
			bool											get_window_exists() override;
			void											set_window_exists(bool does_window_exist) override;
			void											message_listener() override;
			void											swap_buffers() override;
			void											push_input_event(Window::InputEvent input_event) override;
			Message<InputEvent>								pull_input_event() override;
			void											push_reshape_event(Window::ReshapeEvent reshape_event) override;
			Message<Window::ReshapeEvent>					pull_reshape_event() override;
			void											set_mouse_cursor_visibility(bool should_be_visible) override;

		private:

			BD3GE::WinAPIWindow::WindowProcData*			window_proc_data;
			HWND											window_handle;
			HDC												display_context;
	};

	class WinAPITimer : public Timer {
		public:

			WinAPITimer(std::string name);
			WinAPITimer(std::string name, uint64_t timer_frequency_Hz);
			void start() override;
			void pause() override;
			void unpause() override;
			void toggle_pause() override;
			uint64_t elapsed() override;
			bool is_due() override;

		private:

			uint64_t get_current_timestamp();
	};
}

#endif // BD3GE_WIN32_H