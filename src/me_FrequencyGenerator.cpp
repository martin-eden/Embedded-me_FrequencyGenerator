// Frequency generator implementation

/*
  Author: Martin Eden
  Last mod.: 2026-02-13
*/

/*
  Implementation details

  * We're using counter 1 in single-slope PWM mode
  * Output is done on pin 5
  * Initial and final signal is LOW
*/

#include <me_FrequencyGenerator.h>

#include <me_BaseTypes.h>

#include <me_Counters.h>
#include <me_Pins.h>
#include <me_HardwareClockScaling.h>

using namespace me_FrequencyGenerator;

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

  const TUint_1 Spec_Prescale_PowOfTwo = 3;
  const TUint_1 Spec_ScaleSize_NumBits = 8;

  me_Counters::Counter1::TCounter Counter;
  me_HardwareClockScaling::THardwareDuration HwDur;

  if (
    !me_HardwareClockScaling::CalculateHardwareDuration(
      &HwDur, Freq_Hz, Spec_Prescale_PowOfTwo, Spec_ScaleSize_NumBits
    )
  )
    return false;

  /*
    Post-process hardware duration

    <.Scale_BaseOne> field contains number of cycles to slow.
    It's stored biased by one: zero means one cycle, one means two etc.

    This value is duration of LOW-HIGH period. We want middle setpoint
    in that period where we switch pin.

    We made promise of 50% duty cycle. That means that period duration
    must be even. Considering bias it means we want odd duration.
  */
  HwDur.Scale_BaseOne |= 1;

  {
    const TUint_1 OutputPinNumber = 5;
    me_Pins::TOutputPin OutputPin;

    OutputPin.Init(OutputPinNumber);
    OutputPin.Write(0);
  }

  Counter.Control->DriveSource = (TUint_1) me_Counters::Counter1::TDriveSource::None;

  Counter.SetAlgorithm(me_Counters::Counter1::TAlgorithm::FastPwm_ToMarkA);
  *Counter.MarkA = HwDur.Scale_BaseOne;
  *Counter.MarkB = (HwDur.Scale_BaseOne >> 1);

  *Counter.Current = 0;

  /*
    Specially for Arduino

    Disable Arduino's timer interrupt.

    Arduino uses counter 1 as timer. We're using counter 1 as frequency
    generator. It can tick real fast.
  */
  Counter.Interrupts->OnDone = false;

  return true;
}

void me_FrequencyGenerator::StartFreqGen()
{
  using namespace me_Counters::Counter1;

  TCounter Counter;

  Counter.Control->PinActionOnMarkB = (TUint_1) me_Counters::TPinAction::Clear;
  Counter.Control->DriveSource = (TUint_1) TDriveSource::Internal_SlowBy2Pow3;
}

void me_FrequencyGenerator::StopFreqGen()
{
  using namespace me_Counters::Counter1;

  TCounter Counter;

  if (Counter.Control->DriveSource == (TUint_1) TDriveSource::None)
    return;

  /*
    If we're not stopped then wait to complete wave cycle

    Stopping gracefully is not that simple.

    After setting pin action on mark A to None, pin instantly
    returns to what value it has before. We want to finish current
    wave before releasing it.

    To finish wave we're waiting for "got mark A" flag.
    This flag is likely set now from previous iterations.
    So we're clearing it first. And clearing is done
    by writing "true" to it. Yes, "true". Hardware magic!
  */

  Counter.Status->GotMarkA = true;
  while (!Counter.Status->GotMarkA);

  // Okay, we're at start of cycle, disconnect pin and power off counter
  Counter.Control->PinActionOnMarkB = (TUint_1) me_Counters::TPinAction::None;
  Counter.Control->DriveSource = (TUint_1) TDriveSource::None;
}

/*
  2025 # # # # # # #
  2026-02-13
*/
