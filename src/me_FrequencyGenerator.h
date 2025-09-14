// Frequency generator interface

/*
  Author: Martin Eden
  Last mod.: 2025-09-14
*/

/*
  Limitations

  Current implementation uses pin 3 for frequency output.
  It also uses hardware counter 3.
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
