#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::changeFilamentPageInit()
{
    screen_status.setPerformance(CHANGE_FILAMENT);
    QTimer::singleShot(500, this, SLOT(changeFilamentTempChecking()));
}

void MainWindow::changeFilamentTempChecking()
{
    strMachineStatus new_status;
    m_port->getXhPage()->GetMachineStatus(&new_status);
    if(screen_status.getPerformance() == CHANGE_FILAMENT)
    {
        if(new_status.CurTemp[0] > 180)
        {
            ui->qw_LeftHeating->rootObject()->setProperty("extrudeEnable", true);
        }
        else
        {
            ui->qw_LeftHeating->rootObject()->setProperty("extrudeEnable", false);
        }
        if(new_status.CurTemp[1] > 180)
        {
            ui->qw_RightHeating->rootObject()->setProperty("extrudeEnable", true);
        }
        else
        {
            ui->qw_RightHeating->rootObject()->setProperty("extrudeEnable", false);
        }
        QTimer::singleShot(500, this, SLOT(changeFilamentTempChecking()));
    }
}

void MainWindow::leftSetTemp()
{
    mchoose = new chooseTemp(this);
    mchoose->init(QByteArray());
    QObject::connect(mchoose, SIGNAL(hideWidget()), this, SLOT(onSetTemp()), Qt::QueuedConnection);
    changeFilamentSelectExtruder = 0;
    mchoose->show();
}

void MainWindow::onSetTemp()
{
    QList<QByteArray> ret = mchoose->get_return_value();
    if(ret[0].toInt() != 0)
    {
        ui->pushButton_113->setEnabled(false);
        ui->pushButton_117->setEnabled(false);
        ui->pushButton_118->setEnabled(false);
    }
    else
    {
        ui->pushButton_113->setEnabled(true);
        ui->pushButton_117->setEnabled(true);
        ui->pushButton_118->setEnabled(true);
    }
    if(changeFilamentSelectExtruder == 0)
    {
        ui->qw_LeftHeating->rootObject()->setProperty("text", ret[0] + "°C");
    }
    else
    {
        ui->qw_RightHeating->rootObject()->setProperty("text", ret[0] + "°C");
    }
    m_port->setHeattingUnit(changeFilamentSelectExtruder, ret[0].toUInt());
    delete mchoose;
}


void MainWindow::leftExtrude()
{
    m_port->ldown();
}

void MainWindow::leftRetract()
{
    m_port->lup();
}

void MainWindow::rightSetTemp()
{
    mchoose = new chooseTemp(this);
    mchoose->init(QByteArray());
    QObject::connect(mchoose, SIGNAL(hideWidget()), this, SLOT(onSetTemp()), Qt::QueuedConnection);
    changeFilamentSelectExtruder = 1;
    mchoose->show();
}

void MainWindow::rightExtrude()
{
    m_port->rdown();
}

void MainWindow::rightRetract()
{
    m_port->rup();
}

void MainWindow::on_pushButton_359_clicked()
{
    ui->qw_LeftHeating->rootObject()->setProperty("text", "0°C");
    ui->qw_RightHeating->rootObject()->setProperty("text", "0°C");
    m_port->setHeattingUnit("0","0");
    ui->pushButton_113->setEnabled(true);
    ui->pushButton_117->setEnabled(true);
    ui->pushButton_118->setEnabled(true);
}

void MainWindow::on_pushButton_113_clicked()
{
    screen_status.setPerformance(IDLE);
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_117_clicked()
{
    screen_status.setPerformance(IDLE);
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}
