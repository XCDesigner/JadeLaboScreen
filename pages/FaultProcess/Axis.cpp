#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CMOD/XhUpdater.h"
#include <QThread>

void MainWindow::MovementFaultDetected()
{
    pdlg_warning->init(QByteArray("Movement"));
    pdlg_warning->show();
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
    screen_status.setPerformance(IDLE);
}

