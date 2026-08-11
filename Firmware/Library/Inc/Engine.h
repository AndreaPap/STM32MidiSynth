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
Engine_TypeStateGeneratorSample;

void Engine_GeneratorSampleInit( Engine_TypeStateGeneratorSample* State, float* Sample, uint16_t SampleSize, float Frequency, float InitialPhase, float SampleRate );
float Engine_GeneratorSampleStep( Engine_TypeStateGeneratorSample* State );

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
Engine_TypeStateGeneratorSine;

void Engine_GeneratorSineInit( Engine_TypeStateGeneratorSine* State, float Frequency, float InitialPhase, float SampleRate );
float Engine_GeneratorSineStep( Engine_TypeStateGeneratorSine* State );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	bool Up;
	float RelTime;
	float Step;
	float HalfPeriod;
}
Engine_TypeStateGeneratorSaw;

void Engine_GeneratorSawInit( Engine_TypeStateGeneratorSaw* State, float Frequency, float InitialPhase, float SampleRate );
float Engine_GeneratorSawStep( Engine_TypeStateGeneratorSaw* State );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	float RelTime;
	float Step;
	float Period;
}
Engine_TypeStateGeneratorSawtooth;

void Engine_GeneratorSawtoothInit( Engine_TypeStateGeneratorSawtooth* State, float Frequency, float InitialPhase, float SampleRate );
float Engine_GeneratorSawtoothStep( Engine_TypeStateGeneratorSawtooth* State );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	bool Init;
	float B1;
	float Y1;
}
Engine_TypeStateGeneratorExp;

void Engine_GeneratorExpInit( Engine_TypeStateGeneratorExp* State, float Duration, float SampleRate );
float Engine_GeneratorExpStep( Engine_TypeStateGeneratorExp* State );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	bool Pressed;
	float Y1;
	uint8_t Phase;	// 0 attack, 1 decay, 2 sustain, 3 release
	float RelTime;
	float Step;
	float SampleRate;
	Engine_TypeStateGeneratorExp ExpGenerator;
	float Attack;
	float Decay;
	float Sustain;
	float Release;
	float AttackStart;	// valore da cui parte attack ( non è per forza 0 se release non nullo )
	float ReleaseStart;	// valore da cui parte al release ( non è per forza il sustain se non ci è arrivato )
}
Engine_TypeStateGeneratorADSR;

void Engine_GeneratorADSRInit( Engine_TypeStateGeneratorADSR* State, float Attack, float Decay, float Sustain, float Release, float SampleRate );
float Engine_GeneratorADSRStep( Engine_TypeStateGeneratorADSR* State, bool Pressed );

#endif /* LIBRARY_INC_ENGINE_H_ */
