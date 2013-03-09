#define HALL_PIN 5
#define WHEEL_CIRCUM 12.17367
#define ROT_TIMEOUT 5000        // if it takes more than 5 seconds to rotate the tire, then dont count it

long timerA = 0;
long timerB = 0;
boolean timerSelect = true;


/*
 * this is the ISR for the HAL effect sensor.  
 * It alternates between updataing 2 timers
 * that should be it to keep it quick
*/
void pulseDetected()
{
  if(timerSelect)
  {
    timerA = millis();
    timerSelect = false;
  }
  else
  {
    timerB = millis();
    timerSelect = true;
  }
}// end pulseDetected

float calcRPM()
{
  int time = (timerA - timerB);
  if (abs(time) <= ROT_TIMEOUT)
  {
    if(timerSelect) // timerA just updated
    {
      return (timerA - timerB) / 1000;
    }
    else            // timerB just updated
    {
      return (timerB - timerA) / 1000;
    }
  }
}// end calcRPM

float calcSpeed()
{
  int time = (timerA - timerB);
  if (abs(time) <= ROT_TIMEOUT)      // make sure it hasnt been stopped for quite a while
  {
    if(timerSelect)  // timerA just updated
    {
      return (timerA - timerB) * WHEEL_CIRCUM;
    }
    else            // timerB just updated
    {
      return (timerB - timerA) * WHEEL_CIRCUM;
    }
  }
}//end calcSpeed
