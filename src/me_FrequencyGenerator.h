// Frequency generator interface

/*
  Author: Martin Eden
  Last mod.: 2025-12-14
*/

/*
  Scope

  Module provides on/off interface for square wave generation.
*/

/*
  Implementation specifications

    * Uses counter 1 and pin 6
    * 50% duty cycle
    * Accepted frequencies: 8..1000 kHz

  Intended use is 38 kHz wave generation for IR emitter.
*/

#pragma once

#include <me_BaseTypes.h>

namespace me_FrequencyGenerator
{
  TBool SetFrequency_Hz(TUint_4 Frequency);
  void StartFreqGen();
  void StopFreqGen();
}

/*
  2025-02-21
  2025-09-14
*/
