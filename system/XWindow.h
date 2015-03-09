#ifndef XWINDOW_H
#define XWINDOW_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include <queue>
#include <utility>

#include <GL/glew.h>
#include <GL/glx.h>
#include <X11/Xlib.h>

#include "../utility/message.h"
#include "constants.h"

class XWindow
{
	public:

											XWindow();
											~XWindow(void);
		void 								messageListener(void);
		void 								swapBuffers(void);
		Message< std::pair<char*, bool> >	pullInputMessage(void);
		Message< std::pair<int, int> >		pullReshapeMessage(void);

	private:

		std::queue< Message< std::pair<char*, bool> > >	mInputQueue;
		std::queue< Message< std::pair<int, int> > >	mReshapeQueue;
		Display* 										mDisplay;
		Window 											mWindow;
		GC 												mGraphicsContext;
		GLXFBConfig* 									mFBConfig;
		XVisualInfo* 									mVisualInfo;
		XSetWindowAttributes							mWindowAttr;
		GLXContext 										mGlxContext;
		GLXWindow 										mGlxWindow;
		bool 											mDBFlag;
		// Single-buffered attributes.
		int 											mSBAttr[];
		// Double-buffered attributes.
		int 											mDBAttr[];
};

#endif // XWINDOW_H
