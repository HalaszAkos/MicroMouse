#include <Arduino.h>
#include <Wire.h>

// put function declarations here:
byte RxByte;
bool enable=false;
int ENCA=13;
int ENCB=14;

void setup() {
  // put your setup code here, to run once:
    Wire.begin(); // Initialize I2C (Master Mode: address is optional)
    pinMode(33, OUTPUT);
    pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:Wire.begin(); // Initialize I2C (Master Mode: address is optional)
  Wire.requestFrom(0x55, 1); // Request From Slave @ 0x55, Data Length = 1Byte
  while(Wire.available()) {  // Read Received Datat From Slave Device
    RxByte = Wire.read();
    if(RxByte ==0xAA)
    {
      enable=true;
    }
  }
  delay(100);
  if(enable)
  {
    digitalWrite(33, HIGH);
    delay(1000);
    digitalWrite(33, LOW);
    delay(1000);
digitalWrite(33, HIGH);
    delay(1000);
    digitalWrite(33, LOW);
    delay(1000);

  }

}

// put function definitions here:
