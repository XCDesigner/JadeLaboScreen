#ifndef JLNETPORT_H
#define JLNETPORT_H

#include <QObject>
#include <QWidget>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QByteArray>
#include <QDebug>
#include "portreceiver.h"
#include "jlprotocal.h"
#include <QtNetwork>
#include <QAbstractSocket>

class JLNetPort : public portReceiver
{
    Q_OBJECT
public:
    JLNetPort();

    void StartWork();

private slots:
    void onSocketRead();

protected:
    QByteArray parseData() override;

protected:
    QAbstractSocket *p_Socket;
    JLProtocal *protocal;
};

#endif // JLNETPORT_H
