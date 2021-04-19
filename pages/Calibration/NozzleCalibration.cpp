#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_308_clicked()
{
    ui->stackedWidget->setCurrentIndex(51);
    m_port->setHeattingUnit("0","0");
}

void MainWindow::on_pushButton_303_clicked()
{
    ui->stackedWidget->setCurrentIndex(62);
//    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(jump23()));
//    m_timer.start(2000);
    m_port->n_nozzleCalibration();
}

void MainWindow::on_pushButton_302_clicked()
{
    m_port->setHeattingUnit("0","0");
    ui->stackedWidget->setCurrentIndex(51);
}

void MainWindow::on_pushButton_292_clicked()
{
    m_port->setHeattingUnit("0","0");
    ui->stackedWidget->setCurrentIndex(51);
}

void MainWindow::on_pushButton_287_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}