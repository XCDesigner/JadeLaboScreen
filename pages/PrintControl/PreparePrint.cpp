#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::StopPreHeatting() 
{
    m_port->setHeattingUnit("0", "0");
    m_port->setHeattingUnit(2, 0);
    if(m_timer.isActive())
    {
        m_timer.stop();
        QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpSeventeen()));
    }
    changePageOnStatus(QByteArray::fromHex("00"), ui->page_GetStart);
}
