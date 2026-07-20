/*
 * Engine.h
 *
 *  Created on: Jul 20, 2026
 *      Author: andrea
 */

#ifndef LIBRARY_INC_AUDIOENGINE_H_
#define LIBRARY_INC_AUDIOENGINE_H_

#include "stdint.h"

typedef struct
{
	float* Sample;
	uint16_t SampleSize;

	float PhaseIncrement;
	float Phase;// fase intera tra 0 e sample size
} AudioEngine_TypeState;

float AudioEngine_Sample( AudioEngine_TypeState* State );

#endif /* LIBRARY_INC_AUDIOENGINE_H_ */
