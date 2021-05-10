#ifndef WINDOWSPATH_H
#define WINDOWSPATH_H

#include <QDir>

#define downloadUpdateFile      QDir::currentPath()+"/download/Update.JUP"
#define downloadGcodeFile       QDir::currentPath()+"/download/tmp.gcode"
#define downloadFile            QDir::currentPath()+"/download/tmp.file"
#define UDiskPath               QDir::currentPath()+"/UD"
#define UDiskfind               QDir::currentPath()+"/dev"
#define localPath               QDir::currentPath()+"/3D/"
#define UpdateFile              QDir::currentPath()+"/updatefiles/local_update.JUP"
#define UpdateSourceFile        QDir::currentPath()+"/UD/TestPack.JUP"

#define UPDATE_FILE_TMP         QDir::currentPath() + "/Update/J1Screen.tar"

#define RECOVERY_INFO           QDir::currentPath() + "/RE/Recovery.txt"

#endif // WINDOWSPATH_H
