#include "window.h"

namespace BD3GE
{

#ifdef __linux__

	/*
	 *	XWindow class
	 */

	std::map<std::string, BD3GE::KEY_CODE> XWindow::m_key_map =
	{
		{ "BackSpace", BD3GE::KEY_CODE::BACKSPACE },
		{ "Tab", BD3GE::KEY_CODE::TAB },
		{ "Escape", BD3GE::KEY_CODE::ESCAPE },
		{ "space", BD3GE::KEY_CODE::SPACE },
		{ "apostrophe", BD3GE::KEY_CODE::QUOTE },
		{ "comma", BD3GE::KEY_CODE::COMMA },
		{ "minus", BD3GE::KEY_CODE::MINUS },
		{ "period", BD3GE::KEY_CODE::PERIOD },
		{ "slash", BD3GE::KEY_CODE::SLASH },
		{ "0", BD3GE::KEY_CODE::NUM_0 },
		{ "1", BD3GE::KEY_CODE::NUM_1 },
		{ "2", BD3GE::KEY_CODE::NUM_2 },
		{ "3", BD3GE::KEY_CODE::NUM_3 },
		{ "4", BD3GE::KEY_CODE::NUM_4 },
		{ "5", BD3GE::KEY_CODE::NUM_5 },
		{ "6", BD3GE::KEY_CODE::NUM_6 },
		{ "7", BD3GE::KEY_CODE::NUM_7 },
		{ "8", BD3GE::KEY_CODE::NUM_8 },
		{ "9", BD3GE::KEY_CODE::NUM_9 },
		{ "semicolon", BD3GE::KEY_CODE::SEMICOLON },
		{ "equal", BD3GE::KEY_CODE::EQUAL },
		{ "bracketleft", BD3GE::KEY_CODE::BRACKETLEFT },
		{ "backslash", BD3GE::KEY_CODE::BACKSLASH },
		{ "bracketright", BD3GE::KEY_CODE::BRACKETRIGHT },
		{ "grave", BD3GE::KEY_CODE::GRAVE },
		{ "a", BD3GE::KEY_CODE::A },
		{ "b", BD3GE::KEY_CODE::B },
		{ "c", BD3GE::KEY_CODE::C },
		{ "d", BD3GE::KEY_CODE::D },
		{ "e", BD3GE::KEY_CODE::E },
		{ "f", BD3GE::KEY_CODE::F },
		{ "g", BD3GE::KEY_CODE::G },
		{ "h", BD3GE::KEY_CODE::H },
		{ "i", BD3GE::KEY_CODE::I },
		{ "j", BD3GE::KEY_CODE::J },
		{ "k", BD3GE::KEY_CODE::K },
		{ "l", BD3GE::KEY_CODE::L },
		{ "m", BD3GE::KEY_CODE::M },
		{ "n", BD3GE::KEY_CODE::N },
		{ "o", BD3GE::KEY_CODE::O },
		{ "p", BD3GE::KEY_CODE::P },
		{ "q", BD3GE::KEY_CODE::Q },
		{ "r", BD3GE::KEY_CODE::R },
		{ "s", BD3GE::KEY_CODE::S },
		{ "t", BD3GE::KEY_CODE::T },
		{ "u", BD3GE::KEY_CODE::U },
		{ "v", BD3GE::KEY_CODE::V },
		{ "w", BD3GE::KEY_CODE::W },
		{ "x", BD3GE::KEY_CODE::X },
		{ "y", BD3GE::KEY_CODE::Y },
		{ "z", BD3GE::KEY_CODE::Z },
		{ "Return", BD3GE::KEY_CODE::RETURN },
		{ "Print", BD3GE::KEY_CODE::PRINT },
		{ "Scroll_Lock", BD3GE::KEY_CODE::SCROLLLOCK },
		{ "Pause", BD3GE::KEY_CODE::PAUSE },
		{ "Insert", BD3GE::KEY_CODE::INSERT },
		{ "Home", BD3GE::KEY_CODE::HOME },
		{ "Prior", BD3GE::KEY_CODE::PAGEUP },
		{ "Delete", BD3GE::KEY_CODE::DEL },
		{ "End", BD3GE::KEY_CODE::END },
		{ "Next", BD3GE::KEY_CODE::PAGEDOWN },
		{ "Up", BD3GE::KEY_CODE::UP },
		{ "Left", BD3GE::KEY_CODE::LEFT },
		{ "Down", BD3GE::KEY_CODE::DOWN },
		{ "Right", BD3GE::KEY_CODE::RIGHT },
		{ "Shift_L", BD3GE::KEY_CODE::SHIFTL },
		{ "Shift_R", BD3GE::KEY_CODE::SHIFTR },
		{ "Alt_L", BD3GE::KEY_CODE::ALTL },
		{ "Alt_R", BD3GE::KEY_CODE::ALTR },
		{ "Super_L", BD3GE::KEY_CODE::SUPERL },
		{ "Caps_Lock", BD3GE::KEY_CODE::CAPSLOCK },
		{ "Num_Lock", BD3GE::KEY_CODE::NUMLOCK },
		{ "F1", BD3GE::KEY_CODE::F1 },
		{ "F2", BD3GE::KEY_CODE::F2 },
		{ "F3", BD3GE::KEY_CODE::F3 },
		{ "F4", BD3GE::KEY_CODE::F4 },
		{ "F5", BD3GE::KEY_CODE::F5 },
		{ "F6", BD3GE::KEY_CODE::F6 },
		{ "F7", BD3GE::KEY_CODE::F7 },
		{ "F8", BD3GE::KEY_CODE::F8 },
		{ "F9", BD3GE::KEY_CODE::F9 },
		{ "F10", BD3GE::KEY_CODE::F10 },
		{ "F11", BD3GE::KEY_CODE::F11 },
		{ "F12", BD3GE::KEY_CODE::F12 },
		{ "KP_Divide", BD3GE::KEY_CODE::KP_DIVIDE },
		{ "KP_Multiply", BD3GE::KEY_CODE::KP_MULTIPLY },
		{ "KP_Subtract", BD3GE::KEY_CODE::KP_SUBTRACT },
		{ "KP_Add", BD3GE::KEY_CODE::KP_ADD },
		{ "KP_Enter", BD3GE::KEY_CODE::KP_ENTER },
		{ "KP_Decimal", BD3GE::KEY_CODE::KP_DECIMAL },
		{ "KP_0", BD3GE::KEY_CODE::KP_0 },
		{ "KP_1", BD3GE::KEY_CODE::KP_1 },
		{ "KP_2", BD3GE::KEY_CODE::KP_2 },
		{ "KP_3", BD3GE::KEY_CODE::KP_3 },
		{ "KP_4", BD3GE::KEY_CODE::KP_4 },
		{ "KP_5", BD3GE::KEY_CODE::KP_5 },
		{ "KP_6", BD3GE::KEY_CODE::KP_6 },
		{ "KP_7", BD3GE::KEY_CODE::KP_7 },
		{ "KP_8", BD3GE::KEY_CODE::KP_8 },
		{ "KP_9", BD3GE::KEY_CODE::KP_9 },
	};

