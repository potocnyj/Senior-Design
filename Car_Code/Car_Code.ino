#include <stdlib.h>
#include <Servo.h>
#include <PWM.h>
#include <Timer.h>
#include <PinChangeInt.h>

#define SPEED_UPDATE_TIME  250    // time in mS to update the speed
#define PACKET_LEN    12
#define HALL_PIN      7
#define BAUD_RATE     9600
#define MOTOR_MAX    1700  // Should work to 2000, but scary on a table
#define MOTOR_MIN    1300  // should work to 1000, but scary on a table
#define MOTOR_NEU    1500

Timer t;
int i;
int lastSpeed;
int revCount = 1;
char data[] = {'0','0','0','0','0','0','0','0','0','0','0','0','0'};
volatile int revCounter = 0;       // used to count # of forward revolutions of wheel
boolean success;
boolean inReverse = false;      // used to ensure revCount only gets updated when going forward
boolean collisionNear = false;


void setup()
{
  motorSetup();                     // initalize motor
  steerSetup();                     // initalize steer
  Serial.begin(BAUD_RATE);          // start serial
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);

  // interrupt stuff, VERIFIY BEFORE MODIFYING 
  pinMode(HALL_PIN, INPUT);         // set pin for hall interrupt  
  digitalWrite(HALL_PIN, HIGH);
  PCintPort::attachInterrupt(HALL_PIN, ISR_hall, FALLING);
  t.every(250, speedUpdate);
}//end setup


void loop()
{
  checkSerial();    // find if there is any data waiting for us
  collisionNear = collisionImminent();
  motorAlphaControl();
  t.update();
}// end loop

// here lies the ISR for the wheel. KISS
void ISR_hall()
{
  if(!inReverse) // do not update the counter if you are going backwards.
    revCount++;
  Serial.print("RevCount: ");
  Serial.println(revCount);
}
