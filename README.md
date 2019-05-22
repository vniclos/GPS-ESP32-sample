# ESP32 DEVKIT V1 GPS NEO 6M

![alt text](https://github.com/vniclos/GPS-ESP32-sample/blob/master/img/hardware.jpg "ESP32 GPS NEO 6M V2" )
?raw=true
## Hardware

- 1 ESP32 DEVKIT V1
- 1 NEO GPS 6M
- 1 Power suply 5v 2a

## Software
- Arduino IDE
- Libraries
- HardwareSerial.h ( better results than "sofwareserial.h"
- TinyGPSPlus available on
https://github.com/mikalhart/TinyGPSPlus




### You can get 
GPS latitud
GPS longitud
GPS date time (Is not rtc time)
GPS Altitud

On Serial monintor you get this exit
```
Location: 40.413200,-3.724031  Date/Time: 5/21/2019 15:09:44.00 Satellites: 7 Altitude: 673.90
Location: 40.413200,-3.724031  Date/Time: 5/21/2019 15:09:44.00 Satellites: 7 Altitude: 673.90
Location: 40.413200,-3.724031  Date/Time: 5/21/2019 15:09:44.00 Satellites: 7 Altitude: 673.90
Location: 40.413200,-3.724031  Date/Time: 5/21/2019 15:09:44.00 Satellites: 7 Altitude: 673.90
Location: 40.413200,-3.724031  Date/Time: 5/21/2019 15:09:44.00 Satellites: 7 Altitude: 673.90
Location: 40.413200,-3.724031  Date/Time: 5/21/2019 15:09:44.00 Satellites: 7 Altitude: 673.90
...
```

Or in web site example version you can get 
![alt text](https://github.com/vniclos/GPS-ESP32-sample/blob/master/img/web.jpg?raw=true "ESP32 GPS NEO 6M V2 web" )

There are two samples.
- First only **serial output**,  and you dont need to do changes,
- Second has **serial and web output** and you need edit _global.h for configure your wifi access point and ip preferences

``` c++
#ifndef _GLOBAL_H
#define _GLOBAL_H

const char* g_wifi_siid = "HERE YOU WIFI ACCESPOINT NAME";
const char* g_wifi_pwd  = "HERE YOUR WIFI PASSWORD ";
const char* g_wifi_host  = "my-gps";

IPAddress g_wifi_ip(192, 168, 1, 200);
IPAddress g_wifi_gateway(192, 168, 1, 1);
IPAddress g_wifi_subnet(255, 255, 255, 0);
IPAddress g_wifi_primaryDNS(8, 8, 8, 8); //optional
IPAddress g_wifi_secondaryDNS(8, 8, 4, 4); //optional
```

Contac with me on facebook 
https://www.facebook.com/vicente.niclos
