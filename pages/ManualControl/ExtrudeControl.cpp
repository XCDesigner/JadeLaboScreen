#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::ExtrudeControlInit()
{
    ui->qw_ExtrudeSelect->setClearColor("#202020");
    ui->qw_Extrude->setClearColor("#202020");
    QObject::connect(ui->qw_Extrude->rootObject(), SIGNAL(chooseTempClicked(int)), this, SLOT(extrudeControlChooseTemp(int)));
    QObject::connect(ui->qw_Extrude->rootObject(), SIGNAL(chooseDistanceClicked(int)), this, SLOT(extrudeControlChooseDistance(int)));
    QObject::connect(ui->qw_Extrude->rootObject(), SIGNAL(extrudeClicked(int)), this, SLOT(extrudeControlExtrude(int)));
    QObject::connect(ui->qw_Extrude->rootObject(), SIGNAL(retractClicked(int)), this, SLOT(extrudeControlRetract(int)));
    QObject::connect(ui->qw_Extrude->rootObject(), SIGNAL(cooldownClicked(int)), this, SLOT(extrudeControlCooldown(int)));
    QObject::connect(ui->qw_ExtrudeSelect->rootObject(), SIGNAL(clicked(int)), this, SLOT(extrudeControlSelectExtruder(int)));
}

void MainWindow::extrudeControlChooseTemp(int Index)
{
    pdlg_choose_extruder_temp = new ChooseExtruderTemp();
    QByteArray init_data;
    init_data.append(1, Index);
    pdlg_choose_extruder_temp->init(init_data);
    pdlg_choose_extruder_temp->show();
    QObject::connect(pdlg_choose_extruder_temp, SIGNAL(hideWidget()), this, SLOT(extrudeControlChooseTempReturn()), Qt::QueuedConnection);
}

void MainWindow::extrudeControlCooldown(int Index)
{
    ui->qw_Extrude->rootObject()->setProperty("temp", 0);
    m_port->setHeattingUnit(Index, 0);
}

void MainWindow::extrudeControlChooseDistance(int Index)
{
    pdlg_choose_distance = new ChooseDistance();
    QByteArray init_data;
    init_data.append(1, Index);
    pdlg_choose_distance->init(init_data);
    pdlg_choose_distance->show();
    QObject::connect(pdlg_choose_distance, SIGNAL(hideWidget()), this, SLOT(extrudeControlChooseDistanceReturn()), Qt::QueuedConnection);
}

void MainWindow::extrudeControlExtrude(int Index)
{
    float dis = ui->qw_Extrude->rootObject()->property("distance").toFloat() * 1000.0f;
    m_port->ExtruderMotion(Index, dis);
}

void MainWindow::extrudeControlRetract(int Index)
{
    float dis = ui->qw_Extrude->rootObject()->property("distance").toFloat() * -1000.0f;
    m_port->ExtruderMotion(Index, dis);
}

void MainWindow::extrudeControlSelectExtruder(int Index)
{
    qDebug()<<Index;
    ui->qw_Extrude->rootObject()->setProperty("indicator", Index);
}

void MainWindow::extrudeControlChooseTempReturn()
{
    QList<QByteArray> ret = pdlg_choose_extruder_temp->get_return_value();
    int index = ret.at(0).toUInt();
    int temp = ret.at(1).toUInt();
    m_port->setHeattingUnit(index, temp);
    ui->qw_Extrude->rootObject()->setProperty("temp", temp);
    delete pdlg_choose_extruder_temp;
}

void MainWindow::extrudeControlChooseDistanceReturn()
{
    QList<QByteArray> ret = pdlg_choose_distance->get_return_value();
    QString str_distance = ret.at(1);
    ui->qw_Extrude->rootObject()->setProperty("distance", str_distance);
    delete pdlg_choose_distance;
}

void MainWindow::extruderControlCheckTemp()
{
    if(screen_status.getPerformance() == MANUAL_EXTRUDE) {
        int index = ui->qw_Extrude->rootObject()->property("indicator").toUInt();
        strMachineStatus cur_status;
        m_port->getXhPage()->GetMachineStatus(&cur_status);
        if(index == 0) {
            if(cur_status.CurTemp[0] > 175)
                ui->qw_Extrude->rootObject()->setProperty("enableMotor", true);
            else
                ui->qw_Extrude->rootObject()->setProperty("enableMotor", false);
        }
        else {
            if(cur_status.CurTemp[1] > 175)
                ui->qw_Extrude->rootObject()->setProperty("enableMotor", true);
            else
                ui->qw_Extrude->rootObject()->setProperty("enableMotor", false);
        }
        QTimer::singleShot(200, this, SLOT(extruderControlCheckTemp()));
    }
}

void MainWindow::on_pushButton_270_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_ExtrudeControl);
    screen_status.setPerformance(MANUAL_EXTRUDE);
    QTimer::singleShot(200, this, SLOT(extruderControlCheckTemp()));
}

void MainWindow::on_pushButton_141_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_457_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeFilament);
}

void MainWindow::on_pushButton_458_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}
