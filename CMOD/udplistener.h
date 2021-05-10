#ifndef UPDLISTENER_H
#define UPDLISTENER_H

#include "jlnetport.h"
#include "customTypes.h"

class UdpListener : public JLNetPort
{
    Q_OBJECT
public:
    UdpListener();

    bool startListen(int);

    void writeProtocalData(QByteArray);

    void broadCastProcess(QByteArray);
    void connectRequest(QByteArray);
    void broadCastReply(QByteArray);
    void connectReply(QByteArray);
    void disconnectRequest(QByteArray);
    void disconnectReply(QByteArray);


protected:
    QByteArray readData() override;

private slots:
    void DataProcess(QByteArray);

private:
    static strUDPMessageMap static_maps[];
    QHostAddress host;
    uint16_t host_port;
    bool isConnected;

signals:
    void sigManageEvent(QByteArray);
};

#endif // UPDLISTENER_H
