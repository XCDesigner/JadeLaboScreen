#ifndef LINUXPATH_H
#define LINUXPATH_H

#include <QDebug>
#include <QString>

#define downloadPath            QString("/usr/share/download")
#define downloadUpdateFile      QString("/usr/share/download/Update.JUP")
#define downloadGcodeFile       QString("/usr/share/download/tmp.gcode")
#define downloadFile            QString("/usr/share/download/tmp.file")
#define localPath               QString("/usr/gode/")
#define UDiskPath               QString("/mnt/exUDISK/gcode")
#define UDiskfind               QString("/mnt/exUDISK/gcode")
#define serialNum               "ttyS2"
#define UpdateFile              "/usr/share/3d_printer/TestPack.JUP"
#define localWIFI               "/usr/share/3d_printer/wifi.txt"
#define UpdateSourceFile        "/usr/share/3d_printer/log.bin"

#define LogFile                 QDir::currentPath()+"/UD/Log.bin"

#define UPDATE_FILE_TMP         "/usr/share/3d_printer/tmp/J1Screen.tar"
//void tWifi_event_callback(struct Manager *wmg,int event_lavel)
//{
//    qDebug()<<"tWifi_event_callback";
//}

#define RECOVERY_INFO           "/usr/share/3d_printer/recovery_info.txt"

#endif // LINUXPATH_H
