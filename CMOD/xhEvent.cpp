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
    m_serial_port->writeCustomData(pDataSend);
    command_to_wait = pDataSend[0];
    subcode_to_wait = pDataSend[1];
    wait_type = WAIT_TYPE_PAGE;
}

/**
  * @brief  Send serial command and wait reply
  * @param  pDataSend: Data to send
  * @param  pDataReply: Data received
  * @param  Timeout:  Time to wait in microsecnods. 0 for always waiting.
  * @retval None
  */
void JLEvent::waitDialog(QByteArray pDataSend, uint8_t Timeout)
{
    m_serial_port->writeCustomData(pDataSend);
    command_to_wait = pDataSend[0];
    subcode_to_wait = pDataSend[1];
    wait_type = WAIT_TYPE_DIALOG;
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
        if(wait_type == WAIT_TYPE_PAGE)
            emit changePageAccept(Data);
        else if(wait_type == WAIT_TYPE_DIALOG)
            emit changeDialogAccept(Data);
    }
}
