#include <motorStuff>
#include <Timer.h>
#define leftThreshold    ((NEUTRAL_TURN- MIN_TURN)/2) + MIN_TURN
#define rightThreshold   ((MAX_TURN - NEUTRAL_TURN)/2) + NEUTRAL_TURN
#define leftOff          NEUTRAL_TURN - ((NEUTRAL_TURN- MIN_TURN)/4)
#define rightOff         NEUTRAL_TURN + ((MAX_TURN - NEUTRAL_TURN)/4)


boolean ledOn = false;
int tickEvent;
int signalOn;
int signalOver = 0;              // has wheel turned beyond min to turn turn signal off


// Set up the turn signals
void initSignals()
{
  pinMode(leftSignal, OUTPUT);
  pinMode(rightSignal, OUTPUT);
}


// Detect when our turn signal is activated
// NOTE: The signal may delay up to 500ms before turning on
void signalButtonPressed(int input)
{
  if(input == signalOn)
  {
    t.stop(tickEvent);
    signalOn = 0;
    input = 0;
  }
  else if(input == leftSignal)
  {
    if(signalOn == rightSignal)
    {
      t.stop(tickEvent);
    }
    
    signalOn = input;
    tickEvent = t.every(1000, ledState);
  }
  else if(input == rightSignal)
  {
    if(signalOn)
    {
      t.stop(tickEvent);
    }
    
    signalOn = input;
    tickEvent = t.every(1000,ledState);
  }
}


// oscillate the state of the turn signal
void ledState()
{
  if(signalOn == rightSignal || signalOn == leftSignal)
  {
    if(!ledOn)
    {
      t.pulse(signalOn, 500, LOW);
    }
  }
}


// Identify when the car has completed a turn 
// when the turn signal is activated,
// and turn it off
void wheelTurned(int steerPos)
{
  if((steerPos > rightThreshold) && (signalOn == rightSignal))
  {
    signalOver = rightSignal;
  }
  if((steerPos < leftThreshold) && (signalOn == leftSignal))
  {
    signalOver = leftSignal;
  }
  
  if(((steerPos < rightOff) && (signalOver == rightSignal)) || ((steerPos > leftOff) && (signalOver == leftSignal)))
  {
    if(signalOn != 0)
    {
      signalButtonPressed(signalOn);
      signalOver = 0;
    }
    else
    {
      signalOver = 0;
    }
  }
}
