#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::onPauseDialogHide()
{
    qDebug()<<"Pause dialog hide";
    QList<QByteArray> ret = skpWin->get_return_value();
    qDebug()<<ret[0];
    if(ret[0] == "Stop")
        printstop();
    else if(ret[0] == "Pause")
        printpause();
    else if(ret[0] == "Cancel")
        ;
}

void MainWindow::printstop()
{
    QByteArray command = QByteArray::fromHex("0601");
    m_printsec->stop();
    m_time->setHMS(0,0,0);
    blockingChangePage(command, ui->page_GetStart);
    // ui->stackedWidget->setCurrentIndex(33);
}

void MainWindow::printpause()
{
    m_printsec->stop();
    QByteArray command = QByteArray::fromHex("0602");
    blockingChangePage(command, ui->page_37);
    //m_port->pausePrint();
}

