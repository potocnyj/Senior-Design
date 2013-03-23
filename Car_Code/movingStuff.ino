#define WHEEL_CIRCUM 12.17367/2   // because we now have 2 magnets
#define DIST_UPDATE_RATE  5

int totalRevCount = 0;
byte updateDistCount = 0;
boolean timerSelect = true;
int voltageCounter = 0;
int timerCounter = 0;

// Update the car's current speed
// based on the hall effect sensor
void speedUpdate()
{
  float carSpeed;
  float distance;
  String carSpeedOut;

  distance = (revCount * WHEEL_CIRCUM) / 12.0f; // distance in ft
    // speed   =   distance(feet) /     time (seconds )                (scaling factor)
  carSpeed = ((float)(distance / ((float)(SPEED_UPDATE_TIME / 1000.0f))))*100;
  carSpeedInt = (int)floor(carSpeed);
  if (cruiseControl && updateSpeed) // if we have throttled up, then change our saved speed to the new speed
  {
    savedSpeed = carSpeedInt;
    updateSpeed = false;
  }
  carSpeedOut = (String)carSpeedInt;
  carSpeedOut = zeroPadVar((String)carSpeedOut, 12);
  
  Serial.println("**s" + carSpeedOut);
    
  // use this to update the odometer
  if(updateDistCount >= DIST_UPDATE_RATE)    // time for updateDist = (updateDistCount)*Speed_update_time (in seconds)
  {
    writeDist((totalRevCount * WHEEL_CIRCUM) / 12.0f);
    updateDistCount = 0;
    totalRevCount = 0;    
  }
  
  totalRevCount += revCount;
  revCount = 0;
  updateDistCount++;  
  
  if(voltageCounter == 10)
  {
    getVoltage();
    voltageCounter = 0;
  }
  else
  {
    voltageCounter++;
  }
  if(timerCounter == 60)
  {  
    calculateTime();
    timerCounter = 0;
  }
  else
  {
    timerCounter++;
  }
}// end speedUpdate


// Updates the car's distance travelled
// based on the hall effect sensor data
void writeDist(float distance)
{
  unsigned long dist = floor(distance);
  totalDistance = totalDistance + dist;  // wtf is this line for?
  String distString = (String)(dist + readOdom());
  distString = zeroPadVar(distString, 12);
  
  Serial.println("**o" + distString);
  
  writeOdom(dist + readOdom());
}// end writeDist


// Pad the raw string value of 
// the speed and distance packets with zeroes
String zeroPadVar(String input, int length)
{
  String val = input;
  while(val.length() < length)
  {
    val = "0" + val;
  }
  
  return val;
}
