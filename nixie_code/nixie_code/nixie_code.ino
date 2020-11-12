//TODO:
//if clock doesnt work try powering it from the analog pins (needs rewire to do this)
//add button support
//add anti-posion function

#include "RTClib.h"
#include <Wire.h>

int A = 3;
int B = 2;
int C = 1;
int D = 0;


int MULTIPLEX_DELAY = 2; //pulse width
int BLANKING_INTERVAL = 200; //microseconds

//replace this line when rtc module installed
//RTC_DS1307 rtc;
RTC_Millis rtc;

// 0 for digit test 1 for voltage test
int mode = 1;

int hr;
int mn;
int sec;

int T1;
int T2;
int T3;
int T4;
int T5;
int T6;

void setup() {

  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);

  pinMode(4, OUTPUT);
  
  //nixie anode pins
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  //TODO - remove when rtc installed
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  

}





void loop() {

 
 DateTime tm = rtc.now();
 hr = tm.hour();
 mn = tm.minute();
 sec = tm.second();
 

  //get decimal values for each tube
  
  T1 = (hr / 10) % 10;
  T2 = hr % 10;
  T3 = (mn / 10) % 10;
  T4 = mn % 10;
  T5 = (sec / 10) % 10;
  T6 = sec % 10;
  


      displayDigit(T1);
      digitalWrite(11, HIGH);
      delay(MULTIPLEX_DELAY);
      digitalWrite(11,LOW);
      delayMicroseconds(BLANKING_INTERVAL);
      displayDigit(T2);
      digitalWrite(10, HIGH);
      delay(MULTIPLEX_DELAY);
      digitalWrite(10,LOW);
      delayMicroseconds(BLANKING_INTERVAL);
      displayDigit(T3);
      digitalWrite(9, HIGH);
      delay(MULTIPLEX_DELAY);
      digitalWrite(9,LOW);
      delayMicroseconds(BLANKING_INTERVAL);
      displayDigit(T4);
      digitalWrite(8, HIGH);
      delay(MULTIPLEX_DELAY);
      digitalWrite(8,LOW);
      delayMicroseconds(BLANKING_INTERVAL);
      displayDigit(T5);
      digitalWrite(7, HIGH);
      delay(MULTIPLEX_DELAY);
      digitalWrite(7,LOW);
      delayMicroseconds(BLANKING_INTERVAL);
      displayDigit(T6);
      digitalWrite(6, HIGH);
      delay(MULTIPLEX_DELAY);
      digitalWrite(6,LOW);
      delayMicroseconds(BLANKING_INTERVAL);

}





void displayDigit(int i){

  if(i==0){
  digitalWrite(A,LOW);
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
  digitalWrite(D,LOW);
  }
  
  if(i==1){
  digitalWrite(A,HIGH);
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
  digitalWrite(D,LOW);
  }
  
  if(i==2){
  digitalWrite(A,LOW);
  digitalWrite(B,HIGH);
  digitalWrite(C,LOW);
  digitalWrite(D,LOW);
  }
  
  
  if(i==3){
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,LOW);
  digitalWrite(D,LOW);
  }
  
  
  if(i==4){
  digitalWrite(A,LOW);
  digitalWrite(B,LOW);
  digitalWrite(C,HIGH);
  digitalWrite(D,LOW);
  }
  
  
  if(i==5){
  digitalWrite(A,HIGH);
  digitalWrite(B,LOW);
  digitalWrite(C,HIGH);
  digitalWrite(D,LOW);
  }
  
  
  if(i==6){
  digitalWrite(A,LOW);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,LOW);
  }
  
  
  if(i==7){
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,LOW);
  }
  
  
  if(i==8){
  digitalWrite(A,LOW);
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
  digitalWrite(D,HIGH);
  }
  
  
  if(i==9){
  digitalWrite(A,HIGH);
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
  digitalWrite(D,HIGH);
  }



}
