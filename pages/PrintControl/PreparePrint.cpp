#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::preparePrintingPageInit()
{
    QObject::connect(ui->labPreparePrintControl, SIGNAL(stopClicked()), this, SLOT(StopPreHeatting()));
    QObject::connect(ui->labPreparePrintControl, SIGNAL(settingClicked()), this, SLOT(ShowParameterDialogClicked()));
}

void MainWindow::preparePrintPageLoad()
{
    ui->labPreparePrintControl->setSettingDisable();
    ui->labPreparePrintControl->setStopEnable();
    QTimer::singleShot(4000, this, SLOT(preparePrintTempChecking()));
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

void MainWindow::preparePrintTempChecking()
{
    strMachineStatus new_status;
    m_port->getXhPage()->GetMachineStatus(&new_status);
    if(screen_status.getPerformance() == PREPARE_RECOVERY)
    {
        if((new_status.CurTemp[0] > (new_status.TarTemp[0] * 0.9)) && (new_status.CurTemp[1] > (new_status.TarTemp[1] * 0.9)))
        {
            ui->stackedWidget->setCurrentWidget(ui->page_Printing);
            m_port->resumeRecovery();
        }
        else
        {
            QTimer::singleShot(200, this, SLOT(preparePrintTempChecking()));
        }
    }
    else
    {
        if(screen_status.getPerformance() == PREPARE_PRINT)
        {
            if((new_status.CurTemp[0] > (new_status.TarTemp[0] * 0.8)) && (new_status.CurTemp[1] > (new_status.TarTemp[1] * 0.8)))
            {
                ui->labPreparePrintControl->setSettingDisable();
                ui->labPreparePrintControl->setStopDisable();
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
                if(m_port->setPrintFile(print_desc.FileName) != true)
                {
                    qDebug()<<"Set print file fail!";
                }
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
                QTimer::singleShot(200, this, SLOT(preparePrintTempChecking()));
            }
        }
    }
}

void MainWindow::onPreparePirntComplete(QByteArray Data)
{
    qDebug()<<"Prepare complete!";
    m_port->startPrint();
    ui->stackedWidget->setCurrentWidget(ui->page_Printing);
}
