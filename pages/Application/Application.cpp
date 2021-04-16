#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::blockingChangePage(QByteArray Command, QWidget *pPage)
{
    m_event->wait(Command, 5);
    pNextShowPage = pPage;
    ui->stackedWidget->setCurrentWidget(ui->page_Masker);
}

void MainWindow::blockingChangeDialog(QByteArray Command, JLWidget *pDialog)
{
    pDialogToShow = pDialog;
    if(Command.size() == 0)
    {
        m_event->waitDialog(Command, 5);
        pNextShowPage = ui->stackedWidget->currentWidget();
        ui->stackedWidget->setCurrentWidget(ui->page_Masker);
    }
    else
    {
        pDialogToShow->init(QByteArray());
        pDialogToShow->show();
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
