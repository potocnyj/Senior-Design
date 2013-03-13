#define WHEEL_CIRCUM 12.17367
#define ROT_TIMEOUT 5000        // if it takes more than 5 seconds to rotate the tire, then dont count it
#define DIST_UPDATE_RATE  4

int oldRevCount = 0;
byte updateDistCount = 0;
boolean timerSelect = true;


void speedUpdate()
{
  // use this to update the odometer
  if(updateDistCount >= DIST_UPDATE_RATE)    // time for updateDist = (updateDistCount)*Speed_update_time (in seconds)
  {
    updateDistCount = 0;
    writeDist();
  }
  
  // NOTE: units are inches per second (Ft/S)
  // distance * time (milliseconds/1000 == second  
  String carSpeed = (String)((int)(((revCount - oldRevCount) * WHEEL_CIRCUM * ((float)SPEED_UPDATE_TIME / 1000.0f))) / 12);
  carSpeed = zeroPadVar(carSpeed, 12);
  // (int)(((((revCount - oldRevCount) * WHEEL_CIRCUM) * ((float)SPEED_UPDATE_TIME / 1000.0f)) / 12));
  Serial.println("**s" + carSpeed);

  oldRevCount = revCount;
  updateDistCount++;  
}// end speedUpdate


void writeDist()
{
  unsigned long dist = (revCount * WHEEL_CIRCUM / 12);
  String distString = (String)dist;
  distString = zeroPadVar(distString, 12);
  
  Serial.println("**o" + distString);
  
  writeOdom(dist);
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
