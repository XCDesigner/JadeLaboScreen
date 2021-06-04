#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::changeFilamentPageInit()
{
    char temp[20];
    strMachineStatus new_status;
    m_port->getXhPage()->GetMachineStatus(&new_status);
    sprintf(temp, "%03d°C", new_status.TarTemp[0]);
    ui->qw_LeftHeating->rootObject()->setProperty("text", temp);
    sprintf(temp, "%03d°C", new_status.TarTemp[1]);
    ui->qw_RightHeating->rootObject()->setProperty("text", temp);
    screen_status.setPerformance(CHANGE_FILAMENT);
    ui->qw_LeftHeating->rootObject()->setProperty("extrudeEnable", false);
    ui->qw_RightHeating->rootObject()->setProperty("extrudeEnable", false);
    QTimer::singleShot(500, this, SLOT(changeFilamentTempChecking()));
}

void MainWindow::changeFilamentTempChecking()
{
    strMachineStatus new_status;
    m_port->getXhPage()->GetMachineStatus(&new_status);
    if(screen_status.getPerformance() == CHANGE_FILAMENT)
    {
        if((new_status.CurTemp[0] > (new_status.TarTemp[0] - 5)) && (new_status.TarTemp[0] > 0))
        {
            ui->qw_LeftHeating->rootObject()->setProperty("extrudeEnable", true);
        }
        else
        {
            ui->qw_LeftHeating->rootObject()->setProperty("extrudeEnable", false);
        }
        if((new_status.CurTemp[1] > (new_status.TarTemp[1] - 5)) && (new_status.TarTemp[1] > 0))
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

void MainWindow::changeFilamentLeftSetTemp()
{
    pdlg_choose_extruder_temp = new ChooseExtruderTemp();
    QByteArray init_data;
    init_data.append(1, 0);
    pdlg_choose_extruder_temp->init(init_data);
    QObject::connect(pdlg_choose_extruder_temp, SIGNAL(hideWidget()), this, SLOT(changeFilamentSetTemp()), Qt::QueuedConnection);
    changeFilamentSelectExtruder = 0;
    pdlg_choose_extruder_temp->show();
}

void MainWindow::changeFilamentSetTemp()
{
    QList<QByteArray> ret = pdlg_choose_extruder_temp->get_return_value();
    int index = ret.at(0).toUInt();
    int temp = ret.at(1).toUInt();
    if(temp != 0)
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
    if(index == 0)
    {
        ui->qw_LeftHeating->rootObject()->setProperty("text", ret.at(1) + "°C");
    }
    else
    {
        ui->qw_RightHeating->rootObject()->setProperty("text", ret.at(1) + "°C");
    }
    m_port->setHeattingUnit(index, ret.at(1).toUInt());
    delete pdlg_choose_extruder_temp;
}

void MainWindow::changeFilamentLeftExtrude()
{
    m_port->ldown();
}

void MainWindow::changeFilamentLeftRetract()
{
    m_port->lup();
}

void MainWindow::changeFilamentRightSetTemp()
{
    pdlg_choose_extruder_temp = new ChooseExtruderTemp();
    QByteArray init_data;
    init_data.append(1, 1);
    pdlg_choose_extruder_temp->init(init_data);
    QObject::connect(pdlg_choose_extruder_temp, SIGNAL(hideWidget()), this, SLOT(changeFilamentSetTemp()), Qt::QueuedConnection);
    changeFilamentSelectExtruder = 1;
    pdlg_choose_extruder_temp->show();
}

void MainWindow::changeFilamentRightExtrude()
{
    m_port->rdown();
}

void MainWindow::changeFilamentRightRetract()
{
    m_port->rup();
}

void MainWindow::on_pushButton_359_clicked()
{
    screen_status.setPerformance(IDLE);
    ui->qw_LeftHeating->rootObject()->setProperty("text", "000°C");
    ui->qw_RightHeating->rootObject()->setProperty("text", "000°C");
    m_port->setHeattingUnit("0","0");
    ui->pushButton_113->setEnabled(true);
    ui->pushButton_117->setEnabled(true);
    ui->pushButton_118->setEnabled(true);
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
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
