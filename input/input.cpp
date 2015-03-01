#include "input.h"

/*
 * 		Key class
 */

Key::Key()
{
	mCharacter = '\0';
	mState = false;
}

Key::~Key()
{
}

/*
 * 		Input class
 */

Input::Input()
{
	// Initialize a-z character keys
	for (unsigned int i = 0; i < 26; ++i)
	{
		mKeys[i].setCharacter((char)(i + 97));
	}
	// Initialize space key
	mKeys[26].setCharacter(' ');
}

Input::~Input()
{
}

void Input::handler(XEvent event)
{
	KeySym keysym;
	char *keyString = NULL;

	if (KeyPress == event.type)
	{
		XLookupString(&event.xkey, keyString, 32, &keysym, NULL);
		keyString = XKeysymToString(keysym);
		if (0 == strcmp("Escape", keyString))
		{
			quit();
		}
		setKeyState(*keyString, true);
		std::cout << BD3GE_PRINT_INFORMATION << "'" << keyString << "' key pressed." << std::endl;
	}

	else if (KeyRelease == event.type)
	{

		XLookupString(&event.xkey, keyString, 32, &keysym, NULL);
		keyString = XKeysymToString(keysym);
		setKeyState(*keyString, false);
		std::cout << BD3GE_PRINT_INFORMATION << "'" << keyString << "' key released" << std::endl;

	}
}

void Input::setKeyState(char character, bool state)
{
	for (unsigned int i = 0; i < BD3GE_KEY_COUNT; ++i)
	{
		if (mKeys[i].getCharacter() == character)
		{
			mKeys[i].setState(state);
		}
	}
}

bool Input::getKeyState(char character)
{
	for (unsigned int i = 0; i < BD3GE_KEY_COUNT; ++i)
	{
		if (mKeys[i].getCharacter() == character)
		{
			return mKeys[i].getState();
		}
	}

	return false;
}
