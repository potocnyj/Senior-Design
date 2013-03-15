#define WHEEL_CIRCUM 12.17367
#define DIST_UPDATE_RATE  4

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
  int carSpeedInt;
  String carSpeedOut;
  
  // use this to update the odometer
  if(updateDistCount >= DIST_UPDATE_RATE)    // time for updateDist = (updateDistCount)*Speed_update_time (in seconds)
  {
    writeDist();
    updateDistCount = 0;
    totalRevCount = 0;    
  }

  // speed   =         distance    (/12 => feet) /     time (seconds )              (scaling factor)
  carSpeed = ((float)((float)(revCount * WHEEL_CIRCUM) / 12.0f) / ((float)(SPEED_UPDATE_TIME / 1000.0f)))*100;
  carSpeedInt = (int)floor(carSpeed);
  carSpeedOut = (String)carSpeedInt;
  carSpeedOut = zeroPadVar((String)carSpeedOut, 12);
    
  Serial.println("**s" + carSpeedOut);
  
  totalRevCount = revCount;
  revCount = 0;
  updateDistCount++;  
  
  if(voltageCounter == 4)
  {
    getVoltage();
    voltageCounter = 0;
  }
  else
  {
    voltageCounter++;
  }
  if(timerCounter == 120)
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
void writeDist()
{
  unsigned long dist = (totalRevCount * WHEEL_CIRCUM / 12);
  totalDistance = totalDistance + dist;
  String distString = (String)dist + (String)readOdom();
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
