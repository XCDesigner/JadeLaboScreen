#include "jlnetport.h"

JLNetPort::JLNetPort()
{
    protocal = new JLProtocal(0x31);

}

void JLNetPort::StartWork()
{
    start();
    QObject::connect(p_Socket, SIGNAL(readyRead()), this, SLOT(onSocketRead()));
}

void JLNetPort::StopWork()
{
    terminate();
    QObject::disconnect(p_Socket, SIGNAL(readyRead()), this, SLOT(onSocketRead()));
}

void JLNetPort::onSocketRead()
{
    QByteArray datas = readData();
    if(datas.size() > 0)
    {
        mtx_receiver_buffer.lock();
        receive_buffer.append(datas);
        mtx_receiver_buffer.unlock();
    }
}

QByteArray JLNetPort::parseData() {
    uint32_t rn;
    QByteArray ret = protocal->parseData(receive_buffer, &rn);
    mtx_receiver_buffer.lock();
    receive_buffer.remove(0, rn);
    mtx_receiver_buffer.unlock();
    return ret;
}
