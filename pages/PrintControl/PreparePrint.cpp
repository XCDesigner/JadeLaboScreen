#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::preparePrintPageInit()
{
    ui->qw_PreparePrintControl->rootObject()->setProperty("settingEnabled", true);
    ui->qw_PreparePrintControl->rootObject()->setProperty("stopEnabled", true);
    QTimer::singleShot(4000, this, SLOT(preparePrinTempChecking()));
    screen_status.setPerformance(PREPARE_PRINT);
    print_start_time.setDate(QDate(2021, 1, 1));
    print_end_time.setDate(QDate(2021, 1, 1));
    print_start_time.setTime(QTime(0, 0, 0));
    print_end_time.setTime(QTime(0, 0, 0));
    m_printsec->start(1000);
}

void MainWindow::StopPreHeatting() 
{
    m_port->setHeattingUnit("0", "0");
    m_port->setHeattingUnit(2, 0);
    screen_status.setPerformance(IDLE);
    changePageOnStatus(QByteArray::fromHex("00"), ui->page_GetStart);
}

void MainWindow::preparePrinTempChecking()
{
    strMachineStatus new_status;
    m_port->getXhPage()->GetMachineStatus(&new_status);
    if(screen_status.getPerformance() == PREPARE_PRINT)
    {
        // qDebug()<<"Temp check";
        // qDebug()<<new_status.CurTemp[0];
        // qDebug()<<new_status.TarTemp[0];
        // qDebug()<<new_status.CurTemp[1];
        // qDebug()<<new_status.TarTemp[1];
        if((new_status.CurTemp[0] > (new_status.TarTemp[0] * 0.8)) && (new_status.CurTemp[1] > (new_status.TarTemp[1] * 0.8)))
        {
            ui->qw_PreparePrintControl->rootObject()->setProperty("settingEnabled", false);
            ui->qw_PreparePrintControl->rootObject()->setProperty("stopEnabled", false);
            screen_status.setPerformance(PRINTING);
        }
    }
    if((screen_status.getPerformance() == PREPARE_PRINT) || (screen_status.getPerformance() == PRINTING))
    {
        if((new_status.CurTemp[0] > (new_status.TarTemp[0] * 0.9)) && (new_status.CurTemp[1] > (new_status.TarTemp[1] * 0.9)))
        {
            screen_status.setExtruderEnabled(0, true);
            screen_status.setExtruderEnabled(1, true);
            screen_status.setPrintMode(print_desc.Mode.toUtf8());
            QByteArray offset;
            int int_offset;
            int_offset = print_desc.XOffset * 1000;
            offset.append(1, int_offset);
            offset.append(1, int_offset >> 8);
            offset.append(1, int_offset >> 16);
            offset.append(1, int_offset >> 24);
            m_port->getXhPage()->setPrintFile(print_desc.FileName);
            qDebug()<<"StartPrint:" << print_desc.ParsedMode;
            // Direct mode contains "Direct" "Origin-Mirror" "Origin-Duplicate" "Mix" "Unsupport"
            if(print_desc.Mode == "Direct")
            {
                if((print_desc.ParsedMode == "Origin-Mirror") || (print_desc.ParsedMode == "Origin-Duplicate"))
                    m_port->preparePrint(print_desc.ParsedMode, offset);
                else
                    m_port->preparePrint(print_desc.Mode, offset);
            }
            else
            {
                m_port->preparePrint(print_desc.Mode, offset);
            }
            qDebug()<<"readyprint offset " << offset;
            qDebug()<<"readyprint mode" << printMode;
            AddListen(QByteArray(QByteArray::fromHex("060D00")), &MainWindow::onPreparePirntComplete, false);
        }
        else
        {
            QTimer::singleShot(200, this, SLOT(preparePrinTempChecking()));
        }
    }
}

void MainWindow::onPreparePirntComplete(QByteArray Data)
{
    qDebug()<<"Prepare complete!";
    m_port->startPrint();
    ui->stackedWidget->setCurrentWidget(ui->page_Printint);
}
