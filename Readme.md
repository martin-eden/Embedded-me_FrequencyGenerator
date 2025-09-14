## What

(2025-09)

Frequency generator.

Generates square wave with 50% duty cycle.

It's main use is generate 38 kHz for infrared emitter.

Implementation produces perfect timing when frequency is divisor
of 2000000. Minimum frequency ~ 8 kHz. Maximum frequency 1 MHz.

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


[Interface]: src/me_FrequencyGenerator.h
[Implementation]: src/me_FrequencyGenerator.cpp
[Example]: examples/me_FrequencyGenerator/me_FrequencyGenerator.ino

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
