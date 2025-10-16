I2C Slave Rx Code Example

#include <Wire.h>
 
byte RxByte;
 
void I2C_RxHandler(int numBytes)
{
  while(Wire.available()) {  // Read Any Received Data
    RxByte = Wire.read();
  }
}
 
void setup() {
  Wire.begin(0x55); // Initialize I2C (Slave Mode: address=0x55 )
  Wire.onReceive(I2C_RxHandler);
}
 
void loop() {
  // Nothing To Be Done Here
}
I2C Slave Tx Code Example

#include <Wire.h>
 
byte TxByte = 0xAA;
 
void I2C_TxHandler(void)
{
  Wire.write(TxByte);
}
 
void setup() {
  Wire.begin(0x55); // Initialize I2C (Slave Mode: address=0x55 )
  Wire.onRequest(I2C_TxHandler);
}
 
void loop() {
  // Nothing To Be Done Here
}