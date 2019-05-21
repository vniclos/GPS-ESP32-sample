#ifndef _DEFINES_H
#define _DEFINES_H

#define PIN_RX_GPS        16
#define PIN_TX_GPS        17
#define GPS_BAUDS 9600
#define GPS_PARITY=SERIAL_8N1

//----------------------------------------------
// tool Macro for get only firmaware file name
#define FILENAME ({ \
    const char* filename_start = __FILE__; \
    const char* filename = filename_start; \
    while(*filename != '\0') \
      filename++; \
    while((filename != filename_start) && (*(filename - 1) != '\\')) \
      filename--; \
    filename; })
#endif
