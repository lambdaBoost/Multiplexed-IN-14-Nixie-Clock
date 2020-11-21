# Multiplexed IN-14 Nixie Clock
PCB design and coding for a slimline nixie clock using multiplexing of 6 IN-14 nixie tubes. Powered by a standard Micro USB.

![Prototype Build](https://github.com/Alex-Hall-Data/nixie-clock/blob/master/images/IN-14.jpg?raw=true)

## Principle of Operation.
This clock uses a Soviet-era Nixie driver to drive 6 Soviet-era Nixie tubes. The aim of this project was to produce a slimline and aesthetically pleasing clock for a minimal cost. To achieve this, the tubes are multiplexed meaning only a single driver chip is required. Multiplexing is not complicated - it is simply the act of switching the tubes on and off at a high enough frequency that the human eye cannot detect the flicker. By only having one tube on at a given time, only one driver chip is needed, less microprocessor pins are needed and the power consumption is reduced.

Rather than attempting to rectify mains voltage, the unit is powered from a +5V USB. While less efficient, this removes the danger of dealing with mains voltage.


## PCB design

**Note there are two seperate designs - the original and the rev 2. The original is tested and pictured above sitting on my desk (with some minor modifications to connect the buttons and add decoupling capacitors and add a switch which was not included on the original schematic). The rev 2 fixes some issues discussed below but I have not had this version manufactured so it is currently untested but should work fine providing I didn't make any mistakes fixing up the issues.**

The 'PCB design' directory contains all the files necessary for production of the PCB. For those just wanting to make the clock, the gerber files alone are sufficient - they can be sent to your PCB manufacturer of choice.

For anyone wanting to improve on the design, which is not perfect, the sehematic and PCB files are also included.

The bill of materials is also included. In addition to the components stated, you will need:
* 6 X IN-14 nixie tubes 
* a single K155ID1 nixie driver. A 74141 driver may also be used but these are rare/expensive and offer no real benefit over the former (the K155ID1 is a Russian copy of the 74141). 
* A nixie power supply. One that can provide 170V from a 5V DC source is necessary - plenty are available online but check the order of the output pins - the one I used was cheap but seems to work fine for now. It is available [here]( https://bit.ly/2IDABvU).  
* (OPTIONAL). If you want the clock to keep time when it is unplugged you'll need a DS1307 RTC module like [this](https://www.amazon.co.uk/DS1307-AT24C32-Clock-module-board/dp/B00CWX6UXY). Again, check that the pins are in the same order as that shown. You need them in the order GND,VCC,SDA,SCL.
* A USB -> micro USB cable to power it.

It would be possible to reduce the profile of the PCB further by using a SMD microprocessor and an alternate driver chip for the tubes. However, the configuration used here is far easier to program and install. I also personally like the aesthetics of the DIP chips next to the Nixie tubes.


## Arduino code
As the unit uses an ATMEGA328p DIP chip, it can be programmed using an arduino UNO. Simply upload the code to your UNO, remove the DIP chip and insert it into the holder on the PCB - that's it, no ISP programmer needed.

The code required depends on whether you have a DS1307 module installed:
* If you have a ds1307 module installed, upload the code at nixie_code/nixie_code/hardware_rtc.ino
* If you don't, upload the code at nixie_code/nixie_code/software_rtc.ino

I won't go into details here since the code is commented.

## Improvements
As I designed this PCB a few years ago, and I'm not an electronics engineer, it has some issues which I should really fix. I'll keep these updated in the project issues.


