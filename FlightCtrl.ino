void FlightControl(){

#ifdef SAFE
  if(ch3.getValue()<1180){
    motorStop();
  }
#endif

  if(ch5<1500){//switch
    rateAngleSwitch=0;
    //leds_status(0);
    digitalWrite(7,LOW);
  }
  else{
    rateAngleSwitch=1;
    //leds_status(1);
    digitalWrite(7,HIGH);
    PIDangleX.resetI();
    PIDangleY.resetI();
  }

  throttle=map(ch3.getValue(),THROTTLE_RMIN,THROTTLE_RMAX,THROTTLE_WMIN,THROTTLE_WMAX);

#ifdef RX_EXPO  //Software RX EXPO
  if(ch4.getValue()<1480){
    setZ=map(ch4.getValue(),YAW_RMIN,1480,YAW_WMAX,0);
  }//if rxVal[0]
  else{
    setZ=map(ch4.getValue(),1520,YAW_RMAX,0,YAW_WMIN);
  }//else

  if (rateAngleSwitch == 0){//angle mode

    if(ch2.getValue()<1480){//angle around y (pitch)
      setY=map(ch2.getValue(),PITCH_RMIN,1480,PITCH_WMIN,0);
    }
    else{
      setY=map(ch2.getValue(),1520,PITCH_RMAX,0,PITCH_WMAX);
    }

    if(ch1.getValue()<1480){//roll angle around x
      setX=map(ch1.getValue(),ROLL_RMIN,1480,ROLL_WMAX,0);
    }
    else{
      setX=map(ch1.getValue(),1520,ROLL_RMAX,0,ROLL_WMIN);
    }  
  }//if rateAngleSwitch==0
  
  else{//rate mode

    if(ch2.getValue()<1480){//pitch
      setY=map(ch2.getValue(),PITCH_RMIN,1480,PITCH_WMIN*RX_RATE_SENSITIVITY,0);
    }
    else{
      setY=map(ch2.getValue(),1520,PITCH_RMAX,0,PITCH_WMAX*RX_RATE_SENSITIVITY);
    }//else

    if(ch1.getValue()<1480){//roll
      setX=map(ch1.getValue(),ROLL_RMIN,1480,ROLL_WMAX*RX_RATE_SENSITIVITY,0);
    }//if rxVal[2]
    else{
      setX=map(ch1.getValue(),1520,ROLL_RMAX,0,ROLL_WMIN*RX_RATE_SENSITIVITY);
    }//else 
  } //else (rateAngleSwitch==1)

  if((ch1.getValue()>1480) & (ch1.getValue()<1520)) setX=0.0;
  if((ch2.getValue()>1480) & (ch2.getValue()<1520)) setY=0.0;
  if((ch4.getValue()>1480) & (ch4.getValue()<1520)) setZ=0.0;

#else
  setZ=map(ch4.getValue(),YAW_RMIN,YAW_RMAX,YAW_WMAX,YAW_WMIN);
  if (rateAngleSwitch == 0){
    setX=map(ch1.getValue(),ROLL_RMIN,ROLL_RMAX,ROLL_WMIN,ROLL_WMAX);
    setY=map(ch2.getValue(),PITCH_RMIN,PITCH_RMAX,PITCH_WMAX,PITCH_WMIN);
  }
  else{
    setX=map(ch1.getValue(),ROLL_RMIN,ROLL_RMAX,ROLL_WMIN*RX_RATE_SENSITIVITY,ROLL_WMAX*RX_RATE_SENSITIVITY);
    setY=map(ch2.getValue(),PITCH_RMIN,PITCH_RMAX,PITCH_WMAX*RX_RATE_SENSITIVITY,PITCH_WMIN*RX_RATE_SENSITIVITY); 
  }
#endif
  if (rateAngleSwitch == 0){//angle mode
    ref_angle_x = setX;
    ref_angle_y = setY;
    
    setX=(int)PIDangleX.Compute((double)setX-roll,rotX,(double)setX/RX_ANGLE_DAMPNING,1,14,-14); //maybe use float instead
    setY=(int)PIDangleY.Compute((double)setY-pitch,rotY,(double)setY/RX_ANGLE_DAMPNING,1,14,-14);//pitch
  }
  ref_rate_x = setX;
  ref_rate_y = setY;
  ref_rate_z = setZ;
  
  int PIDroll_val= (int)PIDroll.Compute((double)setX-rotX,1,7,-7);
  int PIDpitch_val= (int)PIDpitch.Compute((double)setY-rotY,1,7,-7);
  int PIDyaw_val= (int)PIDyaw.Compute((double)setZ-rotZ,1,7,-7);
  
  m1_val=throttle+PIDroll_val+PIDpitch_val+PIDyaw_val;
  m2_val=throttle+PIDroll_val-PIDpitch_val-PIDyaw_val;
  m3_val=throttle-PIDroll_val+PIDpitch_val-PIDyaw_val;
  m4_val=throttle-PIDroll_val-PIDpitch_val+PIDyaw_val;
  if(m1_val>220){
    m1_val = 220;
  }
  else if (m1_val<150){
    m1_val = 150; 
  }
  if(m2_val>220){
    m2_val = 220;
  }
  else if (m2_val<150){
    m2_val = 150; 
  }
  if(m3_val>220){
    m3_val = 220;
  }
  else if (m3_val<150){
    m3_val = 150; 
  }
  if(m4_val>220){
    m4_val = 220;
  }
  else if (m4_val<150){
    m4_val = 150; 
  }
  analogWrite(MOTOR_1_PIN,m1_val);
  analogWrite(MOTOR_2_PIN,m2_val);
  analogWrite(MOTOR_3_PIN,m3_val);
  analogWrite(MOTOR_4_PIN,m4_val);

}
