#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CMOD/XhUpdater.h"
#include <QThread>

void MainWindow::AboutPageInit()
{
    QObject::connect(ui->wqVersion->rootObject(), SIGNAL(clicked(int)), this, SLOT(on_AboutReturn(int)));
    AddListen(QByteArray(QByteArray::fromHex("0B")), &MainWindow::DebugCallback, true);
    QTimer::singleShot(500, this, SLOT(aboutTimerTester()));
}

void MainWindow::on_pushButton_126_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_About);
    char version[30];
    sprintf(version, "Ver:%s-%s", __DATE__, __TIME__);
    m_port->getFirmwareVersion();
    AddListen(QByteArray(QByteArray::fromHex("0503")), &MainWindow::onFirmwareVersionReceived, false);
    ui->quickWidget_2->rootObject()->setProperty("icon", "qrc:/image/platform_warning.png");
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

void MainWindow::aboutTimerTester()
{
    if(ui->checkBox->isChecked() == true) {
        QByteArray regs = QByteArray::fromHex("001241");
        m_port->getTMCValue(3, regs);
        m_port->trigFILSample();
        m_port->getFILValue();
    }
    QTimer::singleShot(500, this, SLOT(aboutTimerTester()));
}

void MainWindow::DebugCallback(QByteArray Data)
{
    QByteArray prefix = Data.mid(0, 3).toHex();
    if(prefix == "0b0100") {
        QString gconf = Data.mid(5, 4).toHex() + "\n";
        QString step = Data.mid(10, 4).toHex() + "\n";
        QString sg_result = Data.mid(15, 4).toHex() + "\n";
        char value[32];
        sprintf(value, "%d\n", ((uint8_t)Data.at(16) << 8) | (uint8_t)Data.at(15));
        ui->label->setText("GConf:" + gconf + "STEP:" + step + "SG_RESULT:" + value);
    }
    else if(prefix == "0b0700") {
        QString fil1 = Data.mid(3, 4).toHex() + "\n";
        QString fil1_raw = Data.mid(7, 4).toHex() + "\n";
        QString fil2 = Data.mid(11, 4).toHex() + "\n";
        QString fil2_raw = Data.mid(15, 4).toHex() + "\n";
        ui->label_3->setText("FIL1:" + fil1 + "FIL1_Raw:" + fil1_raw + "FIL2:" + fil2 + "FIL2_Raw:" + fil2_raw);
    }
}
