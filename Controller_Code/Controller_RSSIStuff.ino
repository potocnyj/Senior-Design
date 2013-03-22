#define RSSI_PIN 3
#define RSSI_TIMEOUT 200

int getRSSI()
{
  // use the map function to map the pin output from 100 to 0.  
  // has to be 100 to zero because bigger numbers are less signal  
  // pulseIn should use LOW, but high gives us non 0 values
  int pulseDur = pulseIn(RSSI_PIN, HIGH, RSSI_TIMEOUT);
  
  // by if it is to close, we get all 0s for some reason, 
  // NEED TO TRY: having it go from 100 to 0 at closer ranges -works on far ranges, not so much the close
  pulseDur = map(pulseDur, 0, RSSI_TIMEOUT, 0, 100);
  
  return (pulseDur == 0) ? -1 : pulseDur;
}
