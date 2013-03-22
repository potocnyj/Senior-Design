// Steer Stuff
#define steeringPin  9    // The digital output pin for the steering servo

Servo steer;


// sets up the steer stuff for us
void steerSetup()
{
  steer.attach(steeringPin, MIN_TURN, MAX_TURN);
  steer.writeMicroseconds(NEUTRAL_TURN);
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
  
  int steerPos = map(atoi(dataOut), DRIVE_LOW, DRIVE_HIGH, MIN_TURN, MAX_TURN);
  
  return steerPos;
}// end steerParse


// calls Johns steering code
void steerControl(int steerPos)
{
  // write the turn amount to the engine

  if((steerPos >= MIN_TURN) &&  (steerPos <= MAX_TURN))
  {
    steer.writeMicroseconds(steerPos);
  }
  
  wheelTurned(steerPos);  
}// end steer
