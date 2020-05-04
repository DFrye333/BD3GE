#ifndef BD3GE_WINDOW_H
#define BD3GE_WINDOW_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <queue>
#include <utility>
#include <map>

#include <GL/glew.h>

#ifdef __linux__

#include <unistd.h>
#include <GL/glx.h>
#include <X11/Xlib.h>

#elif _WIN32

#include <Windows.h>

#endif

#include "../system/constants.h"
#include "../system/globals.h"
#include "../utility/message.h"

namespace BD3GE {
	class Window {
		public:

			typedef struct InputEvent {
				BD3GE::KEY_CODE key;
				bool state;
			} InputEvent;
			typedef struct ReshapeEvent {
				uint16_t width;
				uint16_t height;
			} ReshapeEvent;

			virtual 											~Window() {};
			virtual void										message_listener(void) = 0;
			virtual void										swap_buffers(void) = 0;
			virtual Message<std::pair<BD3GE::KEY_CODE, bool>>	pull_input_message(void) = 0;
			virtual Message<std::pair<int, int>>				pull_reshape_message(void) = 0;

		protected:

			std::queue<Message<InputEvent>>*					input_queue;
			std::queue<Message<ReshapeEvent>>*					reshape_queue;
	};

#ifdef __linux__

	class XWindow : public Window {
		public:

																		XWindow();
																		~XWindow(void);
			void 														message_listener(void);
			void 														swap_buffers(void);
			Message<std::pair<BD3GE::KEY_CODE, bool>>					pull_input_message(void);
			Message<std::pair<int, int>>								pull_reshape_message(void);

		private:

			static std::map<std::string, BD3GE::KEY_CODE>> t_key_map	m_key_map;
			std::queue<Message<std::pair<BD3GE::KEY_CODE, bool>>>		m_input_queue;
			Display* 													m_display;
			Window 														m_window;
			GC 															m_graphics_context;
			GLXFBConfig* 												m_framebuffer_configuration;
			XVisualInfo* 												m_visual_information;
			XSetWindowAttributes										m_window_attributes;
			GLXContext 													m_GLX_context;
			GLXWindow 													m_GLX_window;
			bool 														m_doublebuffered_flag;
			int															m_singlebuffered_attributes[16];
			int															m_doublebuffered_attributes[16];
	};

#elif _WIN32

	class WinAPIWindow : public Window {
		public:

			struct WinAPIEntryArgs {
				HINSTANCE hInstance;
				HINSTANCE hPrevInstance;
				LPSTR lpCmdLine;
				int nCmdShow;
			};

			struct WindowProcData {
				std::queue<Message<InputEvent>>* input_queue;
				std::queue<Message<ReshapeEvent>>* reshape_queue;
			};

															WinAPIWindow(WinAPIEntryArgs winAPIEntryArgs);
															~WinAPIWindow(void);
			void											message_listener(void);
			void											swap_buffers(void);
			Message<std::pair<BD3GE::KEY_CODE, bool>>		pull_input_message(void);
			Message<std::pair<int, int>>					pull_reshape_message(void);

			static std::map<int, BD3GE::KEY_CODE>			key_map;

		private:

			BD3GE::WinAPIWindow::WindowProcData*			window_proc_data;
			HWND											window_handle;
			HDC												display_context;
	};

#endif

}

#endif // BD3GE_WINDOW_H
