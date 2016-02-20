#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace BD3GE
{
	const std::string 	WINDOW_TITLE = 	"Game Prototype 0 | BD3GE";

	const std::string	DEFAULT_SYSTEM_DIRECTORY	=	"/home/david/.local/share/BD3GE/";
	const std::string	DEFAULT_LOG_DIRECTORY		=	"log/";
	const std::string	DEFAULT_LOG_FILE			=	"BD3GE.log";
	const std::string	LOG_PRINT_INFORMATION		=	"(BD3GE | Information): ";
	const std::string	LOG_PRINT_ERROR				=	"(BD3GE | Error): ";

	const int			SCREEN_WIDTH = 	1920;
	const int			SCREEN_HEIGHT =	1080;
	const int			WINDOW_WIDTH =	1600;
	const int			WINDOW_HEIGHT =	900;

	const float			PLAYER_SPEED = 1.0f;

	typedef enum
	{
		LOG_INFORMATION =	0,
		LOG_ERROR = 		1
	} LOG_OUTPUT;

	// Number of ticks to be processed per-second.
	const float			TICK_RATE = 60.0f;
	// Minimum time between ticks, in milliseconds.
	const float			TICK_TIME = (1.0f / TICK_RATE) * 1000.0f;

	// Number of frames to be processed per-second.
	const float			FRAME_RATE = 60.0f;
	// Minimum time between frames, in milliseconds.
	const float			FRAME_TIME = (1.0f / FRAME_RATE) * 1000.0f;

	// Number of keys contained within the input handler.
	const int			KEY_COUNT = 128;

	// Keystring mappings.
	const std::string KEY_BACKSPACE = 		"BackSpace";
	const std::string KEY_TAB =				"Tab";
	const std::string KEY_ESCAPE = 			"Escape";
	const std::string KEY_SPACE =			"space";
	const std::string KEY_APOSTROPHE =		"apostrophe";
	const std::string KEY_COMMA =			"comma";
	const std::string KEY_MINUS =			"minus";
	const std::string KEY_PERIOD =			"period";
	const std::string KEY_SLASH =			"slash";
	const std::string KEY_0 =				"0";
	const std::string KEY_1 =				"1";
	const std::string KEY_2 =				"2";
	const std::string KEY_3 =				"3";
	const std::string KEY_4 =				"4";
	const std::string KEY_5 =				"5";
	const std::string KEY_6 =				"6";
	const std::string KEY_7 =				"7";
	const std::string KEY_8 =				"8";
	const std::string KEY_9 =				"9";
	const std::string KEY_SEMICOLON =		"semicolon";
	const std::string KEY_EQUAL =			"equal";
	const std::string KEY_BRACKETLEFT =		"bracketleft";
	const std::string KEY_BACKSLASH =		"backslash";
	const std::string KEY_BRACKETRIGHT =	"bracketright";
	const std::string KEY_GRAVE =			"grave";
	const std::string KEY_A = 				"a";
	const std::string KEY_B = 				"b";
	const std::string KEY_C = 				"c";
	const std::string KEY_D = 				"d";
	const std::string KEY_E = 				"e";
	const std::string KEY_F = 				"f";
	const std::string KEY_G = 				"g";
	const std::string KEY_H = 				"h";
	const std::string KEY_I = 				"i";
	const std::string KEY_J = 				"j";
	const std::string KEY_K = 				"k";
	const std::string KEY_L = 				"l";
	const std::string KEY_M = 				"m";
	const std::string KEY_N = 				"n";
	const std::string KEY_O = 				"o";
	const std::string KEY_P = 				"p";
	const std::string KEY_Q = 				"q";
	const std::string KEY_R = 				"r";
	const std::string KEY_S = 				"s";
	const std::string KEY_T = 				"t";
	const std::string KEY_U = 				"u";
	const std::string KEY_V = 				"v";
	const std::string KEY_W = 				"w";
	const std::string KEY_X = 				"x";
	const std::string KEY_Y = 				"y";
	const std::string KEY_Z = 				"z";
	const std::string KEY_RETURN =			"Return";
	const std::string KEY_PRINT =			"Print";
	const std::string KEY_SCROLLLOCK =		"Scroll_Lock";
	const std::string KEY_PAUSE =			"Pause";
	const std::string KEY_INSERT =			"Insert";
	const std::string KEY_HOME =			"Home";
	const std::string KEY_PRIOR =			"Prior";
	const std::string KEY_DELETE =			"Delete";
	const std::string KEY_END =				"End";
	const std::string KEY_NEXT =			"Next";
	const std::string KEY_UP =				"Up";
	const std::string KEY_LEFT =			"Left";
	const std::string KEY_DOWN =			"Down";
	const std::string KEY_RIGHT =			"Right";
	const std::string KEY_SHIFTL =			"Shift_L";
	const std::string KEY_SHIFTR =			"Shift_R";
	const std::string KEY_CONTROLL =		"Control_L";
	const std::string KEY_CONTROLR =		"Control_R";
	const std::string KEY_ALTL =			"Alt_L";
	const std::string KEY_ALTR =			"Alt_R";
	const std::string KEY_SUPERL =			"Super_L";
	const std::string KEY_CAPSLOCK =		"Caps_Lock";
	const std::string KEY_NUMLOCK =			"Num_Lock";
	const std::string KEY_F1 =				"F1";
	const std::string KEY_F2 =				"F2";
	const std::string KEY_F3 =				"F3";
	const std::string KEY_F4 =				"F4";
	const std::string KEY_F5 =				"F5";
	const std::string KEY_F6 =				"F6";
	const std::string KEY_F7 =				"F7";
	const std::string KEY_F8 =				"F8";
	const std::string KEY_F9 =				"F9";
	const std::string KEY_F10 =				"F10";
	const std::string KEY_F11 =				"F11";
	const std::string KEY_F12 =				"F12";
	const std::string KEY_KPDIVIDE =		"KP_Divide";
	const std::string KEY_KPMULTIPLY =		"KP_Multiply";
	const std::string KEY_KPSUBTRACT =		"KP_Subtract";
	const std::string KEY_KPADD =			"KP_Add";
	const std::string KEY_KPENTER =			"KP_Enter";
	const std::string KEY_KPDECIMAL =		"KP_Decimal";
	const std::string KEY_KP0 =				"KP_0";
	const std::string KEY_KP1 =				"KP_1";
	const std::string KEY_KP2 =				"KP_2";
	const std::string KEY_KP3 =				"KP_3";
	const std::string KEY_KP4 =				"KP_4";
	const std::string KEY_KP5 =				"KP_5";
	const std::string KEY_KP6 =				"KP_6";
	const std::string KEY_KP7 =				"KP_7";
	const std::string KEY_KP8 =				"KP_8";
	const std::string KEY_KP9 =				"KP_9";
}

#endif // CONSTANTS_H
