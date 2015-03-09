#ifndef GAME_H
#define GAME_H

#include <sys/time.h>

#include "../audio/AL.h"
#include "../input/input.h"
#include "../utility/timer.h"
#include "../video/GL.h"
#include "../video/scene.h"
#include "constants.h"
#include "XWindow.h"

class Game
{
	public:
				Game();
		void	startup(void);
		void	shutdown(void);
		void 	run(void);
		void	busMessages(void);

	private:

		bool	mRunning;
		// The below order matters! For instance, if mXWindow is placed after (and therefore initialized after) mGL, the OpenGL context is not properly set up.
		XWindow	mXWindow;
		Scene	mScene;
		GL		mGL;
		AL		mAL;
		Input	mInput;
};

#endif // GAME_H
