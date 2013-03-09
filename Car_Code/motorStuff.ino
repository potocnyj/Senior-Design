// Motor Stuff
#define MOTOR_PIN    6
#define MOTOR_MAX    1700  // Should work to 2000, but scary on a table
#define MOTOR_MIN    1300  // should work to 1000, but scary on a table
#define MOTOR_NEU    1500

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
  
  if(requestedMotorSpeed != 0)
  {
    lastSpeed = requestedMotorSpeed;
  }
  
  if(!cruiseControl)            // if cruise control if off
  {
    motorControl(requestedMotorSpeed);
  }
  else                          // cruise control is on
  {
    if(requestedMotorSpeed > savedSpeed) // inadvertently prevents reverse :(
    {
      motorControl(requestedMotorSpeed);
    }
    else
    {
      motorControl(savedSpeed);
    }
  } 
}//end motorAlphaControl
