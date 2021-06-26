#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::blockingChangePage(QByteArray Command, QWidget *pPage, bool NeedProcessingPage)
{
    m_event->wait(Command, 5);
    pNextShowPage = pPage;
    if(NeedProcessingPage == true)
        ui->stackedWidget->setCurrentWidget(ui->page_Masker);
}

void MainWindow::changePageOnStatus(QByteArray Status, QWidget *pPage)
{
    pNextShowPage = pPage;
    ui->stackedWidget->setCurrentWidget(ui->page_Masker);
    statusWaiting = Status;
    QTimer::singleShot(1000, this, SLOT(waitforIdleStatus()));
}

void MainWindow::waitforIdleStatus()
{
    strMachineStatus new_status;
    m_port->getXhPage()->GetMachineStatus(&new_status);
    int status_count = statusWaiting.size();
    for(int i=0;i<status_count;i++) {
        if(new_status.Status == statusWaiting.at(i))
        {
            statusWaiting.clear();
            ui->stackedWidget->setCurrentWidget(pNextShowPage);
            return;
        }
    }
    QTimer::singleShot(1000, this, SLOT(waitforIdleStatus()));
}

void MainWindow::blockingChangeDialog(QByteArray Command, JLWidget *pDialog)
{
    pDialogToShow = pDialog;
    if(Command.size() == 0)
    {
        pDialogToShow->init(QByteArray());
        pDialogToShow->show();
    }
    else
    {
        m_event->waitDialog(Command, 5);
        pNextShowPage = ui->stackedWidget->currentWidget();
        ui->stackedWidget->setCurrentWidget(ui->page_Masker);
    }
}

void MainWindow::changeDialog(JLWidget *pDialog)
{
    QByteArray s;
    pDialogToShow = pDialog;
    pDialogToShow->init(s);
    pDialogToShow->show();
}

void MainWindow::changePageCallback(QByteArray &ReplyData)
{
    ui->stackedWidget->setCurrentWidget(pNextShowPage);
}

void MainWindow::changeDialogCallback(QByteArray &ReplyData)
{
    pDialogToShow->init(ReplyData);
    pDialogToShow->show();
    ui->stackedWidget->setCurrentWidget(pNextShowPage);
}

void MainWindow::ListenerInit()
{
    QObject::connect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray &)), this, SLOT(onMessageListen(uint8_t, uint8_t, QByteArray &)));
    // AddListen(QByteArray(QByteArray::fromHex("0100")), &MainWindow::TestListener, true);
}

void MainWindow::onMessageListen(uint8_t Command, uint8_t SubCode, QByteArray &MessageData)
{
    // bool found = false;
    // QByteArray s;
    // s.append(1, Command);
    // s.append(1, SubCode);
    // foreach(QByteArray tmp, command_received_list)
    // {
    //     if(tmp == s)
    //     {
    //         found = true;
    //         break;
    //     }
    // }
    // if(found == false)
    // {
    //     command_received_list.append(s);
    //     qDebug()<<"New Command:" << s;
    // }
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

void MainWindow::TestListener(QByteArray &Datas)
{
    // qDebug()<<"Listen arrived";
}
