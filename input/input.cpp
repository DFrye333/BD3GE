#include "input.h"

/*
 *	Input class
 */

Input::Input()
{
	// TODO: I should probably remove all of this dead code.
//	std::map<const std::string, bool> mKeystringTable = {
//			{BD3GE_KEY_BACKSPACE, false}, {BD3GE_KEY_TAB, false}, {BD3GE_KEY_ESCAPE, false}, {BD3GE_KEY_SPACE, false},
//			{BD3GE_KEY_APOSTROPHE, false}, {BD3GE_KEY_COMMA, false}, {BD3GE_KEY_MINUS, false}, {BD3GE_KEY_PERIOD, false},
//			{BD3GE_KEY_SLASH, false}, {BD3GE_KEY_0, false}, {BD3GE_KEY_1, false}, {BD3GE_KEY_2, false},
//			{BD3GE_KEY_3, false}, {BD3GE_KEY_4, false}, {BD3GE_KEY_5, false}, {BD3GE_KEY_6, false},
//			{BD3GE_KEY_7, false}, {BD3GE_KEY_8, false}, {BD3GE_KEY_9, false}, {BD3GE_KEY_SEMICOLON, false},
//			{BD3GE_KEY_EQUAL, false}, {BD3GE_KEY_BRACKETLEFT, false}, {BD3GE_KEY_BACKSLASH, false}, {BD3GE_KEY_BRACKETRIGHT, false},
//			{BD3GE_KEY_GRAVE, false}, {BD3GE_KEY_A, false}, {BD3GE_KEY_B, false}, {BD3GE_KEY_C, false},
//			{BD3GE_KEY_D, false}, {BD3GE_KEY_E, false}, {BD3GE_KEY_F, false}, {BD3GE_KEY_G, false},
//			{BD3GE_KEY_H, false}, {BD3GE_KEY_I, false}, {BD3GE_KEY_J, false}, {BD3GE_KEY_K, false},
//			{BD3GE_KEY_L, false}, {BD3GE_KEY_M, false}, {BD3GE_KEY_N, false}, {BD3GE_KEY_O, false},
//			{BD3GE_KEY_P, false}, {BD3GE_KEY_Q, false}, {BD3GE_KEY_R, false}, {BD3GE_KEY_S, false},
//			{BD3GE_KEY_T, false}, {BD3GE_KEY_U, false}, {BD3GE_KEY_V, false}, {BD3GE_KEY_W, false},
//			{BD3GE_KEY_X, false}, {BD3GE_KEY_Y, false}, {BD3GE_KEY_Z, false}, {BD3GE_KEY_RETURN, false},
//			{BD3GE_KEY_PRINT, false}, {BD3GE_KEY_SCROLLLOCK, false}, {BD3GE_KEY_PAUSE, false}, {BD3GE_KEY_INSERT, false},
//			{BD3GE_KEY_HOME, false}, {BD3GE_KEY_PRIOR, false}, {BD3GE_KEY_DELETE, false}, {BD3GE_KEY_END, false},
//			{BD3GE_KEY_NEXT, false}, {BD3GE_KEY_UP, false}, {BD3GE_KEY_LEFT, false}, {BD3GE_KEY_DOWN, false},
//			{BD3GE_KEY_RIGHT, false}, {BD3GE_KEY_SHIFTL, false}, {BD3GE_KEY_SHIFTR, false}, {BD3GE_KEY_CONTROLL, false},
//			{BD3GE_KEY_CONTROLR, false}, {BD3GE_KEY_ALTL, false}, {BD3GE_KEY_ALTR, false}, {BD3GE_KEY_SUPERL, false},
//			{BD3GE_KEY_CAPSLOCK, false}, {BD3GE_KEY_NUMLOCK, false}, {BD3GE_KEY_F1, false}, {BD3GE_KEY_F2, false},
//			{BD3GE_KEY_F3, false}, {BD3GE_KEY_F4, false}, {BD3GE_KEY_F5, false}, {BD3GE_KEY_F6, false},
//			{BD3GE_KEY_F7, false}, {BD3GE_KEY_F8, false}, {BD3GE_KEY_F9, false}, {BD3GE_KEY_F10, false},
//			{BD3GE_KEY_F11, false}, {BD3GE_KEY_F12, false}, {BD3GE_KEY_KPDIVIDE, false}, {BD3GE_KEY_KPMULTIPLY, false},
//			{BD3GE_KEY_KPSUBTRACT, false}, {BD3GE_KEY_KPADD, false}, {BD3GE_KEY_KPENTER, false}, {BD3GE_KEY_KPDECIMAL, false},
//			{BD3GE_KEY_KP0, false}, {BD3GE_KEY_KP1, false}, {BD3GE_KEY_KP2, false}, {BD3GE_KEY_KP3, false},
//			{BD3GE_KEY_KP4, false}, {BD3GE_KEY_KP5, false}, {BD3GE_KEY_KP6, false}, {BD3GE_KEY_KP7, false},
//			{BD3GE_KEY_KP8, false}, {BD3GE_KEY_KP9, false}
//	};
}

void Input::handler(Message< std::pair <char*, bool> > message)
{
	if (message.getData())
	{
		setKeyState(message.getData()->first, message.getData()->second);

		if (message.getData()->second == true)
		{
			// TODO: Implement logging.
//			std::cout << BD3GE_PRINT_INFORMATION << "'" << message.getData()->first << "' key pressed." << std::endl;
		}

		else if (message.getData()->second == false)
		{
			// TODO: Implement logging.
//			std::cout << BD3GE_PRINT_INFORMATION << "'" << message.getData()->first << "' key released" << std::endl;
		}
	}
}

void Input::setKeyState(std::string key, bool state)
{
	mKeys[key] = state;
}

bool Input::getKeyState(const std::string key)
{
	return mKeys[key];
}
