#include "XWindow.h"

XWindow::XWindow()
{
	mGraphicsContext = 	NULL;
	mFBConfig = 		NULL;
	mVisualInfo = 		NULL;
	mGlxContext = 		NULL;
	mDBFlag = 			true;

	// Request a single-buffered color buffer with the maximum number of color bits for each component.
	mSBAttr[0] = 	GLX_DRAWABLE_TYPE;
	mSBAttr[1] = 	GLX_WINDOW_BIT;
	mSBAttr[2] = 	GLX_RENDER_TYPE;
	mSBAttr[3] = 	GLX_RGBA_BIT;
	mSBAttr[4] = 	GLX_RED_SIZE;
	mSBAttr[5] = 	1;
	mSBAttr[6] = 	GLX_GREEN_SIZE;
	mSBAttr[7] = 	1;
	mSBAttr[8] = 	GLX_BLUE_SIZE;
	mSBAttr[9] = 	1;
	mSBAttr[10] = 	None;

	// Request a double-buffered color buffer with the maximum number of color bits for each component.
	mDBAttr[0] = 	GLX_DRAWABLE_TYPE;
	mDBAttr[1] = 	GLX_WINDOW_BIT;
	mDBAttr[2] = 	GLX_RENDER_TYPE;
	mDBAttr[3] = 	GLX_RGBA_BIT;
	mDBAttr[4] = 	GLX_DOUBLEBUFFER;
	mDBAttr[5] = 	true;
	mDBAttr[6] = 	GLX_RED_SIZE;
	mDBAttr[7] = 	1;
	mDBAttr[8] = 	GLX_GREEN_SIZE;
	mDBAttr[9] = 	1;
	mDBAttr[10] = 	GLX_BLUE_SIZE;
	mDBAttr[11] = 	1;
	mDBAttr[12] = 	None;

	int colorBlack = 		0;
	int colorWhite = 		0;
	int configReturn = 		0;
	int windowAttrMask = 	0;
	int inputMask = 		0;

	// Initialize the display.
	mDisplay = XOpenDisplay(NULL);
	if (NULL == mDisplay)
	{
		std::cout << BD3GE_PRINT_ERROR << "Null display" << std::endl;
		exit(1);
	}

	// Get the black and white pixels for the screen.
	colorBlack = BlackPixel(mDisplay, DefaultScreen(mDisplay));
	colorWhite = WhitePixel(mDisplay, DefaultScreen(mDisplay));

	// Get frame buffer configurations.
	mFBConfig = glXChooseFBConfig(mDisplay, DefaultScreen(mDisplay), mDBAttr, &configReturn);
	if (!mFBConfig)
	{
		mFBConfig = glXChooseFBConfig(mDisplay, DefaultScreen(mDisplay), mSBAttr, &configReturn);
		mDBFlag = false;
	}

	// Get visual associated with frame buffer configuration.
	mVisualInfo = glXGetVisualFromFBConfig(mDisplay, mFBConfig[0]);

	// Set window attributes.
	mWindowAttr.border_pixel = 0;
	mWindowAttr.event_mask = StructureNotifyMask;
	mWindowAttr.colormap = XCreateColormap(mDisplay, RootWindow(mDisplay, mVisualInfo->screen), mVisualInfo->visual, AllocNone);
	windowAttrMask = CWBorderPixel | CWColormap | CWEventMask;

	// Create the window.
	mWindow = XCreateWindow(mDisplay, DefaultRootWindow(mDisplay),
			BD3GE_SCREEN_WIDTH - BD3GE_WINDOW_WIDTH, 0, BD3GE_WINDOW_WIDTH, BD3GE_WINDOW_HEIGHT,
			0, mVisualInfo->depth, InputOutput, mVisualInfo->visual, windowAttrMask, &mWindowAttr);
	mGlxContext = glXCreateNewContext(mDisplay, mFBConfig[0], GLX_RGBA_TYPE, NULL, true);
	mGlxWindow = glXCreateWindow(mDisplay, mFBConfig[0], mWindow, NULL);

	// Select input events to be notified about.
	inputMask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ExposureMask;
	XSelectInput(mDisplay, mWindow, inputMask);

	// Set the window's name.
	XStoreName(mDisplay, mWindow, BD3GE_WINDOW_TITLE.c_str());

	// Map the new window.
	XMapWindow(mDisplay, mWindow);

	// Create a graphics context.
	mGraphicsContext = XCreateGC(mDisplay, mWindow, 0, NULL);

	// Set the window foreground color.
	XSetForeground(mDisplay, mGraphicsContext, colorWhite);

	// Wait on the MapNotify event.
	XEvent event;
	while (1)
	{
		XNextEvent(mDisplay, &event);
		if (event.type == MapNotify)
		{
			break;
		}
	}

	// Make the new context current.
	glXMakeContextCurrent(mDisplay, mGlxWindow, mGlxWindow, mGlxContext);

	// Flush the display.
	XFlush(mDisplay);
}

