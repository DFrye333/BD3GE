#ifndef XWINDOW_H
#define XWINDOW_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

#include <GL/glew.h>
#include <GL/glx.h>
#include <X11/Xlib.h>

#include "constants.h"
#include "globals.h"

class XWindow
{
	public:

						XWindow(void);
						~XWindow(void);
		void 			messageListener(void);
		void 			swapBuffers(void);
		unsigned int	getWindowWidth();
		unsigned int	getWindowHeight();

	private:

		Display* 				mDisplay;
		Window 					mWindow;
		GC 						mGraphicsContext;
		GLXFBConfig* 			mFBConfig;
		XVisualInfo* 			mVisualInfo;
		XSetWindowAttributes 	mWindowAttr;
		GLXContext 				mGlxContext;
		GLXWindow 				mGlxWindow;
		bool 					mDBFlag;
		// Single-buffered attributes.
		int 					mSBAttr[];
		// Double-buffered attributes.
		int 					mDBAttr[];
};

#endif // XWINDOW_H
