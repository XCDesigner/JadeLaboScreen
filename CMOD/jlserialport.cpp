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
    protocal = new JLProtocal(0x30);
    QObject::connect(m_port, SIGNAL(readyRead()), this, SLOT(onSerialRead()));
    start();
    return ret;
}

void JLSerialPort::onSerialRead()
{
    QByteArray datas;
    if(m_port->isOpen())
        datas = m_port->readAll();
    if(datas.size() > 0)
    {
        mtx_receiver_buffer.lock();
        receive_buffer.append(datas);
        mtx_receiver_buffer.unlock();
    }
}

bool JLSerialPort::openPort(QString PortName) {
    return openPort(PortName, QSerialPort::Baud115200);
}

QByteArray JLSerialPort::readData() {
    QByteArray ret;
    if(m_port->isOpen())
        ret = m_port->read(512);
    return ret;
}

QByteArray JLSerialPort::parseData() {
    uint32_t rn;
    QByteArray ret = protocal->parseData(receive_buffer, &rn);
    mtx_receiver_buffer.lock();
    receive_buffer.remove(0, rn);
    mtx_receiver_buffer.unlock();
    return ret;
}

void JLSerialPort::write(QByteArray DataToWrite) {
    writeData(DataToWrite);
}

void JLSerialPort::writeData(QByteArray DataToWrite) {
    if(m_port->isOpen())
        m_port->write(DataToWrite);
}

void JLSerialPort::writeProtocalData(QByteArray SourceData) {
    QByteArray pack_data = protocal->setupPackage(SourceData);
    writeData(pack_data);
}


