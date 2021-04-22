#ifndef SCREENSTATUS_H
#define SCREENSTATUS_H
#include "stdint.h"

typedef struct{
    bool Wifi;
    bool UDisk;
    bool Light;
    uint16_t CurrentTemp[3];
    uint16_t TargetTemp[3];
    uint32_t ZHeight;
    uint8_t print_mode;
    bool extruder_enabled[2];
}strScreenStatus;

class ScreenStatus
{
public:
    ScreenStatus();
    void getStatus(strScreenStatus *);
    void setStatus(strScreenStatus *);
    void setPrintMode(uint8_t);
    void setWifiStatus(bool);
    void setUdiskStatus(bool);
    void setLightStatus(bool);
    void setTemp(int16_t*, int16_t*);
    bool getWifiStatus();
    bool getUdiskStatus();
    bool getLightStatus();
    void getTemp(int16_t*, int16_t*);
    uint8_t getPrintMode();
    bool isExtruderEnabled(uint8_t);
    void setExtruderEnabled(uint8_t, bool);
private:
    strScreenStatus status;
};

#endif // SCREENSTATUS_H
