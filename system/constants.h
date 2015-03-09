#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

const std::string 	BD3GE_WINDOW_TITLE = 	"Game Prototype 0";

const std::string	BD3GE_PRINT_INFORMATION =	"(BD3GE | Information): ";
const std::string	BD3GE_PRINT_ERROR = 		"(BD3GE | Error): ";

const int			BD3GE_SCREEN_WIDTH = 	1920;
const int			BD3GE_SCREEN_HEIGHT =	1080;
const int			BD3GE_WINDOW_WIDTH =	1600;
const int			BD3GE_WINDOW_HEIGHT =	900;

const float			BD3GE_PLAYER_SPEED = 0.1;

// Number of ticks to be processed per-second.
const float			BD3GE_TICK_RATE = 60.0;
// Minimum time between ticks, in milliseconds.
const float			BD3GE_TICK_TIME = (1.0 / BD3GE_TICK_RATE) * 1000.0;

// Number of frames to be processed per-second.
const float			BD3GE_FRAME_RATE = 60.0;
// Minimum time between frames, in milliseconds.
const float			BD3GE_FRAME_TIME = (1.0 / BD3GE_FRAME_RATE) * 1000.0;

// Number of keys contained within the input handler.
const int			BD3GE_KEY_COUNT = 128;

// Keystring mappings.
const std::string	BD3GE_KEY_BACKSPACE = 		"BackSpace";
const std::string	BD3GE_KEY_TAB =				"Tab";
const std::string	BD3GE_KEY_ESCAPE = 			"Escape";
const std::string	BD3GE_KEY_SPACE =			"space";
const std::string	BD3GE_KEY_APOSTROPHE =		"apostrophe";
const std::string	BD3GE_KEY_COMMA =			"comma";
const std::string	BD3GE_KEY_MINUS =			"minus";
const std::string	BD3GE_KEY_PERIOD =			"period";
const std::string	BD3GE_KEY_SLASH =			"slash";
const std::string	BD3GE_KEY_0 =				"0";
const std::string	BD3GE_KEY_1 =				"1";
const std::string	BD3GE_KEY_2 =				"2";
const std::string	BD3GE_KEY_3 =				"3";
const std::string	BD3GE_KEY_4 =				"4";
const std::string	BD3GE_KEY_5 =				"5";
const std::string	BD3GE_KEY_6 =				"6";
const std::string	BD3GE_KEY_7 =				"7";
const std::string	BD3GE_KEY_8 =				"8";
const std::string	BD3GE_KEY_9 =				"9";
const std::string	BD3GE_KEY_SEMICOLON =		"semicolon";
const std::string	BD3GE_KEY_EQUAL =			"equal";
const std::string	BD3GE_KEY_BRACKETLEFT =		"bracketleft";
const std::string	BD3GE_KEY_BACKSLASH =		"backslash";
const std::string	BD3GE_KEY_BRACKETRIGHT =	"bracketright";
const std::string	BD3GE_KEY_GRAVE =			"grave";
const std::string	BD3GE_KEY_A = 				"a";
const std::string	BD3GE_KEY_B = 				"b";
const std::string	BD3GE_KEY_C = 				"c";
const std::string	BD3GE_KEY_D = 				"d";
const std::string	BD3GE_KEY_E = 				"e";
const std::string	BD3GE_KEY_F = 				"f";
const std::string	BD3GE_KEY_G = 				"g";
const std::string	BD3GE_KEY_H = 				"h";
const std::string	BD3GE_KEY_I = 				"i";
const std::string	BD3GE_KEY_J = 				"j";
const std::string	BD3GE_KEY_K = 				"k";
const std::string	BD3GE_KEY_L = 				"l";
const std::string	BD3GE_KEY_M = 				"m";
const std::string	BD3GE_KEY_N = 				"n";
const std::string	BD3GE_KEY_O = 				"o";
const std::string	BD3GE_KEY_P = 				"p";
const std::string	BD3GE_KEY_Q = 				"q";
const std::string	BD3GE_KEY_R = 				"r";
const std::string	BD3GE_KEY_S = 				"s";
const std::string	BD3GE_KEY_T = 				"t";
const std::string	BD3GE_KEY_U = 				"u";
const std::string	BD3GE_KEY_V = 				"v";
const std::string	BD3GE_KEY_W = 				"w";
const std::string	BD3GE_KEY_X = 				"x";
const std::string	BD3GE_KEY_Y = 				"y";
const std::string	BD3GE_KEY_Z = 				"z";
const std::string	BD3GE_KEY_RETURN =			"Return";
const std::string	BD3GE_KEY_PRINT =			"Print";
const std::string	BD3GE_KEY_SCROLLLOCK =		"Scroll_Lock";
const std::string	BD3GE_KEY_PAUSE =			"Pause";
const std::string	BD3GE_KEY_INSERT =			"Insert";
const std::string	BD3GE_KEY_HOME =			"Home";
const std::string	BD3GE_KEY_PRIOR =			"Prior";
const std::string	BD3GE_KEY_DELETE =			"Delete";
const std::string	BD3GE_KEY_END =				"End";
const std::string	BD3GE_KEY_NEXT =			"Next";
const std::string	BD3GE_KEY_UP =				"Up";
const std::string	BD3GE_KEY_LEFT =			"Left";
const std::string	BD3GE_KEY_DOWN =			"Down";
const std::string	BD3GE_KEY_RIGHT =			"Right";
const std::string	BD3GE_KEY_SHIFTL =			"Shift_L";
const std::string	BD3GE_KEY_SHIFTR =			"Shift_R";
const std::string	BD3GE_KEY_CONTROLL =		"Control_L";
const std::string	BD3GE_KEY_CONTROLR =		"Control_R";
const std::string	BD3GE_KEY_ALTL =			"Alt_L";
const std::string	BD3GE_KEY_ALTR =			"Alt_R";
const std::string	BD3GE_KEY_SUPERL =			"Super_L";
const std::string	BD3GE_KEY_CAPSLOCK =		"Caps_Lock";
const std::string	BD3GE_KEY_NUMLOCK =			"Num_Lock";
const std::string	BD3GE_KEY_F1 =				"F1";
const std::string	BD3GE_KEY_F2 =				"F2";
const std::string	BD3GE_KEY_F3 =				"F3";
const std::string	BD3GE_KEY_F4 =				"F4";
const std::string	BD3GE_KEY_F5 =				"F5";
const std::string	BD3GE_KEY_F6 =				"F6";
const std::string	BD3GE_KEY_F7 =				"F7";
const std::string	BD3GE_KEY_F8 =				"F8";
const std::string	BD3GE_KEY_F9 =				"F9";
const std::string	BD3GE_KEY_F10 =				"F10";
const std::string	BD3GE_KEY_F11 =				"F11";
const std::string	BD3GE_KEY_F12 =				"F12";
const std::string	BD3GE_KEY_KPDIVIDE =		"KP_Divide";
const std::string	BD3GE_KEY_KPMULTIPLY =		"KP_Multiply";
const std::string	BD3GE_KEY_KPSUBTRACT =		"KP_Subtract";
const std::string	BD3GE_KEY_KPADD =			"KP_Add";
const std::string	BD3GE_KEY_KPENTER =			"KP_Enter";
const std::string	BD3GE_KEY_KPDECIMAL =		"KP_Decimal";
const std::string	BD3GE_KEY_KP0 =				"KP_0";
const std::string	BD3GE_KEY_KP1 =				"KP_1";
const std::string	BD3GE_KEY_KP2 =				"KP_2";
const std::string	BD3GE_KEY_KP3 =				"KP_3";
const std::string	BD3GE_KEY_KP4 =				"KP_4";
const std::string	BD3GE_KEY_KP5 =				"KP_5";
const std::string	BD3GE_KEY_KP6 =				"KP_6";
const std::string	BD3GE_KEY_KP7 =				"KP_7";
const std::string	BD3GE_KEY_KP8 =				"KP_8";
const std::string	BD3GE_KEY_KP9 =				"KP_9";

#endif // CONSTANTS_H
