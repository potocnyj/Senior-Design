#define WHEEL_CIRCUM 12.17367
#define ROT_TIMEOUT 5000        // if it takes more than 5 seconds to rotate the tire, then dont count it
#define DIST_UPDATE_RATE  4

int totalRevCount = 0;
byte updateDistCount = 0;
boolean timerSelect = true;


void speedUpdate()
{
  float carSpeed;
  int carSpeedInt;
  String carSpeedOut;
  
  // use this to update the odometer
  if(updateDistCount >= DIST_UPDATE_RATE)    // time for updateDist = (updateDistCount)*Speed_update_time (in seconds)
  {
    updateDistCount = 0;
    writeDist();
  }
/*  -- OLD CODE, KEPT UNTILL IT IS KNOWN THAT SPEED CALCULATIONS ARE ACCURATE 
  // NOTE: units are inches per second (Ft/S)
  // distance * time (milliseconds/1000 == second  
  String carSpeed = (String)((int)(((revCount - totalRevCount) * WHEEL_CIRCUM * ((float)SPEED_UPDATE_TIME / 1000.0f))) / 12);
  carSpeed = zeroPadVar(carSpeed, 12);
  // (int)(((((revCount - totalRevCount) * WHEEL_CIRCUM) * ((float)SPEED_UPDATE_TIME / 1000.0f)) / 12));
  Serial.println("**s" + carSpeed);
*/
// speed   =         distance    (/12 => feet) /     time (seconds )              (scaling factor)
  carSpeed = (((revCount * WHEEL_CIRCUM) / 12) / ((float)SPEED_UPDATE_TIME / 1000)) * 100;
  carSpeedInt = (int)floor(carSpeed);
  carSpeedOut = (String)carSpeedInt;
  carSpeedOut = zeroPadVar((String)carSpeedOut, 12);
  
  Serial.println("**s" + carSpeedOut);
  
  totalRevCount = revCount;
  revCount = 0;
  updateDistCount++;  

  totalRevCount = revCount;
  updateDistCount++;  
}// end speedUpdate


void writeDist()
{
  unsigned long dist = (revCount * WHEEL_CIRCUM / 12);
  String distString = (String)dist + (String)readOdom();
  distString = zeroPadVar(distString, 12);
  
  Serial.println("**o" + distString);
  
  writeOdom(dist + readOdom());
}// end writeDist


String zeroPadVar(String input, int length)
{
  String val = input;
  while(val.length() < length)
  {
    val = "0" + val;
  }
  
  return val;
}
