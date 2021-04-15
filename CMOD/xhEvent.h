#ifndef _EVENT_H_
#define _EVENT_H_

#include <QWidget>
#include <QUdpSocket>
#include <QHostInfo>
#include <QDebug>
#include <QtNetwork>
#include <QByteArray>
#include "xhpage.h"
#include "xhport.h"

typedef struct {
    uint8_t Command;
    uint8_t SubCode;
    uint8_t SendData[256];
    uint8_t RecvData[256];
}strEventTCB;

class JLEvent : public QObject
{
    Q_OBJECT
public:
    explicit JLEvent(QObject *parent = nullptr);
    ~JLEvent();

    bool wait(uint8_t Command, uint8_t SubCode, uint8_t *pDataSend, uint8_t *pDataReply);
    void setup(XhPort *pSerialPort);
    // bool setListen(uint8_t Command, uint8_t SubCode);

private:
   QList<strEventTCB> event_list;
   XhPort *m_serial_port;

public slots:
   void test();
   void commandAccept(uint8_t Command, uint8_t SubCode, QByteArray Data);
};

#endif
