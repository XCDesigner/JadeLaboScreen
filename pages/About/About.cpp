#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CMOD/XhUpdater.h"
#include <QThread>

void MainWindow::AboutPageInit()
{
    AddListen(QByteArray(QByteArray::fromHex("0B")), &MainWindow::DebugCallback, true);
    QTimer::singleShot(500, this, SLOT(aboutTimerTester()));
}

void MainWindow::on_pushButton_126_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_About);
    char version[30];
    sprintf(version, "Ver:%s-%s", __DATE__, __TIME__);
    ui->labScreenVersion->setText(version);
    m_port->getFirmwareVersion();
    AddListen(QByteArray(QByteArray::fromHex("0503")), &MainWindow::onFirmwareVersionReceived, false);
}

void MainWindow::onFirmwareVersionReceived(QByteArray &Datas)
{
    QString ver = QString(Datas.mid(3, -1));
    ui->labFirmwareVersion->setText(ver);
}

void MainWindow::aboutTimerTester()
{
    if(ui->checkBox->isChecked() == true) {
        QByteArray regs = QByteArray::fromHex("0012416f");
        m_port->getTMCValue(2, regs);
        m_port->trigFILSample();
        m_port->getFILValue();
    }
    QTimer::singleShot(500, this, SLOT(aboutTimerTester()));
}

void MainWindow::DebugCallback(QByteArray &Data)
{
    QByteArray prefix = Data.mid(0, 3).toHex();
    if(prefix == "0b0100") {
        char value[32];
        QByteArray tmp;
        QString gconf = Data.mid(8, 1).toHex() + Data.mid(7, 1).toHex() + Data.mid(6, 1).toHex() + Data.mid(5, 1).toHex() + "\n";
        QString step = Data.mid(13, 1).toHex() + Data.mid(12, 1).toHex() + Data.mid(11, 1).toHex() + Data.mid(10, 1).toHex() + "\n";
        QString sg_result = (Data.mid(18, 1) + Data.mid(17, 1) + Data.mid(16, 1) + Data.mid(15, 1)) + "\n";

        QString pwm_scale = Data.mid(22, 1).toHex() + "\n";
        sprintf(value, "%d\n", ((uint8_t)Data.at(16) << 8) | (uint8_t)Data.at(15));
        ui->label->setText("GConf:" + gconf + "STEP:" + step + "SG_RESULT:" + value + "PWM:" + pwm_scale);
    }
    else if(prefix == "0b0700") {
        QString fil1 = Data.mid(3, 4).toHex() + "\n";
        QString fil1_raw = Data.mid(7, 4).toHex() + "\n";
        QString fil2 = Data.mid(11, 4).toHex() + "\n";
        QString fil2_raw = Data.mid(15, 4).toHex() + "\n";
        ui->label_3->setText("FIL1:" + fil1 + "FIL1_Raw:" + fil1_raw + "FIL2:" + fil2 + "FIL2_Raw:" + fil2_raw);
    }
    else if(prefix == "0b0f00") {
        bool added = false;
        test_counter = test_counter + 1;
        for(uint i=0;i<sizeof(test_buffer);i++)
        {
            if(test_buffer[i] != 0xff)
            {
                added = true;
                test_buffer[i]++;
                break;
            }
        }
        if(added == false)
        {
            for(uint i=0;i<sizeof(test_buffer);i++)
            {
                test_buffer[i] = 0;
            }
        }
        if(test_counter == 65535)
        {
            qDebug()<<"test_counter:" << test_counter;
        }
        m_port->SendTest(QByteArray::fromRawData((char*)test_buffer, sizeof(test_buffer)));
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_2_clicked()
{
    char len[32];
    sprintf(len, "%d", m_port->getReceiveLen());
    ui->pushButton_2->setText(len);
}
