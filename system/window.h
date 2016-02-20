#ifndef WINDOW_H
#define WINDOW_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include <queue>
#include <utility>

#include <GL/glew.h>
#include <GL/glx.h>
#include <X11/Xlib.h>

#include "../system/constants.h"
#include "../system/globals.h"
#include "../utility/message.h"

namespace BD3GE
{
	class Abstract_Window
	{
		public:

			virtual 									~Abstract_Window() {};
			virtual void								message_listener(void) = 0;
			virtual void								swap_buffers(void) = 0;
			virtual Message< std::pair<char*, bool> >	pull_input_message(void) = 0;
			virtual Message< std::pair<int, int> >		pull_reshape_message(void) = 0;
	};

	class X_Window : public Abstract_Window
	{
		public:

														X_Window();
														~X_Window(void);
			void 										message_listener(void);
			void 										swap_buffers(void);
			Message< std::pair<char*, bool> >	pull_input_message(void);
			Message< std::pair<int, int> >		pull_reshape_message(void);

		private:

			std::queue< Message< std::pair<char*, bool> > >		m_input_queue;
			std::queue< Message< std::pair<int, int> > >		m_reshape_queue;
			Display* 											m_display;
			Window 												m_window;
			GC 													m_graphics_context;
			GLXFBConfig* 										m_framebuffer_configuration;
			XVisualInfo* 										m_visual_information;
			XSetWindowAttributes								m_window_attributes;
			GLXContext 											m_GLX_context;
			GLXWindow 											m_GLX_window;
			bool 												m_doublebuffered_flag;
			int													m_singlebuffered_attributes[16];
			int													m_doublebuffered_attributes[16];
	};
}

#endif // WINDOW_H
