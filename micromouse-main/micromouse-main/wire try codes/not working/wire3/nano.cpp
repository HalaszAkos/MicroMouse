#include <Arduino.h>
#include <Wire.h>
// put function declarations here:
byte TxByte = 0xAA;
void I2C_TxHandler(void);


void setup() {
  // put your setup code here, to run once:
   Wire.begin(0x55); // Initialize I2C (Slave Mode: address=0x55 )
  Wire.onRequest(I2C_TxHandler);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:

void I2C_TxHandler(void)
{
  Wire.write(TxByte);
}