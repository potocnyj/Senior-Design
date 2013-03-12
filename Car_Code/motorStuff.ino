// Motor Stuff
#define MOTOR_PIN    6

Servo motor;
int engineSpeed;


void motorSetup()
{
  engineSpeed = MOTOR_NEU;
  motor.attach(MOTOR_PIN, MOTOR_MIN, MOTOR_MAX);    // setup min and max for the motor
  motor.writeMicroseconds(engineSpeed);               // set motor for neutral  
}// end motorSetup


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
    
    
void neutralEngine()
{
  motor.writeMicroseconds(MOTOR_NEU);
}//end neutralEngine    


void motorAlphaControl()
{
  int requestedMotorSpeed = motorParse();
  
  if(requestedMotorSpeed >= 0)    // if going forward
    inReverse = false;
  else                            // if going backwards
    inReverse = false;
  
  if(requestedMotorSpeed != 0) // from controller: -3768 or something is full reverse, while 3768 or something is full forward
  {
    lastSpeed = requestedMotorSpeed;  // last good speed.
  }
  
  if(!cruiseControl)            // if cruise control if off
  {
    motorControl(requestedMotorSpeed);  // use the requested motor speed
  }
  else                          // cruise control is on
  {
    if(requestedMotorSpeed > savedSpeed) // if user wants to go faster than cruise is going, let them
    {                                    // inadvertently prevents reverse :(
      motorControl(requestedMotorSpeed);
    }
    else
    {
      motorControl(savedSpeed); // otherwise use cruise control speed
    }
    
    if(requestedMotorSpeed < -1) // if user tries to put in reverse, stop cruise control
    {
      cruiseControl = false;
    }
  } 
}//end motorAlphaControl
