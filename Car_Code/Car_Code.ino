#include <stdlib.h>
#include <Servo.h>
#include <PWM.h>
#include <Timer.h>
#include <PinChangeInt.h>

#define MOTOR_DATA_START  1
#define MOTOR_DATA_END    6
#define STEER_DATA_START  7
#define STEER_DATA_END    12
#define DRIVE_HIGH        32767
#define DRIVE_LOW         -32768
#define SPEED_UPDATE_TIME  500   // time in mS to update the speed
#define PACKET_LEN    12
#define HALL_PIN      7
#define BAUD_RATE     9600
#define MOTOR_MAX_A  1800        // Should work to 2000, but scary on a table was 1700
#define MOTOR_MIN_A  1200        // should work to 1000, but scary on a table was 1300
#define MOTOR_MAX_B  1600        // grandma mode
#define MOTOR_MIN_B  1400        // grandma mode
#define MOTOR_NEU    1500

const int leftSignal = 13;
const int rightSignal = 8;

Timer t;
int lastSpeed;
int revCount = 1;
int MOTOR_MAX = MOTOR_MAX_B;
int MOTOR_MIN = MOTOR_MIN_B;
volatile int revCounter = 0;     // used to count # of forward revolutions of wheel
boolean inReverse = false;       // used to ensure revCount only gets updated when going forward
boolean grandmaMode = false;
boolean usedBreaks = false;      // if breaks are used for collison avoidance, dont use till reset

// battery
int digitalBatteryPin = 2;
unsigned long totalDistance = 0;

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
  
  // DELETE THIS< THIS IS FOR DEBUG PURPOSES
  
  writeOdom(0);
  Serial.println(readOdom());
  // DO NOT RELEASE 
  
  
  
  // interrupt stuff, VERIFIY BEFORE MODIFYING 
  pinMode(HALL_PIN, INPUT);         // set pin for hall interrupt 
  pinMode(digitalBatteryPin, OUTPUT); 
  digitalWrite(HALL_PIN, HIGH);
  PCintPort::attachInterrupt(HALL_PIN, ISR_hall, FALLING);
  t.every(SPEED_UPDATE_TIME, speedUpdate);
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
