//TODO:
//if clock doesnt work try powering it from the analog pins (needs rewire to do this)
//add button support
//add anti-posion function

#include <ShiftRegister74HC595.h>
#include <RTClib.h>
#include <RealTimeClockDS1307.h>
#include <Wire.h>

// create shift register objectS (number of shift registers, SER pin, SRCLK pin, RCLK pin)
ShiftRegister74HC595 srH (1, 8, 9, 10); 
ShiftRegister74HC595 srM (1, 5, 6, 7); 
ShiftRegister74HC595 srS (1, 2, 3, 4); 

RTC_DS1307 rtc;

void setup() {
  
   //use internal pullup resistor for button.
  pinMode(1 , INPUT_PULLUP)
  
  //set the clock up
  Serial.begin(9600);
  delay(2000); //give the clock a chance to be read

}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now =rtc.now();

  setTubePair(srH , now.hour());
  setTubePair(srM , now.minute());
  setTubePair(srS, now.second());

}

// function to display two digits on a given shift registers nixies
void setTubePair(ShiftRegister74HC595 sr , int number_pair){
  
  //decimal numbers to display on each nixie
  int tube_1 = (number_pair ) % 10;
  int tube_2 = (number_pair / 10U) % 10;

  //passing binary of the desired decimal for a tube to its 74141 to pins DCBA causes it to output the desired digit
  // most significant bit goes to pin D and least significant to A (contrary to what we may guess)
  int sr_A = bitRead(tube_1 , 0); //least significant digit
  int sr_B = bitRead(tube_1 , 1);
  int sr_C = bitRead(tube_1 , 2);
  int sr_D = bitRead(tube_1 , 3);
  int sr_E = bitRead(tube_2 , 0);
  int sr_F = bitRead(tube_2 , 1);
  int sr_G = bitRead(tube_2 , 2);
  int sr_H = bitRead(tube_2 , 3);

  sr.set(0,sr_A);
  sr.set(1,sr_B);
  sr.set(2,sr_C);
  sr.set(3,sr_D);
  sr.set(4,sr_E);
  sr.set(5,sr_F);
  sr.set(6,sr_G);
  sr.set(7,sr_H);
} 
