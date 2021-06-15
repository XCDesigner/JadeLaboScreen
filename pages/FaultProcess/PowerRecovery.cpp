#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CMOD/XhUpdater.h"
#include <QThread>

void MainWindow::PowerLostInit()
{
    ui->qw_RecoveryHeating->setClearColor(QColor(qmlColor));
    ui->qw_RecoveryControl->setClearColor(QColor(qmlColor));
    ui->qw_RecoveryControl->rootObject()->setProperty("settingEnabled", false);
    ui->qw_RecoveryControl->rootObject()->setProperty("stopEnabled", true);
    ui->qw_RecoveryControl->rootObject()->setProperty("pauseEnabled", false);
    AddListen(QByteArray(QByteArray::fromHex("0103")), &MainWindow::PowerTestResult, false);
    QObject::connect(ui->qw_RecoveryControl->rootObject(), SIGNAL(stopClicked()), this, SLOT(RecoveryStop()));
    QObject::connect(ui->qw_RecoveryControl->rootObject(), SIGNAL(settingClicked()), this, SLOT(RecoverySettingShow()));
    m_port->getPowerLostStatus();
}

void MainWindow::PowerTestResult(QByteArray Data)
{
    if(Data.at(3) == 0x01)
    {
        m_power = new powerLost();
        m_power->init(QByteArray());
        m_power->show();
        QObject::connect(m_power, SIGNAL(hideWidget()), this, SLOT(PowerLostDialogReturn()));
    }
}

void MainWindow::AcceptRecoveryInfo(QByteArray Data)
{
    int16_t temp[3];
    QString mode[] = {"Direct", "", "Duplicate", "Mirror", "Original-Duplicate", "Original-Mirror"};
    temp[0] = Data.at(4) << 8 | (uint8_t)Data.at(3);
    temp[1] = Data.at(6) << 8 | (uint8_t)Data.at(5);
    temp[2] = Data.at(8) << 8 | (uint8_t)Data.at(7);

    m_port->setPrintFanPercentage(0, (uint8_t)Data.at(9));
    m_port->setPrintFanPercentage(1, (uint8_t)Data.at(10));
    // Carrier Mode 1Byte
    ui->label_43->setText(mode[(uint8_t)Data.at(11)]);
    ui->label_36->setText(mode[(uint8_t)Data.at(11)]);
    ui->label_69->setText(mode[(uint8_t)Data.at(11)]);

    // Mirror enabled 1Byte

    // Active extruder 1Byte

    // Extruder avaliable flag 1Byte

    m_port->setHeattingUnit(0, temp[0]);
    m_port->setHeattingUnit(1, temp[1]);
    m_port->setHeattingUnit(2, temp[2]);
    ui->stackedWidget->setCurrentWidget(ui->page_PrepareRecovery);
    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpSeventeen()));
    m_printsec->start(1000);
    m_timer.start(100);
}

void MainWindow::PowerLostDialogReturn()
{
    QList<QByteArray> ret = m_power->get_return_value();
    if(ret[0] == "Cancel")
    {
        m_port->markPowerLostFlag();
    }
    else if(ret[0] == "Recovery")
    {
        if(m_port->getXhPage()->setPrintFile(GetRecoveryFile()) == true)
        {
            qDebug()<<"Set file success";
            AddListen(QByteArray(QByteArray::fromHex("0615")), &MainWindow::AcceptRecoveryInfo, false);
            m_port->getRecoveryInfo();
        }
        else
        {
            m_port->markPowerLostFlag();
        }
    }
    delete m_power;
}

QString MainWindow::GetRecoveryFile()
{
    qDebug()<<RECOVERY_RECORD;
    QFile *pfile = new QFile(RECOVERY_RECORD);
    QString ret = "";
    if(pfile->open(QIODevice::ReadOnly | QIODevice::Text) == true)
    {
        QByteArray line = pfile->readLine(0);
        ui->qw_FileName_0->rootObject()->setProperty("text", line);
        ui->qw_FileName_1->rootObject()->setProperty("text", line);
        ui->qw_FileName_2->rootObject()->setProperty("text", line);
        qDebug()<<line;
        ret = QString(line);
        pfile->close();
    }
    delete pfile;
    return ret;
}

void MainWindow::WriteRecoveryFilaName(QString FileName)
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
    changePageOnStatus(QByteArray::fromHex("00"), ui->page_GetStart);
}

void MainWindow::RecoverySettingShow()
{
    QByteArray s = QByteArray::fromHex("0614");
    blockingChangeDialog(s, m_setdlog);
}
