#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::ListenerInit()
{
    QObject::connect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(onMessageListen(uint8_t, uint8_t, QByteArray)));
    AddListen(QByteArray(QByteArray::fromHex("0100")), &MainWindow::TestListener, true);
}

void MainWindow::onMessageListen(uint8_t Command, uint8_t SubCode, QByteArray MessageData)
{
    if(lst_listen_item.count() > 0)
    {
        foreach(ListenerItem tmp, lst_listen_item)
        {
            if(MessageData.startsWith(tmp.Data))
            {
                if(tmp.Callback != NULL)
                    (this->*tmp.Callback)(MessageData);
                if(tmp.Repeated == false)
                    lst_listen_item.removeOne(tmp);
            }
        }
    }
}

void MainWindow::AddListen(QByteArray MatchData, pFunction Callback = NULL, bool Repeated = true)
{
    ListenerItem newItem;
    newItem.Data = MatchData;
    newItem.Repeated = Repeated;
    newItem.Callback = Callback;
    lst_listen_item.append(newItem);
}

void MainWindow::TestListener(QByteArray Datas)
{
    qDebug()<<"Listen arrived";
}
