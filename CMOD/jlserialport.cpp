#include "jlserialport.h"

JLSerialPort::JLSerialPort(QObject *parent) : portReceiver(parent)
{
    m_port = nullptr;
}

QList<QString> JLSerialPort::getPortNames() {
    QList<QSerialPortInfo> port_infos = QSerialPortInfo::availablePorts();
    QList<QString> ret;
    QSerialPortInfo item;
    foreach (item, port_infos) {
        ret.append(item.portName());
    }
    return ret;
}

bool JLSerialPort::openPort(QString PortName, int Baudary) {
    m_port = new QSerialPort(this);
    m_port->setPortName(PortName);
    m_port->setBaudRate(Baudary, QSerialPort::AllDirections);
    bool ret = m_port->open(QIODevice::ReadWrite);
    m_port->setStopBits(QSerialPort::OneStop);
    m_port->setParity(QSerialPort::NoParity);
    m_port->setReadBufferSize(20480);
    m_port->setDataBits(QSerialPort::Data8);
    m_port->setFlowControl(QSerialPort::NoFlowControl);
    return ret;
}

bool JLSerialPort::openPort(QString PortName) {
    return openPort(PortName, QSerialPort::Baud115200);
}

QByteArray JLSerialPort::readData() {
    QByteArray ret;
    ret = m_port->read(1024);
    return ret;
}

QByteArray JLSerialPort::parseData() {
    qDebug()<<"HH";
    qDebug()<<receive_buffer;
    mtx_receiver_buffer.lock();
    receive_buffer.clear();
    mtx_receiver_buffer.unlock();
    return QByteArray();
}

void JLSerialPort::writeData(QByteArray DataToWrite) {
    m_port->write(DataToWrite);
}


