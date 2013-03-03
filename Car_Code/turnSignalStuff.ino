#include <motorStuff>
#include <Timer.h>

int signalOn = 0;
boolean ledOn = false;
int tickEvent;

void signalButtonPressed(int input){
  Serial.println("loop ran");
  if(input == signalOn){
    Serial.println("setting signal to off");
    t.stop(tickEvent);
    signalOn = 0;
    input = 0;
  }
  else if(input == 13){
    Serial.println("turning left signal on");
    if(signalOn == 8){
      t.stop(tickEvent);
    }
    signalOn = input;
    tickEvent = t.every(1000, ledState);
  }
  else if(input == 8){
    Serial.println("turning right signal on");
    if(signalOn){
      t.stop(tickEvent);
    }
    signalOn = input;
    tickEvent = t.every(1000,ledState);
  }
}

void ledState(){
  if(signalOn == 8 || signalOn == 13){
    if(!ledOn){
      t.pulse(signalOn, 500, LOW);
    }
  }
}
