#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_286_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_NozzleCali_1);
    ui->qw_NozzleCalibrateP1->setClearColor(QColor(qmlColor));
    m_port->setHeattingUnit("200","200");
    screen_status.setPerformance(NOZZLE_CALIBRATING);
    QTimer::singleShot(500, this, SLOT(nozzleCalibrationHeating()));
}

void MainWindow::on_pushButton_648_clicked()
{
    m_port->setHeattingUnit("0","0");
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
    screen_status.setPerformance(IDLE);
}

void MainWindow::on_pushButton_308_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
    screen_status.setPerformance(IDLE);
    m_port->setHeattingUnit("0","0");
}

void MainWindow::on_pushButton_303_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_NozzleCali_2);
    m_port->n_nozzleCalibration();
}

void MainWindow::on_pushButton_302_clicked()
{
    m_port->setHeattingUnit("0","0");
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
    screen_status.setPerformance(IDLE);
}

void MainWindow::on_pushButton_287_clicked()
{
    screen_status.setPerformance(IDLE);
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::nozzleCalibrationHeating()
{
    strMachineStatus new_status;
    m_port->getXhPage()->GetMachineStatus(&new_status);

    if(screen_status.getPerformance() == NOZZLE_CALIBRATING)
    {
        if((new_status.CurTemp[0] >190 ) && (new_status.CurTemp[1] >190))
        {
            m_port->n_nozzleCalibration();
            ui->stackedWidget->setCurrentWidget(ui->page_NozzleCali_2);
            QObject::connect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(nozzleCalibrationMessageProcess(uint8_t, uint8_t, QByteArray)));
        }
        else
        {
            QTimer::singleShot(500, this, SLOT(nozzleCalibrationHeating()));
        }
    }
}

void MainWindow::nozzleCalibrationMessageProcess(uint8_t Command, uint8_t SubCode, QByteArray Datas)
{
    if(Command == 0x03)
    {
        if(SubCode == 0x00) 
        {
            float z_diff = (int32_t)(((uint8_t)Datas.at(6) << 24) | ((uint8_t)Datas.at(5) << 16) | ((uint8_t)Datas.at(4) << 8) | (uint8_t)Datas.at(3)) / 1000.0f;
            if(z_diff != 0) 
            {
                ui->stackedWidget->setCurrentWidget(ui->page_NozzleCali_3);
                ui->qw_NozzleCalibrateP1->setProperty("value", (int)z_diff);
            }
            else
            {
                ui->stackedWidget->setCurrentWidget(ui->page_NozzleCali_4);
                QObject::disconnect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(nozzleCalibrationMessageProcess(uint8_t, uint8_t, QByteArray)));
            }
        }
    }
}
