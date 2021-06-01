void MotorAnalogInit(){
  pinMode (7, OUTPUT);
  
  pinMode(MOTOR_1_PIN,OUTPUT); 
  pinMode(MOTOR_2_PIN,OUTPUT);
  pinMode(MOTOR_3_PIN,OUTPUT);
  pinMode(MOTOR_4_PIN,OUTPUT);

  analogWrite(MOTOR_1_PIN,ANALOG_MAX_SIGNAL);
  analogWrite(MOTOR_2_PIN,ANALOG_MAX_SIGNAL);
  analogWrite(MOTOR_3_PIN,ANALOG_MAX_SIGNAL);
  analogWrite(MOTOR_4_PIN,ANALOG_MAX_SIGNAL);

  digitalWrite (7, HIGH);
  delay(2000);
  digitalWrite (7, LOW);
  delay(3000);
  digitalWrite (7, HIGH);
  delay(2000);
  digitalWrite (7, LOW);

  analogWrite(MOTOR_1_PIN,ANALOG_MIN_SIGNAL);
  analogWrite(MOTOR_2_PIN,ANALOG_MIN_SIGNAL);
  analogWrite(MOTOR_3_PIN,ANALOG_MIN_SIGNAL);
  analogWrite(MOTOR_4_PIN,ANALOG_MIN_SIGNAL);
}

void motorStop(){
  analogWrite(MOTOR_1_PIN,MOTOR_ZERO_LEVEL);
  analogWrite(MOTOR_2_PIN,MOTOR_ZERO_LEVEL);
  analogWrite(MOTOR_3_PIN,MOTOR_ZERO_LEVEL);
  analogWrite(MOTOR_4_PIN,MOTOR_ZERO_LEVEL);
#ifdef SAFE
  while(ch3.getValue()<1190){
    if(Serial.available()>0){
     ANGLEX_KD = Serial.parseFloat();
     ANGLEY_KD = ANGLEX_KD;
     Serial.print("\n");
      }
  Serial.print(ANGLEX_KD);
  Serial.print(",");
  Serial.println(ch3.getValue());
};
  
//  ts=micros();
//  tf=micros();
  PID_init();
  PIDroll.resetI();
  PIDpitch.resetI();
  PIDyaw.resetI();
  PIDangleX.resetI();
  PIDangleY.resetI();
#endif
}
