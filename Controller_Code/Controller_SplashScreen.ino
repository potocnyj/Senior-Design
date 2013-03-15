
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
  
      delay(1000);

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
