#include "portreceiver.h"

portReceiver::portReceiver(QObject *parent) : QThread(parent)
{

}

void portReceiver::run()
{
    while(true){
        QByteArray tmp_data = readData();
        if(tmp_data.size() > 0) {
            mtx_receiver_buffer.lock();
            receive_buffer.append(tmp_data);
            mtx_receiver_buffer.unlock();
        }
        if(receive_buffer.size() > 0) {
            tmp_data = parseData();
            if(tmp_data.size() > 0) {
                emit sigDataParsed(tmp_data);
            }
        } else {
          msleep(1000);
        }
    }
}

QByteArray portReceiver::parseData() {
    qDebug()<<"Parse data unremaped!";
    msleep(200);
    QByteArray nop;
    return nop;
}

QByteArray portReceiver::readData()
{
    qDebug()<<"Read data unremaped!";
    msleep(200);
    QByteArray nop;
    return nop;
}
