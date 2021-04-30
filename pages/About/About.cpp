#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CMOD/XhUpdater.h"
#include <QThread>

void MainWindow::AboutPageInit()
{
    QObject::connect(ui->wqVersion->rootObject(), SIGNAL(), this, SLOT(onAboutReturn));
}

void MainWindow::on_pushButton_126_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_About);
    char version[30];
    sprintf(version, "Ver:%s-%s", __DATE__, __TIME__);
    ui->wqVersion->rootObject()->setProperty("text", version);
}

void MainWindow::on_AboutReturn()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}
