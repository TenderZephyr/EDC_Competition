#ifndef	__WIFI_CONTROL_H
#define	__WIFI_CONTROL_H

#include "stdio.h"

void  uinit ();
void  ESP8266_ModeInit (void);
void  wifi_control_init (void);
void  send_b (unsigned char dat);
void  send_s(unsigned char* dat);
void  wifi_control_init (void);
void  senddatatemp (float temp);
void  senddatahumi (int humi);
void  senddatasmoke (int smoke);
void  senddatabeam (int beam);
void senddatas (float temp, int humi, int smoke, int lx);

#endif