#include "window.h"

namespace BD3GE
{
	/*
	 *	X_Window class
	 */

	X_Window::X_Window()
	{
		m_graphics_context 			= 	NULL;
		m_framebuffer_configuration = 	NULL;
		m_visual_information 		= 	NULL;
		m_GLX_context 				= 	NULL;
		m_doublebuffered_flag 		= 	true;

		// Request a single-buffered color buffer with the maximum number of color bits for each component.
		m_singlebuffered_attributes[0] = 	GLX_DRAWABLE_TYPE;
		m_singlebuffered_attributes[1] = 	GLX_WINDOW_BIT;
		m_singlebuffered_attributes[2] = 	GLX_RENDER_TYPE;
		m_singlebuffered_attributes[3] = 	GLX_RGBA_BIT;
		m_singlebuffered_attributes[4] = 	GLX_RED_SIZE;
		m_singlebuffered_attributes[5] = 	1;
		m_singlebuffered_attributes[6] = 	GLX_GREEN_SIZE;
		m_singlebuffered_attributes[7] = 	1;
		m_singlebuffered_attributes[8] = 	GLX_BLUE_SIZE;
		m_singlebuffered_attributes[9] = 	1;
		m_singlebuffered_attributes[10] = 	None;

		// Request a double-buffered color buffer with the maximum number of color bits for each component.
		m_doublebuffered_attributes[0] = 	GLX_DRAWABLE_TYPE;
		m_doublebuffered_attributes[1] = 	GLX_WINDOW_BIT;
		m_doublebuffered_attributes[2] = 	GLX_RENDER_TYPE;
		m_doublebuffered_attributes[3] = 	GLX_RGBA_BIT;
		m_doublebuffered_attributes[4] = 	GLX_DOUBLEBUFFER;
		m_doublebuffered_attributes[5] = 	true;
		m_doublebuffered_attributes[6] = 	GLX_RED_SIZE;
		m_doublebuffered_attributes[7] = 	1;
		m_doublebuffered_attributes[8] = 	GLX_GREEN_SIZE;
		m_doublebuffered_attributes[9] = 	1;
		m_doublebuffered_attributes[10] = 	GLX_BLUE_SIZE;
		m_doublebuffered_attributes[11] = 	1;
		m_doublebuffered_attributes[12] = 	None;

		int color_black = 			0;
		int color_white = 			0;
		int configuration_return = 	0;
		int window_attribute_mask =	0;
		int input_mask = 			0;

		// Initialize the display.
		m_display = XOpenDisplay(NULL);
		if (NULL == m_display)
		{
			g_log.write("Null display", LOG_ERROR);
			exit(1);
		}

		// Get the black and white pixels for the screen.
		color_black = BlackPixel(m_display, DefaultScreen(m_display));
		color_white = WhitePixel(m_display, DefaultScreen(m_display));

		// Get frame buffer configurations.
		m_framebuffer_configuration = glXChooseFBConfig(m_display, DefaultScreen(m_display), m_doublebuffered_attributes, &configuration_return);
		if (!m_framebuffer_configuration)
		{
			m_framebuffer_configuration = glXChooseFBConfig(m_display, DefaultScreen(m_display), m_singlebuffered_attributes, &configuration_return);
			m_doublebuffered_flag = false;
		}

		// Get visual associated with frame buffer configuration.
		m_visual_information = glXGetVisualFromFBConfig(m_display, m_framebuffer_configuration[0]);

		// Set window attributes.
		m_window_attributes.border_pixel = 0;
		m_window_attributes.event_mask = StructureNotifyMask;
		m_window_attributes.colormap = XCreateColormap(m_display, RootWindow(m_display, m_visual_information->screen), m_visual_information->visual, AllocNone);
		window_attribute_mask = CWBorderPixel | CWColormap | CWEventMask;

		// Create the window.
		m_window = XCreateWindow(m_display, DefaultRootWindow(m_display),
				SCREEN_WIDTH - WINDOW_WIDTH, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
				0, m_visual_information->depth, InputOutput, m_visual_information->visual, window_attribute_mask, &m_window_attributes);
		m_GLX_context = glXCreateNewContext(m_display, m_framebuffer_configuration[0], GLX_RGBA_TYPE, NULL, true);
		m_GLX_window = glXCreateWindow(m_display, m_framebuffer_configuration[0], (unsigned long int)m_window, NULL);

		// Select input events to be notified about.
		input_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ExposureMask | PointerMotionMask;
		XSelectInput(m_display, (unsigned long int)m_window, input_mask);

		// Set the window's name.
		XStoreName(m_display, (unsigned long int)m_window, WINDOW_TITLE.c_str());

		// Map the new window.
		XMapWindow(m_display, (unsigned long int)m_window);

		// Create a graphics context.
		m_graphics_context = XCreateGC(m_display, (unsigned long int)m_window, 0, NULL);

		// Set the window foreground color.
		XSetForeground(m_display, m_graphics_context, color_white);

		// Wait on the MapNotify event.
		XEvent event;
		while (true)
		{
			g_log.write("Waiting on MapNotify XEvent...", LOG_INFORMATION);

			XNextEvent(m_display, &event);
			if (event.type == MapNotify)
			{
				g_log.write("Found MapNotify XEvent!", LOG_INFORMATION);
				
				break;
			}
		}

		// Make the new context current.
		glXMakeContextCurrent(m_display, m_GLX_window, m_GLX_window, m_GLX_context);

		// Flush the display.
		XFlush(m_display);
	}

