#include <Arduino.h>
#include <Wire.h>


int forwardMotor1A = 4; //IO4
int forwardMotor1B = 2; //IO2

int backwardMotor2A = 12; //IO12
int backwardMotor2B = 15; //IO15
int ENCA=13;
int ENCB=14;
byte x =0;
int input=1000;
int before1=0;
int before2=0;
int counter1=0;
int counter2=0;



byte i2c_rcv;               // data received from I2C bus
// put function declarations here:

void setup() {
  Wire.setPins(3,1);
  Wire.begin();   // join I2C bus as Slave with address 0x08

  pinMode(33, OUTPUT);
  pinMode(forwardMotor1A, OUTPUT);
  pinMode(forwardMotor1B, OUTPUT);
  pinMode(backwardMotor2A, OUTPUT);
  pinMode(backwardMotor2B, OUTPUT);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  //attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
   //set motor to 0
  digitalWrite(forwardMotor1A,LOW);  
  digitalWrite(forwardMotor1B,LOW);
  digitalWrite(backwardMotor2A,LOW);
  digitalWrite(backwardMotor2B,LOW);
  digitalWrite(33, LOW);
  Wire.beginTransmission(0x08);
  Wire.write(counter1 >> 8);
  Wire.write(counter1 & 255);
  Wire.endTransmission();
}

void loop() {

Wire.requestFrom(0x08, 1);
if(Wire.available()) {	      // read response from slave 0x08
		i2c_rcv = Wire.read();
	}
 if(i2c_rcv==0xA)
 {
    digitalWrite(backwardMotor2A,LOW);
      digitalWrite(backwardMotor2A,HIGH);
      digitalWrite(backwardMotor2B,HIGH);


 }
 
 
}


/*void readEncoder(){
  int b = digitalRead(ENCB);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}*/
// put function definitions here:
