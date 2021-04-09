#-------------------------------------------------
#
# Project created by QtCreator 2020-10-19T14:45:22
#
#-------------------------------------------------

QT       += core gui network
QT       += quickwidgets
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-3dprint
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS XH_WIN XH_VIS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    CMOD/XhGcodeFileParser.cpp \
    CMOD/XhUpdater.cpp \
    CMOD/xhcontrolr818.cpp \
    CMOD/xhpage.cpp \
    CMOD/xhport.cpp \
    dialog/askpause.cpp \
    dialog/choosefile.cpp \
    dialog/choosetemp.cpp \
    dialog/delete.cpp \
    dialog/dupandmirorr.cpp \
    dialog/duponly.cpp \
    dialog/filamentfault.cpp \
    dialog/parsetdlog.cpp \
    dialog/parsing.cpp \
    dialog/powerlost.cpp \
    dialog/printflament.cpp \
    dialog/printsetdlog.cpp \
    dialog/selectmode.cpp \
    dialog/unnoknfile.cpp \
    dialog/updateprogrebar.cpp \
    dialog/xhrest.cpp \
    dialog/xhsensor.cpp \
    dialog/xhwizard.cpp \
    listwidgetitem/mylistwidgetitem.cpp \
    listwidgetitem/mywifiitem.cpp \
        main.cpp \
        mainwindow.cpp \
    oldplan/filecheckthread.cpp

HEADERS += \
    CMOD/XhGcodeFileParser.h \
    CMOD/XhUpdater.h \
    CMOD/xhcontrolr818.h \
    CMOD/xhpage.h \
    CMOD/xhport.h \
    define/imagePath.h \
    define/linuxPath.h \
    define/windowsPath.h \
    dialog/askpause.h \
    dialog/choosefile.h \
    dialog/choosetemp.h \
    dialog/delete.h \
    dialog/dupandmirorr.h \
    dialog/duponly.h \
    dialog/filamentfault.h \
    dialog/parsetdlog.h \
    dialog/parsing.h \
    dialog/powerlost.h \
    dialog/printflament.h \
    dialog/printsetdlog.h \
    dialog/selectmode.h \
    dialog/unnoknfile.h \
    dialog/updateprogrebar.h \
    dialog/xhrest.h \
    dialog/xhsensor.h \
    dialog/xhwizard.h \
    listwidgetitem/mylistwidgetitem.h \
    listwidgetitem/mywifiitem.h \
        mainwindow.h \
    oldplan/filecheckthread.h


FORMS += \
    dialog/askpause.ui \
    dialog/choosefile.ui \
    dialog/choosetemp.ui \
    dialog/delete.ui \
    dialog/dupandmirorr.ui \
    dialog/duponly.ui \
    dialog/filamentfault.ui \
    dialog/parsetdlog.ui \
    dialog/parsing.ui \
    dialog/powerlost.ui \
    dialog/printflament.ui \
    dialog/printsetdlog.ui \
    dialog/selectmode.ui \
    dialog/unnoknfile.ui \
    dialog/updateprogrebar.ui \
    dialog/xhrest.ui \
    dialog/xhsensor.ui \
    dialog/xhwizard.ui \
    listwidgetitem/mylistwidgetitem.ui \
    listwidgetitem/mywifiitem.ui \
        mainwindow.ui \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    IconResource.qrc
