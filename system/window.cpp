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

	// TODO: Make this a property of the BD3GE::WinAPIWindow class?
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT messageCode, WPARAM wParam, LPARAM lParam)
	{
		BD3GE::WinAPIWindow::WindowProcData* data;
		LONG_PTR dataLongPtr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (dataLongPtr != 0) {
			data = reinterpret_cast<BD3GE::WinAPIWindow::WindowProcData*>(dataLongPtr);
		}

		switch (messageCode)
		{
			case WM_CREATE:
				{
					CREATESTRUCT* dataCreation = reinterpret_cast<CREATESTRUCT*>(lParam);
					data = reinterpret_cast<BD3GE::WinAPIWindow::WindowProcData*>(dataCreation->lpCreateParams);
					SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)data);

					HDC displayContext = GetDC(hwnd);

					PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
					PIXELFORMATDESCRIPTOR* pixelFormatDescriptorPointer = &pixelFormatDescriptor;
					pixelFormatDescriptorPointer->nSize = sizeof(PIXELFORMATDESCRIPTOR);
					pixelFormatDescriptorPointer->nVersion = 1;
					pixelFormatDescriptorPointer->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
					pixelFormatDescriptorPointer->iPixelType = PFD_TYPE_COLORINDEX;
					pixelFormatDescriptorPointer->cColorBits = 8;
					pixelFormatDescriptorPointer->cDepthBits = 16;
					pixelFormatDescriptorPointer->cAccumBits = 0;
					pixelFormatDescriptorPointer->cStencilBits = 0;

					int pixelFormat = ChoosePixelFormat(displayContext, pixelFormatDescriptorPointer);
					SetPixelFormat(displayContext, pixelFormat, pixelFormatDescriptorPointer);

					HGLRC renderContext = wglCreateContext(displayContext);
					wglMakeCurrent(displayContext, renderContext);
				}

				break;
			case WM_PAINT:
				{
					PAINTSTRUCT paintStruct;
					BeginPaint(hwnd, &paintStruct);
					EndPaint(hwnd, &paintStruct);
				}

				break;
			case WM_SIZE:
				BD3GE::Window::ReshapeEvent reshapeEvent;
				reshapeEvent.width = LOWORD(lParam);
				reshapeEvent.height = HIWORD(lParam);

				data->reshapeQueue->push(BD3GE::Message(reshapeEvent));

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

		reshapeQueue = new std::queue<BD3GE::Message<BD3GE::Window::ReshapeEvent>>;

		windowProcData = new BD3GE::WinAPIWindow::WindowProcData;
		windowProcData->reshapeQueue = reshapeQueue;

		windowHandle = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			g_szClassName,
			BD3GE::WINDOW_TITLE.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, BD3GE::WINDOW_WIDTH, BD3GE::WINDOW_HEIGHT,
			NULL, NULL, winAPIEntryArgs.hInstance,
			windowProcData
		);

		if (windowHandle == NULL)
		{
			MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
			//return 0;
		}

		ShowWindow(windowHandle, winAPIEntryArgs.nCmdShow);
		UpdateWindow(windowHandle);

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

		/*std::cout << msg.message;
		std::cout << ": (";
		std::cout << msg.pt.x;
		std::cout << ", ";
		std::cout << msg.pt.y;
		std::cout <<  +")" << std::endl;*/
	}

	void WinAPIWindow::swap_buffers(void)
	{
		SwapBuffers(GetDC(windowHandle));
	}

	Message<std::pair<BD3GE::KEY_CODE, bool>> WinAPIWindow::pull_input_message(void)
	{
		Message<std::pair<BD3GE::KEY_CODE, bool>> input_message;
		return input_message;
	}

	Message<std::pair<int, int>> WinAPIWindow::pull_reshape_message(void)
	{
		return Message<std::pair<int, int>> ();
	}

#endif
}