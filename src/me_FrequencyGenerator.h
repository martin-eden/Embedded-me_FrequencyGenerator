// Frequency generator interface

/*
  Author: Martin Eden
  Last mod.: 2025-10-10
*/

/*
  Implementation uses counter 1 and pin 5 for frequency output.
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
