/*
 * Engine.h
 *
 *  Created on: Jul 20, 2026
 *      Author: andrea
 */

#ifndef LIBRARY_INC_ENGINE_H_
#define LIBRARY_INC_ENGINE_H_

#define PI	3.1415927f

#include "stdint.h"
#include "math.h"
#include "stdbool.h"

typedef struct
{
	float* Sample;
	uint16_t SampleSize;

	float PhaseIncrement;
	float Phase;// fase intera tra 0 e sample size
} Engine_TypeSampleState;

void Engine_SampleInit( Engine_TypeSampleState* SampleState, float* Sample, uint16_t SampleSize, float Frequency, float InitialPhase, float SampleRate );
float Engine_SampleStep( Engine_TypeSampleState* State );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Seno generato come risposta impulsiva di un sistema lineare, generato partendo da trasformata zeta del seno e
// ricavando per comparazione l'equazione alle differenze finite
typedef struct
{
	float A1;
	float Y1;
	float Y2;

} Engine_TypeSineGeneratorState;

void Engine_SineGeneratorInit( Engine_TypeSineGeneratorState* SineGeneratorState, float Frequency, float SampleRate );
float Engine_SineGeneratorStep( Engine_TypeSineGeneratorState* SineGeneratorState );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	bool Up;
	float RelTime;
	float Step;
	float HalfPeriod;
} Engine_TypeSawGeneratorState;

void Engine_SawGeneratorInit( Engine_TypeSawGeneratorState* SawGeneratorState, float Frequency, float SampleRate );
float Engine_SawGeneratorStep( Engine_TypeSawGeneratorState* SawGeneratorState );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	float RelTime;
	float Step;
	float Period;
} Engine_TypeSawtoothGeneratorState;

void Engine_SawtoothGeneratorInit( Engine_TypeSawtoothGeneratorState* SawtoothGeneratorState, float Frequency, float SampleRate );
float Engine_SawtoothGeneratorStep( Engine_TypeSawtoothGeneratorState* SawtoothGeneratorState );

#endif /* LIBRARY_INC_ENGINE_H_ */
