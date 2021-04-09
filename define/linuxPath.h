#ifndef LINUXPATH_H
#define LINUXPATH_H

#include <QDebug>

#define localPath               "/usr/gode/"
#define UDiskPath               "/mnt/exUDISK/gcode"
#define UDiskfind               "/mnt/exUDISK/gcode"
#define serialNum               "ttyS2"
#define UpdateFile              "/mnt/exUDISK/updateFile/TestPack.JUP"
#define localWIFI               "/usr/share/3d_printer/wifi.txt"

void tWifi_event_callback(struct Manager *wmg,int event_lavel)
{
    qDebug()<<"tWifi_event_callback";
}


#endif // LINUXPATH_H
