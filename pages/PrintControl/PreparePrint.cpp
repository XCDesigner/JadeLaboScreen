#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::preparePrintPageInit()
{
    ui->qw_PreparePrintControl->rootObject()->setProperty("settingEnabled", true);
    ui->qw_PreparePrintControl->rootObject()->setProperty("stopEnabled", true);
    QTimer::singleShot(4000, this, SLOT(preparePrinTempChecking()));
    screen_status.setPerformance(PREPARE_PRINT);
}

void MainWindow::StopPreHeatting() 
{
    m_port->setHeattingUnit("0", "0");
    m_port->setHeattingUnit(2, 0);
    if(m_timer.isActive())
    {
        m_timer.stop();
        QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpSeventeen()));
    }
    screen_status.setPerformance(IDLE);
    changePageOnStatus(QByteArray::fromHex("00"), ui->page_GetStart);
}

void MainWindow::preparePrinTempChecking()
{
    strMachineStatus new_status;
    m_port->getXhPage()->GetMachineStatus(&new_status);
    if(screen_status.getPerformance() == PREPARE_PRINT)
    {
        qDebug()<<"Temp check";
        qDebug()<<new_status.CurTemp[0];
        qDebug()<<new_status.TarTemp[0];
        qDebug()<<new_status.CurTemp[1];
        qDebug()<<new_status.TarTemp[1];
        if((new_status.CurTemp[0] > (new_status.TarTemp[0] * 0.8)) && (new_status.CurTemp[1] > (new_status.TarTemp[1] * 0.8)))
        {
            ui->qw_PreparePrintControl->rootObject()->setProperty("settingEnabled", false);
            ui->qw_PreparePrintControl->rootObject()->setProperty("stopEnabled", false);
            screen_status.setPerformance(PRINTING);
        }
        else
        {
            QTimer::singleShot(200, this, SLOT(preparePrinTempChecking()));
        }
    }
}
