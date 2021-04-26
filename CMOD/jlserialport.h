#ifndef JLSERIALPORT_H
#define JLSERIALPORT_H

#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "portreceiver.h"
#include "jlprotocal.h"

class JLSerialPort : public portReceiver
{
    Q_OBJECT
public:
    explicit JLSerialPort(QObject *parent = nullptr);
    static QList<QString> getPortNames();
    bool openPort(QString, int);
    bool openPort(QString);
    void write(QByteArray);
    void writeData(QByteArray);
    void writeProtocalData(QByteArray);

private slots:
    void onSerialRead();

protected:
    QByteArray readData() override;
    QByteArray parseData() override;

private:
    QSerialPort *m_port;
    JLProtocal *protocal;
};

#endif // JLSERIALPORT_H
