#include <XBOXUSB.h>
#include <SoftwareSerial.h>

#define PACKET_LEN    12

USB Usb;
XBOXUSB Xbox(&Usb);
char dataIn[] = {'0','0','0','0','0','0','0','0','0','0','0','0','0'};
char dataOut[] = {'0','0','0','0','0','0','0','0','0','0','0','0','0'};
int neutral = 1;
int carSpeed = 0;
int odom = 0;
boolean cruise = false;


void setup() {
  Serial.begin(9600);
  init_Display();
  
  if (Usb.Init() == -1)
  {
    while(1); //halt
  }  
  
  bootScreen();
}


void loop() 
{
  Usb.Task();
  if(Xbox.Xbox360Connected) 
  {
    pollJoySticks();

    if(Xbox.buttonPressed) 
    {
      pollButtons();
    } 
  }
  
  checkSerial();
  //getRSSI();
  
  delay(10);
}// end loop


void pollJoySticks()
{
  int x;
  int y;
  String xval = "000000";
  String yval = "000000";

  if(Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500 || Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500) 
  {
    neutral = 0;
    if(Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500) 
    {
      y = Xbox.getAnalogHat(LeftHatY);
      yval = (String) y;
      while(yval.length() < 6)
      {
        yval = "0" + yval;
      }
    }

    if(Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500) 
    { 
      x = Xbox.getAnalogHat(RightHatX);
      xval = (String) x;
      while(xval.length() < 6)
      {
        xval = "0" + xval;
      }   
    } 

    String dataOut = "**d" + yval + xval;
    if(dataOut.length() == 15)
    {
      delay(1);
      Serial.println(dataOut);
    }
  }
  else
  {
    if(neutral == 0)
    {
      Serial.println("**d000000000000");
      neutral = 1;
    }
  }
}

void pollButtons()
{
  if(Xbox.getButton(UP)) {
    //increment cruise control
    Serial.println("**c100000000001");
  }      
  
  if(Xbox.getButton(DOWN)) {
    //decrement cruise control
    Serial.println("**c200000000001");
  }
  
  if(Xbox.getButton(LEFT)) {
    previousDisplay();
  }
  
  if(Xbox.getButton(RIGHT)) {
    nextDisplay();
  }

  if(Xbox.getButton(START)) {
    //nothing yet
  }
  
  if(Xbox.getButton(BACK)) {
    //potentially do not use, not very responsive but might have been led issues
  }

  if(Xbox.getButton(L1)){
    Serial.println("**c000000000000");
    //will set cruise control
  }
  
  if(Xbox.getButton(A)){
    Serial.println("**a000000000000");
  }
  
  if(Xbox.getButton(B)){
    Serial.println("**b000000000000");
  }
  
  if(Xbox.getButton(X)){
    Serial.println("**x000000000000");
  }
  
  if(Xbox.getButton(Y)){
    Serial.println("**y000000000000");
  }
  
  if(Xbox.getButton(L2) == 255) {
    Serial.println("**l000000000000");
  }
  if(Xbox.getButton(R2) == 255) {
    Serial.println("**r000000000000");
  } 
  
  updateDisplay();
}

void toggleCruise(char cruiseDataalskd)
{
  // 1 signals cruise is on, 0 s off
  if(cruiseDataalskd == '1')
  {
    cruise = true;
  }
  else if (cruiseDataalskd == '0')
  {
    cruise = false; 
  }
  
  updateDisplay();
}


