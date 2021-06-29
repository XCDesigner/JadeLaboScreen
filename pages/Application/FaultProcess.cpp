#include "mainwindow.h"
#include "ui_mainwindow.h"

#define FAULT_FLAG_X0_CARRIER             (1UL<<0)
#define FAULT_FLAG_X1_CARRIER             (1UL<<1)
#define FAULT_FLAG_Y_AXIS                 (1UL<<2)
#define FAULT_FLAG_Z_AXIS                 (1UL<<3)
#define FAULT_FLAG_FILAMENT0              (1UL<<4)
#define FAULT_FLAG_FILAMENT1              (1UL<<5)
#define FAULT_FLAG_HEATER0                (1UL<<6)
#define FAULT_FLAG_HEATER1                (1UL<<7)
#define FAULT_FLAG_TEMP0                  (1UL<<8)
#define FAULT_FLAG_TEMP1                  (1UL<<9)
#define FAULT_FLAG_PROBE                  (1UL<<10)
#define FAULT_FLAG_MOVMENT                (1UL<<11)
#define FAULT_FLAG_POWER_LOST             (1UL<<31)

void MainWindow::FaultDetectInit()
{
    QByteArray s = QByteArray::fromHex("0608");
    // Pause event detection
    AddListen(s, &MainWindow::onPauseRequest, true);
    // Abort event detection
    s = QByteArray::fromHex("060A");
    AddListen(s, &MainWindow::onAbortRequest, true);
    // Get fault flag
    s = QByteArray::fromHex("010100");
    AddListen(s, &MainWindow::onFaultFlag, true);
}

void MainWindow::onPauseRequest(QByteArray &Data)
{
    m_port->getFaultFlag();
}

void MainWindow::onAbortRequest(QByteArray &Data)
{
    m_port->getFaultFlag();
}

void MainWindow::onFaultFlag(QByteArray &Data)
{
    uint32_t flag;

    flag = (uint32_t)Data.at(6) << 24 | (uint32_t)Data.at(5) << 16 | (uint32_t)Data.at(4) << 8 | (uint32_t)Data.at(3);
    if(flag & (FAULT_FLAG_FILAMENT0 | FAULT_FLAG_FILAMENT1)) {
        FilamentFaultDetected();
    }
    else if(flag & FAULT_FLAG_MOVMENT) {
        MovementFaultDetected();
    }
}
