#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_679_clicked()
{
    ui->label_5->clear();
    ui->label_8->clear();
    ui->label_9->clear();
    ui->label_10->clear();
    ui->label_11->clear();
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_676_clicked()
{
    ui->label_5->clear();
    ui->label_8->clear();
    ui->label_9->clear();
    ui->label_10->clear();
    ui->label_11->clear();
    m_port->prepareChangeFilament();
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeFilament);
}

void MainWindow::on_pushButton_678_clicked()
{
    ui->label_5->clear();
    ui->label_8->clear();
    ui->label_9->clear();
    ui->label_10->clear();
    ui->label_11->clear();
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::on_pushButton_677_clicked()
{
    ui->label_5->clear();
    ui->label_8->clear();
    ui->label_9->clear();
    ui->label_10->clear();
    ui->label_11->clear();
    ui->stackedWidget->setCurrentWidget(ui->page_About);
}

void MainWindow::on_pushButton_342_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_SelfTest_0);
}

void MainWindow::on_pushButton_692_clicked()
{
    ui->label_5->clear();
    ui->label_8->clear();
    ui->label_9->clear();
    ui->label_10->clear();
    ui->label_11->clear();
    ui->stackedWidget->setCurrentWidget(ui->page_SelfTest_0);
}

void MainWindow::on_pushButton_348_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_MachineSetting);

    ui->label_5->clear();
    ui->label_8->clear();
    ui->label_9->clear();
    ui->label_10->clear();
    ui->label_11->clear();
}

void MainWindow::on_pushButton_347_clicked()
{
    AddListen(QByteArray(QByteArray::fromHex("0505")), &MainWindow::onSelfTestReack, false);
    m_port->testAxis();
}

void MainWindow::onSelfTestReack(QByteArray &Data)
{
    uint8_t command = (uint8_t)Data.at(0);
    uint8_t subCode = (uint8_t)Data.at(1);
    uint8_t result = (uint8_t)Data.at(2);
    qDebug()<<Data;
    switch(subCode)
    {
        case 0x05:
            AddListen(QByteArray(QByteArray::fromHex("0506")), &MainWindow::onSelfTestReack, false);
            m_port->testLeftHotend();
        break;

        case 0x06:
            AddListen(QByteArray(QByteArray::fromHex("0507")), &MainWindow::onSelfTestReack, false);
            m_port->testRightHotend();
        break;

        case 0x07:
            AddListen(QByteArray(QByteArray::fromHex("0508")), &MainWindow::onSelfTestReack, false);
            m_port->testBed();
        break;

        case 0x08:
            AddListen(QByteArray(QByteArray::fromHex("0509")), &MainWindow::onSelfTestReack, false);
            m_port->testCalibration();
        break;

        case 0x09:

        break;
    }
}
