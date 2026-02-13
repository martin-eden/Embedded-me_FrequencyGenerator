## What

(2025-09)

Frequency generator. ATmega328/P

## Details

![Wave][Wave_40k]

Generates square wave with 50% duty cycle.

Used to generate 40 kHz for infrared emitter.

Implementation uses pin 5 for output (and counter 1).

Produces perfect timing when frequency is divisor of 2000000.

Minimum frequency ~ 8 kHz. Maximum frequency 1 MHz.


## Code

* [Interface][Interface]
* [Implementation][Implementation]
* [Example][Example]


## Requirements

  * arduino-cli
  * bash


## Install/remove

Easy way is to clone [GetLibs][GetLibs] repo and run it's code.


## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]


[Wave_40k]: extras/40%20kHz.png

[Interface]: src/me_FrequencyGenerator.h
[Implementation]: src/me_FrequencyGenerator.cpp
[Example]: examples/me_FrequencyGenerator/me_FrequencyGenerator.ino

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
