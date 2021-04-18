#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_631_clicked()
{
    ui->stackedWidget->setCurrentIndex(66);
    m_port->setHeattingUnit("200","200");
    QObject::connect(&m_timer,&QTimer::timeout,this,&MainWindow::xyheated);
    m_timer.start(1000);
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