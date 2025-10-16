#include <Arduino.h>
#include <Wire.h>
#include "BluetoothSerial.h"



#define PWM1_Ch    0
#define PWM2_Ch    1
#define PWM3_Ch    2
#define PWM4_Ch    3

#define PWM_Res   8  //4
#define PWM_Freq  500 //1000

int PWM_START = 93; // start = 26 jó előre érték
int PWM_START1= 98; //27
//int PWM_Drift = 20;
int PWM_STOP = 0;


int hatra = 4; //IO4
int Elore = 2; //IO2

int Elore2 = 12; //IO12
int hatra2 = 15; //IO15
int ENCA=13;
int ENCB=14;
byte x =0;
int input=1000;
int before1=0;
int before2=0;
int counter1=0;
int counter2=0;
byte get=0xA;
int receivedValue1=0;
int receivedValue2=0;
int receivedValue3=0;
int receivedValue4=0;
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

  pinMode(hatra, OUTPUT);
  pinMode(Elore, OUTPUT);
  pinMode(Elore2, OUTPUT);
  pinMode(hatra2, OUTPUT);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  //attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
   //set motor to 0
  digitalWrite(hatra,LOW);  
  digitalWrite(Elore,LOW);
  digitalWrite(Elore2,LOW);
  digitalWrite(hatra2,LOW);
  SerialBT.begin(device_name); //Bluetooth device name
  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN");
  #endif
//pwm
ledcAttachPin(Elore, PWM1_Ch);
ledcSetup(PWM1_Ch, PWM_Freq, PWM_Res);

ledcAttachPin(Elore2, PWM2_Ch);
ledcSetup(PWM2_Ch, PWM_Freq, PWM_Res);

ledcAttachPin(hatra, PWM3_Ch);
ledcSetup(PWM3_Ch, PWM_Freq, PWM_Res);

ledcAttachPin(hatra2, PWM4_Ch);
ledcSetup(PWM4_Ch, PWM_Freq, PWM_Res);

ledcWrite(PWM1_Ch, PWM_STOP);// baloldali előre
ledcWrite(PWM2_Ch, PWM_STOP);//jobb elől

ledcWrite(PWM3_Ch, PWM_STOP); //bal hátra
ledcWrite(PWM4_Ch, PWM_STOP);// jobb oldali hátra


}

void loop() {
 int ENCA_Data=digitalRead(ENCA);
 if(ENCA_Data!=before1)
 {
  before1=ENCA_Data;
  counter1=counter1+1;
 }
 int ENCB_Data=digitalRead(ENCB);
  if(ENCB_Data!=before2)
 {
  before2=ENCB_Data;
  counter2=counter2+1;
 }
 
 if(counter1%5==0){
  SerialBT.println("L1");
  SerialBT.println(receivedValue1);
  SerialBT.println("L2");
  SerialBT.println(receivedValue2);
  SerialBT.println("R1");
  SerialBT.println(receivedValue3);
  SerialBT.println("R2");
  SerialBT.println(receivedValue4);
  SerialBT.println("ENC jobb");
  SerialBT.println(counter1);
  SerialBT.println("ENC bal");
  SerialBT.println(counter2);
 }
  if(receivedValue1<360 )
 {
  /*digitalWrite(hatra,LOW);  
  digitalWrite(Elore,HIGH);
  digitalWrite(Elore2,HIGH);
  digitalWrite(hatra2,LOW);*/
  ledcWrite(PWM1_Ch, PWM_START);// baloldali előre pwm start
  ledcWrite(PWM2_Ch, PWM_START1);//jobb elől pwm start 1

  ledcWrite(PWM3_Ch, PWM_STOP); //bal hátra
  ledcWrite(PWM4_Ch, PWM_STOP);// jobb oldali hátra
  
 }

  if(receivedValue1>360 )
 {
   ledcWrite(PWM1_Ch, PWM_STOP); //baloldalielőre
  ledcWrite(PWM2_Ch, PWM_STOP);//jobbelől

  ledcWrite(PWM3_Ch, PWM_STOP); //bal hátra
  ledcWrite(PWM4_Ch, PWM_STOP); //jobboldali hátra
 /* digitalWrite(hatra,LOW);  
  digitalWrite(Elore,LOW);
  digitalWrite(Elore2,LOW);
  digitalWrite(hatra2,LOW);*/
 }
 //if(receivedValue1>440 L1)
 //{}
 Wire.beginTransmission(0x08);
  Wire.write(counter1 >> 8);
  Wire.write(counter1 & 255);
  Wire.endTransmission();
  asd=Wire.requestFrom(0x08, 8);
  if(asd==1){counter1=asd;}
  if(asd==2){counter1=asd;}
if(Wire.available()) {	      // read response from slave 0x08
		receivedValue1  = Wire.read() << 8; 
    receivedValue1 |= Wire.read();
    receivedValue2  = Wire.read() << 8; 
    receivedValue2 |= Wire.read();
    receivedValue3  = Wire.read() << 8; 
    receivedValue3 |= Wire.read();
    receivedValue4  = Wire.read() << 8; 
    receivedValue4 |= Wire.read();

	}
 //if(receivedValue1!=0)
 //{
 // digitalWrite(forwardMotor1A,LOW);  
 // digitalWrite(forwardMotor1B,HIGH);
 // digitalWrite(backwardMotor2A,HIGH);
 // digitalWrite(backwardMotor2B,LOW);



 //}
 
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
