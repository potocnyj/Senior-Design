#include <stdlib.h>
#include <Servo.h>
#include <PWM.h>

#define PACKET_LEN    12
#define BAUD_RATE   9600

int i;
int lastSpeed;
boolean success;


void setup()
{
  motorSetup();                     // initalize motor
  steerSetup();                     // initalize steer
  Serial.begin(BAUD_RATE);          // start serial
}//end setup


void loop()
{
  checkSerial();    // find if there is any data waiting for us
  motorAlphaControl();
}// end loop


