#ifndef BD3GE_CONSTANTS_H
#define BD3GE_CONSTANTS_H

#include <string>

namespace BD3GE {
	const std::string 	WINDOW_TITLE = 	"BD3GE";

#ifdef __linux__
	// TODO: Come up with a more permanent location for this
	const std::string	DEFAULT_RELATIVE_SYSTEM_DIRECTORY	=	"/home/david/.local/share/BD3GE/";
#elif _WIN32
	// Relative to Local AppData.
	const std::string	DEFAULT_RELATIVE_SYSTEM_DIRECTORY	=	"BD3GE/";
#endif
	const std::string	DEFAULT_LOG_DIRECTORY		=	"log/";
	const std::string	DEFAULT_LOG_FILE			=	"BD3GE.log";
	const std::string	DEFAULT_RESOURCE_DIRECTORY	=	"resources/";
	const std::string	DEFAULT_MODEL_DIRECTORY		=	DEFAULT_RESOURCE_DIRECTORY + "models/";
	const std::string	DEFAULT_SHADER_DIRECTORY	=	DEFAULT_RESOURCE_DIRECTORY + "shaders/";
	const std::string	DEFAULT_TEXTURE_DIRECTORY	=	DEFAULT_RESOURCE_DIRECTORY + "textures/";
	const std::string	LOG_PRINT_INFORMATION		=	"(BD3GE | Information): ";
	const std::string	LOG_PRINT_ERROR				=	"(BD3GE | Error): ";

	const int			SCREEN_WIDTH = 	3440;
	const int			SCREEN_HEIGHT =	1440;
	const int			WINDOW_WIDTH =	1920;
	const int			WINDOW_HEIGHT =	1080;

	const float			PLAYER_SPEED = 1.0f;
	const float			CAMERA_SPEED = 1.0f;

	// Number of ticks to be processed per-second.
	const float			TICK_RATE = 60.0f;
	// Minimum time between ticks, in milliseconds.
	const float			TICK_TIME = (1.0f / TICK_RATE) * 1000.0f;

	// Number of frames to be processed per-second.
	const float			FRAME_RATE = 60.0f;
	// Minimum time between frames, in milliseconds.
	const float			FRAME_TIME = (1.0f / FRAME_RATE) * 1000.0f;

	constexpr double	PI = 3.1415926535;
	constexpr float		FLOAT_EPSILON = 1.0e-12f;

	// Keystring mappings.
	enum class KEY_CODE {
		BACKSPACE,
		TAB,
		ESCAPE,
		SPACE,
		QUOTE,
		COMMA,
		MINUS,
		PERIOD,
		SLASH,
		NUM_0,
		NUM_1,
		NUM_2,
		NUM_3,
		NUM_4,
		NUM_5,
		NUM_6,
		NUM_7,
		NUM_8,
		NUM_9,
		SEMICOLON,
		EQUAL,
		BRACKETLEFT,
		BACKSLASH,
		BRACKETRIGHT,
		GRAVE,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		RETURN,
		PRINTSCREEN,
		SCROLLLOCK,
		PAUSE,
		INSERT,
		HOME,
		PAGEUP,
		DEL,
		END,
		PAGEDOWN,
		UP,
		LEFT,
		DOWN,
		RIGHT,
		SHIFT,
		SHIFTL,
		SHIFTR,
		CONTROLL,
		CONTROLR,
		ALTL,
		ALTR,
		SUPERL,
		CAPSLOCK,
		NUMLOCK,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		F16,
		F17,
		F18,
		F19,
		F20,
		F21,
		F22,
		F23,
		F24,
		KP_DIVIDE,
		KP_MULTIPLY,
		KP_SUBTRACT,
		KP_ADD,
		KP_ENTER,
		KP_DECIMAL,
		KP_0,
		KP_1,
		KP_2,
		KP_3,
		KP_4,
		KP_5,
		KP_6,
		KP_7,
		KP_8,
		KP_9,
		MOUSE_LEFTBUTTON,
		MOUSE_RIGHTBUTTON,
		MOUSE_MIDDLEBUTTON,
		MOUSE_X1BUTTON,
		MOUSE_X2BUTTON,
		MOUSE_WHEELUP,
		MOUSE_WHEELDOWN
	};
}

#endif // BD3GE_CONSTANTS_H