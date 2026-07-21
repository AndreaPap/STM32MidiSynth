/*
 * Engine.h
 *
 *  Created on: Jul 20, 2026
 *      Author: andrea
 */

#ifndef LIBRARY_INC_ENGINE_H_
#define LIBRARY_INC_ENGINE_H_

#include "stdint.h"

typedef struct
{
	float* Sample;
	uint16_t SampleSize;

	float PhaseIncrement;
	float Phase;// fase intera tra 0 e sample size
} Engine_TypeSampleState;

void Engine_SampleInit( Engine_TypeSampleState* SampleState, float* Sample, uint16_t SampleSize, float Frequency, float InitialPhase, float SampleRate );
float Engine_SampleStep( Engine_TypeSampleState* State );

#endif /* LIBRARY_INC_ENGINE_H_ */
