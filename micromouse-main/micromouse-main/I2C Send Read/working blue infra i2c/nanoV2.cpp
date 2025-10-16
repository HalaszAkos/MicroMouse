#include <Arduino.h>
#include <Wire.h>

#define I2C_SDA 18  //a4  
#define I2C_SCL 19 //a5
int IRSensorL1 = A0;  // Analog input
int IRSensorL2 = A1;  // Analog input
int IRSensorR1 = A2;  // Analog input
int IRSensorR2 = A3;  // Analog input
 
int IRSensorL1_EN = 9;  // Digital input
int IRSensorL2_EN = 8;  // Digital input
int IRSensorR1_EN = 7;  // Digital input
int IRSensorR2_EN = 6;  // Digital input
 
int SensorL1value = 0;
int SensorL2value = 0;
int SensorR1value = 0;
int SensorR2value = 0;

byte i2c_rcv;               // data received from I2C bus
byte data=0xA;


// put function declarations here:
void receiveCallback(int aCount);
void dataRqst();

void setup() {

  Wire.begin(0x08);
  Wire.onReceive(receiveCallback);
  Wire.onRequest(dataRqst);
  Serial.begin(9600);
  Serial.println("Serial Working.");
  pinMode(IRSensorL1_EN, OUTPUT);
  pinMode(IRSensorL2_EN, OUTPUT);
  pinMode(IRSensorR1_EN, OUTPUT);
  pinMode(IRSensorR2_EN, OUTPUT);
 
  digitalWrite(IRSensorL1_EN, HIGH);
  digitalWrite(IRSensorL2_EN, HIGH);
  digitalWrite(IRSensorR1_EN, HIGH);
  digitalWrite(IRSensorR2_EN, HIGH);
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  SensorL1value = analogRead(IRSensorL1);
  SensorL2value = analogRead(IRSensorL2);
  SensorR1value = analogRead(IRSensorR1);
  SensorR2value = analogRead(IRSensorR2);

}


void receiveCallback(int aCount)
{
  if(aCount == 2)
  {
    Serial.println("Working");
    int receivedValue  = Wire.read() << 8; 
    receivedValue |= Wire.read();
    Serial.println(receivedValue);
   // int receivedValue2  = Wire.read() << 8; 
    //receivedValue2 |= Wire.read();
   // Serial.println(receivedValue2);
   Serial.println("Working");
  }
  else
  {
    Serial.print("Unexpected number of bytes received: ");
    Serial.println(aCount);
  }
}
// put function definitions here:
void dataRqst(){
 Wire.write(SensorL1value >> 8);
 Wire.write(SensorL1value & 255);
 Wire.write(SensorL2value >> 8);
 Wire.write(SensorL2value & 255);
 Wire.write(SensorR1value >> 8);
 Wire.write(SensorR1value & 255);
 Wire.write(SensorR2value >> 8);
 Wire.write(SensorR2value & 255);

}
        