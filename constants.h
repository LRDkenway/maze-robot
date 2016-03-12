#ifndef __constants_h__
#define __constants_h__

#define VERBOSE_DFS
#define VERBOSE_STACK

#ifdef TEST

#include <iostream>
#define print_out(x) std::cout << (x);

#include <time.h>
#define random(l, u) (u - 1 - (rand() % (u - i)))

#define HIGH 1
#define LOW 0
#define OUTPUT 1
#define INPUT 0

#define digitalWrite(x,y)
#define pinMode(x,y)
#define delayMicroseconds(x)
#define analogRead(x) 0
#define micros() 0

#else /* TEST */

#include "Arduino.h"
#define print_out(x) Serial.print(x);

#endif /* TEST */



#define NUM_ROWS 13
#define NUM_COLS 13



#endif /* __constants_h__ */
