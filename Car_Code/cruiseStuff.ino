void parseCruise(char cruiseControlBit, char cruiseSpeedBit)
{  
  if(cruiseControlBit == '0') // if its 0, toggle cruise control
  {
    initCruise();
  }

  // Make sure
  if((cruiseControl) && (cruiseSpeedBit == '1') && (cruiseControlBit == '1')) // if cruise is on, and bit is 1, incrument cruise
  {
    cruiseSpeedUp();
    Serial.println("cruiseSpeedUp called");
  }
  
  if((cruiseControl) && (cruiseSpeedBit == '2') && (cruiseControlBit == '1'))
  {
    cruiseSpeedDown();
    Serial.println("cruiseSpeedDown called");
  }
}// end parseCruise


void initCruise()
{
  if(cruiseControl)
  {
    cruiseControl = false;            // cruise was on, now turn off
    savedSpeed = -1;                  // reset the defalut saved speed
    Serial.println("**c000000000000");  // tell controller cruise is off
  }
  else
  {
    cruiseControl = true;             // cruise is not on, turn on
    savedSpeed = lastSpeed;           // set the cruise speed as the last known good speed      
    motorControl(savedSpeed);         // tell motor to go that speed
    Serial.println("**c000000000001");  // tell controller cruise is on
  }
}//end initCruise


void cruiseSpeedUp()
{
  if(cruiseControl)
  {
    if(savedSpeed + 20 < MOTOR_MAX)
    {
      savedSpeed = savedSpeed + 20;
    }
  }
}// end cruiseSpeedUp


void cruiseSpeedDown()
{
  if(cruiseControl) // make sure cruise is on
  {
    if(savedSpeed - 20 > MOTOR_MIN)  // so we dont explode our motor
    {
      savedSpeed = savedSpeed - 20;
    }
  }
}// end cruiseSpeedDown
