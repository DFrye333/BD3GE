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
	const std::string KEY_BACKSPACE = 		"KEY_BACKSPACE";
	const std::string KEY_TAB =				"KEY_TAB";
	const std::string KEY_ESCAPE = 			"KEY_ESCAPE";
	const std::string KEY_SPACE =			"KEY_SPACE";
	const std::string KEY_APOSTROPHE =		"KEY_APOSTROPHE";
	const std::string KEY_COMMA =			"KEY_COMMA";
	const std::string KEY_MINUS =			"KEY_MINUS";
	const std::string KEY_PERIOD =			"KEY_PERIOD";
	const std::string KEY_SLASH =			"KEY_SLASH";
	const std::string KEY_0 =				"KEY_0";
	const std::string KEY_1 =				"KEY_1";
	const std::string KEY_2 =				"KEY_2";
	const std::string KEY_3 =				"KEY_3";
	const std::string KEY_4 =				"KEY_4";
	const std::string KEY_5 =				"KEY_5";
	const std::string KEY_6 =				"KEY_6";
	const std::string KEY_7 =				"KEY_7";
	const std::string KEY_8 =				"KEY_8";
	const std::string KEY_9 =				"KEY_9";
	const std::string KEY_SEMICOLON =		"KEY_SEMICOLON";
	const std::string KEY_EQUAL =			"KEY_EQUAL";
	const std::string KEY_BRACKETLEFT =		"KEY_BRACKETLEFT";
	const std::string KEY_BACKSLASH =		"KEY_BACKSLASH";
	const std::string KEY_BRACKETRIGHT =	"KEY_BRACKETRIGHT";
	const std::string KEY_GRAVE =			"KEY_GRAVE";
	const std::string KEY_A = 				"KEY_A";
	const std::string KEY_B = 				"KEY_B";
	const std::string KEY_C = 				"KEY_C";
	const std::string KEY_D = 				"KEY_D";
	const std::string KEY_E = 				"KEY_E";
	const std::string KEY_F = 				"KEY_F";
	const std::string KEY_G = 				"KEY_G";
	const std::string KEY_H = 				"KEY_H";
	const std::string KEY_I = 				"KEY_I";
	const std::string KEY_J = 				"KEY_J";
	const std::string KEY_K = 				"KEY_K";
	const std::string KEY_L = 				"KEY_L";
	const std::string KEY_M = 				"KEY_M";
	const std::string KEY_N = 				"KEY_N";
	const std::string KEY_O = 				"KEY_O";
	const std::string KEY_P = 				"KEY_P";
	const std::string KEY_Q = 				"KEY_Q";
	const std::string KEY_R = 				"KEY_R";
	const std::string KEY_S = 				"KEY_S";
	const std::string KEY_T = 				"KEY_T";
	const std::string KEY_U = 				"KEY_U";
	const std::string KEY_V = 				"KEY_V";
	const std::string KEY_W = 				"KEY_W";
	const std::string KEY_X = 				"KEY_X";
	const std::string KEY_Y = 				"KEY_Y";
	const std::string KEY_Z = 				"KEY_Z";
	const std::string KEY_RETURN =			"KEY_RETURN";
	const std::string KEY_PRINT =			"KEY_PRINT";
	const std::string KEY_SCROLLLOCK =		"KEY_SCROLLLOCK";
	const std::string KEY_PAUSE =			"KEY_PAUSE";
	const std::string KEY_INSERT =			"KEY_INSERT";
	const std::string KEY_HOME =			"KEY_HOME";
	const std::string KEY_PRIOR =			"KEY_PRIOR";
	const std::string KEY_DELETE =			"KEY_DELETE";
	const std::string KEY_END =				"KEY_END";
	const std::string KEY_NEXT =			"KEY_NEXT";
	const std::string KEY_UP =				"KEY_UP";
	const std::string KEY_LEFT =			"KEY_LEFT";
	const std::string KEY_DOWN =			"KEY_DOWN";
	const std::string KEY_RIGHT =			"KEY_RIGHT";
	const std::string KEY_SHIFTL =			"KEY_SHIFTL";
	const std::string KEY_SHIFTR =			"KEY_SHIFTR";
	const std::string KEY_CONTROLL =		"KEY_CONTROLL";
	const std::string KEY_CONTROLR =		"KEY_CONTROLR";
	const std::string KEY_ALTL =			"KEY_ALTL";
	const std::string KEY_ALTR =			"KEY_ALTR";
	const std::string KEY_SUPERL =			"KEY_SUPERL";
	const std::string KEY_CAPSLOCK =		"KEY_CAPSLOCK";
	const std::string KEY_NUMLOCK =			"KEY_NUMLOCK";
	const std::string KEY_F1 =				"KEY_F1";
	const std::string KEY_F2 =				"KEY_F2";
	const std::string KEY_F3 =				"KEY_F3";
	const std::string KEY_F4 =				"KEY_F4";
	const std::string KEY_F5 =				"KEY_F5";
	const std::string KEY_F6 =				"KEY_F6";
	const std::string KEY_F7 =				"KEY_F7";
	const std::string KEY_F8 =				"KEY_F8";
	const std::string KEY_F9 =				"KEY_F9";
	const std::string KEY_F10 =				"KEY_F10";
	const std::string KEY_F11 =				"KEY_F11";
	const std::string KEY_F12 =				"KEY_F12";
	const std::string KEY_KPDIVIDE =		"KEY_KPDIVIDE";
	const std::string KEY_KPMULTIPLY =		"KEY_KPMULTIPLY";
	const std::string KEY_KPSUBTRACT =		"KEY_KPSUBTRACT";
	const std::string KEY_KPADD =			"KEY_KPADD";
	const std::string KEY_KPENTER =			"KEY_KPENTER";
	const std::string KEY_KPDECIMAL =		"KEY_KPDECIMAL";
	const std::string KEY_KP0 =				"KEY_KP0";
	const std::string KEY_KP1 =				"KEY_KP1";
	const std::string KEY_KP2 =				"KEY_KP2";
	const std::string KEY_KP3 =				"KEY_KP3";
	const std::string KEY_KP4 =				"KEY_KP4";
	const std::string KEY_KP5 =				"KEY_KP5";
	const std::string KEY_KP6 =				"KEY_KP6";
	const std::string KEY_KP7 =				"KEY_KP7";
	const std::string KEY_KP8 =				"KEY_KP8";
	const std::string KEY_KP9 =				"KEY_KP9";
}

#endif // CONSTANTS_H
