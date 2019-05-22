#ifndef DEV_GPS_H
#define DEV_GPS_H
void fncDev_Gps_setup() {
  g_device_GpsSerial.begin(9600, SERIAL_8N1, 16, 17);
}
#ifdef DEBUG
void fncDev_Gps_PrintSerial() {
  if (!g_dev_gpsIsConnected) {
    Serial.print (" GPS NOT DETECTED, Where are the pins?");
  }
  else
  {
    Serial.print("GPS g_dev_gps_iCountFill=");
    Serial.print(g_dev_gps_iCountFill);

    Serial.print(" g_DL_GpsSatellites=");
    Serial.print(g_DL_GpsSatellites);
    Serial.print(" g_DL_GpsLatiLong=");
    Serial.print(g_DL_GpsLatiLong);
    Serial.print(" g_DL_GpsDateTime=");
    Serial.print(g_DL_GpsDateTime);
    Serial.print(" g_DL_GpsAltitud=");
    Serial.print(g_DL_GpsAltitud);


    Serial.print(" IsConnected=");
    Serial.print(g_dev_gpsIsConnected);
    Serial.print(" IsReadLocation=");
    Serial.print(g_dev_gpsIsReadLocation);
    Serial.print(" IsReadDate=");
    Serial.print(g_dev_gpsIsReadDate);
    Serial.print(" IsReadTime=");
    Serial.print(g_dev_gpsIsReadTime);
    Serial.print(" IsReadAltitude=");

    Serial.println(g_dev_gpsIsReadAltitude);
    Serial.print(" g_dev_gpsIsReadAll=");
    Serial.println(g_dev_gpsIsReadAll);

  }


}
#endif DEBUG
void fncDev_Gps_FillFlds() {

  g_dev_gps_iCountFill++;

  unsigned int uiSat = g_device_Gps.satellites.value();
  if (uiSat > 3) {
    g_dev_gpsIsReadAltitude = true;
  }
  snprintf(g_DL_GpsSatellites, sizeof(g_DL_GpsSatellites) , "%zu", g_device_Gps.satellites.value());

  sprintf(g_DL_GpsAltitud, "%0.0f", g_device_Gps.altitude.meters());
  if (g_device_Gps.location.isValid()) {
    //sprintf(g_DL_GpsLatiLong, "%0.6f,%0.6f",  g_device_Gps.location.lat(), g_device_Gps.location.lng());
    snprintf(g_DL_GpsLatiLong, sizeof(g_DL_GpsLatiLong) , "%0.6f,%0.6f",  g_device_Gps.location.lat(), g_device_Gps.location.lng());
    g_dev_gpsIsReadLocation = true;
    strcpy (g_UrlMap, g_UrlMap_start);
    strcat(g_UrlMap, g_DL_GpsLatiLong);

  }


  if (g_device_Gps.time.isValid() && g_device_Gps.date.isValid() && g_device_Gps.date.year() > 2018)
  {

    //  sprintf(g_DL_GpsDateTime, "%04u/%02u/%02u %02u:%02u:%02u:%02u", g_device_Gps.date.year(), g_device_Gps.date.month(), g_device_Gps.date.day(),
    //          g_device_Gps.time.hour(), g_device_Gps.time.minute(), g_device_Gps.time.second(), g_device_Gps.time.second(), g_device_Gps.time.centisecond());

    snprintf(g_DL_GpsDateTime, sizeof(g_DL_GpsDateTime) , "%04u/%02u/%02u %02u:%02u:%02u:%02u", g_device_Gps.date.year(), g_device_Gps.date.month(), g_device_Gps.date.day(),
             g_device_Gps.time.hour(), g_device_Gps.time.minute(), g_device_Gps.time.second(), g_device_Gps.time.second(), g_device_Gps.time.centisecond());


    if (g_device_Gps.time.isValid()) {
      g_dev_gpsIsReadTime = true;
    }
    if (g_device_Gps.date.isValid()) {
      g_dev_gpsIsReadDate = true;
    }

  }



}
//-------------------------------------------

void fncDev_Gps_Read() {
  g_dev_gpsIsConnected = false;
  g_dev_gpsIsReadLocation = false;
  g_dev_gpsIsReadDate = false;
  g_dev_gpsIsReadTime = false;
  g_dev_gpsIsReadAltitude = false;
  g_dev_gpsIsReadAll = false;
  g_dev_gps_iCountFill  = 0;
  g_dev_gpsLookFor = true;
  g_dev_gpsTryCount = 0; // flag for end seach if not find data
  while ( g_dev_gpsLookFor)
  {
    g_dev_gpsTryCount++;
    //Serial.println(g_dev_gpsTryCount);
    while (g_device_GpsSerial.available() > 0)
    {
      if (g_device_Gps.encode(g_device_GpsSerial.read()))
      {
        g_dev_gpsIsConnected = true;
        fncDev_Gps_FillFlds();
       #ifdef DEBUG
        fncDev_Gps_PrintSerial();
        #endif
      }
    } // end while 2
    if (millis() > 5000 && g_device_Gps.charsProcessed() < 10)
    {
      g_dev_gpsIsConnected = false;
      #ifdef DEBUG
      Serial.println(F("No GPS detected: check wiring."));
      #endif
      while (true);
    }

    // if all data filled force exit
    if (g_dev_gpsIsReadAltitude && g_dev_gpsIsReadLocation && g_dev_gpsIsReadTime && g_dev_gpsIsReadDate && g_dev_gpsIsReadAltitude)
    {
      #ifdef DEBUG
      Serial.println ("GPS All data filled, stop search");
      #endif DEBUG
      g_dev_gpsLookFor = false; // if fill all data not continue search
      g_dev_gpsIsReadAll = true;
    }
    // if too many time for get data force exit
    if (GPS_READ_TRIES < g_dev_gpsTryCount)
    {
      #ifdef DEBUG
      Serial.println("Gps end for max tries");
      #endif
      g_dev_gpsLookFor = false;

    }
  } // end while 1
}
void fncDev_Gps_Loop_IsInterval() {
  unsigned long  IntervalAct = millis();
  unsigned long Dif = IntervalAct - g_dev_gpsIntervalBefore;
  if (g_dev_gpsIntervalBefore > IntervalAct)
  {
    g_dev_gpsIntervalBefore = 0;
  }
  if (IntervalAct - g_dev_gpsIntervalBefore >= g_dev_gpsIntervalRead)
  {
    g_dev_gpsIntervalBefore = IntervalAct;
    fncDev_Gps_Read();
  }
}
#endif
