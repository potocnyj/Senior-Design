#include <stdlib.h>
#include <Servo.h>
#include <PWM.h>
#include <Timer.h>
#include <PinChangeInt.h>

#define MOTOR_DATA_START  1
#define MOTOR_DATA_END    6
#define STEER_DATA_START  7
#define STEER_DATA_END    12
#define DRIVE_HIGH        32768
#define DRIVE_LOW         -32768
#define SPEED_UPDATE_TIME  250   // time in mS to update the speed
#define PACKET_LEN    12
#define HALL_PIN      7
#define BAUD_RATE     9600
#define MOTOR_MAX    1700        // Should work to 2000, but scary on a table
#define MOTOR_MIN    1300        // should work to 1000, but scary on a table
#define MOTOR_NEU    1500

const int leftSignal = 13;
const int rightSignal = 8;

Timer t;
int lastSpeed;
int revCount = 1;
volatile int revCounter = 0;     // used to count # of forward revolutions of wheel
boolean inReverse = false;       // used to ensure revCount only gets updated when going forward

// Collision Avoidance
boolean collisionNear = false;

// Cruise Control Vars
boolean  cruiseControl = false;
int      savedSpeed = -1;

void setup()
{
  motorSetup();                     // initalize motor
  steerSetup();                     // initalize steer
  Serial.begin(BAUD_RATE);          // start serial
  initSignals();
  
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
}
