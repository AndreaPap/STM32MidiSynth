/*
 * Engine.c
 *
 *  Created on: Jul 20, 2026
 *      Author: andrea
 */
#include <Engine.h>

void Engine_GeneratorSampleInit( Engine_TypeStateGeneratorSample* State, float* Sample, uint16_t SampleSize, float Frequency, float InitialPhase, float SampleRate )
{
	// DeltaPhase / MaxPhase = DeltaT / Period = ( 1 / Samplerate ) / ( 1 / Frequency ) = DeltaPhase = MaxPhase * Frequency / Samplerate
	State->Sample = Sample;
	State->SampleSize = SampleSize;
	State->PhaseIncrement = ( float )SampleSize * Frequency / SampleRate;
	State->Phase = ( float )SampleSize * InitialPhase; // fase iniziale normalizzata
}

float Engine_GeneratorSampleStep( Engine_TypeStateGeneratorSample* State )
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



void Engine_GeneratorSineInit( Engine_TypeStateGeneratorSine* State, float Frequency, float InitialPhase, float SampleRate )
{
	State->Init = true;
	State->A0 = sinf( 2.0f * PI * InitialPhase );
	State->A1 = sinf( 2.0f * PI * ( ( Frequency / SampleRate ) - InitialPhase ) );
	State->B1 = 2.0f * cosf( 2.0f * PI * Frequency / SampleRate );
	State->X1 = 0.0f;
	State->Y2 = 0.0f;
	State->Y1 = 0.0f;
}

float Engine_GeneratorSineStep( Engine_TypeStateGeneratorSine* State )
{
	float X = State->Init ? 1.0f : 0.0f;
	float Y = ( State->B1 * State->Y1 ) - State->Y2 + ( State->A0 * X ) + ( State->A1 * State->X1 );
	float Y2 = State->Y1;

	State->Init = false;
	State->X1 = X;
	State->Y1 = Y;
	State->Y2 = Y2;

	return Y;
}

void Engine_GeneratorFastSineInit( Engine_TypeStateGeneratorFastSine* State, float Frequency, float InitialPhase, float SampleRate )
{
	/*
	 * F / Fs = Rad / 2 pi -> Rad = 2 pi F / Fs, T / P = Phi / 2 * pi -> Phi = 2 * pi * T / P = 2 * pi * T * F = 2 * pi * n * F / Fs
	 * step inizia a calcolare da y[ 0 ], se impulso a x[ -2 ] step indipendente da ingresso
	 */

	float W = 2.0f * PI * Frequency / SampleRate;
	float Phi = -( 2.0f * PI * 2.0f * Frequency / SampleRate) + InitialPhase;
	State->B1 = 2.0f * cosf( W );
	State->Y2 = sinf( Phi ); // y[ -2 ] = sin( phi )x[ -2 ]
	State->Y1 = ( State->B1 *State->Y2 ) + sinf( W - Phi ); // conta y[ -1 ] = b1y[ -1 ] + sin( w - phi )x[ -2 ]
}

float Engine_GeneratorFastSineStep( Engine_TypeStateGeneratorFastSine* State )
{
	float Out = ( State->B1 * State->Y1 ) - State->Y2;
	State->Y2 = State->Y1;
	State->Y1 = Out;
	return Out;
}

void Engine_GeneratorSawInit( Engine_TypeStateGeneratorSaw* State, float Frequency, float InitialPhase, float SampleRate )
{
	float HalfPeriod = 1.0f / ( 2.0f * Frequency );
	float RelTime = InitialPhase / Frequency;
	State->Up = RelTime < HalfPeriod;
	State->RelTime = RelTime < HalfPeriod ? RelTime : RelTime - HalfPeriod;
	State->Step = 1.0f / SampleRate;
	State->HalfPeriod = HalfPeriod;
}

float Engine_GeneratorSawStep( Engine_TypeStateGeneratorSaw* State )
{
	float NewRelTime = State->RelTime + State->Step;
	bool NewUp = State->Up;

	if( NewRelTime >= State->HalfPeriod )
	{
		NewRelTime -= State->HalfPeriod;
		NewUp = !NewUp;
	}

	float Out = ( ( NewUp ? NewRelTime / State->HalfPeriod : 1.0f - ( NewRelTime / State->HalfPeriod ) ) * 2.0f ) - 1.0f;

	State->RelTime = NewRelTime;
	State->Up = NewUp;

	return Out;
}

void Engine_GeneratorSawtoothInit( Engine_TypeStateGeneratorSawtooth* State, float Frequency, float InitialPhase, float SampleRate )
{
	State->RelTime = InitialPhase / Frequency;
	State->Step = 1.0f / SampleRate;
	State->Period = 1.0f / Frequency;
}

float Engine_GeneratorSawtoothStep( Engine_TypeStateGeneratorSawtooth* State )
{
	float NewRelTime = State->RelTime + State->Step;

	if( NewRelTime >= State->Period ){ NewRelTime -= State->Period; }
	float Out = ( ( NewRelTime / State->Period ) * 2.0f ) - 1.0f;

	State->RelTime = NewRelTime;

	return Out;
}

void Engine_GeneratorExpInit( Engine_TypeStateGeneratorExp* State, float Duration, float SampleRate )
{
	State->Init = true;
	State->B1 = expf( -3.0f / ( SampleRate * Duration ) ); // duration a 3 tau ( decadimento a 5 % )
	State->Y1 = 0.0f;
}

