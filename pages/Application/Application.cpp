#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::blockingChangePage(QByteArray Command, QWidget *pPage)
{
    m_event->wait(Command, 5);
    pNextShowPage = pPage;
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

void MainWindow::changePageCallback(QByteArray ReplyData)
{
    ui->stackedWidget->setCurrentWidget(pNextShowPage);
}

void MainWindow::changeDialogCallback(QByteArray ReplyData)
{
    pDialogToShow->init(ReplyData);
    pDialogToShow->show();
    ui->stackedWidget->setCurrentWidget(pNextShowPage);
}
