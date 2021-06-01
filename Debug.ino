void debugProcess(){
#ifdef DEBUG_QUAT_ANGLE
//  Serial.print(accel);
//  Serial.print(",");
//  Serial.print(gyro);
//  Serial.print(",");
//  Serial.print(mg);
//  Serial.print(",");
//  Serial.print(system_1); 
//  Serial.print(",");
//  Serial.print(roll);
//  Serial.print(',');
//  Serial.print(pitch);
//  Serial.print(',');
//  Serial.print(yaw);
//  Serial.print(",");
//  Serial.print(ch1.getValue());
//  Serial.print(",");
//  Serial.print(ch2.getValue());
//  Serial.print(",");
//  Serial.print(ch3.getValue());
//  Serial.print(",");
//  Serial.print(ch4.getValue());
//  Serial.print(",");
//  Serial.print(ch5);
//  Serial.print(",");
//  Serial.print(ch6);
//  Serial.print(",");
  Serial.print((float)(gx_aver));  
  Serial.print(",");
  Serial.print((float)(gy_aver));  
  Serial.print(",");
  Serial.print((float)(gz_aver));
  Serial.print(",");
  Serial.print(m1_val);
  Serial.print(",");
  Serial.print(m2_val);
  Serial.print(",");
  Serial.print(m3_val);
  Serial.print(",");
  Serial.print(m4_val);
#endif

#ifdef DEBUG_MPU
//
// Serial.print(roll);
// Serial.print(",");
// Serial.print(pitch);
// Serial.print(",");
// Serial.print(rotX); //our gx
// Serial.print(",");
// Serial.print(rotY); //our gy
// Serial.print(",");
// Serial.print(rotZ);//gz
// Serial.print(",");
// Serial.print(m1_val);
// Serial.print(",");
// Serial.print(m2_val);
// Serial.print(",");
// Serial.print(m3_val);
// Serial.print(",");
//Serial.println(m4_val);

mySensorData = SD.open("PTData.txt", FILE_WRITE);
if (mySensorData) {
  
mySensorData.print(roll);                             //write temperature data to card
mySensorData.print(",");                               //write a commma

mySensorData.print(pitch);                             //write temperature data to card
mySensorData.print(",");  

mySensorData.print(rotX);                             //write temperature data to card
mySensorData.print(",");  

mySensorData.print(rotY);                             //write temperature data to card
mySensorData.print(",");  

mySensorData.print(rotZ);                             //write temperature data to card
mySensorData.print(",");

mySensorData.print(ref_angle_x);                             //write temperature data to card
mySensorData.print(",");

mySensorData.print(ref_angle_y);                             //write temperature data to card
mySensorData.print(",");

mySensorData.print(ref_rate_x);                             //write temperature data to card
mySensorData.print(",");

mySensorData.print(ref_rate_y);                             //write temperature data to card
mySensorData.print(",");


mySensorData.println(ref_rate_z);                        //write pressure and end the line (println)
mySensorData.close();
}


#endif

//  Serial.print('\n');

}
