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
          dataIn[i] = Serial.read();
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
    case 'c': // cruise control
      if(dataIn[1] == '0')
      {
        toggleCruise(dataIn[PACKET_LEN]);
      }
      break;
    case 's':
        updateCurrentSpeed(dataIn);
      break;
    case 'b':
      if(dataIn[1] == '0')
      {
        updateBatteryTime(dataIn);
      }
      if(dataIn[1] == '1')
      {
        updateBatteryDist(dataIn);
      }
      break;
    case 'o':
        Serial.println(dataIn);
        updateOdometer();
      break;
    default:
      break;
  }
}// end gateKeeper


// returns the MSB of the data packet
char MSB()
{
  return dataIn[MSB_DATA];
}// end MSB


boolean dataValid()
{
  if(checkChar((int)dataIn[0])) // first char is a lowercase letter
  {
    for(int i = 1; i <= DATA_LEN; i++)
    {
      if(!((((int)dataIn[i] >= 48) && ((int)dataIn[i] <= 57)) || ((int)dataIn[i] == 45)))    // if data != number, return false
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


void toggleCruise(char cruiseDataalskd)
{
  // 1 signals cruise is on, 0 s off
  if(cruiseDataalskd == '1')
  {
    cruise = true;
  }
  else if (cruiseDataalskd == '0')
  {
    cruise = false; 
  }
  
  updateDisplay();
}


void updateCurrentSpeed(char speedInfo[])
{ 
  speedInFTS = atof(cleanInfo(dataIn));
  speedInFTS = speedInFTS / 100;
  speedInScaled = speedInFTS * 6.82;
  if((previousSpeed != speedInFTS) && (currentDisplay == 1))
  {
       updateDisplay();
  }
  previousSpeed = speedInFTS;
  
}


void updateBatteryDist(char batDist[])
{
    batDistFT = atof(cleanInfo(dataIn));
    batDistScaled = batDistFT * 6.82;
    if((previousBatDist != batDistFT) && ( currentDisplay == 4))
    {
      updateDisplay();
    }
}


void updateBatteryTime(char batTime[])
{
  cleanInfo(batTime);
  batTimeLeft = atof(cleanInfo(batTime));
  if((previousBatTime != batTimeLeft) && (currentDisplay == 3))
  {
    updateDisplay();
  }
}


void updateOdometer()
{
  currentODOFT = atoi(cleanInfo(dataIn));
  currentODOScaled = currentODOFT * .01894;
  if(currentDisplay == 1)
  {
      updateDisplay();
  }
  previousODO = currentODOFT;
  Serial.print("currentODOFT: ");
  Serial.println(currentODOFT);
}


void updateRangeInfo()
{
   rangePercent = getRSSI();
   if((rangePercent <= 30) && (rangePercent > 0))
   {
     displayRangeWarning();
   }
   if(rangePercent != -1)
   {
     if((previousRange != rangePercent) && (currentDisplay == 5))
     {
       updateDisplay();
     }
     
     previousRange = rangePercent;
   }
}


char* cleanInfo(char arrayToClean[])
{
    char cleanArray[PACKET_LEN -1];
    for(int i = 1; i <=  PACKET_LEN; i++)
  {
      cleanArray[i-1] = arrayToClean[i];
  }
  return cleanArray;
}
