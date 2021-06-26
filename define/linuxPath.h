#ifndef LINUXPATH_H
#define LINUXPATH_H

#include <QDebug>
#include <QString>

#define downloadPath            QString("/usr/share/download")
#define downloadUpdateFile      QString("/usr/share/download/Update.JUP")
#define downloadGcodeFile       QString("/usr/share/download/tmp.gcode")
#define downloadFile            QString("/usr/share/download/tmp.file")
#define localPath               QString("/usr/gcode")
#define UDiskPath               QString("/mnt/exUDISK/gcode")
#define UDiskfind               QString("/mnt/exUDISK/gcode")
#define serialNum               "ttyS2"
#define UpdateFile              "/usr/share/3d_printer/TestPack.JUP"
#define localWIFI               "/usr/share/3d_printer/wifi.txt"
#define UpdateSourceFile        "/mnt/exUDISK/updateFile/TestPack.JUP"

#define LogFile                 "/usr/share/3d_printer/Log.bin"

#define FileListRecordPath      QString("/usr/share/3d_printer")
#define FileListRecord          QString("/usr/share/3d_printer/fileList.txt")
#define FileListRecord_BAK      QString("/usr/share/3d_printer/fileList_bak.txt")

#define UPDATE_FILE_TMP         "/usr/share/3d_printer/tmp/J1Screen.tar"
//void tWifi_event_callback(struct Manager *wmg,int event_lavel)
//{
//    qDebug()<<"tWifi_event_callback";
//}

#define RECOVERY_INFO_PATH      "/usr/share/3d_printer"
#define RECOVERY_INFO           "/usr/share/3d_printer/recovery_info.txt"

#endif // LINUXPATH_H
