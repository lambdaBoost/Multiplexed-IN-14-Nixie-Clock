int A = 3;
int B = 2;
int C = 1;
int D = 0;

int i = 6;
int MULTIPLEX_DELAY = 2; //pulse width
unsigned long previousMillis = 0; 
int NUM = 0; //first number to display
const long interval = 1000; //digit change interval

// 0 for digit test 1 for voltage test
int mode = 1;

void setup() {

pinMode(A,OUTPUT);
pinMode(B,OUTPUT);
pinMode(C,OUTPUT);
pinMode(D,OUTPUT);

digitalWrite(A, LOW);
digitalWrite(B, LOW);
digitalWrite(C, LOW);
digitalWrite(D, LOW);

//nixie anode pins
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
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
