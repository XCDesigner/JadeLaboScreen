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
QMAKE_CXXFLAGS += -g

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    CMOD/XhGcodeFileParser.cpp \
    CMOD/XhUpdater.cpp \
    CMOD/jlnetport.cpp \
    CMOD/jlprotocal.cpp \
    CMOD/jlserialport.cpp \
    CMOD/screenstatus.cpp \
    CMOD/tcpcontroler.cpp \
    CMOD/udplistener.cpp \
    CMOD/xhEvent.cpp \
    CMOD/xhcontrolr818.cpp \
    CMOD/xhpage.cpp \
    CMOD/xhport.cpp \
    customwidget/jlbutton.cpp \
    customwidget/jlcontrolbox.cpp \
    customwidget/jlextruderselect.cpp \
    customwidget/jlextruderunit.cpp \
    customwidget/jlheatedbedunit.cpp \
    customwidget/jlheatingunit.cpp \
    customwidget/jlheatingunit2.cpp \
    customwidget/jlnozzleturnindicator.cpp \
    customwidget/jlonoffswitch.cpp \
    customwidget/jlscrolllabel.cpp \
    customwidget/jlsliderbar.cpp \
    customwidget/jlturnindicator.cpp \
    dialog/askpause.cpp \
    dialog/changefilamentdlg.cpp \
    dialog/choosebedtemp.cpp \
    dialog/choosedistance.cpp \
    dialog/chooseextrudertemp.cpp \
    dialog/choosefile.cpp \
    dialog/choosetemp.cpp \
    dialog/delete.cpp \
    dialog/dupandmirror.cpp \
    dialog/duponly.cpp \
    dialog/filamentfault.cpp \
    dialog/firststartdialog.cpp \
    dialog/inputdialog.cpp \
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
    pages/ChangeHotend/ChangeHotend.cpp \
    pages/FaultProcess/Axis.cpp \
    pages/FaultProcess/Filament.cpp \
    pages/FaultProcess/PowerRecovery.cpp \
    pages/JodMove/JodMove.cpp \
    pages/Keyboard/KeyBoard.cpp \
    pages/MachineSetting/LightSetting/LightSetting.cpp \
    pages/MachineSetting/SelfTest/SelfTest.cpp \
    pages/ManualControl/ExtrudeControl.cpp \
    pages/ManualControl/TempControl.cpp \
    pages/PauseDialog/PauseDialog.cpp \
    pages/PrintControl/FileList.cpp \
    pages/PrintControl/PreparePrint.cpp \
    pages/FilmentSensorSetting/FilamentSetting.cpp  \
    pages/PrintControl/Printting.cpp \
    pages/PrintSetting/PrintSetting.cpp \
    pages/StatusBar/StatusBar.cpp \
    pages/Update/UpdateProcess.cpp \
    pages/Wifi/Wifi.cpp \
    portreceiver.cpp

HEADERS += \
    CMOD/XhGcodeFileParser.h \
    CMOD/XhUpdater.h \
    CMOD/jlnetport.h \
    CMOD/jlprotocal.h \
    CMOD/jlserialport.h \
    CMOD/screenstatus.h \
    CMOD/tcpcontroler.h \
    CMOD/udplistener.h \
    CMOD/xhEvent.h \
    CMOD/xhcontrolr818.h \
    CMOD/xhpage.h \
    CMOD/xhport.h \
    customTypes.h \
    customwidget/JLWidgets.h \
    customwidget/jlbutton.h \
    customwidget/jlcontrolbox.h \
    customwidget/jlextruderselect.h \
    customwidget/jlextruderunit.h \
    customwidget/jlheatedbedunit.h \
    customwidget/jlheatingunit.h \
    customwidget/jlheatingunit2.h \
    customwidget/jlnozzleturnindicator.h \
    customwidget/jlonoffswitch.h \
    customwidget/jlscrolllabel.h \
    customwidget/jlsliderbar.h \
    customwidget/jlturnindicator.h \
    define/imagePath.h \
    define/linuxPath.h \
    define/windowsPath.h \
    dialog/askpause.h \
    dialog/changefilamentdlg.h \
    dialog/choosebedtemp.h \
    dialog/choosedistance.h \
    dialog/chooseextrudertemp.h \
    dialog/choosefile.h \
    dialog/choosetemp.h \
    dialog/delete.h \
    dialog/dupandmirror.h \
    dialog/duponly.h \
    dialog/filamentfault.h \
    dialog/firststartdialog.h \
    dialog/inputdialog.h \
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
    customwidget/jlbutton.ui \
    customwidget/jlcontrolbox.ui \
    customwidget/jlextruderselect.ui \
    customwidget/jlextruderunit.ui \
    customwidget/jlheatedbedunit.ui \
    customwidget/jlheatingunit.ui \
    customwidget/jlheatingunit2.ui \
    customwidget/jlnozzleturnindicator.ui \
    customwidget/jlonoffswitch.ui \
    customwidget/jlscrolllabel.ui \
    customwidget/jlsliderbar.ui \
    customwidget/jlturnindicator.ui \
    dialog/askpause.ui \
    dialog/changefilamentdlg.ui \
    dialog/choosebedtemp.ui \
    dialog/choosedistance.ui \
    dialog/chooseextrudertemp.ui \
    dialog/choosefile.ui \
    dialog/choosetemp.ui \
    dialog/delete.ui \
    dialog/dupandmirror.ui \
    dialog/duponly.ui \
    dialog/filamentfault.ui \
    dialog/firststartdialog.ui \
    dialog/inputdialog.ui \
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
