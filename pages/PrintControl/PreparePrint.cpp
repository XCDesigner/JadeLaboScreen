#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::StopPreHeatting() 
{
    qDebug()<<"Stop clicked";
    m_port->setHeattingUnit(0, 100);
    m_port->setHeattingUnit(1, 200);
    m_port->setHeattingUnit(3, 300);
}