	XWindow::XWindow()
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
			g_log.write("Null display", BD3GE::LOG_TYPE::ERR);
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
			g_log.write("Waiting on MapNotify XEvent...", BD3GE::LOG_TYPE::INFO);

			XNextEvent(m_display, &event);
			if (event.type == MapNotify)
			{
				g_log.write("Found MapNotify XEvent!", BD3GE::LOG_TYPE::INFO);
				
				break;
			}
		}

		// Make the new context current.
		glXMakeContextCurrent(m_display, m_GLX_window, m_GLX_window, m_GLX_context);

		// Flush the display.
		XFlush(m_display);
	}

	XWindow::~XWindow()
	{
		// Destroy the graphics context, window, and display.
		if (m_GLX_context)
		{
			if (!glXMakeCurrent(m_display, None, NULL))
			{
				g_log.write("Could not release X context!", BD3GE::LOG_TYPE::ERR);
			}
			glXDestroyContext(m_display, m_GLX_context);
			m_GLX_context = NULL;
		}
		XFreeGC(m_display, m_graphics_context);
		XDestroyWindow(m_display, (unsigned long int)m_window);
		XCloseDisplay(m_display);
	}

	void XWindow::message_listener(void)
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

					m_input_queue.push(std::make_pair(m_key_map[std::string(key_string)], true));

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
						g_log.write("Extra key release, discarding.", BD3GE::LOG_TYPE::INFO);

						XNextEvent(m_display, &bug_event);
						return;
					}

					// TODO: Is translation into a key string even necessary?
					// Translate event into key string.
					XLookupString(&event.xkey, key_string, 32, &keysym, NULL);
					key_string = XKeysymToString(keysym);

					m_input_queue.push(std::make_pair(m_key_map[std::string(key_string)], false));

					break;
				}

				// TODO: Handle button presses with Input.
				// A mouse button has been pressed.
				case ButtonPress:
				{
					g_log.write("Button " + std::to_string(event.xbutton.button) + " pressed at (" + std::to_string(event.xbutton.x) + ", " + std::to_string(event.xbutton.y) + ")", BD3GE::LOG_TYPE::INFO);

					break;
				}

				// TODO: Handle button releases with Input.
				// A mouse button has been released.
				case ButtonRelease:
				{
					g_log.write("Button " + std::to_string(event.xbutton.button) + " released at (" + std::to_string(event.xbutton.x) + ", " + std::to_string(event.xbutton.y) + ")", BD3GE::LOG_TYPE::INFO);

					break;
				}

				// TODO: Handle pointer motion with Input.
				// The mouse pointer has been moved.
				case MotionNotify:
				{
					// g_log.write("Pointer motion at (" + std::to_string(event.xmotion.x)  + ", " + std::to_string(event.xmotion.y) + ")", BD3GE::LOG_TYPE::INFO);

					break;
				}

				// The window has been resized.
				case ConfigureNotify:
				{
					reshapeQueue.push(std::make_pair(event.xconfigure.width, event.xconfigure.height));

					break;
				}

				default:
				{
					g_log.write("XEvent: " + std::to_string(event.type), BD3GE::LOG_TYPE::INFO);

					break;
				}
			}
		}
	}

	void XWindow::swap_buffers(void)
	{
		glXSwapBuffers(m_display, m_GLX_window);
	}

	Message<std::pair<BD3GE::KEY_CODE, bool>> XWindow::pull_input_message(void)
	{
		Message<std::pair<BD3GE::KEY_CODE, bool>> input_event;

		if (!m_input_queue.empty())
		{
			input_event = m_input_queue.front();

			m_input_queue.pop();
		}

		return input_event;
	}

	Message<std::pair<int, int>> XWindow::pull_reshape_message(void)
	{
		Message<std::pair<int, int>> reshape_event;

		if (!reshapeQueue.empty())
		{
			reshape_event = reshapeQueue.front();

			reshapeQueue.pop();
		}

		return reshape_event;
	}

