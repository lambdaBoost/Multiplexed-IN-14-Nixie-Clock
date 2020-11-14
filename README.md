# nixie-clock
PCB design and coding for aa slimline nixie clock using multiplexing of 6 IN-14 nixie tubes.

## Principle of Operation.
This clock uses a Soviet-era Nixie driver to drive 6 Soviet-era Nixie tubes. The aim of this project was to produce a slimline and aesthetically pleasing clock for a minimal cost. To achieve this, the tubes are multiplexed meaning only a single driver chip is required. Multiplexing is no complicate - it is simply the act of switching the tubes on and off at a high enough frequency that the human eye cannot detect the flicker. By only having one tube on at a given time, only one driver chip is needed, less microprocessor pins are needed and the power consumption is reduced.


## PCB design
The 'PCB design' directory contains all the files necessary for production of the PCB. For those just wanting to make the clock, the gerber files alone are sufficient - they can be sent to your PCB manufacturer of choice.

For anyone wanting to improve on the design, which is not perfect, the sehematic and PCB files are also included.

The bill of materials is also included. In addition to the components stated, you will need:
* 6 X IN-14 nixie tubes and a single K155ID1 nixie driver. 
* A 74141 driver may also be used but these are rare/expensive and offer no real benefit over the former. 
* A nixie power supply. One that can provide 170V from a 5V DC source is necessary - plenty are available online but check the order of the output pins - the one I used was cheap but seems to work fine for now. It is available [here]( https://bit.ly/2IDABvU).  
* (OPTIONAL). If you want the clock to keep time when it is unplugged you'll need a DS1307 RTC module like [this](https://www.amazon.co.uk/DS1307-AT24C32-Clock-module-board/dp/B00CWX6UXY). Again, check that the pins are in the same order as that shown. You need them in the order GND,VCC,SDA,SCL.
* A USB -> micro USB cable to power it.

It would be possible to reduce the profile of the PCB further by using a SMD microprocessor and an alternate driver chip for the tubes. However, the configuration used here is far easier to program and install. I also personally like the aesthetics of the DIP chips next to the Nixie tubes.


## Arduino code
The code is really pretty simple. The script from the 'nixie_code/nixie_code' directory is all that is needed. Note that in the current configuration, the hour and minute buttons can be pressed to advance the time. Pressing both resets the seconds.

I won't go into details here since the code is commented.

## Improvements
As I designed this PCB a few years ago, and I'm not an electronics engineer, it has some issues which I should really fix. I'll keep these updated in the project issues.


