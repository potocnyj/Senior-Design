/*
 Example sketch for the Xbox 360 USB library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or 
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <XBOXUSB.h>
USB Usb;
XBOXUSB Xbox(&Usb);

void setup() {
  Serial.begin(115200);

  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while(1); //halt
  }  
  Serial.print(F("\r\nXBOX USB Library Started"));
}
void loop() {
  Usb.Task();
  if(Xbox.Xbox360Connected) {
    Xbox.setRumbleOn(Xbox.getButton(L2),Xbox.getButton(R2));
    if(Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500 || Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500 || Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500 || Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
      if(Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500) {
        Serial.print(F("LeftHatX: ")); 
        Serial.print(Xbox.getAnalogHat(LeftHatX));
        Serial.print("\t");
      } 
      if(Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500) {
        Serial.print(F("LeftHatY: ")); 
        Serial.print(Xbox.getAnalogHat(LeftHatY));
        Serial.print("\t");
      } 
      if(Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500) {
        Serial.print(F("RightHatX: ")); 
        Serial.print(Xbox.getAnalogHat(RightHatX));
        Serial.print("\t");      
      } 
      if(Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
        Serial.print(F("RightHatY: ")); 
        Serial.print(Xbox.getAnalogHat(RightHatY));  
      }
      Serial.println("");
    }
  delay(1);
}
