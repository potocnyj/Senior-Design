// Steer Stuff
#define minTurn      1300 // The lowest microsecond pulse the turning servo can take; a full left turn
#define maxTurn      1700 // The highest microsecond pulse the turning servo can take; a full right turn
#define neutralTurn  1500 // Neutral turn position on the servo
#define steeringPin  9    // The digital output pin for the steering servo

Servo steer;
int steerPos;


// sets up the steer stuff for us
void steerSetup()
{
  steerPos = neutralTurn;
  steer.attach(steeringPin, minTurn, maxTurn);
  steer.writeMicroseconds(steerPos);
}//end steerSetup


// takes the steering data (bytes 1-6) out of the drive packet and returns it
int steerParse()
{
  char dataOut[] = {'0','0','0','0','0','0','\0'};
  byte j = 0;
  
  for(byte i = STEER_DATA_START; i <= STEER_DATA_END; i++)
  {
    dataOut[j] = data[i]; 
    j++;
  }
  
  return atoi(dataOut);
}// end steerParse


// calls Johns steering code
void steerControl(int dataIn)
{
  // write the turn ammount to the engine
  steerPos = map(dataIn, DRIVE_LOW, DRIVE_HIGH, minTurn, maxTurn);  
  if((steerPos >= minTurn) &&  (steerPos <= maxTurn))
  {
    steer.writeMicroseconds(steerPos);
  }
}// end steer
