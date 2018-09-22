//TODO:
//if clock doesnt work try powering it from the analog pins (needs rewire to do this)
//add timer mode
//add anti-posion function


#include <RTClib.h>
#include <RealTimeClockDS1307.h>
#include <Wire.h>

//74141 outputs. remember the serial output is read in order DCBA to determine the displayed number
int pin_A=3;
int pin_B=2;
int pin_C=1;
int pin_D=0;

//anode switching outputs
int pin_hr1 =11;
int pin_hr2=10;
int pin_min1=9;
int pin_min2=8;
int pin_sec1=7;
int pin_sec2=6;

int anodeList[] = {pin_hr1 , pin_hr2 , pin_min1 , pin_min2 , pin_sec1 , pin_sec2};
int displayValue; //the value to display on a tube
int i=0;

//buttons
int minButton = 4;
int hrButton = 5;

int minButtonState=0;
int hrButtonState=0;
int lastHrButtonState=0;

//in clock or timer mode - clock = 0 timer = 1
int clockMode=0;

//is the timer running
int timerRunning=0;
int timerStarted=0;
int timerStartTime=0;
int timerTime=0;


RTC_DS1307 rtc;

void setup() {

  pinMode(pin_D,OUTPUT); //output D
  pinMode(pin_C, OUTPUT); //output C
  pinMode(pin_B, OUTPUT); //output B
  pinMode(pin_A , OUTPUT); //output A
  
  
  pinMode(pin_hr1, OUTPUT); //hr 1 anode
  pinMode(pin_hr2, OUTPUT); //hr 2 anode
  pinMode(pin_min1, OUTPUT); //min 1 anode
  pinMode(pin_min2, OUTPUT); //min 2 anode
  pinMode(pin_sec1, OUTPUT); //sec 1 anode
  pinMode(pin_sec2, OUTPUT); //sec 2 anode

  
   //use internal pullup resistor for buttons.
  pinMode(minButton , INPUT_PULLUP);
  pinMode(hrButton , INPUT_PULLUP);
  
  //set the clock up
  Serial.begin(57600);
  delay(2000); //give the clock a chance to be read
  
}

void loop() {
  if(i>5){
    i=0;
  }


  //get the time
  DateTime now =rtc.now();
 

  //check button press state (no edge detect function in arduino)
  minButtonState=digitalRead(minButton);
  hrButtonState=digitalRead(hrButton);

  if(minButtonState==1 && hrButtonState==1){
    clockMode = ~clockMode;
    delay(300);
  }

  //if in regularclock mode
  if(clockMode==0){
    timerRunning=0;
    timerStarted=0;
  if(minButtonState==1 && hrButtonState==0){
    delay(200); //delay to make sure user isnt pushing both buttons
    if(minButtonState==1 && hrButtonState==0){
      DateTime newTime(now.unixtime() + 60);
      rtc.adjust(newTime);
    }
  }

  if(minButtonState==0 && hrButtonState==1){
    delay(200); //delay to make sure user isnt pushing both buttons
    if(minButtonState==0 && hrButtonState==1){
      DateTime newTime(now.unixtime() + 3600);
      rtc.adjust(newTime);
    }
  }

  
  DateTime now=rtc.now();
  int hr = now.hour();
  int mn = now.minute();
  int sec = now.second();

  int hr1;
  int hr2;
  int mn1;
  int mn2;
  int sec1;
  int sec2;

  if(hr <10){
    hr1 = 0;
    hr2 = hr;
    }
    else{
    hr1=hr%10;
    hr2=(hr/10U)%10;
    }

    if(mn <10){
    mn1 = 0;
    mn2 = mn;
    }
    else{
    mn1=mn%10;
    mn2=(mn/10U)%10;
    }

    if(sec <10){
    sec1 = 0;
    sec2 = sec;
    }
    else{
    sec1=sec%10;
    sec2=(sec/10U)%10;
    }

  //same order as anode list so the correct tube will always be on
  int timeList[] = { hr1,hr2,mn1,mn2,sec1,sec2 };
  

  displayValue = timeList[i];

  //define the number to display
  setNumber(displayValue);
  //display it on the correct tube
  switchOnAnode(i);

  }

  //if in timer mode
  if(clockMode==1){
  
    //if timer not started
    if(timerStarted==0){
        //display all zeros
        setNumber(0);
        //display it on the correct tube
        switchOnAnode(i);

        //if timer started (no delay to check if both buttons pushed necessary here)
        if(minButtonState==0 && hrButtonState==1){
          timerStarted=1;
          timerRunning=1;

          //start the timer exactly when the button is pressed
          if(lastHrButtonState != hrButtonState){
            timerStartTime = millis();

          }
    
          lastHrButtonState=hrButtonState;
        }
    }

    //if timer is running
    if(timerRunning){
      timerTime = millis()-timerStartTime;

      //if button pressed stop the timer
      if(hrButtonState==1){
        timerRunning=0;
      }
    //TODO - display the time here
    }

    //if timer has been stopped
    if(timerRunning==0 && timerStarted==1){

      //reset the timer if button pressed
      if(minButtonState==1){
        timerRunning=0;
        timerStarted=0;
      }

      //TODO - add restart functionality here
      //TODO - display the time here
    }

    
  }

    delay(5);
    i+=1;
}


//function to display a number
void setNumber(int value){
  int D = bitRead(value , 0);
  int C = bitRead(value , 1);
  int B = bitRead(value , 2);
  int A = bitRead(value , 3);

  digitalWrite(pin_D , D);
  digitalWrite(pin_C , C);
  digitalWrite(pin_B , B);
  digitalWrite(pin_A , A);
  
}

//function to display a value on a given tube (0 indexed)
void switchOnAnode(int tubeID){
  //switch off all anodes first
  digitalWrite(pin_hr1, 0) ;
  digitalWrite(pin_hr2, 0) ;
  digitalWrite(pin_min1, 0) ;
  digitalWrite(pin_min2, 0) ;
  digitalWrite(pin_sec1, 0) ;
  digitalWrite(pin_sec2, 0);

  digitalWrite(anodeList[tubeID],1);
}

