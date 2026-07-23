/*
 * Engine.c
 *
 *  Created on: Jul 20, 2026
 *      Author: andrea
 */
#include <Engine.h>

void Engine_SampleInit( Engine_TypeSampleState* SampleState, float* Sample, uint16_t SampleSize, float Frequency, float InitialPhase, float SampleRate )
{
	// DeltaPhase / MaxPhase = DeltaT / Period = ( 1 / Samplerate ) / ( 1 / Frequency ) = DeltaPhase = MaxPhase * Frequency / Samplerate
	SampleState->Sample = Sample;
	SampleState->SampleSize = SampleSize;
	SampleState->PhaseIncrement = ( float )SampleSize * Frequency / SampleRate;
	SampleState->Phase = ( float )SampleSize * InitialPhase; // fase iniziale normalizzata
}

float Engine_SampleStep( Engine_TypeSampleState* SampleState )
{
	float NewPhase = SampleState->Phase + SampleState->PhaseIncrement;
	if( NewPhase >= SampleState->SampleSize ){ NewPhase -= SampleState->SampleSize; }

	uint16_t Index0 = ( uint16_t )NewPhase;
	uint16_t Index1 = Index0 + 1 == SampleState->SampleSize ? 0 : Index0 + 1;

	float S0 = SampleState->Sample[ Index0 ];
	float S1 = SampleState->Sample[ Index1 ];

	float Output = S0 + ( ( NewPhase - ( float )Index0 ) * ( S1 - S0 ) );

	SampleState->Phase = NewPhase;

	return Output;
}



void Engine_SineGeneratorInit( Engine_TypeSineGeneratorState* SineGeneratorState, float Frequency, float SampleRate )
{
	// Prepara il sistema e lo inizializza come se avesse ricevuto un impulso allo step precedente, così step non deve valutare l'input
	SineGeneratorState->A1 = 2 * cosf( 2 * PI * Frequency / SampleRate );
	SineGeneratorState->Y1 = sinf( 2 * PI * Frequency / SampleRate );
	SineGeneratorState->Y2 = 0.0f;
}

float Engine_SineGeneratorStep( Engine_TypeSineGeneratorState* SineGeneratorState )
{
	float Y1 = ( SineGeneratorState->A1 * SineGeneratorState->Y1 ) - SineGeneratorState->Y2;
	float Out = ( Y1 * 0.5f ) + 0.5f;
	float Y2 = SineGeneratorState->Y1;

	SineGeneratorState->Y1 = Y1;
	SineGeneratorState->Y2 = Y2;

	return Out;
}

void Engine_SawGeneratorInit( Engine_TypeSawGeneratorState* SawGeneratorState, float Frequency, float SampleRate )
{
	SawGeneratorState->Up = true;
	SawGeneratorState->RelTime = 0.0f;
	SawGeneratorState->Step = 1.0f / SampleRate;
	SawGeneratorState->HalfPeriod = 1.0f / ( 2.0f * Frequency );
}

float Engine_SawGeneratorStep( Engine_TypeSawGeneratorState* SawGeneratorState )
{
	float NewRelTime = SawGeneratorState->RelTime + SawGeneratorState->Step;
	bool NewUp = SawGeneratorState->Up;

	if( NewRelTime >= SawGeneratorState->HalfPeriod )
	{
		NewRelTime -= SawGeneratorState->HalfPeriod;
		NewUp = !NewUp;
	}

	float Out = NewUp ? NewRelTime / SawGeneratorState->HalfPeriod : 1.0f - ( NewRelTime / SawGeneratorState->HalfPeriod );

	SawGeneratorState->RelTime = NewRelTime;
	SawGeneratorState->Up = NewUp;

	return Out;
}

void Engine_SawtoothGeneratorInit( Engine_TypeSawtoothGeneratorState* SawtoothGeneratorState, float Frequency, float SampleRate )
{
	SawtoothGeneratorState->RelTime = 0.0f;
	SawtoothGeneratorState->Step = 1.0f / SampleRate;
	SawtoothGeneratorState->Period = 1.0f / Frequency;
}

float Engine_SawtoothGeneratorStep( Engine_TypeSawtoothGeneratorState* SawtoothGeneratorState )
{
	float NewRelTime = SawtoothGeneratorState->RelTime + SawtoothGeneratorState->Step;

	if( NewRelTime >= SawtoothGeneratorState->Period ){ NewRelTime -= SawtoothGeneratorState->Period; }
	float Out = NewRelTime / SawtoothGeneratorState->Period;

	SawtoothGeneratorState->RelTime = NewRelTime;

	return Out;
}
