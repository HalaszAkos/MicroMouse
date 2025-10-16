#include <Arduino.h>
#include <Wire.h>

// put function declarations here:
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

void setup() 
{
  Wire.begin();
  pinMode(IRSensorL1_EN, OUTPUT);
  pinMode(IRSensorL2_EN, OUTPUT);
  pinMode(IRSensorR1_EN, OUTPUT);
  pinMode(IRSensorR2_EN, OUTPUT);
 
  digitalWrite(IRSensorL1_EN, HIGH);
  digitalWrite(IRSensorL2_EN, HIGH);
  digitalWrite(IRSensorR1_EN, HIGH);
  digitalWrite(IRSensorR2_EN, HIGH);
  
}
void loop() 
{
  SensorL1value = analogRead(IRSensorL1);
  SensorL2value = analogRead(IRSensorL2);
  SensorR1value = analogRead(IRSensorR1);
  SensorR2value = analogRead(IRSensorR2);
  // send command to start blinking
  Wire.beginTransmission( 0x08);
  if(SensorR2value>8 && SensorL2value>8){
  Wire.write( 101);
  Wire.endTransmission();
  }
  else if (SensorR2value<8 || SensorL2value<8)
  {
  Wire.write( 100);
  Wire.endTransmission();
  
  }
  
  // send command to stop blinking
  //Wire.beginTransmission( 0x08);
  

  
}