XWindow::~XWindow()
{
	// Destroy the graphics context, window, and display.
	if (mGlxContext)
	{
		if (!glXMakeCurrent(mDisplay, None, NULL))
		{
			std::cout << BD3GE_PRINT_ERROR << "Could not release X context!" << std::endl;
		}
		glXDestroyContext(mDisplay, mGlxContext);
		mGlxContext = NULL;
	}
	XFreeGC(mDisplay, mGraphicsContext);
	XDestroyWindow(mDisplay, mWindow);
	XCloseDisplay(mDisplay);
}

void XWindow::messageListener(void)
{
	// If there is a pending message, handle it.
	if (XPending(mDisplay))
	{
		// Grab the next event message.
		XEvent event;
		XNextEvent(mDisplay, &event);

		// Determine the type of the event.
		KeySym keysym;
		char* keyString = NULL;
		switch (event.type)
		{
			// A keyboard key has been pressed.
			case KeyPress:
			{
				// Translate event into key string.
				XLookupString(&event.xkey, keyString, 32, &keysym, NULL);
				keyString = XKeysymToString(keysym);

				mInputQueue.push(std::make_pair(keyString, true));

				break;
			}

			// A keyboard key has been released.
			case KeyRelease:
			{
				// Make sure there are events in the queue to prevent XPeekEvent from blocking execution.
				XEvent bugEvent;
				if (XPending(mDisplay))
				{
					XPeekEvent(mDisplay, &bugEvent);
				}

				// Check for X11 auto-repeat and dispose of false releases/presses.
				if (KeyPress == bugEvent.type && bugEvent.xkey.keycode == event.xkey.keycode && bugEvent.xkey.time == event.xkey.time)
				{
					// TODO: Implement logging.
	//				std::cout << BD3GE_PRINT_INFORMATION << "Extra key release, discarding." << std::endl;
					XNextEvent(mDisplay, &bugEvent);
					return;
				}

				// Translate event into key string.
				XLookupString(&event.xkey, keyString, 32, &keysym, NULL);
				keyString = XKeysymToString(keysym);

				mInputQueue.push(std::make_pair(keyString, false));

				break;
			}

			// The window has been resized.
			case ConfigureNotify:
			{
				mReshapeQueue.push(std::make_pair(event.xconfigure.width, event.xconfigure.height));

				break;
			}

			default:
			{
				std::cout <<  BD3GE_PRINT_INFORMATION << "XEvent: " << event.type << std::endl;

				break;
			}
		}
	}
}

void XWindow::swapBuffers(void)
{
	glXSwapBuffers(mDisplay, mGlxWindow);
}

Message< std::pair<char*, bool> > XWindow::pullInputMessage(void)
{
	Message< std::pair<char*, bool> > inputEvent;

	if (!mInputQueue.empty())
	{
		inputEvent = mInputQueue.front();

		mInputQueue.pop();
	}

	return inputEvent;
}

Message< std::pair<int, int> > XWindow::pullReshapeMessage(void)
{
	Message< std::pair<int, int> > reshapeEvent;

	if (!mReshapeQueue.empty())
	{
		reshapeEvent = mReshapeQueue.front();

		mReshapeQueue.pop();
	}

	return reshapeEvent;
}
