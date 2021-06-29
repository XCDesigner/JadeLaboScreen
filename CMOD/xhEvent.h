#ifndef _EVENT_H_
#define _EVENT_H_

#include <QWidget>
#include <QUdpSocket>
#include <QHostInfo>
#include <QDebug>
#include <QtNetwork>
#include <QByteArray>
#include <QThread>
#include "xhpage.h"
#include "xhport.h"

typedef struct {
    uint8_t Command;
    uint8_t SubCode;
    QByteArray RecvivedDatas;
}strEventTCB;

enum
{
    WAIT_TYPE_PAGE = 0,
    WAIT_TYPE_DIALOG
};

class JLEvent : public QObject
{
    Q_OBJECT
public:
    explicit JLEvent(QObject *parent = nullptr);
    ~JLEvent();

    void wait(QByteArray &pDataSend, uint8_t Timeout);
    void waitDialog(QByteArray &pDataSend, uint8_t Timeout);
    void setup(XhPort *pSerialPort);
    // bool setListen(uint8_t Command, uint8_t SubCode);

private:
   QList<strEventTCB> event_list;
   XhPort *m_serial_port;
   uint8_t command_to_wait;
   uint8_t subcode_to_wait;
   uint8_t wait_type;

public slots:
   void test();
   void commandAccept(uint8_t Command, uint8_t SubCode, QByteArray &Data);

signals:
   void changePageAccept(QByteArray &);
   void changeDialogAccept(QByteArray &);
};

#endif
