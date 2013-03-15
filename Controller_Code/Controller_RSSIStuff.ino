#define RSSI_PIN 3
#define RSSI_TIMEOUT 200

long getRSSI()
{
  return pulseIn(RSSI_PIN, LOW, RSSI_TIMEOUT);
  
}
