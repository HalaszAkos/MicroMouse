#include <Arduino.h>
#include <Wire.h>
#include "BluetoothSerial.h"


//PWM initializing--------------------------
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
//-----------------------------------------


//init Input outputs-----------------------
//motor direction:
int hatra = 4; //IO4 BAL
int Elore = 2; //IO2 BAL
int Elore2 = 12; //IO12 Jobb
int hatra2 = 15; //IO15 Jobb
//Morot encoders:
int ENCA=13;
int ENCB=14;
//-----------------------------------------


//Global variables-------------------------
//encoder 0-1 switch
int before1=0;
int before2=0;
//encoder counting change:
int counter1=0;
int counter2=0;
//received value from nano (4x IR sensor)
int receivedValue1=0;
int receivedValue2=0;
int receivedValue3=0;
int receivedValue4=0;
//-----------------------------------------



//Bluetooth---------------------------------------------------------------------------------------------------------------
const char *pin = "1234"; // Change this to more secure PIN.
 
String device_name = "ESP32-BT-Slave";
 
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
 
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif
 
BluetoothSerial SerialBT;
//------------------------------------------------------------------------------------------------------

// put function declarations here:

void turnLeft(int encData);

void turnRight(int encData);

void moveForward(int encData);


void setup() {
  Wire.setPins(3,1);
  Wire.begin();   // join I2C bus as Slave with address 0x08

  //pinMode(hatra, OUTPUT);
 // pinMode(Elore, OUTPUT);
  //pinMode(Elore2, OUTPUT);
 // pinMode(hatra2, OUTPUT);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  //attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
   //set motor to 0
  //digitalWrite(hatra,LOW);  
 // digitalWrite(Elore,LOW);
 // digitalWrite(Elore2,LOW);
 // digitalWrite(hatra2,LOW);
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
 int ENCB_Data=digitalRead(ENCB);
  if(ENCB_Data!=before2)
 {
  before2=ENCB_Data;
  counter2=counter2+1;
 }
 
 /*if(counter1%5==0){
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

//code to try
if(receivedValue3>900)//r1
{
  turnRight(counter1);

}

if(receivedValue2>900)//l2
{
  turnLeft(counter1);

}

if(receivedValue1>900)
{
  moveForward(counter1);
}
*/
 
 Wire.beginTransmission(0x08);
  Wire.write(counter1 >> 8);
  Wire.write(counter1 & 255);
  Wire.endTransmission();
  Wire.requestFrom(0x08, 8);
  
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
 
 
}

// put function definitions here:
void turnLeft(int encData)
{
//bal hátra jobb előre
while(counter1<(40+encData)){

int ENCA_Data=digitalRead(ENCA);
 if(ENCA_Data!=before1)
 {
  before1=ENCA_Data;
  counter1=counter1+1;
 }
ledcWrite(PWM1_Ch, PWM_STOP);// baloldali előre
ledcWrite(PWM2_Ch, PWM_START1);//jobb elől

ledcWrite(PWM3_Ch, PWM_START1); //bal hátra
ledcWrite(PWM4_Ch, PWM_STOP);// jobb oldali hátra
}
delay(500);
ledcWrite(PWM1_Ch, PWM_STOP);// baloldali előre
ledcWrite(PWM2_Ch, PWM_STOP);//jobb elől

ledcWrite(PWM3_Ch, PWM_STOP); //bal hátra
ledcWrite(PWM4_Ch, PWM_STOP);// jobb oldali hátra
}

void turnRight(int encData)//r1 l2
{
//bal előre jobb hátra
while(counter1<(55+encData)){

int ENCA_Data=digitalRead(ENCA);
 if(ENCA_Data!=before1)
 {
  before1=ENCA_Data;
  counter1=counter1+1;
 }


ledcWrite(PWM1_Ch, PWM_START1);// baloldali előre
ledcWrite(PWM2_Ch, PWM_STOP);//jobb előre

ledcWrite(PWM3_Ch, PWM_STOP); //bal hátra
ledcWrite(PWM4_Ch, PWM_START1);// jobb oldali hátra
}
ledcWrite(PWM1_Ch, PWM_STOP);// bal oldali előre
ledcWrite(PWM2_Ch, PWM_STOP);//jobb elől 

ledcWrite(PWM3_Ch, PWM_STOP); //bal hátra
ledcWrite(PWM4_Ch, PWM_STOP);// jobb oldali hátra
}


void moveForward(int encData)
{


while(counter1<(165+encData)){

int ENCA_Data=digitalRead(ENCA);
 if(ENCA_Data!=before1)
 {
  before1=ENCA_Data;
  counter1=counter1+1;
 }

ledcWrite(PWM1_Ch, PWM_START);// baloldali előre pwm start
ledcWrite(PWM2_Ch, 101);//jobb elől pwm start 1

ledcWrite(PWM3_Ch, PWM_STOP); //bal hátra
ledcWrite(PWM4_Ch, PWM_STOP);// jobb oldali hátra

}

ledcWrite(PWM1_Ch, PWM_STOP);// bal oldali előre
ledcWrite(PWM2_Ch, PWM_STOP);//jobb elől 

ledcWrite(PWM3_Ch, PWM_STOP); //bal hátra
ledcWrite(PWM4_Ch, PWM_STOP);// jobb oldali hátra
}
/*
if(receivedValue1<360 )
 {
  
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

 }
 */