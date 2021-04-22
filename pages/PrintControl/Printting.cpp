#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::StopPrintClicked()
{
    if(m_timer.isActive())
    {
        m_timer.stop();
        QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpFourteen()));
    }
    qDebug()<<"Stop clicked";
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

void MainWindow::onFinishPrintClicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
    ui->quickWidget_3->rootObject()->setProperty("currentPercent", 0);
    ui->quickWidget_3->rootObject()->setProperty("finishEnabled", false);
    ui->qw_PrintingControl->rootObject()->setProperty("settingEnabled", true);
    ui->qw_PrintingControl->rootObject()->setProperty("stopEnabled", true);
    ui->qw_PrintingControl->rootObject()->setProperty("pauseEnabled", true);
}

void MainWindow::printMessageProcess(uint8_t Command, uint8_t SubCode, QByteArray Datas)
{
    if(Command == 0x06)
    {
        if(SubCode == 0x06)
        {
            ui->stackedWidget->setCurrentWidget(ui->page_Printint);
        }
        if(SubCode == 0x07)
        {
            ui->qw_PrintingControl->rootObject()->setProperty("settingEnabled", false);
            ui->qw_PrintingControl->rootObject()->setProperty("stopEnabled", false);
            ui->qw_PrintingControl->rootObject()->setProperty("pauseEnabled", false);
        }
        else if(SubCode == 0x09)
        {
            ui->quickWidget_3->rootObject()->setProperty("currentPercent", 100);
            ui->quickWidget_3->rootObject()->setProperty("finishEnabled", true);
        }
    }
    if(Command == 0x01)
    {
        if(SubCode == 0x07)
        {
            qDebug()<<Datas;
        }
    }
}
