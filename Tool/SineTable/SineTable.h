#ifndef SINE_TABLE
#define SINE_TABLE

#include "stdint.h"

extern const float PI2;
extern const uint32_t TableMask;
extern const float Table[ 16384 ];
extern float Sine( float Phase );

#endif
