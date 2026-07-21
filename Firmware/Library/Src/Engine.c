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
