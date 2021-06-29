#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CMOD/XhUpdater.h"
#include <QThread>

void MainWindow::PowerLostInit()
{
    QByteArray s = QByteArray::fromHex("0103");
    AddListen(s, &MainWindow::PowerTestResult, false);
    m_port->getPowerLostStatus();
}

void MainWindow::PowerTestResult(QByteArray &Data)
{
    if(Data.at(3) == 0x01)
    {
        m_power = new powerLost();
        QByteArray s;
        m_power->init(s);
        m_power->show();
        QObject::connect(m_power, SIGNAL(hideWidget()), this, SLOT(PowerLostDialogReturn()));
    }
}

void MainWindow::AcceptRecoveryInfo(QByteArray &Data)
{
    int16_t temp[3];
    QString mode[] = {"Direct", "", "Duplicate", "Mirror", "Original-Duplicate", "Original-Mirror"};
    temp[0] = Data.at(4) << 8 | (uint8_t)Data.at(3);
    temp[1] = Data.at(6) << 8 | (uint8_t)Data.at(5);
    temp[2] = Data.at(8) << 8 | (uint8_t)Data.at(7);

    m_port->setPrintFanPercentage(0, (uint8_t)Data.at(9));
    m_port->setPrintFanPercentage(1, (uint8_t)Data.at(10));
    // Carrier Mode 1Byte
    ui->label_36->setText(mode[(uint8_t)Data.at(11)]);
    ui->label_69->setText(mode[(uint8_t)Data.at(11)]);

    // Mirror enabled 1Byte

    // Active extruder 1Byte

    // Extruder avaliable flag 1Byte

    m_port->setHeattingUnit(0, temp[0]);
    m_port->setHeattingUnit(1, temp[1]);
    m_port->setHeattingUnit(2, temp[2]);
    screen_status.setPerformance(PREPARE_RECOVERY);
    ui->stackedWidget->setCurrentWidget(ui->page_PreparePrint);
    // ui->stackedWidget->setCurrentWidget(ui->page_PrepareRecovery);
    // QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpSeventeen()));
    // m_printsec->start(1000);
    // m_timer.start(100);
}

void MainWindow::PowerLostDialogReturn()
{
    QList<QByteArray> ret = m_power->get_return_value();
    if(ret[0] == "Cancel")
    {
        qDebug()<<"Cancel power lost";
        m_port->markPowerLostFlag();
    }
    else if(ret[0] == "Recovery")
    {
        qDebug()<<"Power lost recovery";
        if(m_port->setPrintFile(GetRecoveryFile()) == true)
        {
            qDebug()<<"Set file success";
            QByteArray s = QByteArray::fromHex("0615");
            AddListen(s, &MainWindow::AcceptRecoveryInfo, false);
            m_port->getRecoveryInfo();
        }
        else
        {
            qDebug()<<"Set file fail" << GetRecoveryFile();
            m_port->markPowerLostFlag();
        }
    }
    delete m_power;
}

QString MainWindow::GetRecoveryFile()
{
    QFile *pfile = new QFile(RECOVERY_RECORD);
    QString ret = "";
    if(pfile->open(QIODevice::ReadOnly | QIODevice::Text) == true)
    {
        QByteArray line = pfile->readLine(0);
        QString file_path = QString(localPath) + "/";
        ui->labFileName_0->setText(line);
        ui->labFileName_1->setText(line);
        ret = QString(file_path + line).trimmed();
        qDebug()<< ret;
        pfile->close();
    }
    delete pfile;
    return ret;
}

void MainWindow::WriteRecoveryFilaName(QString &FileName)
{
    qDebug()<<"WriteRecovery";
    QFile *pfile = new QFile(RECOVERY_RECORD);
    QDir *pDir = new QDir(RECOVERY_RECORD_PATH);
    if(pDir->exists() == false)
    {
        pDir->mkpath(RECOVERY_RECORD_PATH);
    }
    if(pfile->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text) == true)
    {
        QTextStream writer(pfile);
        writer<< FileName + "\n";
        pfile->close();
    }
    delete pfile;
    delete pDir;
}

void MainWindow::RecoveryStop()
{
    m_port->setHeattingUnit("0", "0");
    m_port->setHeattingUnit(2, 0);
    if(m_timer.isActive())
    {
        m_timer.stop();
        QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpSeventeen()));
    }
    screen_status.setPerformance(IDLE);
    QByteArray s = QByteArray::fromHex("00");
    changePageOnStatus(s, ui->page_GetStart);
}

void MainWindow::RecoverySettingShow()
{
    QByteArray s = QByteArray::fromHex("0614");
    blockingChangeDialog(s, m_setdlog);
}