float Engine_GeneratorExpStep( Engine_TypeStateGeneratorExp* State )
{
	float X = State->Init ? 1.0f : 0.0f;
	float Out;

	Out = X + ( State->B1 * State->Y1 );

	State->Init = false;
	State->Y1 = Out;
	return Out;
}

void Engine_GeneratorExpReset( Engine_TypeStateGeneratorExp* State )
{
	State->Init = true;
	State->Y1 = 0.0f;
}


void Engine_GeneratorADSRInit( Engine_TypeStateGeneratorADSR* State, float Attack, float Decay, float Sustain, float Release, float SampleRate )
{
	State->Pressed = false;
	State->Y1 = 0.0f;
	State->Phase = 0;
	State->RelTime = 0.0f;
	State->Step = 1.0f / SampleRate;
	State->SampleRate = SampleRate;
	Engine_GeneratorExpInit( &State->ExpGeneratorAttack, Attack, SampleRate );
	Engine_GeneratorExpInit( &State->ExpGeneratorDecay, Decay, SampleRate );
	Engine_GeneratorExpInit( &State->ExpGeneratorRelease, Release, SampleRate );
	State->Attack = Attack;
	State->Decay = Decay;
	State->Sustain = Sustain;
	State->Release = Release;
	State->AttackStart = 0.0f;
	State->DecayStart = 0.0f;
	State->ReleaseStart = 0.0f;
}

float Engine_GeneratorADSRStep( Engine_TypeStateGeneratorADSR* State, bool Pressed )
{
	uint8_t NewPhase = State->Phase;
	float NewRelTime = State->RelTime;
	float NewAttackStart = State->AttackStart;
	float NewDecayStart = State->DecayStart;
	float NewReleaseStart = State->ReleaseStart;
	float Out = 0.0f;
	Engine_TypeStateGeneratorExp NewExpGeneratorAttack = State->ExpGeneratorAttack;
	Engine_TypeStateGeneratorExp NewExpGeneratorDecay = State->ExpGeneratorDecay;
	Engine_TypeStateGeneratorExp NewExpGeneratorRelease = State->ExpGeneratorRelease;

	if( Pressed && !State->Pressed ) 		// da fase generica a attack per pressione
	{
		NewPhase = 0;
		NewRelTime = 0.0f;
		NewAttackStart = State->Y1;
	}
	else if( !Pressed && State->Pressed ) 	// da fase generica a release per pressione
	{
		NewPhase = 3;
		NewRelTime = 0.0f;
		NewReleaseStart = State->Y1;
	}
	else if( Pressed || NewPhase == 3 )						// variazione per avanzamento nel tempo
	{
		NewRelTime += State->Step;

		if( State->Phase == 0 && NewRelTime > State->Attack ) // da attacco a decay
		{
			NewPhase = 1;
			NewDecayStart = State->Y1;
			NewRelTime -= State->Attack;
		}
		else if( State->Phase == 1 && NewRelTime > State->Decay ) // da decay a sustain
		{
			NewPhase = 2;
			NewRelTime -= State->Decay;
		}
	}

	if( NewPhase != State->Phase )	// inizializzo di nuovo generatore esponenziale
	{
		switch ( NewPhase )
		{
			case 0: Engine_GeneratorExpReset( &NewExpGeneratorAttack );	break;
			case 1: Engine_GeneratorExpReset( &NewExpGeneratorDecay );	break;
			case 3: Engine_GeneratorExpReset( &NewExpGeneratorRelease );break;
		}

	}

	if( Pressed || NewPhase == 3 )
	{
		switch( NewPhase )
		{
			case 0: Out = NewAttackStart + (
					( 1.0f  - NewAttackStart ) *
					( 1.0f - Engine_GeneratorExpStep( &NewExpGeneratorAttack ) ) );				break; 	// start + ( 1 - start )( 1 - exp( -k )
			case 1: Out = State->Sustain + (
					( NewDecayStart - State->Sustain ) *
					Engine_GeneratorExpStep( &NewExpGeneratorDecay ) );							break;	// sustain + ( start - sustain )exp( -k )
			case 2: Out = State->Sustain;														break;	// sustain
			case 3: Out = NewReleaseStart * Engine_GeneratorExpStep( &NewExpGeneratorRelease );	break;	// ReleaseStart * exp( -k )
		}
	}

	State->Pressed = Pressed;
	State->Phase = NewPhase;
	State->RelTime = NewRelTime;
	State->ExpGeneratorAttack = NewExpGeneratorAttack;
	State->ExpGeneratorDecay = NewExpGeneratorDecay;
	State->ExpGeneratorRelease = NewExpGeneratorRelease;
	State->Y1 = Out;
	State->AttackStart = NewAttackStart;
	State->DecayStart = NewDecayStart;
	State->ReleaseStart = NewReleaseStart;

	return Out;
}

void Engine_GeneratorADSRReset( Engine_TypeStateGeneratorADSR* State )
{
	State->Pressed = false;
	State->Y1 = 0.0f;
	State->Phase = 0;
	State->RelTime = 0.0f;
	Engine_GeneratorExpReset( &State->ExpGeneratorAttack );
	Engine_GeneratorExpReset( &State->ExpGeneratorDecay );
	Engine_GeneratorExpReset( &State->ExpGeneratorRelease );
	State->AttackStart = 0.0f;
	State->DecayStart = 0.0f;
	State->ReleaseStart = 0.0f;
}
