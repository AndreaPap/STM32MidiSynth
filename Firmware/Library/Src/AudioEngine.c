/*
 * Engine.c
 *
 *  Created on: Jul 20, 2026
 *      Author: andrea
 */
#include "AudioEngine.h"

float AudioEngine_Sample( AudioEngine_TypeState* State )
{
	float NewPhase = State->Phase + State->PhaseIncrement;
	if( NewPhase > State->SampleSize ){ NewPhase -= State->SampleSize; }

	uint16_t Index0 = ( uint16_t )NewPhase;
	uint16_t Index1 = Index0 + 1 == State->SampleSize ? 0 : Index0 + 1;

	float Output = ( State->Sample[ Index0 ] ) + ( ( NewPhase - Index0 ) * ( State->Sample[ Index1 ] - State->Sample[ Index0 ] ) );

	State->Phase = NewPhase;

	return Output;
}
