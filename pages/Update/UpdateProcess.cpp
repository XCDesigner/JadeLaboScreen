#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::updateFileAnalize()
{
    QFile *file = new QFile(UpdateFile);
    if(file->open(QIODevice::ReadOnly) == true)
    {
        printerUpdateFileBuffer = file->readAll();
        printerUpdatePacks = printerUpdateFileBuffer.size() / 512;
        if(printerUpdateFileBuffer.size() % 512 != 0)
            printerUpdatePacks++;
    }
}

void MainWindow::startUpdatePrinter()
{
    m_port->startUpdate();
    printTimer->stop();
    QObject::connect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(updateCommandProcess(uint8_t, uint8_t, QByteArray)), Qt::QueuedConnection);
}

void MainWindow::sendPrinterUpdatePack(uint16_t PackIndex)
{
    QByteArray s;
    uint16_t read_len;
    s.append(1, PackIndex);
    s.append(1, (PackIndex >> 8));
    if(PackIndex == (printerUpdatePacks - 1))
        read_len = printerUpdateFileBuffer.size() - 512 * PackIndex;
    else
        read_len = 512;
    s.append(printerUpdateFileBuffer.mid(PackIndex * 512), read_len);
    m_port->sendUpdateData(s);
}

void MainWindow::sendEndUpdatePrinter()
{
    m_port->sendEndUpdate();
}

void MainWindow::startUpdateScreen()
{

}

void MainWindow::updateCommandProcess(uint8_t Command, uint8_t SubCode, QByteArray Datas)
{
    if(Command == 0x05)
    {
        if(SubCode == 0x00)
        {
            if(Datas.at(2) != 0)
            {
                qDebug()<<"Start update fail!";
            }
        }
        else if(SubCode == 0x01)
        {
            uint16_t req_pack;
            req_pack = ((uint8_t)Datas.at(3) << 8) | Datas.at(2);
            if(req_pack < printerUpdatePacks)
                sendPrinterUpdatePack(req_pack);
            else
                sendEndUpdatePrinter();
        }
        else if(SubCode == 0x02)
        {
            QObject::connect(this, SIGNAL(printUpdateCompleted), this, SLOT(startUpdateScreen), Qt::QueuedConnection);
        }
    }
}
