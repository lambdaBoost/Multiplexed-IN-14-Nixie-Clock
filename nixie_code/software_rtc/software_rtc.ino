
#include "RTClib.h"
#include <Wire.h>

int A = 3;
int B = 2;
int C = 1;
int D = 0;

int hrButton = 4;
int minButton = 5;


int MULTIPLEX_DELAY = 2; //pulse width 2
int BLANKING_INTERVAL_OPTIONS[5] = {200,400,800,1600,2400};
int BLANKING_INTERVAL = BLANKING_INTERVAL_OPTIONS[0]; //microseconds 200
const long CYCLE_INTERVAL = 1000; //interval between changes for cathode poisoning prevention scheme
int NUM = 0; //start digit for cathode poisoning prevention
unsigned long previousMillis = 0;

//replace this line when rtc module installed
//RTC_DS1307 rtc;
RTC_Millis rtc;

// 0 for digit test 1 for voltage test
int mode = 0;

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

  
  pinMode(hrButton, INPUT_PULLUP);
  pinMode(minButton, INPUT_PULLUP);
  
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


int previousHrButton = digitalRead(hrButton);
int previousMinButton = digitalRead(minButton);
int hrButtonState;
int minButtonState;


void loop() {

 DateTime tm = rtc.now();
 hr = tm.hour();
 mn = tm.minute();
 sec = tm.second();

 //run anti cathode poisoining for 1 hr at 2am (excessive but thats ok)
  if(hr ==2 or mode==1){
    antiPoison();
  }

  else{
  displayTime();
  }

  //handle button pushes
  //increment on button release so second zero doesnt affect hrs and mins
  //hold both for second zero
  hrButtonState = digitalRead(hrButton);
  minButtonState = digitalRead(minButton);

  if(hrButtonState == HIGH and previousHrButton == LOW){
    incrementHour();
  }

  if(minButtonState == HIGH and previousMinButton == LOW){
    incrementMinute();
  }

  if(minButtonState == LOW and hrButtonState ==LOW){
    delay(1000);
    hrButtonState = digitalRead(hrButton);
    minButtonState = digitalRead(minButton);
    if(minButtonState == HIGH or hrButtonState ==HIGH){

    zeroSeconds();
    }
  

    
    else{

      int x=1;


      //if both buttons held, change brightness
      while(minButtonState == LOW and hrButtonState ==LOW){

        displayTime();
        
        if(x>4){
          x = 0;
        }
        
        
        unsigned long currentMillis = millis();
        if(currentMillis - previousMillis >= CYCLE_INTERVAL){
        previousMillis = currentMillis;
        BLANKING_INTERVAL = BLANKING_INTERVAL_OPTIONS[x];
        x=x+1;
        }

        hrButtonState = digitalRead(hrButton);
        minButtonState = digitalRead(minButton);
      }

      // allow time to release both buttons
      delay(1000);

      previousMillis = 0;
      
    }
  }
  


  previousHrButton = digitalRead(hrButton);
  previousMinButton = digitalRead(minButton);

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


void displayTime(){

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



void incrementHour(){

  DateTime nw = rtc.now();
  int yr = nw.year();
  int mm = nw.month();
  int da = nw.day();
  int hr = nw.hour();
  int mn = nw.minute();
  int sec = nw.second();

  hr = hr+1;
  
  rtc.adjust(DateTime(yr, mm, da, hr, mn, sec)); //Set the RTC time to the new updated time
}


void incrementMinute(){

  DateTime nw = rtc.now();
  int yr = nw.year();
  int mm = nw.month();
  int da = nw.day();
  int hr = nw.hour();
  int mn = nw.minute();
  int sec = nw.second();

  mn = mn+1;
  
  rtc.adjust(DateTime(yr, mm, da, hr, mn, sec)); //Set the RTC time to the new updated time
}


void zeroSeconds(){

  DateTime nw = rtc.now();
  int yr = nw.year();
  int mm = nw.month();
  int da = nw.day();
  int hr = nw.hour();
  int mn = nw.minute();
  int sec = 0;
  
  rtc.adjust(DateTime(yr, mm, da, hr, mn, sec)); //Set the RTC time to the new updated time
}


//cycle all digits to mitigate cathode poisoning
void antiPoison(){
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= CYCLE_INTERVAL) {
    previousMillis = currentMillis;
    NUM = NUM+1;

    if(NUM >9){
      NUM = 0;
    }
  }

  else{
      displayDigit(NUM);
      digitalWrite(6, HIGH);
      delay(MULTIPLEX_DELAY);
      digitalWrite(6,LOW);
      digitalWrite(7, HIGH);
      delay(MULTIPLEX_DELAY);
      digitalWrite(7,LOW);
      digitalWrite(8, HIGH);
      delay(MULTIPLEX_DELAY);
      digitalWrite(8,LOW);
      digitalWrite(9, HIGH);
      delay(MULTIPLEX_DELAY);
      digitalWrite(9,LOW);
      digitalWrite(10, HIGH);
      delay(MULTIPLEX_DELAY);
      digitalWrite(10,LOW);
      digitalWrite(11, HIGH);
      delay(MULTIPLEX_DELAY);
      digitalWrite(11,LOW);
  }

}