#elif _WIN32

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT messageCode, WPARAM wParam, LPARAM lParam)
	{
		BD3GE::WinAPIWindow::WindowProcData* data;
		LONG_PTR data_long_ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (data_long_ptr != 0) {
			data = reinterpret_cast<BD3GE::WinAPIWindow::WindowProcData*>(data_long_ptr);
		}

		switch (messageCode)
		{
			case WM_CREATE:
				{
					CREATESTRUCT* data_creation = reinterpret_cast<CREATESTRUCT*>(lParam);
					data = reinterpret_cast<BD3GE::WinAPIWindow::WindowProcData*>(data_creation->lpCreateParams);
					SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)data);

					HDC display_context = GetDC(hwnd);

					PIXELFORMATDESCRIPTOR pixel_format_descriptor;
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

				break;
			case WM_PAINT:
				{
					PAINTSTRUCT paint_struct;
					BeginPaint(hwnd, &paint_struct);
					EndPaint(hwnd, &paint_struct);
				}

				break;
			case WM_KEYDOWN:
				{
					BD3GE::Window::InputEvent input_event;
					input_event.key = WinAPIWindow::key_map[wParam];
					input_event.state = true;
					data->input_queue->push(input_event);
				}

				break;
			case WM_KEYUP:
				{
					BD3GE::Window::InputEvent input_event;
					input_event.key = WinAPIWindow::key_map[wParam];
					input_event.state = false;
					data->input_queue->push(input_event);
				}

				break;
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_XBUTTONDOWN:
				{
					BD3GE::KEY_CODE key;
					if (wParam & MK_LBUTTON) {
						key = BD3GE::KEY_CODE::MOUSE_LEFTBUTTON;
					} if (wParam & MK_RBUTTON) {
						key = BD3GE::KEY_CODE::MOUSE_RIGHTBUTTON;
					}

					BD3GE::Window::InputEvent input_event;
					input_event.key = key;
					input_event.state = true;
					data->input_queue->push(input_event);

					return true;
				}
			case WM_LBUTTONUP:
				{
					BD3GE::Window::InputEvent input_event;
					input_event.key = BD3GE::KEY_CODE::MOUSE_LEFTBUTTON;
					input_event.state = false;
					data->input_queue->push(input_event);

					return true;
				}
			case WM_RBUTTONUP:
				{
					BD3GE::Window::InputEvent input_event;
					input_event.key = BD3GE::KEY_CODE::MOUSE_RIGHTBUTTON;
					input_event.state = false;
					data->input_queue->push(input_event);

					return true;
				}
			case WM_MBUTTONUP:
				{
					BD3GE::Window::InputEvent input_event;
					input_event.key = BD3GE::KEY_CODE::MOUSE_MIDDLEBUTTON;
					input_event.state = false;
					data->input_queue->push(input_event);

					return true;
				}
			case WM_XBUTTONUP:
				{
					/*BD3GE::Window::InputEvent input_event;
					input_event.key = BD3GE::KEY_CODE::MOUSE_X1BUTTON;
					input_event.state = false;
					data->input_queue->push(input_event);

					return true;*/
				}
			case WM_SIZE:
				BD3GE::Window::ReshapeEvent reshape_event;
				reshape_event.width = LOWORD(lParam);
				reshape_event.height = HIWORD(lParam);

				data->reshape_queue->push(BD3GE::Message(reshape_event));

				break;
			case WM_CLOSE:
				DestroyWindow(hwnd);

				break;
			case WM_DESTROY:
				PostQuitMessage(0);

				break;
			default:
				return DefWindowProc(hwnd, messageCode, wParam, lParam);
		}

		return 0;
	}

	std::map<int, BD3GE::KEY_CODE> WinAPIWindow::key_map =
	{
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

	WinAPIWindow::WinAPIWindow(BD3GE::WinAPIWindow::WinAPIEntryArgs winAPIEntryArgs)
	{
		WNDCLASSEX wc;
		const char g_szClassName[] = "BD3GEWindowClass";

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

		if (!RegisterClassEx(&wc))
		{
			MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
			//return 0;
		}

		input_queue = new std::queue<BD3GE::Message<BD3GE::Window::InputEvent>>;
		reshape_queue = new std::queue<BD3GE::Message<BD3GE::Window::ReshapeEvent>>;

		window_proc_data = new BD3GE::WinAPIWindow::WindowProcData;
		window_proc_data->input_queue = input_queue;
		window_proc_data->reshape_queue = reshape_queue;

		window_handle = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			g_szClassName,
			BD3GE::WINDOW_TITLE.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, BD3GE::WINDOW_WIDTH, BD3GE::WINDOW_HEIGHT,
			NULL, NULL, winAPIEntryArgs.hInstance,
			window_proc_data
		);

		if (window_handle == NULL)
		{
			MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
			//return 0;
		}

		ShowWindow(window_handle, winAPIEntryArgs.nCmdShow);
		UpdateWindow(window_handle);

		std::cout << "Command line arguments: ";
		std::cout << winAPIEntryArgs.lpCmdLine << std::endl;
	}

	WinAPIWindow::~WinAPIWindow()
	{

	}

	void WinAPIWindow::message_listener(void)
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WinAPIWindow::swap_buffers(void)
	{
		display_context = GetDC(window_handle);
		SwapBuffers(display_context);
		ReleaseDC(window_handle, display_context);
	}

	Message<std::pair<BD3GE::KEY_CODE, bool>> WinAPIWindow::pull_input_message(void)
	{
		Message<std::pair<BD3GE::KEY_CODE, bool>> input_message;

		if (!input_queue->empty())
		{
			InputEvent* input_event = input_queue->front().get_data();
			input_message.set_data(std::make_pair(input_event->key, input_event->state));
			input_queue->pop();
		}

		return input_message;
	}

	Message<std::pair<int, int>> WinAPIWindow::pull_reshape_message(void)
	{
		Message<std::pair<int, int>> reshape_message;

		if (!reshape_queue->empty())
		{
			ReshapeEvent* reshape_event = reshape_queue->front().get_data();
			reshape_message.set_data(std::make_pair(reshape_event->width, reshape_event->height));
			reshape_queue->pop();
		}

		return reshape_message;
	}

#endif
}