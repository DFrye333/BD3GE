#include "window.h"

namespace BD3GE
{

#ifdef __linux__

	/*
	 *	XWindow class
	 */

	XWindow::t_key_map XWindow::m_key_map =
	{
		{ "BackSpace", KEY_BACKSPACE },
		{ "Tab", KEY_TAB },
		{ "Escape", KEY_ESCAPE },
		{ "space", KEY_SPACE },
		{ "apostrophe", KEY_APOSTROPHE },
		{ "comma", KEY_COMMA },
		{ "minus", KEY_MINUS },
		{ "period", KEY_PERIOD },
		{ "slash", KEY_SLASH },
		{ "0", KEY_0 },
		{ "1", KEY_1 },
		{ "2", KEY_2 },
		{ "3", KEY_3 },
		{ "4", KEY_4 },
		{ "5", KEY_5 },
		{ "6", KEY_6 },
		{ "7", KEY_7 },
		{ "8", KEY_8 },
		{ "semicolon", KEY_SEMICOLON },
		{ "equal", KEY_EQUAL },
		{ "bracketleft", KEY_BRACKETLEFT },
		{ "backslash", KEY_BACKSLASH },
		{ "bracketright", KEY_BRACKETRIGHT },
		{ "grave", KEY_GRAVE },
		{ "a", KEY_A },
		{ "b", KEY_B },
		{ "c", KEY_C },
		{ "d", KEY_D },
		{ "e", KEY_E },
		{ "f", KEY_F },
		{ "g", KEY_G },
		{ "h", KEY_H },
		{ "i", KEY_I },
		{ "j", KEY_J },
		{ "k", KEY_K },
		{ "l", KEY_L },
		{ "m", KEY_M },
		{ "n", KEY_N },
		{ "o", KEY_O },
		{ "p", KEY_P },
		{ "q", KEY_Q },
		{ "r", KEY_R },
		{ "s", KEY_S },
		{ "t", KEY_T },
		{ "u", KEY_U },
		{ "v", KEY_V },
		{ "w", KEY_W },
		{ "x", KEY_X },
		{ "y", KEY_Y },
		{ "z", KEY_Z },
		{ "Return", KEY_RETURN },
		{ "Print", KEY_PRINT },
		{ "Scroll_Lock", KEY_SCROLLLOCK },
		{ "Pause", KEY_PAUSE },
		{ "Insert", KEY_INSERT },
		{ "Home", KEY_HOME },
		{ "Prior", KEY_PRIOR },
		{ "Delete", KEY_DELETE },
		{ "End", KEY_END },
		{ "Next", KEY_NEXT },
		{ "Up", KEY_UP },
		{ "Left", KEY_LEFT },
		{ "Down", KEY_DOWN },
		{ "Right", KEY_RIGHT },
		{ "Shift_L", KEY_SHIFTL },
		{ "Shift_R", KEY_SHIFTR },
		{ "Alt_L", KEY_ALTL },
		{ "Alt_R", KEY_ALTR },
		{ "Super_L", KEY_SUPERL },
		{ "Caps_Lock", KEY_CAPSLOCK },
		{ "Num_Lock", KEY_NUMLOCK },
		{ "F1", KEY_F1 },
		{ "F2", KEY_F2 },
		{ "F3", KEY_F3 },
		{ "F4", KEY_F4 },
		{ "F5", KEY_F5 },
		{ "F6", KEY_F6 },
		{ "F7", KEY_F7 },
		{ "F8", KEY_F8 },
		{ "F9", KEY_F9 },
		{ "F10", KEY_F10 },
		{ "F11", KEY_F11 },
		{ "F12", KEY_F12 },
		{ "KP_Divide", KEY_KPDIVIDE },
		{ "KP_Multiply", KEY_KPMULTIPLY },
		{ "KP_Subtract", KEY_KPSUBTRACT },
		{ "KP_Add", KEY_KPADD },
		{ "KP_Enter", KEY_KPENTER },
		{ "KP_Decimal", KEY_KPENTER },
		{ "KP_0", KEY_KP0 },
		{ "KP_1", KEY_KP1 },
		{ "KP_2", KEY_KP2 },
		{ "KP_3", KEY_KP3 },
		{ "KP_4", KEY_KP4 },
		{ "KP_5", KEY_KP5 },
		{ "KP_6", KEY_KP6 },
		{ "KP_7", KEY_KP7 },
		{ "KP_8", KEY_KP8 },
		{ "KP_9", KEY_KP9 },
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

	Message<std::pair<std::string, bool>> XWindow::pull_input_message(void)
	{
		Message< std::pair<std::string, bool> > input_event;

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

	Message<std::pair<std::string, bool>> WinAPIWindow::pull_input_message(void)
	{
		return Message<std::pair<std::string, bool>>();
	}

	Message<std::pair<int, int>> WinAPIWindow::pull_reshape_message(void)
	{
		return Message<std::pair<int, int>> ();
	}

#endif
}