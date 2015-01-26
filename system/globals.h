#ifndef GLOBALS_H
#define GLOBALS_H

#include "../audio/AL.h"
#include "../input/input.h"
#include "../system/XWindow.h"
#include "../video/GL.h"

// Forward declaration.
class XWindow;
extern XWindow xWindow;

// Forward declaration.
class GL;
extern GL gl;

extern AL al;

// Forward declaration.
class Input;
extern Input input;

#endif // GLOBALS_H
