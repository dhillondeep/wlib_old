#ifndef WLIB_WLIB_H
#define WLIB_WLIB_H

#include <Arduino.h>

#if defined(AVR)
#include "core/pins/Hardware/AVR/Board.h"
#elif defined(SAM)
#include "core/pins/Hardware/SAM/Board.h"
#endif

#endif //WLIB_WLIB_H
