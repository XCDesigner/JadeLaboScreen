#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_242_clicked()
{
    m_port->setHeattingUnit("200","200");
    ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_1);
    screen_status.setPerformance(PLATFORM_CALIBRATING);
    QTimer::singleShot(500, this, SLOT(platformCalibrationHeating()));
}

void MainWindow::on_pushButton_243_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::on_pushButton_248_clicked()
{
    m_port->setHeattingUnit("0","0");
    screen_status.setPerformance(IDLE);
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::on_pushButton_259_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_2);
    m_port->p_platformCalibration();
}

void MainWindow::on_pushButton_253_clicked()
{
    screen_status.setPerformance(IDLE);
    m_port->cancleCalibration();
}

void MainWindow::on_pushButton_365_clicked()
{
    m_port->setHeattingUnit("0","0");
    screen_status.setPerformance(IDLE);
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
    QObject::disconnect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(platformCalibrationMessageProcess(uint8_t, uint8_t, QByteArray)));
    m_port->carbinfinished();
}

void MainWindow::on_pushButton_367_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_4);
}

void MainWindow::on_pushButton_371_clicked()
{
    m_port->setHeattingUnit("0","0");
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
    screen_status.setPerformance(IDLE);
    QObject::disconnect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(platformCalibrationMessageProcess(uint8_t, uint8_t, QByteArray)));
    m_port->carbincancel();
}

void MainWindow::on_pushButton_375_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_5);
}

void MainWindow::on_pushButton_373_clicked()
{
    m_port->setHeattingUnit("0","0");
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
    screen_status.setPerformance(IDLE);
    QObject::disconnect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(platformCalibrationMessageProcess(uint8_t, uint8_t, QByteArray)));
    m_port->carbincancel();
}

void MainWindow::platformCalibrationHeating()
{
    strMachineStatus new_status;
    m_port->getXhPage()->GetMachineStatus(&new_status);

    if(screen_status.getPerformance() == PLATFORM_CALIBRATING)
    {
        if((new_status.CurTemp[0] >190 ) && (new_status.CurTemp[1] >190))
        {
            m_port->p_platformCalibration();
            ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_2);
            QObject::connect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(platformCalibrationMessageProcess(uint8_t, uint8_t, QByteArray)));
        }
        else
        {
            qDebug()<<"Platform cali heating..";
            QTimer::singleShot(500, this, SLOT(platformCalibrationHeating()));
        }
    }
}

void MainWindow::platformCalibrationMessageProcess(uint8_t Command, uint8_t SubCode, QByteArray Datas)
{
    if(Command == 0x03)
    {
        if(SubCode == 0x02) {
            float z_diff[4];
            z_diff[0] = (int32_t)(((uint8_t)Datas.at(6) << 24) | ((uint8_t)Datas.at(5) << 16) | ((uint8_t)Datas.at(4) << 8) | (uint8_t)Datas.at(3)) / 1000.0f;
            z_diff[1] = (int32_t)(((uint8_t)Datas.at(10) << 24) | ((uint8_t)Datas.at(9) << 16) | ((uint8_t)Datas.at(8) << 8) | (uint8_t)Datas.at(7)) / 1000.0f;
            z_diff[2] = (int32_t)(((uint8_t)Datas.at(14) << 24) | ((uint8_t)Datas.at(13) << 16) | ((uint8_t)Datas.at(12) << 8) | (uint8_t)Datas.at(11)) / 1000.0f;
            z_diff[3] = (int32_t)(((uint8_t)Datas.at(18) << 24) | ((uint8_t)Datas.at(17) << 16) | ((uint8_t)Datas.at(16) << 8) | (uint8_t)Datas.at(15)) / 1000.0f;
            if((z_diff[0] == 0) && (z_diff[1] == 0) && (z_diff[2] == 0) && (z_diff[3] == 0))
            {
                ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_6);
                QObject::disconnect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(platformCalibrationMessageProcess(uint8_t, uint8_t, QByteArray)));
            }
            else
            {
                ui->label_253->setNum((int)(z_diff[0]));
                ui->label_253->setAlignment(Qt::AlignCenter);
                ui->label_261->setNum((int)(z_diff[3]));
                ui->label_261->setAlignment(Qt::AlignCenter);
                ui->label_256->setNum((int)(z_diff[1]));
                ui->label_256->setAlignment(Qt::AlignCenter);
                ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_3);
            }
        }
    }
}
