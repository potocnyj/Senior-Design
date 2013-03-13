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
  }
  // NOTE: units are inches per second (In/S)
//  Serial.print("in/S: ");
//  Serial.println(((revCount - oldRevCount) * WHEEL_CIRCUM) * ((float)SPEED_UPDATE_TIME / 1000.0f)); // distance * time (milliseconds/1000 == second
  oldRevCount = revCount;
  updateDistCount++;
  
}// end speedUpdate


void writeDist()
{
  unsigned long dist = (revCount * WHEEL_CIRCUM);
//  Serial.print("Odo: ");
//  Serial.println(dist);
  writeOdom(dist);
}// end writeDist
