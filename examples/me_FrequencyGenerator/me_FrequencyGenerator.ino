// [me_FrequencyGenerator] test

/*
  Author: Martin Eden
  Last mod.: 2025-10-12
*/

#include <me_FrequencyGenerator.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>
#include <me_Console.h>
#include <me_Delays.h>

void RunTest()
{
  const TUint_4 Freq_Hz = 40000;
  const TUint_2 Duration_Ms = 2;

  Console.Print("( Emitting frequency for given time on pin 6.");
  Console.Indent();

  Console.Write("Frequency (Hz)");
  Console.Print(Freq_Hz);
  Console.EndLine();

  Console.Write("Duration (Ms)");
  Console.Print(Duration_Ms);
  Console.EndLine();

  if (!me_FrequencyGenerator::SetFrequency_Hz(Freq_Hz))
    Console.Print("Failed to set frequency.");
  me_FrequencyGenerator::StartFreqGen();
  me_Delays::Delay_Ms(Duration_Ms);
  me_FrequencyGenerator::StopFreqGen();

  Console.Unindent();
  Console.Print(") Done");
}

void setup()
{
  Console.Init();

  Console.Print("( [me_FrequencyGenerator] test");
  Console.Indent();
  RunTest();
  Console.Unindent();
  Console.Print(") Done");
}

void loop()
{
}

/*
  2025-09-14
  2025-10-12
*/
