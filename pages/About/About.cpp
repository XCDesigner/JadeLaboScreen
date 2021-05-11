#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CMOD/XhUpdater.h"
#include <QThread>

void MainWindow::AboutPageInit()
{
    QObject::connect(ui->wqVersion->rootObject(), SIGNAL(click(int)), this, SLOT(on_AboutReturn(int)));
}

void MainWindow::on_pushButton_126_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_About);
    char version[30];
    sprintf(version, "Ver:%s-%s", __DATE__, __TIME__);
    m_port->getFirmwareVersion();
    AddListen(QByteArray(QByteArray::fromHex("0503")), &MainWindow::onFirmwareVersionReceived, false);
    ui->wqVersion->rootObject()->setProperty("text", version);
}

void MainWindow::on_AboutReturn(int Index)
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::onFirmwareVersionReceived(QByteArray Datas)
{
    QString ver = QString(Datas.mid(3, -1));
    ui->wqVersionFirmware->rootObject()->setProperty("text", ver);
}
