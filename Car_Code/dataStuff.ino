#define MSB_DATA          0
#define DATA_LEN          6        // how many bytes the relevant data is

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


// The main function to decide what to do with received packets
void gateKeeper()
{
  switch(MSB())
  {
    // Drive case 
    case 'd':
      // the drive packet is 13 bytes long.  first char is identifier 
      // next 6 chars is throttle position, the last 6 are steering
      // position.
      steerControl(steerParse());     // steering
      motorAlphaControl();            // engine
      break;
    case 'c': // cruise control
      parseCruise(data[PACKET_LEN], data[1]);  // last byte for parsing, 1 for speed control
      break;
    case 'l':
      signalButtonPressed(leftSignal);
      break;
    case 'r':
      signalButtonPressed(rightSignal);
      break;
    case 'y':
      driveSelect();  // Change between comfort and sport mode
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


// ensure that the data packet is in our standard form (1 letter, all digits following)
boolean dataValid()
{
  if(checkChar((int)data[0])) // first char is a lowercase letter
  {
    for(int i = 1; i <= DATA_LEN; i++)
    {
      if(!((((int)data[i] >= 48) && ((int)data[i] <= 57)) || ((int)data[i] == 45)))    // if data != number, return false
        return false;
    }
    
    return true;
  }
  
  return false;
}// end dataValid


// Check to make sure that the input integer is equal to an ascii character (a-z)
boolean checkChar(int character)
{
  return ((character >= 97) && (character <= 122));
}


// Toggle between comfort and sport mode for driving
void driveSelect()
{
  if(!comfortMode)
  {
    MOTOR_MAX = MOTOR_MAX_B;  //slow down the engine (comfort mode)
    MOTOR_MIN = MOTOR_MIN_B;
    comfortMode = true;
  }
  else
  {
    MOTOR_MAX = MOTOR_MAX_A;   // speed up the engine (sport mode)
    MOTOR_MIN = MOTOR_MIN_A;
    comfortMode = false;
  }
}//end driveSelect
