#include "screenstatus.h"

ScreenStatus::ScreenStatus()
{

}

void ScreenStatus::getStatus(strScreenStatus *Status)
{
    *Status = status;
}

void ScreenStatus::setStatus(strScreenStatus *NewStatus)
{
    status = *NewStatus;
}

uint8_t ScreenStatus::getPerformance()
{
    return status.performance;
}

void ScreenStatus::setPerformance(uint8_t NewPerformance)
{
    status.performance = NewPerformance;
}

void ScreenStatus::setPrintMode(uint8_t Mode)
{
    status.print_mode = Mode;
}

uint8_t ScreenStatus::getPrintMode()
{
    return status.print_mode;
}

void ScreenStatus::setWifiStatus(bool NewStatus)
{
    status.Wifi = NewStatus;
}

void ScreenStatus::setUdiskStatus(bool NewStatus)
{
    status.UDisk = NewStatus;
}

void ScreenStatus::setLightStatus(bool NewStatus)
{
    status.Light = NewStatus;
}

void ScreenStatus::setTemp(int16_t *CurrentTemp, int16_t *TargetTemp)
{
    status.CurrentTemp[0] = CurrentTemp[0];
    status.CurrentTemp[1] = CurrentTemp[1];
    status.CurrentTemp[2] = CurrentTemp[2];

    status.TargetTemp[0] = TargetTemp[0];
    status.TargetTemp[1] = TargetTemp[1];
    status.TargetTemp[2] = TargetTemp[2];
}

bool ScreenStatus::getWifiStatus()
{
    return status.Wifi;
}

bool ScreenStatus::getUdiskStatus()
{
    return status.UDisk;
}

bool ScreenStatus::getLightStatus()
{
    return status.Light;
}

void ScreenStatus::getTemp(int16_t *CurrentTemp, int16_t *TargetTemp)
{
    CurrentTemp[0] = status.CurrentTemp[0];
    CurrentTemp[1] = status.CurrentTemp[1];
    CurrentTemp[2] = status.CurrentTemp[2];
    TargetTemp[0] = status.TargetTemp[0];
    TargetTemp[1] = status.TargetTemp[1];
    TargetTemp[2] = status.TargetTemp[2];
}

bool ScreenStatus::isExtruderEnabled(uint8_t Index)
{
    return status.extruder_enabled[Index];
}

void ScreenStatus::setExtruderEnabled(uint8_t Index, bool NewStatus)
{
    status.extruder_enabled[Index] = NewStatus;
}
