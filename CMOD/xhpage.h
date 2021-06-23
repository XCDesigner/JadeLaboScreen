#ifndef XHPAGE_H
#define XHPAGE_H

#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QtEndian>
#include <QDataStream>

#include "XhUpdater.h"

typedef struct {
    float ZHeight;
    int16_t CurTemp[3];
    int16_t TarTemp[3];
    uint16_t Percent;
    uint8_t Status;
    uint8_t StepperHold;
}strMachineStatus;

class XhPage : public QObject
{
    Q_OBJECT
public:
    explicit XhPage(QObject *parent = nullptr);
    ~XhPage();

    int analysis(QByteArray package);
    /*frist start页面*/
    void fTGet(QByteArray data);//温度获取
    void GetMachineStatus(strMachineStatus *pStatus);
private:
    /*first start自检变量*/
    QMutex mtxMachineStatus;

    strMachineStatus cur_machine_status;
signals:
    void command_received(uint8_t, uint8_t, QByteArray);
};

#endif // XHPAGE_H
