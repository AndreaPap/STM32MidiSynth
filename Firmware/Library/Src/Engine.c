/*
 * Engine.c
 *
 *  Created on: Jul 20, 2026
 *      Author: andrea
 */
#include <Engine.h>

void Engine_SampleInit( Engine_TypeSampleState* State, float* Sample, uint16_t SampleSize, float Frequency, float InitialPhase, float SampleRate )
{
	// DeltaPhase / MaxPhase = DeltaT / Period = ( 1 / Samplerate ) / ( 1 / Frequency ) = DeltaPhase = MaxPhase * Frequency / Samplerate
	State->Sample = Sample;
	State->SampleSize = SampleSize;
	State->PhaseIncrement = ( float )SampleSize * Frequency / SampleRate;
	State->Phase = ( float )SampleSize * InitialPhase; // fase iniziale normalizzata
}

float Engine_SampleStep( Engine_TypeSampleState* State )
{
	float NewPhase = State->Phase + State->PhaseIncrement;
	if( NewPhase >= State->SampleSize ){ NewPhase -= State->SampleSize; }

	uint16_t Index0 = ( uint16_t )NewPhase;
	uint16_t Index1 = Index0 + 1 == State->SampleSize ? 0 : Index0 + 1;

	float S0 = State->Sample[ Index0 ];
	float S1 = State->Sample[ Index1 ];

	float Output = S0 + ( ( NewPhase - ( float )Index0 ) * ( S1 - S0 ) );

	State->Phase = NewPhase;

	return Output;
}



void Engine_SineGeneratorInit( Engine_TypeSineGeneratorState* State, float Frequency, float InitialPhase, float SampleRate )
{
	State->Init = true;
	State->A0 = sinf( 2.0f * PI * InitialPhase );
	State->A1 = sinf( 2.0f * PI * ( ( Frequency / SampleRate ) - InitialPhase ) );
	State->B1 = 2.0f * cosf( 2.0f * PI * Frequency / SampleRate );
	State->X1 = 0.0f;
	State->Y2 = 0.0f;
	State->Y1 = 0.0f;
}

float Engine_SineGeneratorStep( Engine_TypeSineGeneratorState* State )
{
	float X = State->Init ? 1.0f : 0.0f;
	float Y = ( State->B1 * State->Y1 ) - State->Y2 + ( State->A0 * X ) + ( State->A1 * State->X1 );
	float Out = ( Y * 0.5f ) + 0.5f;
	float Y2 = State->Y1;

	State->Init = false;
	State->X1 = X;
	State->Y1 = Y;
	State->Y2 = Y2;

	return Out;
}

void Engine_SawGeneratorInit( Engine_TypeSawGeneratorState* State, float Frequency, float InitialPhase, float SampleRate )
{
	float HalfPeriod = 1.0f / ( 2.0f * Frequency );
	float RelTime = InitialPhase / Frequency;
	State->Up = RelTime < HalfPeriod;
	State->RelTime = RelTime < HalfPeriod ? RelTime : RelTime - HalfPeriod;
	State->Step = 1.0f / SampleRate;
	State->HalfPeriod = HalfPeriod;
}

float Engine_SawGeneratorStep( Engine_TypeSawGeneratorState* State )
{
	float NewRelTime = State->RelTime + State->Step;
	bool NewUp = State->Up;

	if( NewRelTime >= State->HalfPeriod )
	{
		NewRelTime -= State->HalfPeriod;
		NewUp = !NewUp;
	}

	float Out = NewUp ? NewRelTime / State->HalfPeriod : 1.0f - ( NewRelTime / State->HalfPeriod );

	State->RelTime = NewRelTime;
	State->Up = NewUp;

	return Out;
}

void Engine_SawtoothGeneratorInit( Engine_TypeSawtoothGeneratorState* State, float Frequency, float InitialPhase, float SampleRate )
{
	State->RelTime = InitialPhase / Frequency;
	State->Step = 1.0f / SampleRate;
	State->Period = 1.0f / Frequency;
}

float Engine_SawtoothGeneratorStep( Engine_TypeSawtoothGeneratorState* State )
{
	float NewRelTime = State->RelTime + State->Step;

	if( NewRelTime >= State->Period ){ NewRelTime -= State->Period; }
	float Out = NewRelTime / State->Period;

	State->RelTime = NewRelTime;

	return Out;
}

void Engine_ExpGeneratorInit( Engine_TypeExpGeneratorState* State, float Duration, float SampleRate )
{
	State->Init = true;
	State->B1 = expf( -3.0f / ( SampleRate * Duration ) ); // duration a 3 tau ( decadimento a 5 % )
	State->Y1 = 0.0f;
}

float Engine_ExpGeneratorStep( Engine_TypeExpGeneratorState* State )
{
	float X = State->Init ? 1.0f : 0.0f;
	float Out;

	Out = X + ( State->B1 * State->Y1 );

	State->Init = false;
	State->Y1 = Out;
	return Out;
}

void Engine_ADSRGeneratorInit( Engine_TypeADSRGeneratorState* State, float Attack, float Decay, float Sustain, float Release, float SampleRate )
{
	State->Pressed = true;
	State->Y1 = 0.0f;
	State->Phase = 0;
	State->RelTime = 0.0f;
	State->Step = 1 / SampleRate;

	State->Attack = Attack;
	State->AttackB1 = expf( -5.0f * Attack * State->Step );

	State->Decay = Decay;
	State->DecayB1 = expf( -5.0f * Decay * State->Step );

	State->Sustain = Sustain;

	State->Release = Release;
	State->ReleaseB1 = expf( -5.0f * Decay * State->Step );
}

float Engine_ADSRGeneratorStep( Engine_TypeADSRGeneratorState* State, bool Pressed )
{
	float NewPhase = State->Phase;
	float NewRelTime = State->RelTime;
	float Out = 0.0f;

	if( Pressed && !State->Pressed )
	{
		NewPhase = 0;
		NewRelTime = 0.0f;
	}
	else if( !Pressed && State->Pressed )
	{
		NewPhase = 3;
		NewRelTime = 0.0f;
	}
	else
	{
		NewRelTime += State->Step;

		if( State->Phase == 0 && NewRelTime > State->Attack )
		{
			NewPhase = 1;
			NewRelTime -= State->Attack;
		}
		else if( State->Phase == 1 && NewRelTime > State->Decay )
		{
			NewPhase = 2;
			NewRelTime -= State->Sustain;
		}
	}

	if( NewPhase == 0 )
	{

	}

	State->Pressed = Pressed;
	State->Phase = NewPhase;
	State->RelTime = NewRelTime;

	return Out;
}
