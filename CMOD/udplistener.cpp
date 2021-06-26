#include "udplistener.h"

strUDPMessageMap UdpListener::static_maps[] = {
    {0x0800, &UdpListener::broadCastProcess},
    {0x0801, &UdpListener::connectRequest},
    {0x0802, &UdpListener::disconnectRequest},
    {0xffff, 0}
};

UdpListener::UdpListener()
{
    p_Socket = nullptr;
    isConnected = false;
}

bool UdpListener::startListen(int Port)
{
    if(p_Socket != nullptr)
    {
        p_Socket->close();
        delete p_Socket;
    }
    p_Socket = new QUdpSocket(this);
    if(p_Socket->bind(QHostAddress::AnyIPv4, Port) == false) {
        qDebug()<<"Udp Bind fail!";
        return false;
    }
    else {
        p_Socket->open(QIODevice::ReadWrite);
        StartWork();
        QObject::connect(this, SIGNAL(sigDataParsed(QByteArray)), this, SLOT(DataProcess(QByteArray)), Qt::QueuedConnection);
        return true;
    }
}

QByteArray UdpListener::readData()
{
    if(p_Socket == nullptr)
        return QByteArray();
    QUdpSocket* pudp = (QUdpSocket*)p_Socket;
    QByteArray ret;
    ret.resize(pudp->bytesAvailable());
    ((QUdpSocket*)p_Socket)->readDatagram(ret.data(), ret.size(), &host, &host_port);
    qDebug()<<"Recv from: " << host.toString() << ":" << host_port;
    return ret;
}

void UdpListener::writeProtocalData(QByteArray SourceData)
{
    QByteArray send_buff = protocal->setupPackage(SourceData);
    ((QUdpSocket*)p_Socket)->writeDatagram(send_buff, host, host_port);
}

void UdpListener::DataProcess(QByteArray Data)
{
    QByteArray content = Data.mid(11, -1);
    qDebug()<<content;
    uint16_t command = (uint8_t)content.at(0) << 8 | (uint8_t)content.at(1);
    uint32_t i = 0;
    while(true)
    {
        if(static_maps[i].Command == 0xffff)
            break;
        if(static_maps[i].Command == command)
        {
            (this->*static_maps[i].pProcessFunction)(content);
            return;
        }
        i++;
    }
}

void UdpListener::broadCastProcess(QByteArray &Data)
{
    QByteArray s;
    broadCastReply(s);
}

void UdpListener::broadCastReply(QByteArray &Data)
{
    writeProtocalData(QByteArray(QByteArray::fromHex("088000")));
}

void UdpListener::connectRequest(QByteArray &Data)
{
    QList<QByteArray> ret;
    ret.append("Connect Request");
    ret.append(host.toString().toUtf8());
    ret.append("8888");
    QByteArray s;
    connectReply(s);
    emit sigManageEvent(ret);
    if(isConnected == true) {

    }
    else {

        isConnected = true;
    }
}

void UdpListener::connectReply(QByteArray &Data)
{
    writeProtocalData(QByteArray(QByteArray::fromHex("088100")));
}

void UdpListener::disconnectRequest(QByteArray &Data)
{
    QList<QByteArray> ret;
    QByteArray s;
    ret.append("Disconnect Request");
    disconnectReply(s);
    emit sigManageEvent(ret);
    if(isConnected == true) {

    }
    else {
        isConnected = true;
    }
}

void UdpListener::disconnectReply(QByteArray &Data)
{
    writeProtocalData(QByteArray(QByteArray::fromHex("088200")));
}
