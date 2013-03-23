#define COMMAND 0xFE
#define CLEAR   0x01
#define LINE0   0x80
#define LINE1   0xC0

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
  currentDisplay++;
  moveDisplay();
}


void previousDisplay()
{
  currentDisplay--;
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
  
  //top line
  sLCD.print("SPEED: ");
  sLCD.print(speedInFTS);
  sLCD.print(" ft/s");
  
  //change line
  sLCD.write(COMMAND);
  sLCD.write(LINE1);

  //bottom line
  sLCD.print("ODO: ");
//  Serial.print("LCD STUFF: ");
//  Serial.println(currentODOFT);
  sLCD.print(currentODOFT);
  sLCD.print(" ft.");
}


void displaySpeedODOinScaled()
{
  clear_lcd();
  
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
  sLCD.print(" mi.");
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
    
//    //change line
//    sLCD.write(COMMAND);
//    sLCD.write(LINE1);
//  
//    //bottom line
//    sLCD.print("SPEED: ");
//    sLCD.print(speedInFTS);
//    sLCD.print(" ft/s");
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
    
//    //change line
//    sLCD.write(COMMAND);
//    sLCD.write(LINE1);
//  
//    //bottom line
//    sLCD.print("SPEED: ");
//    sLCD.print(speedInScaled);
//    sLCD.print(" MPH");
  }
  else
  {
    sLCD.print("OFF");
  }
}

void displayBatteryTime()
{
  clear_lcd();
  
  //top line
  sLCD.print("Bat. Remaining:");
  
  //change line
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  //bottom line
  if((batTimeLeft == 0) || (batTimeLeft == -1))
  {
      sLCD.print("Initializing");
  }
  else
  {
    sLCD.print("Time: ");
    sLCD.print(batTimeLeft);
    sLCD.print(" min.");
  }
}


void displayBatteryDist()
{
  if(scaled)
  {
    displayBatteryDistScaled();
  }
  else
  {
    displayBatteryDistFTS();
  }
}

void displayBatteryDistFTS()
{
  clear_lcd();
    
  //top line
  sLCD.print("Bat. Remaining:");
  
  //change line
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  //bottom line
  if((batDistFT == 0) || (batDistFT == -1))
  {
    sLCD.print("Initializing");
  }
  else
  {
    sLCD.print("Dist: ");
    sLCD.print(batDistFT);
    sLCD.print(" ft"); 
  }
}

void displayBatteryDistScaled()
{
  clear_lcd();
  
  //top line
  sLCD.print("Bat. Remaining:");
  
  //change line
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  //bottom line
  if((batDistFT == 0) || (batDistFT == -1))
  {
    sLCD.print("Initializing");
  }
  else
  {
    sLCD.print("Dist: ");
    sLCD.print(batDistScaled);
    sLCD.print(" mi."); 
  }
}


void displayRange()
{
  clear_lcd();
  
  //top line
  sLCD.print("Sig Range: ");
  if(rangePercent == -1)
  {
    sLCD.write(COMMAND);
    sLCD.write(LINE1);
    sLCD.print("Intializing");
  }
  else
  {
    sLCD.print(rangePercent);
    sLCD.print("%");
  }
}


void displayRangeWarning()
{
  clear_lcd();
  
  //top line
  sLCD.print("Range Alert!!");
  
  //change line
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("Sig Strength: ");
  sLCD.print(rangePercent);
} 
