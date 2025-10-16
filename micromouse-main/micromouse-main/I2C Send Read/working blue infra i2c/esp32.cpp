#include <Arduino.h>
#include <Wire.h>
#include "BluetoothSerial.h"



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
byte get=0xA;
int receivedValue=0;
int asd;

byte i2c_rcv=0;               // data received from I2C bus
// put function declarations here:
const char *pin = "1234"; // Change this to more secure PIN.
 
String device_name = "ESP32-BT-Slave";
 
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
 
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif
 
BluetoothSerial SerialBT;

void setup() {
  Wire.setPins(3,1);
  Wire.begin();   // join I2C bus as Slave with address 0x08

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
  SerialBT.begin(device_name); //Bluetooth device name
  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN");
  #endif

}

void loop() {
 Wire.beginTransmission(0x08);
  Wire.write(counter1 >> 8);
  Wire.write(counter1 & 255);
  Wire.endTransmission();
  asd=Wire.requestFrom(0x08, 2);
  if(asd==1){counter1=asd;}
  if(asd==2){counter1=asd;}
if(Wire.available()) {	      // read response from slave 0x08
		receivedValue  = Wire.read() << 8; 
    receivedValue |= Wire.read();

	}
 if(receivedValue!=0)
 {
 // digitalWrite(forwardMotor1A,LOW);  
 // digitalWrite(forwardMotor1B,HIGH);
 // digitalWrite(backwardMotor2A,HIGH);
 // digitalWrite(backwardMotor2B,LOW);
  SerialBT.println("hello");
  SerialBT.println(receivedValue);
 
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
