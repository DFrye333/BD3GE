#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

const std::string 	BD3GE_WINDOW_TITLE = "Game Prototype 0";

const std::string	BD3GE_PRINT_INFORMATION = "(BD3GE | Information): ";
const std::string	BD3GE_PRINT_ERROR = "(BD3GE | Error): ";

const int			BD3GE_SCREEN_WIDTH = 1920;
const int			BD3GE_SCREEN_HEIGHT = 1080;
const int			BD3GE_WINDOW_WIDTH = 1600;
const int			BD3GE_WINDOW_HEIGHT = 900;

const float			BD3GE_PLAYER_SPEED = 0.1;

// Number of frames to be created per-second.
const float			BD3GE_FRAME_RATE = 60.0;
// Minimum time between frames, in milliseconds.
const float			BD3GE_FRAME_TIME = (1.0 / BD3GE_FRAME_RATE) * 1000.0;

// Number of keys contained within the input handler.
const int			BD3GE_KEY_COUNT = 64;
const char			BD3GE_KEY_W = 'w';
const char			BD3GE_KEY_S = 's';
const char			BD3GE_KEY_A = 'a';
const char			BD3GE_KEY_D = 'd';

#endif // CONSTANTS_H
