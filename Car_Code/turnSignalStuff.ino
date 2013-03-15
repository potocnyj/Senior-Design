#include <motorStuff>
#include <Timer.h>

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
  else if(input == 13)
  {
    if(signalOn == 8)
    {
      t.stop(tickEvent);
    }
    
    signalOn = input;
    tickEvent = t.every(1000, ledState);
  }
  else if(input == 8)
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
  if(signalOn == 8 || signalOn == 13)
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
  if((steerPos > 1750) && (signalOn != 0))
  {
    signalOver = 1;
  }
  if((steerPos < 1250) && (signalOn != 0))
  {
    signalOver = 2;
  }
  if(((steerPos < 1600) && (signalOver == 1)) || ((steerPos > 1400) && (signalOver == 2)))
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
