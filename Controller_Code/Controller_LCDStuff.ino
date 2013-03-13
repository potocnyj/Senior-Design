#define COMMAND 0xFE
#define CLEAR   0x01
#define LINE0   0x80
#define LINE1   0xC0

int currentDisplay = 0;
SoftwareSerial sLCD =  SoftwareSerial(3, 7/*  RX, TX */); /* Serial LCD is connected on digital I/O pin 7 */


void init_Display()
{
  sLCD.begin(9600);
  clear_lcd();
}


void clear_lcd(void)
{
  sLCD.write(COMMAND);
  sLCD.write(CLEAR);
}  


void moveDisplay()
{
  if(currentDisplay >= 6)
  {
    currentDisplay = 1;
  }
  else if(currentDisplay <= 0)
  {
    currentDisplay = 5;
  }
  
  updateDisplay();
}


void updateDisplay()
{
  switch(currentDisplay)
  {
    case 1:
      displaySpeedAODO();
      break;
    case 2:
      displayCruiseData();
      break;
    case 3:
      displayBatteryTime();
      break;
    case 4:
      displayBatteryDist();
      break;
    case 5:
      displayRange();
      break;
    default:
      break;
    }//end switch
}


void nextDisplay()
{
  Serial.println(++currentDisplay);
  moveDisplay();
}


void previousDisplay()
{
  Serial.println(--currentDisplay);
  moveDisplay();
}

void displaySpeedAODO()
{
  if(scaled)
  {
    displaySpeedODOinScaled();
  }
  else
  {
    displaySpeedODOinFeet();
  }
}

void displaySpeedODOinFeet()
{
  clear_lcd();
  int currentODOft = 1231;
  
  //top line
  sLCD.print("SPEED: ");
  sLCD.print(speedInFTS);
  sLCD.print(" ft/s");
  
  //change line
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  //bottom line
  sLCD.print("ODO: ");
  sLCD.print(currentODOft);
  sLCD.print(" ft.");
}


void displaySpeedODOinScaled()
{
  clear_lcd();
  
  int currentODOScaled = 10000;
  
  //top line
  sLCD.print("SPEED: ");
  sLCD.print(speedInScaled);
  sLCD.print(" MPH");
  
  //change line
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  //bottom line
  sLCD.print("ODO: ");
  sLCD.print(currentODOScaled);
  sLCD.print(" m");
}


void displayCruiseData()
{
  if(scaled)
  {
    displayCruiseDataScaled();
  }
  else
  {
    displayCruiseDataFTS();
  }
}

void displayCruiseDataFTS()
{
  clear_lcd();
  
  //top line
  sLCD.print("CRUISE: ");
  
  if(cruise)
  {
    sLCD.print("ON");
    
    //change line
    sLCD.write(COMMAND);
    sLCD.write(LINE1);
  
    //bottom line
    sLCD.print("SPEED: ");
    sLCD.print(speedInFTS);
    sLCD.print(" ft/s");
  }
  else
  {
    sLCD.print("OFF");
  }
}

void displayCruiseDataScaled()
{
  clear_lcd();
  
  //top line
  sLCD.print("CRUISE: ");
  
  if(cruise)
  {
    sLCD.print("ON");
    
    //change line
    sLCD.write(COMMAND);
    sLCD.write(LINE1);
  
    //bottom line
    sLCD.print("SPEED: ");
    sLCD.print(speedInScaled);
    sLCD.print(" MPH");
  }
  else
  {
    sLCD.print("OFF");
  }
}

void displayBatteryTime()
{
  clear_lcd();
  int batTimeAmount = 30;
  
  //top line
  sLCD.print("Bat. Remaining:");
  
  //change line
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  //bottom line
  sLCD.print("Time: ");
  sLCD.print(batTimeAmount);
  sLCD.print(" min.");
}


void displayBatteryDist()
{
  clear_lcd();
  int batTimeAmount = 1234;
  //top line
  sLCD.print("Bat. Remaining:");
  
  //change line
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  //bottom line
  sLCD.print("Dist: ");
  sLCD.print(batTimeAmount);
  sLCD.print(" m.");
}


void displayRange()
{
  clear_lcd();
  int rangePercent = 78;
  int rangeDistance = 200;
  //top line
  sLCD.print("Sig Range: ");
  sLCD.print(rangePercent);
  sLCD.print("%");
  
  //change line
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("Dist: ");
  sLCD.print(rangeDistance);
  sLCD.print(" ft.");
  
}


void displayRangeWarning()
{
  clear_lcd();
  int rangePercent = 78;
  int rangeDistance = 200;
  //top line
  sLCD.print("RANGE WARNING!");
  
  //change line
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("Dist: ");
  sLCD.print(rangeDistance);
  sLCD.print(" ft.");
} 
