#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CMOD/XhUpdater.h"
#include <QThread>

void MainWindow::AboutPageInit()
{
    QObject::connect(ui->wqVersion->rootObject(), SIGNAL(clicked(int)), this, SLOT(on_AboutReturn(int)));
    AddListen(QByteArray(QByteArray::fromHex("0B0100")), &MainWindow::TMCReadback, true);
    QTimer::singleShot(500, this, SLOT(aboutTimerTester()));
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

void MainWindow::on_checkBox_stateChanged(int arg1)
{

}

void MainWindow::aboutTimerTester()
{
    if(ui->checkBox->isChecked() == true) {
        QByteArray regs = QByteArray::fromHex("001241");
        m_port->getTMCValue(2, regs);
    }
    QTimer::singleShot(500, this, SLOT(aboutTimerTester()));
}

void MainWindow::TMCReadback(QByteArray Data)
{
    if(Data.mid(0, 3).toHex() == "0b0100") {
        qDebug()<<Data;
        QString gconf = Data.mid(5, 4).toHex() + "\n";
        QString step = Data.mid(10, 4).toHex() + "\n";
        QString sg_result = Data.mid(15, 4).toHex() + "\n";
        ui->label->setText("GConf:" + gconf + "STEP:" + step + "SG_RESULT:" + sg_result);
    }
}
