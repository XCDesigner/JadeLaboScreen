#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_342_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_SelfTest_0);
}

void MainWindow::on_pushButton_692_clicked()
{
    ui->label_164->clear();
    ui->label_192->clear();
    ui->label_193->clear();
    ui->label_224->clear();
    ui->label_225->clear();
    ui->label_285->clear();
    ui->stackedWidget->setCurrentWidget(ui->page_SelfTest_0);
}
