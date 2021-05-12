#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::xyCalibrateFail()
{
    m_port->setHeattingUnit(0, 0);
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::on_pushButton_631_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_XYCali_1);
    ui->qw_NozzleCalibrateP1->setClearColor("#202020");
    m_port->setHeattingUnit("200","200");
    QTimer::singleShot(500, this, SLOT(xyCalibrationHeating()));
    screen_status.setPerformance(XY_CALIBRATING);
}

void MainWindow::on_pushButton_637_clicked()
{
    m_port->setHeattingUnit("0","0");
    screen_status.setPerformance(IDLE);
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::on_pushButton_632_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::on_pushButton_647_clicked()
{
    m_port->x_platformCalibration();
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::xyCalibrationHeating() {
    strMachineStatus new_status;
    m_port->getXhPage()->GetMachineStatus(&new_status);
    if(screen_status.getPerformance() == XY_CALIBRATING)
    {
        if((new_status.CurTemp[0] > 190 ) && (new_status.CurTemp[1] > 190))
        {
            m_port->x_xyCalibration();
            ui->stackedWidget->setCurrentWidget(ui->page_XYCali_2);
            QObject::connect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(xyCalibrationMessageProcess(uint8_t, uint8_t, QByteArray)));
        }
        else
        {
            QTimer::singleShot(500, this, SLOT(xyCalibrationHeating()));
        }
    }
}

void MainWindow::xyCalibrationMessageProcess(uint8_t Command, uint8_t SubCode, QByteArray Datas)
{
    if(Command == 0x03)
    {
        if(SubCode == 0x05) {
            m_port->setHeattingUnit("0","0");
            screen_status.setPerformance(IDLE);
            ui->stackedWidget->setCurrentWidget(ui->page_XYCali_3);
            QObject::disconnect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(xyCalibrationMessageProcess(uint8_t, uint8_t, QByteArray)));
        }
    }
}
