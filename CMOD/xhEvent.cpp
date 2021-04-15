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

/**
  * @brief  Send serial command and wait reply
  * @param  pDataSend: Data to send
  * @param  pDataReply: Data received
  * @param  Timeout:  Time to wait in microsecnods. 0 for always waiting.
  * @retval None
  */
void JLEvent::wait(QByteArray pDataSend, uint8_t Timeout)
{
    QByteArray pack_data;
    pack_data.resize(0);
    pack_data.append(pDataSend);

    QByteArray buff;
    buff = m_serial_port->getXhPage()->groupPage(pack_data);
    m_serial_port->getSerialPort()->write(buff);

    command_to_wait = pDataSend[0];
    subcode_to_wait = pDataSend[1];
}

void JLEvent::test()
{
    qDebug()<<"aaa";
}

void JLEvent::commandAccept(uint8_t Command, uint8_t SubCode, QByteArray Data)
{
    if((Command == command_to_wait) && (subcode_to_wait == SubCode))
    {
        command_to_wait = 0xff;
        subcode_to_wait = 0xff;
        bytes_accept = Data;
        emit changePageAccept(Data);
    }
}
