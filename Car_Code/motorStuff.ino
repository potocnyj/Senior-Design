// Motor Stuff
#define MOTOR_PIN    6

Servo motor;

// initialize the motor control
void motorSetup()
{
  motor.attach(MOTOR_PIN, MOTOR_MIN, MOTOR_MAX);    // setup min and max for the motor
  motor.writeMicroseconds(MOTOR_NEU);             // set motor for neutral  
}// end motorSetup


// interpret our motor throttle data 
// into a value for the controller
int motorParse()
{
  char dataOut[] = {'0','0','0','0','0','0','\0'};
  int scaledValue;
  byte j = 0;
  for(byte i = MOTOR_DATA_START; i <= MOTOR_DATA_END; i++)
  {
    dataOut[j] = data[i]; 
    j++;
  }
  
  scaledValue = map(atoi(dataOut), DRIVE_LOW, DRIVE_HIGH, MOTOR_MIN, MOTOR_MAX);

  return scaledValue; // return the mapped value
}// end motorParse


// send speed to the engine
void motorControl(int dataIn)
{
  // write the speed to the engine 
  if((dataIn >= MOTOR_MIN) && (dataIn <= MOTOR_MAX))
  {
    if(!collisionNear)
    {
      motor.writeMicroseconds(dataIn);
    }
    else if(dataIn <= MOTOR_NEU)
    {
      motor.writeMicroseconds(dataIn);
    }
  }
}//end engine
    

// Kill the motor
void neutralEngine()
{
  motor.writeMicroseconds(MOTOR_NEU);
}//end neutralEngine


// Attempt to brake the engine by reversing throttle quickly
void brakeEngine()
{
  motor.writeMicroseconds(MOTOR_NEU);
  delay(50);
  motor.writeMicroseconds(MOTOR_MIN);
  delay(50);
  motor.writeMicroseconds(MOTOR_NEU);
  delay(50);
  motor.writeMicroseconds(MOTOR_MIN);
  delay(250);
  motor.writeMicroseconds(MOTOR_NEU);
}
    

// Parses the motor packet and applies 
// the new throttle value to the speed controller
void motorAlphaControl()
{
  int requestedMotorSpeed = motorParse();
  
  if(requestedMotorSpeed >= MOTOR_NEU)    // if going forward
  {
    inReverse = false;
  }
  else  // if going backwards
  {
    inReverse = true;
    toggleCruise(false); // a reverse vector indicates cruise should be off
  }
  
  lastSpeed = requestedMotorSpeed;   // last good speed.
  
  // if cruise control if off
  if(!cruiseControl)
  {
    motorControl(requestedMotorSpeed);  // use the requested motor speed
  }
  else  // cruise control is on
  {
    if(requestedMotorSpeed > savedSpeed)   // if user wants to go faster than cruise is going, let them
    {                                      // inadvertently prevents reverse :(
      savedSpeed = requestedMotorSpeed;    // We need to update the speed we are cruising at
      motorControl(requestedMotorSpeed);   // Update the throttle speed
    }
    else if(requestedMotorSpeed < MOTOR_NEU)    // if user tries to put in reverse, stop cruise control
    {
      cruiseControl = false;
      motorControl(requestedMotorSpeed);  // Let the user reverse the throttle
    }
  } 
}//end motorAlphaControl
