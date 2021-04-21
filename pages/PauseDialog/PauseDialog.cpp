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
    QByteArray command = QByteArray::fromHex("0601");
    m_printsec->stop();
    m_time->setHMS(0,0,0);
    blockingChangePage(command, ui->page_GetStart);
}

void MainWindow::printPause()
{
    m_printsec->stop();
    QByteArray command = QByteArray::fromHex("0602");
    blockingChangePage(command, ui->page_Printint);
}

void MainWindow::printContinue()
{
    m_printsec->stop();
    QByteArray command = QByteArray::fromHex("060C");
    blockingChangePage(command, ui->page_Printint);
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

void MainWindow::printMessageProcess(QByteArray Datas)
{

}
