#ifndef _GLOBAL_H
#define _GLOBAL_H
HardwareSerial g_device_GpsSerial(1);  // gps  recive data by uart
TinyGPSPlus    g_device_gps;           // decode gps fields
#endif
