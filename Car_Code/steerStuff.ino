// Steer Stuff

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
  wheelTurned(steerPos);  
  if((steerPos >= minTurn) &&  (steerPos <= maxTurn))
  {
    steer.writeMicroseconds(steerPos);
  }
}// end steer
