// Frequency generator implementation

/*
  Author: Martin Eden
  Last mod.: 2025-10-12
*/

/*
  Here we're using counter 1 in PWM mode.
  Output is done on pin 5 which is related to that counter.
*/

#include <me_FrequencyGenerator.h>

#include <me_BaseTypes.h>

#include <me_Counters.h>
#include <me_Pins.h>

using namespace me_FrequencyGenerator;

const TUint_1 OutputPinNumber = 5;
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
  me_Counters::TCounter1 Counter;

  if ((Freq_Hz < MinFreq_Hz) || (Freq_Hz > MaxFreq_Hz))
    return false;

  OutputPin.Init(OutputPinNumber);

  WaveDuration_Ut = (TUint_4) F_CPU / 8 / Freq_Hz;

  if (WaveDuration_Ut < 2)
    return false;

  Counter.Control->DriveSource = (TUint_1) me_Counters::TDriveSource_Counter1::None;
  Counter.Control->PinActionOnMarkA = (TUint_1) me_Counters::TPinAction::None;

  Counter.SetAlgorithm(me_Counters::TAlgorithm_Counter1::FastPwm_ToMarkA);
  *Counter.MarkA = WaveDuration_Ut - 1;
  *Counter.MarkB = (WaveDuration_Ut - 1) / 2;

  return true;
}

void me_FrequencyGenerator::StartFreqGen()
{
  using namespace me_Counters;

  TCounter1 Counter;

  Counter.Control->PinActionOnMarkB = (TUint_1) TPinAction::Set;
  *Counter.Current = 0;
  Counter.Control->DriveSource = (TUint_1) TDriveSource_Counter1::Internal_SlowBy2Pow3;
}

void me_FrequencyGenerator::StopFreqGen()
{
  using namespace me_Counters;

  TCounter1 Counter;

  if (Counter.Control->DriveSource == (TUint_1) TDriveSource_Counter1::None)
    return;

  /*
    If we're not stopped then wait to complete wave cycle

    Stopping gracefully is not that simple.

    After setting pin action on mark B to None, pin instantly
    returns to what value it has before. We want to finish our
    cycle before releasing it. Our cycle is (LOW HIGH).

    To finish cycle we're waiting for "got mark A" flag.
    This flag is likely is set now from previous iterations.
    So we're clearing it first. And clearing in done
    by writing "true" to it. Yes, "true". Hardware magic!
  */

  Counter.Status->GotMarkA = true;
  while (!Counter.Status->GotMarkA);

  // Okay, we're at start of cycle, disconnect pin and power off counter
  Counter.Control->PinActionOnMarkB = (TUint_1) TPinAction::None;
  Counter.Control->DriveSource = (TUint_1) TDriveSource_Counter1::None;
}

/*
  2025-02-21
  2025-09-14
  2025-09-15
  2025-10-10 Switched to counter 1 (from counter 3)
*/
