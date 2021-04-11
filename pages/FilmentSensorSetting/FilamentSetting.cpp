#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_702_clicked()
{
    QQuickItem *pSwitch = ui->qw_FilSensor->rootObject();
    m_port->setFilamentSensorEnableStatus(pSwitch->property("enable").toBool());
    ui->stackedWidget->setCurrentWidget(ui->page_72);
}
