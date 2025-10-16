//I2C Master Tx Code Example

#include <Wire.h>
 
int AN_POT;
 
void setup() {
  Wire.begin(); // Initialize I2C (Master Mode: address is optional)
}
 
void loop() {
  AN_POT = analogRead(A0);
  Wire.beginTransmission(0x55); // Transmit to device with address 85 (0x55)
  Wire.write((AN_POT>>2));      // Sends Potentiometer Reading (8Bit)
  Wire.endTransmission();       // Stop transmitting
  delay(100);
}
//I2C Master Rx Code Example

#include <Wire.h>
 
byte RxByte;
 
void setup() {
  Wire.begin(); // Initialize I2C (Master Mode: address is optional)
}
 
void loop() {
  Wire.requestFrom(0x55, 1); // Request From Slave @ 0x55, Data Length = 1Byte
  while(Wire.available()) {  // Read Received Datat From Slave Device
    RxByte = Wire.read();
  }
  delay(100);
}