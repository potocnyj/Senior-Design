#include <stdlib.h>
#include <Servo.h>
#include <PWM.h>
#include <Timer.h>

#define PACKET_LEN    12
#define BAUD_RATE   9600

Timer t;
int i;
int lastSpeed;
boolean success;
boolean collisionNear = false;

void setup()
{
  motorSetup();                     // initalize motor
  steerSetup();                     // initalize steer
  Serial.begin(BAUD_RATE);          // start serial
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
}//end setup


void loop()
{
  checkSerial();    // find if there is any data waiting for us
  collisionNear = collisionImminent();
  motorAlphaControl();
  t.update();
}// end loop


