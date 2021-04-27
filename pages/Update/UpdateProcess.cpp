#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::updateProcessThread()
{

}

void MainWindow::updateFileAnalize()
{

}

void MainWindow::startUpdatePrinter()
{
    m_port->startUpdate();
}

void MainWindow::sendUpdatePack(uint16_t PackIndex)
{

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
            sendUpdatePack(req_pack);
        }
        else if(SubCode == 0x02)
        {

        }
    }
}
