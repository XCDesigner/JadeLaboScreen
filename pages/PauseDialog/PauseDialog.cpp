#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::onPauseDialogHide()
{
    qDebug()<<"Pause dialog hide";
    QList<QByteArray> ret = skpWin->get_return_value();
    qDebug()<<ret[0];
    if(ret[0] == "Stop")
        printStop();
    else if(ret[0] == "Pause")
        printPause();
    else if(ret[0] == "Continue")
        printContinue();
    else if(ret[0] == "ChangeFilament")
        printChangeFilament();
    else if(ret[0] == "Cancel")
        ;
}

void MainWindow::printStop()
{
    m_port->stopPrint();
    m_printsec->stop();
    m_time->setHMS(0,0,0);
    changePageOnStatus(QByteArray::fromHex("00"), ui->page_GetStart);
}

void MainWindow::printPause()
{
    m_printsec->stop();
    QByteArray command = QByteArray::fromHex("0602");
    m_port->pausePrint();
    changePageOnStatus(QByteArray::fromHex("02"), ui->page_Printint);
}

void MainWindow::printContinue()
{
    QList<QByteArray> ret = skpWin->get_return_value();
    if(ret.count() > 1) {
        qDebug()<<ret[1];
        qDebug()<<ret[2];
        if(ret[1] == "Disable") {
            qDebug()<<"Disable Left Extruder";
            m_port->setExtruderDisable(0);
            screen_status.setExtruderEnabled(0, false);
        }
        else if(ret[2] == "Disable") {
            qDebug()<<"Disable Right Extruder";
            m_port->setExtruderDisable(1);
            screen_status.setExtruderEnabled(1, false);
        }
    }
    m_printsec->start();
    m_port->continuePrint();
    changePageOnStatus(QByteArray::fromHex("01"), ui->page_Printint);
}

void MainWindow::printChangeFilament()
{
    strMachineStatus cur_status;
    m_port->getXhPage()->GetMachineStatus(&cur_status);
    if((cur_status.Status == 2) || (cur_status.Status == 4))
    {
        changeDialog((JLWidget*)changeFilamentDialog);
    }
}
