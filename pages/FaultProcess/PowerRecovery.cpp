#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CMOD/XhUpdater.h"
#include <QThread>

void MainWindow::PowerLostInit()
{
    m_port->getPowerLostStatus();
    AddListen(QByteArray(QByteArray::fromHex("0103")), &MainWindow::PowerTestResult, false);
}

void MainWindow::PowerTestResult(QByteArray Data)
{
    if(Data.at(2) == 0x01)
    {
        m_power = new powerLost();
        m_power->init(QByteArray());
        m_power->show();
        QObject::connect(m_power, SIGNAL(hideWidget()), this, SLOT(PowerLostDialogReturn()));
    }
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

    }
    delete m_power;
}
