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
	float Phase;			// fase attuale tra 0 e SampleSize
}
Engine_TypeSampleState;

void Engine_SampleInit( Engine_TypeSampleState* State, float* Sample, uint16_t SampleSize, float Frequency, float InitialPhase, float SampleRate );
float Engine_SampleStep( Engine_TypeSampleState* State );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Seno generato come risposta impulsiva di un sistema lineare, generato partendo da trasformata zeta del seno e
// ricavando per comparazione l'equazione alle differenze finite
typedef struct
{
	bool Init;
	float A0;
	float A1;
	float B1;
	float X1;
	float Y1;
	float Y2;
}
Engine_TypeSineGeneratorState;

void Engine_SineGeneratorInit( Engine_TypeSineGeneratorState* State, float Frequency, float InitialPhase, float SampleRate );
float Engine_SineGeneratorStep( Engine_TypeSineGeneratorState* State );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	bool Up;
	float RelTime;
	float Step;
	float HalfPeriod;
}
Engine_TypeSawGeneratorState;

void Engine_SawGeneratorInit( Engine_TypeSawGeneratorState* State, float Frequency, float InitialPhase, float SampleRate );
float Engine_SawGeneratorStep( Engine_TypeSawGeneratorState* State );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	float RelTime;
	float Step;
	float Period;
}
Engine_TypeSawtoothGeneratorState;

void Engine_SawtoothGeneratorInit( Engine_TypeSawtoothGeneratorState* State, float Frequency, float InitialPhase, float SampleRate );
float Engine_SawtoothGeneratorStep( Engine_TypeSawtoothGeneratorState* State );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	bool Init;
	float B1;
	float Y1;
}
Engine_TypeExpGeneratorState;

void Engine_ExpGeneratorInit( Engine_TypeExpGeneratorState* State, float Duration, float SampleRate );
float Engine_ExpGeneratorStep( Engine_TypeExpGeneratorState* State );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	bool Pressed;
	float Y1;
	uint8_t Phase;	// 0 attack, 1 decay, 2 sustain, 3 release
	float RelTime;
	float Step;

	float Attack;
	float AttackB1;

	float Decay;
	float DecayB1;

	float Sustain;

	float Release;
	float ReleaseB1;
}
Engine_TypeADSRGeneratorState;

void Engine_ADSRGeneratorInit( Engine_TypeADSRGeneratorState* State, float Attack, float Decay, float Sustain, float Release, float SampleRate );
float Engine_ADSRGeneratorStep( Engine_TypeADSRGeneratorState* State, bool Pressed );

#endif /* LIBRARY_INC_ENGINE_H_ */
