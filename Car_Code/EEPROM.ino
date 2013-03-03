// EEPROM Read/Write Functions
// Author: John Potocny
// This code is used for the reading/writing of the car's 
// internal odometer.

#include <EEPROM.h>

// Odometer starting address
#define ODOM_ADD_START  1
// Odometer value length
#define ODOM_ADD_END    4

unsigned long readOdom()
{
  byte value = 0;
  unsigned long odom = 0;
  for(int addr = ODOM_ADD_START; addr <= ODOM_ADD_END; addr++)
  {
    value = EEPROM.read(addr);

    odom = odom << 8;
    odom += value;    
  }
  
  return odom;
}


void writeOdom(unsigned long odom)
{
  byte value = 0;
  
  for(int addr = ODOM_ADD_END; addr >= ODOM_ADD_END; addr--)
  {
    value = odom;
    odom = odom >> 8;
    EEPROM.write(addr, value);
  }
}
