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
    CMOD/jlprotocal.cpp \
    CMOD/jlserialport.cpp \
    CMOD/screenstatus.cpp \
    CMOD/xhEvent.cpp \
    CMOD/xhcontrolr818.cpp \
    CMOD/xhpage.cpp \
    CMOD/xhport.cpp \
    dialog/askpause.cpp \
    dialog/changefilamentdlg.cpp \
    dialog/choosefile.cpp \
    dialog/choosetemp.cpp \
    dialog/delete.cpp \
    dialog/dupandmirror.cpp \
    dialog/duponly.cpp \
    dialog/filamentfault.cpp \
    dialog/firststartdialog.cpp \
    dialog/jlwidget.cpp \
    dialog/parsetdlog.cpp \
    dialog/parsing.cpp \
    dialog/powerlost.cpp \
    dialog/printflament.cpp \
    dialog/printmodeselect.cpp \
    dialog/printsetdlog.cpp \
    dialog/selectmode.cpp \
    dialog/unnoknfile.cpp \
    dialog/updateprogrebar.cpp \
    dialog/warningdialog.cpp \
    dialog/xhwizard.cpp \
    listwidgetitem/mylistwidgetitem.cpp \
    listwidgetitem/mywifiitem.cpp \
        main.cpp \
        mainwindow.cpp \
    oldplan/filecheckthread.cpp \
    pages/About/About.cpp \
    pages/Application/Application.cpp \
    pages/Application/FaultProcess.cpp \
    pages/Calibration/NozzleCalibration.cpp \
    pages/Calibration/PlatformCalibration.cpp \
    pages/Calibration/XYCalibration.cpp \
    pages/ChangeFilament/ChangeFilament.cpp \
    pages/FaultProcess/Filament.cpp \
    pages/FaultProcess/PowerRecovery.cpp \
    pages/JodMove/JodMove.cpp \
    pages/Keyboard/KeyBoard.cpp \
    pages/LightSetting/LightSetting.cpp \
    pages/PauseDialog/PauseDialog.cpp \
    pages/PrintControl/FileList.cpp \
    pages/PrintControl/PreparePrint.cpp \
    pages/FilmentSensorSetting/FilamentSetting.cpp  \
    pages/PrintControl/Printting.cpp \
    pages/PrintSetting/PrintSetting.cpp \
    pages/StatusBar/StatusBar.cpp \
    pages/Update/UpdateProcess.cpp \
    portreceiver.cpp

HEADERS += \
    CMOD/XhGcodeFileParser.h \
    CMOD/XhUpdater.h \
    CMOD/jlprotocal.h \
    CMOD/jlserialport.h \
    CMOD/screenstatus.h \
    CMOD/xhEvent.h \
    CMOD/xhcontrolr818.h \
    CMOD/xhpage.h \
    CMOD/xhport.h \
    customTypes.h \
    define/imagePath.h \
    define/linuxPath.h \
    define/windowsPath.h \
    dialog/askpause.h \
    dialog/changefilamentdlg.h \
    dialog/choosefile.h \
    dialog/choosetemp.h \
    dialog/delete.h \
    dialog/dupandmirror.h \
    dialog/duponly.h \
    dialog/filamentfault.h \
    dialog/firststartdialog.h \
    dialog/jlwidget.h \
    dialog/parsetdlog.h \
    dialog/parsing.h \
    dialog/powerlost.h \
    dialog/printflament.h \
    dialog/printmodeselect.h \
    dialog/printsetdlog.h \
    dialog/selectmode.h \
    dialog/unnoknfile.h \
    dialog/updateprogrebar.h \
    dialog/warningdialog.h \
    dialog/xhwizard.h \
    listwidgetitem/mylistwidgetitem.h \
    listwidgetitem/mywifiitem.h \
        mainwindow.h \
    oldplan/filecheckthread.h \
    portreceiver.h


FORMS += \
    dialog/askpause.ui \
    dialog/changefilamentdlg.ui \
    dialog/choosefile.ui \
    dialog/choosetemp.ui \
    dialog/delete.ui \
    dialog/dupandmirror.ui \
    dialog/duponly.ui \
    dialog/filamentfault.ui \
    dialog/firststartdialog.ui \
    dialog/parsetdlog.ui \
    dialog/parsing.ui \
    dialog/powerlost.ui \
    dialog/printflament.ui \
    dialog/printmodeselect.ui \
    dialog/printsetdlog.ui \
    dialog/selectmode.ui \
    dialog/unnoknfile.ui \
    dialog/updateprogrebar.ui \
    dialog/warningdialog.ui \
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
