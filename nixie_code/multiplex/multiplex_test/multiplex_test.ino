int A = 3;
int B = 2;
int C = 1;
int D = 0;

int i = 6;

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

  //0
digitalWrite(A,LOW);
digitalWrite(B,LOW);
digitalWrite(C,LOW);
digitalWrite(D,LOW);

digitalWrite(6, HIGH);
delay(2);
digitalWrite(6,LOW);
digitalWrite(7, HIGH);
delay(2);
digitalWrite(7,LOW);
digitalWrite(8, HIGH);
delay(2);
digitalWrite(8,LOW);
digitalWrite(9, HIGH);
delay(2);
digitalWrite(9,LOW);
digitalWrite(10, HIGH);
delay(2);
digitalWrite(10,LOW);
digitalWrite(11, HIGH);
delay(2);
digitalWrite(11,LOW);

}


void loopAllDigits(){

  //0
digitalWrite(A,LOW);
digitalWrite(B,LOW);
digitalWrite(C,LOW);
digitalWrite(D,LOW);
delay(1000);

//1
digitalWrite(A,HIGH);
digitalWrite(B,LOW);
digitalWrite(C,LOW);
digitalWrite(D,LOW);
delay(1000);

//2
digitalWrite(A,LOW);
digitalWrite(B,HIGH);
digitalWrite(C,LOW);
digitalWrite(D,LOW);
delay(1000);

//3
digitalWrite(A,HIGH);
digitalWrite(B,HIGH);
digitalWrite(C,LOW);
digitalWrite(D,LOW);
delay(1000);

//4
digitalWrite(A,LOW);
digitalWrite(B,LOW);
digitalWrite(C,HIGH);
digitalWrite(D,LOW);
delay(1000);

//5
digitalWrite(A,HIGH);
digitalWrite(B,LOW);
digitalWrite(C,HIGH);
digitalWrite(D,LOW);
delay(1000);

//6
digitalWrite(A,LOW);
digitalWrite(B,HIGH);
digitalWrite(C,HIGH);
digitalWrite(D,LOW);
delay(1000);

//7
digitalWrite(A,HIGH);
digitalWrite(B,HIGH);
digitalWrite(C,HIGH);
digitalWrite(D,LOW);
delay(1000);

//8
digitalWrite(A,LOW);
digitalWrite(B,LOW);
digitalWrite(C,LOW);
digitalWrite(D,HIGH);
delay(1000);

//9
digitalWrite(A,HIGH);
digitalWrite(B,LOW);
digitalWrite(C,LOW);
digitalWrite(D,HIGH);
delay(1000);


}
