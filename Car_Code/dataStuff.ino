#define MOTOR_DATA_START  1
#define MOTOR_DATA_END    6
#define STEER_DATA_START  7
#define STEER_DATA_END    12
#define MSB_DATA          0
#define DRIVE_HIGH        32768
#define DRIVE_LOW         -32768
#define DATA_LEN          6        // how many bytes the relevant data is


int leftSignal = 13;
int rightSignal = 8;

// This will process all the data for us
void checkSerial()
{
  if (Serial.available() >= 15) // 13 (0-12) is our packet size with 2 bytes of verification, so we need atleast this much
  {
    if(Serial.read() == '*')    // if char 1 is '*' then data is good
    {
      if(Serial.read() == '*')  // if char 2 is '*' data is still good
      {
        for(int i = 0; i <= PACKET_LEN; i++)    // now, put all the data in the array, check later
        {
          data[i] = Serial.read();
        }
        if(dataValid())
        {
          gateKeeper();
        }
      }
    }
  }
}// end checkSerial


void gateKeeper()
{
  switch(MSB())
  {
  // Drive case 
    case 'd':
      // the drive packet is 13 bytes long.  first char is identifier 
      // next 6 chars is throttle position, the last 6 are steering
      // position.
      motorAlphaControl();        // engine
      steerControl(steerParse());        // steering
      break;
    case 'c': // cruise control
      parseCruise(data[12], data[1]);  // last byte for parsing, 1 for speed control
      break;
    case 'l':
      signalButtonPressed(leftSignal);
      break;
    case 'r':
      signalButtonPressed(rightSignal);
      break;
    default:
      break;
  }
}// end gateKeeper


// returns the MSB of the data packet
char MSB()
{
  return data[MSB_DATA];
}// end MSB


boolean dataValid()
{
  if(((int)data[0] >= 97) && ((int)data[0] <= 122)) // first char is a lowercase letter
  {
    for(int i = 0; i <= DATA_LEN; i++)
    {
      if(!(((int)data[0] >= 48) && ((int)data[0] >= 57)))    // if data != number, return false
        return false;
    }
    
    return true;
  }
  
  return false;
}// end dataValid


