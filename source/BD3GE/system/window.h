#ifndef BD3GE_WINDOW_H
#define BD3GE_WINDOW_H

#include <cstdlib>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>

#ifdef __linux__

#include <unistd.h>
#include <GL/glx.h>
#include <X11/Xlib.h>

#endif

#include "../input/input.h"
#include "../system/api.h"
#include "../system/constants.h"
#include "../system/globals.h"
#include "../utility/message.h"

namespace BD3GE {
	class Window {
		public:
			struct EntryArgs {};

			typedef struct ReshapeEvent {
				uint16_t width;
				uint16_t height;
			} ReshapeEvent;

			virtual 											~Window() {};
			virtual bool										get_window_exists() = 0;
			virtual void										set_window_exists(bool does_window_exist) = 0;
			virtual void										message_listener() = 0;
			virtual void										swap_buffers() = 0;
			virtual void										push_input_event(Input::InputEvent input_message) = 0;
			virtual Message<Input::InputEvent>					pull_input_event() = 0;
			virtual	void										push_reshape_event(ReshapeEvent reshape_message) = 0;
			virtual Message<ReshapeEvent>						pull_reshape_event() = 0;
			virtual void										set_mouse_cursor_visibility(bool shouldBeVisible) = 0;

		protected:

			std::queue<Message<Input::InputEvent>> input_queue;
			std::queue<Message<ReshapeEvent>> reshape_queue;
			bool does_window_exist;
	};

#ifdef __linux__

	class XWindow : public Window {
		public:

			XWindow();
			~XWindow();
			void 														message_listener();
			void 														swap_buffers();
			Message<std::pair<Input::KEY_CODE, bool>>					pull_input_event();
			Message<std::pair<int, int>>								pull_reshape_event();

		private:

			static std::map<std::string, Input::KEY_CODE >> t_key_map	m_key_map;
			std::queue<Message<std::pair<Input::KEY_CODE, bool>>>		m_input_queue;
			Display* m_display;
			Window 														m_window;
			GC 															m_graphics_context;
			GLXFBConfig* m_framebuffer_configuration;
			XVisualInfo* m_visual_information;
			XSetWindowAttributes										m_window_attributes;
			GLXContext 													m_GLX_context;
			GLXWindow 													m_GLX_window;
			bool 														m_doublebuffered_flag;
			int															m_singlebuffered_attributes[16];
			int															m_doublebuffered_attributes[16];
	};

#endif
}

#endif // BD3GE_WINDOW_H