#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_631_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_XYCali_1);
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

void MainWindow::xyheated()
{
    if((ui->label_125->text().left(3).toInt() >190 )&& (ui->label_127->text().left(3).toInt() >190 ))
    {
         m_port->x_xyCalibration();
         QObject::disconnect(&m_timer,&QTimer::timeout,this,&MainWindow::xyheated);
         m_timer.stop();
         ui->stackedWidget->setCurrentWidget(ui->page_XYCali_2);
    }
}

void MainWindow::plat()
{
    ui->stackedWidget->setCurrentWidget(ui->page_XYCali_3);
}
