#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::changeFilamentPageInit()
{
    ui->labChangeFilamentLeft->setIndicator(0);
    ui->labChangeFilamentRight->setIndicator(1);
    QObject::connect(ui->labChangeFilamentLeft, SIGNAL(chooseTempClicked()), this, SLOT(changeFilamentLeftSetTemp()));
    QObject::connect(ui->labChangeFilamentLeft, SIGNAL(extrudeClicked()), this, SLOT(changeFilamentLeftExtrude()));
    QObject::connect(ui->labChangeFilamentLeft, SIGNAL(retractClicked()), this, SLOT(changeFilamentLeftRetract()));

    QObject::connect(ui->labChangeFilamentRight, SIGNAL(chooseTempClicked()), this, SLOT(changeFilamentRightSetTemp()));
    QObject::connect(ui->labChangeFilamentRight, SIGNAL(extrudeClicked()), this, SLOT(changeFilamentRightExtrude()));
    QObject::connect(ui->labChangeFilamentRight, SIGNAL(retractClicked()), this, SLOT(changeFilamentRightRetract()));
}

void MainWindow::changeFilamentPageLoad()
{
    strMachineStatus new_status;
    m_port->getXhPage()->GetMachineStatus(&new_status);
    ui->labChangeFilamentLeft->setValue(new_status.TarTemp[0]);
    ui->labChangeFilamentRight->setValue(new_status.TarTemp[1]);
    screen_status.setPerformance(CHANGE_FILAMENT);
    ui->labChangeFilamentLeft->setExtruderEnable(false);
    ui->labChangeFilamentRight->setExtruderEnable(false);
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
            ui->labChangeFilamentLeft->setExtruderEnable(true);
        }
        else
        {
            ui->labChangeFilamentLeft->setExtruderEnable(false);
        }
        if((new_status.CurTemp[1] > (new_status.TarTemp[1] - 5)) && (new_status.TarTemp[1] > 0))
        {
            ui->labChangeFilamentRight->setExtruderEnable(true);
        }
        else
        {
            ui->labChangeFilamentRight->setExtruderEnable(false);
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
        ui->labChangeFilamentLeft->setValue(ret.at(1).toUInt());
    }
    else
    {
        ui->labChangeFilamentRight->setValue(ret.at(1).toUInt());
    }
    m_port->setHeattingUnit(index, ret.at(1).toUInt());
    pdlg_choose_extruder_temp->close();
    delete pdlg_choose_extruder_temp;
}

void MainWindow::changeFilamentLeftExtrude()
{
    m_port->LoadFilament(0);
}

void MainWindow::changeFilamentLeftRetract()
{
    m_port->UnloadFilament(0);
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
    m_port->LoadFilament(1);
}

void MainWindow::changeFilamentRightRetract()
{
    m_port->UnloadFilament(1);
}

void MainWindow::on_pushButton_359_clicked()
{
    screen_status.setPerformance(IDLE);
    ui->labChangeFilamentLeft->setValue(0);
    ui->labChangeFilamentRight->setValue(0);
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
