#include <XBOXUSB.h>

USB Usb;
XBOXUSB Xbox(&Usb);
int neutral = 1;


void setup() {
  Serial.begin(9600);

  if (Usb.Init() == -1)
  {
    while(1); //halt
  }  
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
  
  delay(10);
  
  getRSSI();  
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

    String data = "**d" + yval + xval;
    if(data.length() == 15)
    {
      delay(1);
      Serial.println(data);
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
    Serial.println("**c20000000001");
  }
  
  if(Xbox.getButton(LEFT)) {
    //will scroll in lcd screen
  }
  
  if(Xbox.getButton(RIGHT)) {
    //will scroll on lcd screen
  }

  if(Xbox.getButton(START)) {
    //no idea what this will do yet
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
}

