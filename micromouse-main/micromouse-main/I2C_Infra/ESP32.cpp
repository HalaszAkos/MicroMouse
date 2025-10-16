#include <Arduino.h>
#include <Wire.h>

byte datatosend=0x42
 
// put function declarations here:
void receiveEvent( int howMany);

volatile bool enableBlinking = false;
int forwardMotor1A = 4; //IO4
int forwardMotor1B = 2; //IO2

int backwardMotor2A = 12; //IO12
int backwardMotor2B = 15; //IO15

void setup() {
  
  Wire.setPins(3,1);
  Wire.begin(0x08);   // join I2C bus as Slave with address 0x08
  Wire.onReceive( receiveEvent);
  pinMode(33, OUTPUT);
  pinMode(forwardMotor1A, OUTPUT);
  pinMode(forwardMotor1B, OUTPUT);
  pinMode(backwardMotor2A, OUTPUT);
  pinMode(backwardMotor2B, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
   if( enableBlinking)
  {
  digitalWrite(forwardMotor1A,LOW);  
  digitalWrite(forwardMotor1B,HIGH);
  digitalWrite(backwardMotor2A,HIGH);
  digitalWrite(backwardMotor2B,LOW);
  digitalWrite(33,HIGH);
  }
  else if (enableBlinking==false)
  {
  digitalWrite(forwardMotor1A,LOW);  
  digitalWrite(forwardMotor1B,LOW);
  digitalWrite(backwardMotor2A,LOW);
  digitalWrite(backwardMotor2B,LOW);
  digitalWrite(33,LOW);

  }
  

}

// put function definitions here:
void receiveEvent( int howMany)
{
  if( howMany == 1)   // extra safety check, expecting just one byte
  {
    int x = Wire.read();
    switch( x)
    {
      case 100:
        enableBlinking = true;
        break;
      case 101:
        enableBlinking = false;
        break;
    }
  }
}