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
    screen_status.setPerformance(IDLE);
    changePageOnStatus(QByteArray::fromHex("00"), ui->page_GetStart);
}

void MainWindow::ShowPauseDialogClicked()
{
    QByteArray s;
    if(m_timer.isActive())
    {
        m_timer.stop();
    }
    blockingChangeDialog(s, (JLWidget*)skpWin);
}

void MainWindow::ShowParameterDialogClicked()
{
    QByteArray s = QByteArray::fromHex("0614");
    m_setdlog->setPrintMode(print_desc.ParsedMode);
    blockingChangeDialog(s, m_setdlog);
}

void MainWindow::onFinishPrintClicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
    ui->quickWidget_3->rootObject()->setProperty("currentPercent", 0);
    ui->quickWidget_3->rootObject()->setProperty("finishEnabled", false);
    ui->qw_PrintingControl->rootObject()->setProperty("settingEnabled", true);
    ui->qw_PrintingControl->rootObject()->setProperty("stopEnabled", true);
    ui->qw_PrintingControl->rootObject()->setProperty("pauseEnabled", true);
    screen_status.setPerformance(IDLE);
}

void MainWindow::timeAdd()
{
    print_end_time = print_end_time.addSecs(1);
    qint64 del = print_start_time.secsTo(print_end_time);
    int days = del / 3600 / 24;
    del = del % (3600 * 24);
    int hours = del / 3600;
    del = del % 3600;
    int minutes = del / 60;
    char strtime[32];
    sprintf(strtime, "%dd %dh %dm", days, hours, minutes);
    ui->label_86->setText(strtime);
    ui->label_78->setText(strtime);
    ui->label_307->setText(strtime);
}


void MainWindow::printMessageProcess(uint8_t Command, uint8_t SubCode, QByteArray Datas)
{
    if(Command == 0x06)
    {
        if(SubCode == 0x06)
        {
            ui->stackedWidget->setCurrentWidget(ui->page_Printing);
        }
        else if(SubCode == 0x07)
        {
            m_printsec->stop();
            ui->qw_PrintingControl->rootObject()->setProperty("settingEnabled", false);
            ui->qw_PrintingControl->rootObject()->setProperty("stopEnabled", false);
            ui->qw_PrintingControl->rootObject()->setProperty("pauseEnabled", false);
        }
        else if(SubCode == 0x09)
        {
            ui->quickWidget_3->rootObject()->setProperty("currentPercent", 1000);
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
