#define RSSI_PIN 3
#define RSSI_TIMEOUT 200

int RSSI1 = 1;
int RSSI2 = 1;
int RSSI3 = 1;
int RSSI4 = 1;
int RSSI5 = 1;
int rssiCount = 1;

int getRSSI()
{
  // use the map function to map the pin output from 100 to 0.  
  // has to be 100 to zero because bigger numbers are less signal  
  // pulseIn should use LOW, but high gives us non 0 values
  int pulseDur = pulseIn(RSSI_PIN, HIGH, RSSI_TIMEOUT);
  
  // by if it is to close, we get all 0s for some reason, 
  // NEED TO TRY: having it go from 100 to 0 at closer ranges -works on far ranges, not so much the close
  pulseDur = map(pulseDur, 0, RSSI_TIMEOUT, 100, 0);
  Serial.println(pulseDur);

  
    
 // Serial.println((RSSI1+RSSI2+RSSI3+RSSI4+RSSI5)/5);
  return rollingAvg(pulseDur);
}

int rollingAvg(int pulseDurIn)
{
  int avg=0;
  if(rssiCount == 1)
    RSSI1 = pulseDurIn;
  else if(rssiCount == 2)
    RSSI2 = pulseDurIn;
  else if(rssiCount == 3)
    RSSI3 = pulseDurIn;
  else if(rssiCount == 4)
    RSSI4 = pulseDurIn;
  else if(rssiCount == 5)
    RSSI5 = pulseDurIn;
  
  if(rssiCount == 5)
    rssiCount = 1;    
  else
    rssiCount++; 
  
  avg = ((RSSI1 + RSSI2 + RSSI3 + RSSI4 + RSSI5) / 5);
  
  return avg;
}//end rollingAvg