	X_Window::~X_Window()
	{
		// Destroy the graphics context, window, and display.
		if (m_GLX_context)
		{
			if (!glXMakeCurrent(m_display, None, NULL))
			{
				g_log.write("Could not release X context!", LOG_ERROR);
			}
			glXDestroyContext(m_display, m_GLX_context);
			m_GLX_context = NULL;
		}
		XFreeGC(m_display, m_graphics_context);
		XDestroyWindow(m_display, (unsigned long int)m_window);
		XCloseDisplay(m_display);
	}

	void X_Window::message_listener(void)
	{
		// If there is a pending message, handle it.
		if (XPending(m_display))
		{
			// Grab the next event message.
			XEvent event;
			XNextEvent(m_display, &event);

			// Determine the type of the event.
			KeySym keysym;
			char* key_string = NULL;
			switch (event.type)
			{
				// A keyboard key has been pressed.
				case KeyPress:
				{
					// TODO: Is translation into a key string even necessary?
					// Translate event into key string.
					XLookupString(&event.xkey, key_string, 32, &keysym, NULL);
					key_string = XKeysymToString(keysym);

					m_input_queue.push(std::make_pair(key_string, true));

					break;
				}

				// A keyboard key has been released.
				case KeyRelease:
				{
					// Make sure there are events in the queue to prevent XPeekEvent from blocking execution.
					XEvent bug_event;
					if (XPending(m_display))
					{
						XPeekEvent(m_display, &bug_event);
					}

					// Check for X11 auto-repeat and dispose of false releases/presses.
					if (KeyPress == bug_event.type && bug_event.xkey.keycode == event.xkey.keycode && bug_event.xkey.time == event.xkey.time)
					{
						g_log.write("Extra key release, discarding.", LOG_INFORMATION);

						XNextEvent(m_display, &bug_event);
						return;
					}

					// TODO: Is translation into a key string even necessary?
					// Translate event into key string.
					XLookupString(&event.xkey, key_string, 32, &keysym, NULL);
					key_string = XKeysymToString(keysym);

					m_input_queue.push(std::make_pair(key_string, false));

					break;
				}

				// TODO: Handle button presses with Input.
				// A mouse button has been pressed.
				case ButtonPress:
				{
					g_log.write("Button " + std::to_string(event.xbutton.button) + " pressed at (" + std::to_string(event.xbutton.x) + ", " + std::to_string(event.xbutton.y) + ")", LOG_INFORMATION);

					break;
				}

				// TODO: Handle button releases with Input.
				// A mouse button has been released.
				case ButtonRelease:
				{
					g_log.write("Button " + std::to_string(event.xbutton.button) + " released at (" + std::to_string(event.xbutton.x) + ", " + std::to_string(event.xbutton.y) + ")", LOG_INFORMATION);

					break;
				}

				// TODO: Handle pointer motion with Input.
				// The mouse pointer has been moved.
				case MotionNotify:
				{
					g_log.write("Pointer motion at (" + std::to_string(event.xmotion.x)  + ", " + std::to_string(event.xmotion.y) + ")", LOG_INFORMATION);

					break;
				}

				// The window has been resized.
				case ConfigureNotify:
				{
					m_reshape_queue.push(std::make_pair(event.xconfigure.width, event.xconfigure.height));

					break;
				}

				default:
				{
					g_log.write("XEvent: " + std::to_string(event.type), LOG_INFORMATION);

					break;
				}
			}
		}
	}

	void X_Window::swap_buffers(void)
	{
		glXSwapBuffers(m_display, m_GLX_window);
	}

	Message< std::pair<char*, bool> > X_Window::pull_input_message(void)
	{
		Message< std::pair<char*, bool> > input_event;

		if (!m_input_queue.empty())
		{
			input_event = m_input_queue.front();

			m_input_queue.pop();
		}

		return input_event;
	}

	Message< std::pair<int, int> > X_Window::pull_reshape_message(void)
	{
		Message< std::pair<int, int> > reshape_event;

		if (!m_reshape_queue.empty())
		{
			reshape_event = m_reshape_queue.front();

			m_reshape_queue.pop();
		}

		return reshape_event;
	}
}