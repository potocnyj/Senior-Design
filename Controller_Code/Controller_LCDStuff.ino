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
  if(currentDisplay >= 7)
  {
    currentDisplay = 1;
  }
  
  else if(currentDisplay <= 0)
  {
    currentDisplay = 6;
  }
  
  updateDisplay();
}


void updateDisplay()
{
      switch(currentDisplay)
  {
    case 1:
      displaySpeedODOinFeet();
      break;
    case 2:
      displaySpeedODOinScaled();
      break;
    case 3:
      displayCruiseData();
      break;
    case 4:
      displayBatteryTime();
      break;
    case 5:
      displayBatteryDist();
      break;
    case 6:
      displayRange();
      break;
    default:
      updateDisplay();
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
  clear_lcd();
  int speedInScaled = 123;
  
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
    sLCD.print(" ft/s");
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


void bootScreen()
{
  clear_lcd();
  sLCD.print("   E");
  delay(60);
  sLCD.print("d");
  delay(60);
  sLCD.print("i");
  delay(60);
  sLCD.print("s");
  delay(60);
  sLCD.print("o");
  delay(60);
  sLCD.print("n");
  
    
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("       M");
    delay(60);
  sLCD.print("o");
  delay(60);
  sLCD.print("t");
  delay(60);
  sLCD.print("o");
  delay(60);
  sLCD.print("r");
  delay(60);
  sLCD.print("s");
  
  slideAway();
}


void slideAway()
{
    delay(1000);
 /* 
  clear_lcd();
  sLCD.write(COMMAND);
  sLCD.write(LINE0);
  
  sLCD.print("    Edison");
  
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("      Motors");
  
  delay(60);
  clear_lcd();
  sLCD.write(COMMAND);
  sLCD.write(LINE0);
  
  sLCD.print("     Edison");
  
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("     Motors");
  
  delay(60);
  clear_lcd();
  sLCD.write(COMMAND);
  sLCD.write(LINE0);
  
  sLCD.print("      Edison");
  
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("    Motors");
  
  delay(60);
  clear_lcd();
  sLCD.write(COMMAND);
  sLCD.write(LINE0);
  
  sLCD.print("       Edison");
  
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("   Motors");
  
  delay(60);
  clear_lcd();
  sLCD.write(COMMAND);
  sLCD.write(LINE0);
  
  sLCD.print("        Edison");
  
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("  Motors");
  
  delay(60);
  clear_lcd();
  sLCD.write(COMMAND);
  sLCD.write(LINE0);
  
  sLCD.print("         Edison");
  
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print(" Motors");
  
  delay(60);
  clear_lcd();
  sLCD.write(COMMAND);
  sLCD.write(LINE0);
  
  sLCD.print("          Edison");
  
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("Motors");
  
  delay(60);
  clear_lcd();
  sLCD.write(COMMAND);
  sLCD.write(LINE0);
  
  sLCD.print("           Ediso");
  
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("otors");
  
  delay(60);
  clear_lcd();
  sLCD.write(COMMAND);
  sLCD.write(LINE0);
  
  sLCD.print("            Edis");
  
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("tors");
  
  delay(60);
  clear_lcd();
  sLCD.write(COMMAND);
  sLCD.write(LINE0);
  
  sLCD.print("             Edi");
  
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("ors");
  
  delay(60);
  clear_lcd();
  sLCD.write(COMMAND);
  sLCD.write(LINE0);
  
  sLCD.print("              Ed");
  
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("rs");
  
  delay(60);
  clear_lcd();
  sLCD.write(COMMAND);
  sLCD.write(LINE0);
  
  sLCD.print("               E");
  
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("s");
  
  */
  delay(60);
  clear_lcd();

  sLCD.print("       -1");
  
  delay(60);
  clear_lcd();

  sLCD.print("      C-17");
  
  delay(60);
  clear_lcd();

  sLCD.print("     CC-170");
  
  delay(60);
  clear_lcd();

  sLCD.print("    NCC-1701");
  
  delay(100);
  sLCD.write(COMMAND);
  sLCD.write(LINE1);
  
  sLCD.print("  L/R for data");
  
  currentDisplay = 0;
}  
  
