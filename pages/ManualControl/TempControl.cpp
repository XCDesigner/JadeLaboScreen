#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::TempControlInit() {
    ui->qw_LeftHeatingUnit->rootObject()->setProperty("unitIndicator", 0);
    ui->qw_LeftHeatingUnit->setClearColor(QColor(qmlColor));
    ui->qw_RightHeatingUnit->rootObject()->setProperty("unitIndicator", 1);
    ui->qw_RightHeatingUnit->setClearColor(QColor(qmlColor));
    ui->qw_BedHeatingUnit->setClearColor(QColor(qmlColor));

    QObject::connect(ui->qw_LeftHeatingUnit->rootObject(), SIGNAL(choseTempClicked(int)), this, SLOT(tempControlChooseExtrudeTemp(int)));
    QObject::connect(ui->qw_LeftHeatingUnit->rootObject(), SIGNAL(cooldownClicked(int)), this, SLOT(tempControlExtruderCooldown(int)));

    QObject::connect(ui->qw_RightHeatingUnit->rootObject(), SIGNAL(choseTempClicked(int)), this, SLOT(tempControlChooseExtrudeTemp(int)));
    QObject::connect(ui->qw_RightHeatingUnit->rootObject(), SIGNAL(cooldownClicked(int)), this, SLOT(tempControlExtruderCooldown(int)));

    QObject::connect(ui->qw_BedHeatingUnit->rootObject(), SIGNAL(choseTempClicked()), this, SLOT(tempControlChooseBedTemp()));
    QObject::connect(ui->qw_BedHeatingUnit->rootObject(), SIGNAL(cooldownClicked()), this, SLOT(tempControlBedCooldown()));
}

void MainWindow::tempControlChooseExtrudeTemp(int Index) {
    pdlg_choose_extruder_temp = new ChooseExtruderTemp();
    QByteArray init_data;
    init_data.append(1, Index);
    pdlg_choose_extruder_temp->init(init_data);
    pdlg_choose_extruder_temp->show();
    QObject::connect(pdlg_choose_extruder_temp, SIGNAL(hideWidget()), this, SLOT(tempControlChooseExtruderTempReturn()), Qt::QueuedConnection);
}

void MainWindow::tempControlExtruderCooldown(int Index) {
    m_port->setHeattingUnit(Index, 0);
    if(Index == 0)
        ui->qw_LeftHeatingUnit->rootObject()->setProperty("value", 0);
    else
        ui->qw_RightHeatingUnit->rootObject()->setProperty("value", 0);
}

void MainWindow::tempControlChooseBedTemp() {
    pdlg_choose_bed_temp = new ChooseBedTemp();
    pdlg_choose_bed_temp->init(QByteArray());
    pdlg_choose_bed_temp->show();
    QObject::connect(pdlg_choose_bed_temp, SIGNAL(hideWidget()), this, SLOT(tempControlChooseBedTempReturn()), Qt::QueuedConnection);
}

void MainWindow::tempControlBedCooldown() {
    m_port->setHeattingUnit(2, 0);
    ui->qw_BedHeatingUnit->rootObject()->setProperty("value", 0);
}

void MainWindow::tempControlChooseExtruderTempReturn() {
    QList<QByteArray> ret = pdlg_choose_extruder_temp->get_return_value();
    int index = ret.at(0).toUInt();
    int temp = ret.at(1).toUInt();
    m_port->setHeattingUnit(index, temp);
    if(index == 0)
        ui->qw_LeftHeatingUnit->rootObject()->setProperty("value", ret.at(1).toInt());
    else
        ui->qw_RightHeatingUnit->rootObject()->setProperty("value", ret.at(1).toInt());
    delete pdlg_choose_extruder_temp;
}

void MainWindow::tempControlChooseBedTempReturn() {
    QList<QByteArray> ret = pdlg_choose_bed_temp->get_return_value();
    int temp = ret.at(0).toUInt();
    m_port->setHeattingUnit(2, temp);
    ui->qw_BedHeatingUnit->rootObject()->setProperty("value", ret.at(0).toInt());
    delete pdlg_choose_bed_temp;
}
