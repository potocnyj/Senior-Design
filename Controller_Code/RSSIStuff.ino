#define RSSI_PIN 3
#define RSSI_TIMEOUT 200

void getRSSI()
{
  long RSSIVal = pulseIn(RSSI_PIN, LOW, RSSI_TIMEOUT);
  Serial.println(RSSIVal);
}
