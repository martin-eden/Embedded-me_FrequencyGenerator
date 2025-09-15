// Frequency generator implementation

/*
  Author: Martin Eden
  Last mod.: 2025-09-15
*/

/*
  Here we're using counter 3 in PWM mode.
  Output is done on pin 3 which is related to that counter.
*/

#include <me_FrequencyGenerator.h>

#include <me_BaseTypes.h>

#include <me_Counters.h>
#include <me_Pins.h>

using namespace me_FrequencyGenerator;

const TUint_1 OutputPinNumber = 3;
me_Pins::TOutputPin OutputPin;

TBool me_FrequencyGenerator::SetFrequency_Hz(
  TUint_4 Freq_Hz
)
{
  /*
    Range is from 7843 Hz to 1 MHz

    Mind that we have only 256 values for speed setting.
    So it's not possible to emit exact duration for any frequency.
    Lower frequencies have better precision.
    Frequencies that divide 2000000 are perfect.

    It's like floating point numbers: more magnitude - less precision.
  */
  const TUint_4 MaxFreq_Hz = (TUint_4) F_CPU / 8 / 2;
  const TUint_4 MinFreq_Hz = (TUint_4) F_CPU / 8 / 255;
  TUint_1 WaveDuration_Ut;
  me_Counters::TCounter3 Counter;

  if ((Freq_Hz < MinFreq_Hz) || (Freq_Hz > MaxFreq_Hz))
    return false;

  OutputPin.Init(OutputPinNumber);

  WaveDuration_Ut = (TUint_4) F_CPU / 8 / Freq_Hz;

  if (WaveDuration_Ut < 2)
    return false;

  StopFreqGen();

  {
    using namespace me_Counters;

    Counter.SetAlgorithm(TAlgorithm_Counter3::FastPwm_ToMarkA);

    *Counter.MarkA = WaveDuration_Ut - 1;
    Counter.Control->PinActionOnMarkA = (TUint_1) TPinAction::None;

    *Counter.MarkB = (WaveDuration_Ut - 1) / 2;
    Counter.Control->PinActionOnMarkB = (TUint_1) TPinAction::Set;
  }

  return true;
}

void me_FrequencyGenerator::StartFreqGen()
{
  using namespace me_Counters;

  TCounter3 Counter;

  Counter.Control->Speed = (TUint_1) TSpeed_Counter3::SlowBy2Pow3;
  *Counter.Current = 0;
}

void me_FrequencyGenerator::StopFreqGen()
{
  const TUint_1 CounterStoppingMargin = 10;

  using namespace me_Counters;

  TCounter3 Counter;

  // If we're not stopped then wait to complete wave cycle
  if (Counter.Control->Speed != (TUint_1) TSpeed_Counter3::None)
  {
    Counter.Control->PinActionOnMarkB = (TUint_1) TPinAction::Clear;
    while (*Counter.Current > CounterStoppingMargin);
  }

  Counter.Control->Speed = (TUint_1) TSpeed_Counter3::None;
  *Counter.Current = 0;
}

/*
  2025-02-21
  2025-09-14
  2025-09-15
*/
