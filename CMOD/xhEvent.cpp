#include "xhEvent.h"

JLEvent::JLEvent(QObject *parent) : QObject(parent)
{
    event_list.clear();
}

JLEvent::~JLEvent()
{

}

void JLEvent::setup(XhPort *pSerialPort)
{
    qDebug()<<"Setup!!";
    m_serial_port = pSerialPort;
    QObject::connect(m_serial_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(commandAccept(uint8_t, uint8_t, QByteArray)));
}

bool JLEvent::wait(uint8_t Command, uint8_t SubCode, uint8_t *pDataSend, uint8_t *pDataReply)
{

}

void JLEvent::test()
{
    qDebug()<<"aaa";
}

void JLEvent::commandAccept(uint8_t Command, uint8_t SubCode, QByteArray Data)
{
    qDebug()<<"aaa";
    qDebug()<<Command;
    qDebug()<<SubCode;
    qDebug()<<Data;
}
