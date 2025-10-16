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
//int before1=0;
//int before2=0;
//encoder counting change:
//int counter1=0;
//int counter2=0;
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


//PID
float kp = 0.5, ki = 0.05, kd = 0.25; // PID coefficients
float error = 0.0, prevError = 0.0, integral = 0.0, derivative = 0.0, PID_output1 = 50,PID_output2 = 50;
unsigned long prevTime = 0;

void calculatePID(float setpoint, float measuredValue, float &PID_output);


//SPeed
unsigned long previousTime = 0;
unsigned long currentTime = 0;

volatile int counter1 = 0; // Counter for encoder transitions for motor 1
volatile int counter2 = 0; // Counter for encoder transitions for motor 2
int before1 = LOW; // Previous state of Encoder A for motor 1
int before2 = LOW; // Previous state of Encoder A for motor 2
float radius1 = 0.022; // Radius of the wheel or pulley for motor 1
float radius2 = 0.022; // Radius of the wheel or pulley for motor 2
float speed1 = 0.0; // Variable to store the calculated speed for motor 1
float speed2 = 0.0; // Variable to store the calculated speed for motor 2

void ai0();
void ai1();


void setup() {
  Wire.setPins(3,1);
  Wire.begin();   // join I2C bus as Slave with address 0x08

 
  pinMode(ENCA, INPUT_PULLUP);
  pinMode(ENCB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCB), ai0, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA), ai1, RISING);
  SerialBT.begin(device_name); //Bluetooth device name
  #ifdef USE_PIN
    SerialBT.setPin(pin);
    //Serial.println("Using PIN");
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

//ledcWrite(PWM1_Ch, 101);// baloldali előre pwm start
//ledcWrite(PWM2_Ch, 101);//jobb elől pwm start 1

//ledcWrite(PWM3_Ch, PWM_STOP); //bal hátra
//ledcWrite(PWM4_Ch, PWM_STOP);// jobb oldali hátra



}

void loop() {

currentTime = millis();
/* pid1
if (currentTime - previousTime >= 1000) { // Measure the time in seconds
    speed1 = (float)counter1 / (currentTime - previousTime) * 1000 * 2 * PI * radius1;
    speed2 = (float)counter2 / (currentTime - previousTime) * 1000 * 2 * PI * radius2;
    SerialBT.print("Speed of motor 1: ");
    SerialBT.print (speed1);
    SerialBT.println(" RPM");
    SerialBT.print("Speed of motor 2: ");
    SerialBT.print(speed2);
    SerialBT.println(" RPM");
    counter1 = 0;
    counter2 = 0;
    previousTime = currentTime;
    calculatePID(30, speed1, PID_output1);
    calculatePID(30, speed2, PID_output2);
    ledcWrite(PWM1_Ch,PID_output1);
    ledcWrite(PWM2_Ch,PID_output2);
    ledcWrite(PWM3_Ch, 0); //bal hátra
    ledcWrite(PWM4_Ch, 0);// jobb oldali hátra
  }*/
  if (currentTime - previousTime >= 1000) {
  previousTime=currentTime;
  SerialBT.print("L1 elore: ");
  SerialBT.println(receivedValue1);
  SerialBT.print("L2 oldalra: ");
  SerialBT.println(receivedValue2);
   SerialBT.print("R1 elore : ");
  SerialBT.println(receivedValue4);
  SerialBT.print("R2 oldalra : ");
  SerialBT.println(receivedValue3);
 
  }

 // float measuredValue1 = speed1; // replace with your measurement function
 // float measuredValue2 = speed2; // replace with your measurement function

  //calculatePID(30, measuredValue1, PID_output1);
  //calculatePID(30, measuredValue2, PID_output2);
  
  /* pid 1
  SerialBT.print("Values 1:  ");

  SerialBT.print(speed1);
  SerialBT.print(" VS ");
  SerialBT.println(PID_output1);
  SerialBT.print("Values 2:  ");

  SerialBT.print(speed2);
  SerialBT.print(" VS ");
  
  SerialBT.println(PID_output2);
  
  
   SerialBT.print(" PWM value 1: ");
  SerialBT.println(PID_output1);
  SerialBT.print(" PWM value 2: ");
  SerialBT.println(PID_output2);*/



  //int pwmValue1 = map(abs(PID_output1), 0, 100, 0, 255);
  //int pwmValue2 = map(abs(PID_output2), 0, 100, 0, 255);
  //ledcWrite(PWM1_Ch, pwmValue1);
 // ledcWrite(PWM2_Ch, pwmValue2);

 
  
 //Bluetooth send:
  /*SerialBT.println("L1");
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
  SerialBT.println(counter2);*/

 
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
 
 delay(10);
}





void ai0() {
  before1 = digitalRead(ENCA);
  if (before1 == HIGH) {
    counter1++;
  }
}

void ai1() {
  before2 = digitalRead(ENCB);
  if (before2 == HIGH) {
    counter2++;
  }
}























// put function definitions here:

//PID
void calculatePID(float setpoint, float measuredValue, float &PID_output) {
if((setpoint >= measuredValue+0.5) && (setpoint <= (measuredValue + 1)) || ((setpoint <=measuredValue-0.5) && (setpoint >= measuredValue-1))){
PID_output=PID_output;
}

else{
if(setpoint> measuredValue)
{
PID_output=PID_output+1;
}
else if (setpoint<measuredValue)
{
PID_output=PID_output-1;

}
}
}




