#ifndef SCREENSTATUS_H
#define SCREENSTATUS_H
#include "stdint.h"
#include <QByteArray>

enum {
    IDLE = 0,
    PREPARE_PRINT,
    PREPARE_RECOVERY,
    PRINTING,
    CHANGE_FILAMENT,
    XY_CALIBRATING,
    PLATFORM_CALIBRATING,
    NOZZLE_CALIBRATING,
    MANUAL_EXTRUDE
};

typedef struct{
    QByteArray print_mode;
    bool Wifi;
    bool UDisk;
    bool Light;
    uint16_t CurrentTemp[3];
    uint16_t TargetTemp[3];
    uint32_t ZHeight;
    uint8_t tmp_print_mode;
    bool extruder_enabled[2];
    uint8_t performance;
}strScreenStatus;

class ScreenStatus
{
public:
    ScreenStatus();
    void getStatus(strScreenStatus *);
    void setStatus(strScreenStatus *);
    uint8_t getPerformance();
    void setPerformance(uint8_t);
    void setPrintMode(uint8_t);
    void setPrintMode(QByteArray &);
    QByteArray getPrintMode();
    void setWifiStatus(bool);
    void setUdiskStatus(bool);
    void setLightStatus(bool);
    void setTemp(int16_t*, int16_t*);
    bool getWifiStatus();
    bool getUdiskStatus();
    bool getLightStatus();
    void getTemp(int16_t*, int16_t*);
    bool isExtruderEnabled(uint8_t);
    void setExtruderEnabled(uint8_t, bool);
private:
    strScreenStatus status;
};

#endif // SCREENSTATUS_H
