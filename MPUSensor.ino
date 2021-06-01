long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;

unsigned long ts=millis();
unsigned long tf=micros();

void MPU_init(){
  Wire.begin();
  setupMPU();
  tp=millis(); //for updateSensorVal
}

void setupMPU(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();  
  //---bw
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1A); //Accessing the register 26  
//  Wire.write(0b00000011); //DLPF_CFG=3 (bandwidth = 20Hz)
//  Wire.write(0b00000100); //DLPF_CFG=4 (bandwidth = 20Hz)
  Wire.write(0b00000101); //DLPF_CFG=5 (bandwidth = 10Hz)
  Wire.endTransmission(); 
  
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 
  
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission(); 

}

void updateSensorVal(){
  if((micros()-tf)>2600){//400hz
    recordGyroRegisters();  //Update only per 1300us, (~800Hz update rate)
    tf=micros();  
  }
  if((millis()-ts)>20){  //Update only once per 20ms (50Hz update rate)
    recordAccelRegisters();
    ts=millis();
  }

  unsigned long t = millis();
  float dt = (float)(t-tp)/1000.0;
  float roll_acc = (atan2(accelX,accelZ)*RadToDeg)-0.48;
  float pitch_acc = -(atan2(accelY,accelZ)*RadToDeg)-1.1;
  roll_acc_f =(ACC_LPF_NR*roll_acc_f+(100.0-ACC_LPF_NR)*roll_acc)/100.0;
  pitch_acc_f =(ACC_LPF_NR*pitch_acc_f+(100.0-ACC_LPF_NR)*pitch_acc)/100.0;
  roll=SPLIT*(rotX*dt+roll)+(1.0-SPLIT)*roll_acc;
  pitch=SPLIT*(rotY*dt+pitch)+(1.0-SPLIT)*pitch_acc;
  tp=t;
  
}

void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  //processAccelData();
  
}

void processAccelData(){
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0; 
  gForceZ = accelZ / 16384.0;
}

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processGyroData();
}

void processGyroData() {
  rotX = (-gyroY / 131.0)+0.34;
  rotY = (-gyroX / 131.0)-1.34; 
  rotZ = (gyroZ / 131.0)+0.78;
}
