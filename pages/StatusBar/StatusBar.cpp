#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setUSBpic(bool isVisible)
{
    ui->qw_StatusNotice->rootObject()->setProperty("udiskVisible", isVisible);
}

void MainWindow::setLightPic(bool isVisible)
{
    ui->qw_StatusNotice->rootObject()->setProperty("lightVisible", isVisible);
}

void MainWindow::setWinPic(bool isVisible)
{
    ui->qw_StatusNotice->rootObject()->setProperty("wifiVisible", isVisible);
}

void MainWindow::on_qw_StatusNotice_Light_clicked()
{
    QQuickItem *item;
    item = ui->qw_StatusNotice->rootObject();
    if(item->property("lightChecked").toBool() == true)
        m_port->setLightOnOff(true);
    else
        m_port->setLightOnOff(false);
}
