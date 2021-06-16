#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_702_clicked()
{
    JLOnOffSwitch *pitem = (JLOnOffSwitch*)ui->label_6;
    m_port->setFilamentSensorEnableStatus(pitem->getEnableStatus());
    ui->stackedWidget->setCurrentWidget(ui->page_MachineSetting);
}
