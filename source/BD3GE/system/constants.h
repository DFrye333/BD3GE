#ifndef BD3GE_CONSTANTS_H
#define BD3GE_CONSTANTS_H

#include <string>

namespace BD3GE {
	const std::string 	DEFAULT_WINDOW_TITLE = 	"BD3GE";

#ifdef __linux__
	// TODO: Come up with a more permanent location for this
	const std::string	DEFAULT_RELATIVE_SYSTEM_DIRECTORY	=	"/home/david/.local/share/BD3GE/";
#elif _WIN32
	// Relative to Local AppData.
	const std::string	DEFAULT_RELATIVE_SYSTEM_DIRECTORY	=	"BD3GE/";
#endif
	const std::string	DEFAULT_LOG_DIRECTORY		=	"log/";
	const std::string	DEFAULT_LOG_FILE			=	"BD3GE.log";
	const std::string	DEFAULT_CONFIG_FILE			=	"BD3GE.config";
	const std::string	DEFAULT_RESOURCE_DIRECTORY	=	"resources/";
	const std::string	DEFAULT_MODEL_DIRECTORY		=	DEFAULT_RESOURCE_DIRECTORY + "models/";
	const std::string	DEFAULT_SHADER_DIRECTORY	=	DEFAULT_RESOURCE_DIRECTORY + "shaders/";
	const std::string	DEFAULT_TEXTURE_DIRECTORY	=	DEFAULT_RESOURCE_DIRECTORY + "textures/";
	const std::string	LOG_PRINT_INFORMATION		=	"(BD3GE | Information): ";
	const std::string	LOG_PRINT_ERROR				=	"(BD3GE | Error): ";

	const int			SCREEN_WIDTH = 	3440;
	const int			SCREEN_HEIGHT =	1440;
	const int			DEFAULT_WINDOW_WIDTH =	1920;
	const int			DEFAULT_WINDOW_HEIGHT =	1080;

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
}

#endif // BD3GE_CONSTANTS_H
