// Parse our cruise control packet and decide what function to perform
// cruiseControlBit: indicates which function to perform (0 = toggle, 1 = on)
// cruiseSpeedBit: indicates whether to increment or decrement cruise speed
void parseCruise(char cruiseControlBit, char cruiseSpeedBit)
{  
  if(cruiseControlBit == '0') // if its 0, toggle cruise control
  {
    toggleCruise(!cruiseControl);
  }

  // Make sure
  if((cruiseControl) && (cruiseSpeedBit == '1') && (cruiseControlBit == '1')) // if cruise is on, and bit is 1, incrument cruise
  {
    cruiseSpeedUp();
  }
  
  if((cruiseControl) && (cruiseSpeedBit == '2') && (cruiseControlBit == '1'))
  {
    cruiseSpeedDown();
  }
}// end parseCruise

// toggle cruise control
void toggleCruise(boolean cruise)
{
  if(cruise == false)
  {
    cruiseControl = false;              // cruise was on, now turn off
    savedThrottle = -1;                 // reset the defalut saved speed
    savedSpeed    = -1;
    lastSpeed     = MOTOR_NEU;
    
    Serial.println("**c000000000000");  // tell controller cruise is off
    Serial.println("**c000000000000");  // tell controller cruise is off
    Serial.println("**c000000000000");  // tell controller cruise is off
  }
  else
  {
    cruiseControl = true;               // cruise is not on, turn on
    savedThrottle = lastSpeed;          // set the cruise throttle as the last known good speed
    savedSpeed    = carSpeedInt;        // set the cruise target speed to the last measured speed
    motorControl(savedThrottle);        // tell motor to go that speed
    
    Serial.println("**c000000000001");  // tell controller cruise is on
    Serial.println("**c000000000001");  // tell controller cruise is on
    Serial.println("**c000000000001");  // tell controller cruise is on
  }
}//end toggleCruise


// increment the cruise control speed
void cruiseSpeedUp()
{
  savedSpeed += 100;
}// end cruiseSpeedUp


// decrement the cruise control speed
void cruiseSpeedDown()
{
  savedSpeed -= 100;
}// end cruiseSpeedDown


void cruiseThrottleUp()
{
  if(cruiseControl)
  {
    if((savedThrottle + 10) <= MOTOR_MAX)
    {
      savedThrottle = savedThrottle + 10;     // Update the stored car speed
      motorControl(savedThrottle);            // Change the motor's current speed
    }
  }
}


void cruiseThrottleDown()
{
  if(cruiseControl) // make sure cruise is on
  {
    if((savedThrottle - 10) >= MOTOR_MIN)
    {
      savedThrottle = savedThrottle - 10;     // Update the stored car speed
      motorControl(savedThrottle);            // Change the motor's current speed
    }
  }
}


void adjustSpeed()
{
  if((carSpeedInt/100) < (savedSpeed/100))
  {
    cruiseThrottleUp();
  }
  else if ((carSpeedInt/100) > (savedSpeed/100))
  {
    cruiseThrottleDown();
  }
}
