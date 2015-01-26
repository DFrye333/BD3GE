#ifndef INPUT_H
#define INPUT_H

#include <cstring>

#include <X11/Xlib.h>

#include "../system/functions.h"
#include "../system/constants.h"

class Key
{
	public:
				Key();
				~Key();
		void	setCharacter(char character)	{ mCharacter = character; }
		void	setState(bool state)			{ mState = state; }
		char	getCharacter(void)				{ return mCharacter; }
		bool	getState(void)					{ return mState; }
	protected:
		char	mCharacter;
		bool	mState;
};

class Input
{
	public:
				Input();
				~Input();
		void	handler(XEvent event);
		void	setKeyState(char character, bool state);
		bool	getKeyState(char character);
	protected:
		Key		mKeys[BD3GE_KEY_COUNT];
};

#endif // INPUT_H
