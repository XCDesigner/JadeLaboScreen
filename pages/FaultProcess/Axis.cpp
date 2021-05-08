#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CMOD/XhUpdater.h"
#include <QThread>

void MainWindow::MovementFaultDetected()
{
    uint8_t current_performance;

    current_performance = screen_status.getPerformance();
    if(current_performance == PLATFORM_CALIBRATING)
    {
        pdlg_warning->init(QByteArray("PlatformCalibrate"));
        platformCalibrateFail();
    }
    else if(current_performance == XY_CALIBRATING)
    {
        pdlg_warning->init(QByteArray("XYCalibrate"));
        xyCalibrateFail();
    }
    else if(current_performance == PRINTING)
    {
        pdlg_warning->init(QByteArray("Movement"));
    }
    pdlg_warning->show();
}

