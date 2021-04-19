#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::StopPrintClicked()
{
    if(m_timer.isActive())
    {
        m_timer.stop();
        QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpFourteen()));
    }
    m_port->stopPrint();
    changePageOnStatus(QByteArray::fromHex("00"), ui->page_GetStart);
}

void MainWindow::ShowPauseDialogClicked()
{
    QByteArray s;
    m_timer.stop();
    blockingChangeDialog(s, (JLWidget*)skpWin);
}

void MainWindow::ShowParameterDialogClicked()
{
    QByteArray s = QByteArray::fromHex("0614");
    blockingChangeDialog(s, m_setdlog);
    m_printsec->stop();
}
