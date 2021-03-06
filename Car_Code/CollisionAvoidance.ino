// Collision avoidance sensor function
// Author: John Potocny
// This code is used for reading the IR distance sensor
// positioned at the front of the car, and determining
// whether a collision is imminent

// The distance sensor for 
// the car's collision avoidance system is pin A0
#define DIST_SENSE_PIN  A0
#define MIN_DIST_CM     75

// We need to stop our car the first time 
// a collision is detected as imminent
boolean firstCollisionDetected = false;

// Check our sensor, determine if an object is near.
int checkDistance() 
{
  // put your main code here, to run repeatedly: 
  int distance = analogRead(DIST_SENSE_PIN);  
  distance = map(distance, 0, 666, 150, 0);
  
  return distance;
}


// Check for close object, kill engine if detected.
boolean collisionImminent()
{
  int nearestObject = checkDistance();
  
  // Is the nearest object < 100cm away?
  if (nearestObject < MIN_DIST_CM)
  {
    if((!firstCollisionDetected) && (lastSpeed > MOTOR_NEU))
    {
      brakeEngine();

      firstCollisionDetected = true;
    }
  }
  else
  {
    firstCollisionDetected = false;
  }
  
  return firstCollisionDetected;
} 
