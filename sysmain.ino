#include <SD.h> //Load SD card library
#include<SPI.h> //Load SPI Library
#include "Config.h"
#include "PWM.hpp"
#include "PIDCont.h"
#include <math.h>
#include <Wire.h>
#include <avr/pgmspace.h>

PWM ch1(19); // Setup pin 2 for input
PWM ch2(18); // Setup pin 3 for input
PWM ch3(2); // Setup pin 18 for input
PWM ch4(3); // Setup pin 19 for input
//------------------------------------
PIDCont PIDroll,PIDpitch,PIDyaw,PIDangleX,PIDangleY;

int chipSelect = 53; //chipSelect pin for the SD card Reader
File mySensorData; //Data object you will write your sesnor data to

unsigned long tp;
float roll=0, pitch=0; 
float rotX=0;
float rotY=0;
float rotZ=0;
float roll_acc_f=0, pitch_acc_f=0;

int setX = 0; //Rate Setpoint for PID
int setY = 0; //Rate Setpoint for PID
int setZ = 0; //Rate Setpoint for PID
int ref_angle_x = 0;
int ref_angle_y = 0;
int ref_rate_x = 0;
int ref_rate_y = 0;
int ref_rate_z = 0;

int throttle=MOTOR_ZERO_LEVEL;
byte rateAngleSwitch = 0;
int ch5 = 0; //2000->rate mode      0->angle mode

void setup() {  
#ifdef DEBUG  
  Serial.begin(115200);
  while(!Serial);
#endif
  ReceiverInit();
  MotorAnalogInit();
  MPU_init();
  motorStop();
  tp=millis(); //for updateSensorVal
  SD.begin(53); //Initialize the SD card reader
}

void loop() {
  updateSensorVal();
  FlightControl();
  digitalWrite (7, HIGH);
#ifdef DEBUG
  debugProcess();
#endif
}
