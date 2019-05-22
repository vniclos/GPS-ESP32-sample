#include <TinyGPS++.h>
#include  <HardwareSerial.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include "_defines.h"    // global defines
#include "_global.h"     // global variables and objects 
#include "dev_gps.h"     // manager functions for gps
#include "dev_wifi.h"     // manager functions for gps
#include "srv_web.h"     // manager functions for gps
void setup() { 
  #ifdef DEBUG
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
  #endif
  fncDev_Gps_setup();
  fncDev_Wifi_setup();
  fncDev_Gps_Read();
  fncSrv_Web_setup();
   
}
void loop() {
  fncDev_Gps_Loop_IsInterval();
  g_websrv.handleClient();
 
  }
