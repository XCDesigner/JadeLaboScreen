#ifndef PORTRECEIVER_H
#define PORTRECEIVER_H

#include <QObject>
#include <QThread>
#include <QtDebug>
#include <QByteArray>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMutex>

class portReceiver : public QThread
{
    Q_OBJECT
public:
    explicit portReceiver(QObject *parent = nullptr);

signals:
    void sigDataParsed(QByteArray);

public:
    virtual QByteArray readData();
    virtual QByteArray parseData();

protected:
    QByteArray receive_buffer;
    QMutex mtx_receiver_buffer;

private:
    void run() override;

};

#endif // PORTRECEIVER_H
