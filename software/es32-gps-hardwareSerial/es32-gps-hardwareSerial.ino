#include <TinyGPS++.h>
#include  <HardwareSerial.h>

#include "_defines.h"    // global defines
#include "_global.h"     // global variables and objects 
#include "dev_gps.h"     // manager functions for gps
void setup()
{
  Serial.begin(115200);
  Serial.println("=====================================");
  Serial.print(FILENAME);
  Serial.print(" compiled: ");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.println(__TIME__);
  Serial.println("Hardware: ESP32, Neo 6m gps conected by serial");
  Serial.println("pins on ESP32 rx=16, tx=18");
  Serial.println("Libraries TinyGPS++.h and HardwareSerial.h");
  Serial.println("by Vicente Niclos 2019");
  Serial.println("=====================================");
  //g_device_GpsSerial.begin(GPS_BAUDS, GPS_PARITY, PIN_RX_GPS, PIN_TX_GPS);
  dev_gps_setup();
  }

void loop()
{
 dev_gps_read();
}
