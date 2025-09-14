// [me_FrequencyGenerator] test

/*
  Author: Martin Eden
  Last mod.: 2025-09-14
*/

#include <me_FrequencyGenerator.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>
#include <me_Console.h>
#include <me_Delays.h>

void RunTest()
{
  Console.Indent();
  Console.Print("( Emitting 38 kHz for 10 seconds on pin 3.");

  if (!me_FrequencyGenerator::SetFrequency_Hz(38000))
    Console.Print("Failed to set frequency.");
  me_FrequencyGenerator::StartFreqGen();
  me_Delays::Delay_S(10);
  me_FrequencyGenerator::StopFreqGen();

  Console.Print(") Done");
  Console.Unindent();
}

void setup()
{
  Console.Init();

  Console.Print("( [me_FrequencyGenerator] test");
  RunTest();
  Console.Print(") Done");
}

void loop()
{
}

/*
  2025-09-14
*/
