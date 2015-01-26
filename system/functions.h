#ifndef UTIL_H
#define UTIL_H

#include <sys/time.h>

#include "../audio/AL.h"
#include "constants.h"
#include "globals.h"

void init(void);
void quit(void);
void keyboard(void);
void run(void);

#endif // UTIL_H
