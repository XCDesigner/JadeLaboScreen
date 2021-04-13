#ifndef _EVENT_H_
#define _EVENT_H_

#include <QWidget>
#include <QUdpSocket>
#include <QHostInfo>
#include <QDebug>
#include <QtNetwork>
#include <QByteArray>

typedef void pFun(uint8_t *, uint16_t);

typedef struct {
    uint8_t Command;
    uint8_t SubCode;
    pFun pCallback;
}strEventTCB;

class JLEvent : QObject
{
public:
    explicit JLEvent(QObject *parent = nullptr);
    static bool SetListen(uint8_t Command, uint8_t SubCode, void* pFunction);

private:

public:

private:
   static QList<strEventTCB> event_list;
};

extern JLEvent event_unit;

#endif
