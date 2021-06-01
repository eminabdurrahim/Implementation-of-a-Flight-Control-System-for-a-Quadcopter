// -----Other Config---------

#define SAFE    //Arming procedure

//---------------------------


//-------PID Config----------
float n=1;
float ROLL_PID_KP = 0.175;//0.15
float ROLL_PID_KI = 0.1;//0.2
float ROLL_PID_KD = 0.001;//0.001
#define ROLL_PID_MIN  -50.0
#define ROLL_PID_MAX  50.0

float PITCH_PID_KP = 0.2;//0.15
float PITCH_PID_KI = 0.1;//0.2
float PITCH_PID_KD = 0.001;//0.001
#define PITCH_PID_MIN  -50.0
#define PITCH_PID_MAX  50.0

float YAW_PID_KP = 0.3;//0.3
float YAW_PID_KI = 0.1;//0.1
float YAW_PID_KD = 0.001;//0.001
#define YAW_PID_MIN  -50.0
#define YAW_PID_MAX  50.0


float ANGLEX_KP = 2.5; //5//roll
float ANGLEX_KI = 0.1;//2
float ANGLEX_KD = 0.0;//0.01
#define ANGLEX_MIN -100.0
#define ANGLEX_MAX 100.0

float ANGLEY_KP = 2.7;//5.5
float ANGLEY_KI=  0.1;//2
float ANGLEY_KD= 0.0;//0.0
#define ANGLEY_MIN -100.0
#define ANGLEY_MAX 100.0

//-----------------------

//.....RX Config............
#define THROTTLE_RMIN  1160
#define THROTTLE_RMAX  1800
#define THROTTLE_WMIN  MOTOR_ARM_START
#define THROTTLE_WMAX  MOTOR_MAX_LEVEL

#define ROLL_RMIN  1090
#define ROLL_RMAX  1864
#define ROLL_WMIN  -15
#define ROLL_WMAX  15

#define PITCH_RMIN  1200
#define PITCH_RMAX  1824
#define PITCH_WMIN  -15
#define PITCH_WMAX  15

#define YAW_RMIN  1060
#define YAW_RMAX  1824
#define YAW_WMIN  -45
#define YAW_WMAX  45

#define RKNOB_RMIN  1008
#define RKNOB_RMAX  2036
#define RKNOB_WMIN  -230
#define RKNOB_WMAX  230

#define LKNOB_RMIN  976
#define LKNOB_RMAX  2004
#define LKNOB_WMIN  0
#define LKNOB_WMAX  500

#define RX_RATE_SENSITIVITY  3
#define RX_ANGLE_DAMPNING  20.0  //D-term dampning
#define RX_EXPO
//..........................

//Motor PWM Levels
#define MOTOR_ZERO_LEVEL  125
#define MOTOR_ARM_START  140
#define MOTOR_MAX_LEVEL  254


//------ESC/Motor Config-------
#define ANALOG_MAX_SIGNAL 249
#define ANALOG_MIN_SIGNAL 140
#define MOTOR_1_PIN 9
#define MOTOR_2_PIN 10
#define MOTOR_3_PIN 11
#define MOTOR_4_PIN 12
int m1_val;
int m2_val;
int m3_val;
int m4_val;

//------Receiver-------------


//------Sensor--------------
#define RadToDeg 180.0/PI 





//----Debug Config---------
#define DEBUG
//#define DEBUG_QUAT_ANGLE
#define DEBUG_MPU


//-------------------------


//*********Sensor Config****************

#define ACC_X_OFFSET  19
#define ACC_Y_OFFSET  7
#define ACC_Z_OFFSET  -73

#define GYRO_X_OFFSET  1.418431
#define GYRO_Y_OFFSET  -1.05606
#define GYRO_Z_OFFSET  -0.54401


#define SPLIT  0.95 //COMP-filter nr
#define RadToDeg 180.0/PI 
#define  ACC_LPF_NR  95  //low pass filter nr
#define  GYRO_HPF_NR 0   //high pass filter nr
#define  GYRO_MAF_NR  2  //Moving average filter nr
//*************************************
