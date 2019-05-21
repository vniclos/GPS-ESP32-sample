#ifndef DEV_GPS.H
#define DEV_GPS.H
void dev_gps_setup()
{
  g_device_GpsSerial.begin(9600, SERIAL_8N1, 16, 17);
}

void dev_gps_ToSerial() {
  Serial.print(F("Location: "));
  if (g_device_gps.location.isValid())
  {
    Serial.print(g_device_gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(g_device_gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (g_device_gps.date.isValid())
  {
    Serial.print(g_device_gps.date.month());
    Serial.print(F("/"));
    Serial.print(g_device_gps.date.day());
    Serial.print(F("/"));
    Serial.print(g_device_gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (g_device_gps.time.isValid())
  {
    if (g_device_gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(g_device_gps.time.hour());
    Serial.print(F(":"));
    if (g_device_gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(g_device_gps.time.minute());
    Serial.print(F(":"));
    if (g_device_gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(g_device_gps.time.second());
    Serial.print(F("."));
    if (g_device_gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(g_device_gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

 Serial.print(F(" Satellites: "));
  Serial.print (g_device_gps.satellites.value());
Serial.print(F(" Altitude: "));
  Serial.print (g_device_gps.altitude.meters());


  Serial.println();
}

void dev_gps_read(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (g_device_GpsSerial.available() > 0)
    if (g_device_gps.encode(g_device_GpsSerial.read()))
      dev_gps_ToSerial();

  if (millis() > 5000 && g_device_gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true);
  }
}
#endif
