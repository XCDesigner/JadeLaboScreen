#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::changeHotendPageInit()
{
    QString btnText[] = {"L Hotendd", "R Hotendd", "Previous", "Next", "Previous", "Next", "Previous", "Next", "Previous", "Removed", "Previous", "Installed", "Finish", "GoCalibratetion"};
    QString btnBackColor[] = {"#ff630b", "#ff630b", "#434343", "#ff630b", "#434343", "#ff630b", "#434343", "#ff630b", "#434343", "#ff630b", "#434343", "#ff630b", "#ff630b", "#ff630b"};
    QQuickWidget *pbutton[14];
    pbutton[0] = ui->qw_btnChangeHotend_0;
    pbutton[1] = ui->qw_btnChangeHotend_1;
    pbutton[2] = ui->qw_btnChangeHotend_2;
    pbutton[3] = ui->qw_btnChangeHotend_3;
    pbutton[4] = ui->qw_btnChangeHotend_4;
    pbutton[5] = ui->qw_btnChangeHotend_5;
    pbutton[6] = ui->qw_btnChangeHotend_6;
    pbutton[7] = ui->qw_btnChangeHotend_7;
    pbutton[8] = ui->qw_btnChangeHotend_8;
    pbutton[9] = ui->qw_btnChangeHotend_9;
    pbutton[10] = ui->qw_btnChangeHotend_10;
    pbutton[11] = ui->qw_btnChangeHotend_11;
    pbutton[12] = ui->qw_btnChangeHotend_12;
    pbutton[13] = ui->qw_btnChangeHotend_13;

    for(uint i=0;i<14;i++)
    {
        pbutton[i]->setSource(QUrl("qrc:/qml/JLPushedButton.qml"));
        pbutton[i]->setClearColor(QColor(qmlColor));
        pbutton[i]->rootObject()->setProperty("text", btnText[i]);
        pbutton[i]->rootObject()->setProperty("color", btnBackColor[i]);
    }

    ui->qw_heatingUnitChangehotend_L->rootObject()->setProperty("text", "200°C");
    ui->qw_heatingUnitChangehotend_R->rootObject()->setProperty("text", "200°C");


    QObject::connect(pbutton[0]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onChangeHotend_btnClick_0(int)));
    QObject::connect(pbutton[1]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onChangeHotend_btnClick_1(int)));
    QObject::connect(pbutton[2]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onChangeHotend_btnClick_2(int)));
    QObject::connect(pbutton[3]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onChangeHotend_btnClick_3(int)));
    QObject::connect(pbutton[4]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onChangeHotend_btnClick_4(int)));
    QObject::connect(pbutton[5]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onChangeHotend_btnClick_5(int)));
    QObject::connect(pbutton[6]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onChangeHotend_btnClick_6(int)));
    QObject::connect(pbutton[7]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onChangeHotend_btnClick_7(int)));
    QObject::connect(pbutton[8]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onChangeHotend_btnClick_8(int)));
    QObject::connect(pbutton[9]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onChangeHotend_btnClick_9(int)));
    QObject::connect(pbutton[10]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onChangeHotend_btnClick_10(int)));
    QObject::connect(pbutton[11]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onChangeHotend_btnClick_11(int)));
    QObject::connect(pbutton[12]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onChangeHotend_btnClick_12(int)));
    QObject::connect(pbutton[13]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onChangeHotend_btnClick_13(int)));

    ui->qw_heatingUnitChangehotend_L->rootObject()->setProperty("indicatorIcon", "qrc:/image/LeftHotendIndecator.png");
    ui->qw_heatingUnitChangehotend_L->rootObject()->setProperty("indicatorText", "Left Extruder");
    ui->qw_heatingUnitChangehotend_L->rootObject()->setProperty("extrudeEnable", false);
    QObject::connect(ui->qw_heatingUnitChangehotend_L->rootObject(), SIGNAL(choseTempClicked()), this, SLOT(changeHotendLeftSetTemp()));
    QObject::connect(ui->qw_heatingUnitChangehotend_L->rootObject(), SIGNAL(extruderClicked()), this, SLOT(changeHotendLeftExtrude()));
    QObject::connect(ui->qw_heatingUnitChangehotend_L->rootObject(), SIGNAL(retackClicked()), this, SLOT(changeHotendLeftRetract()));

    ui->qw_heatingUnitChangehotend_R->rootObject()->setProperty("indicatorIcon", "qrc:/image/RightHotendIndecator.png");
    ui->qw_heatingUnitChangehotend_R->rootObject()->setProperty("indicatorText", "Right Extruder");
    ui->qw_heatingUnitChangehotend_R->rootObject()->setProperty("extrudeEnable", false);
    QObject::connect(ui->qw_heatingUnitChangehotend_R->rootObject(), SIGNAL(choseTempClicked()), this, SLOT(changeHotendRightSetTemp()));
    QObject::connect(ui->qw_heatingUnitChangehotend_R->rootObject(), SIGNAL(extruderClicked()), this, SLOT(changeHotendRightExtrude()));
    QObject::connect(ui->qw_heatingUnitChangehotend_R->rootObject(), SIGNAL(retackClicked()), this, SLOT(changeHotendRightRetract()));
}

void MainWindow::on_pushButton_176_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeHotend_0);
}

void MainWindow::onChangeHotend_btnClick_0(int) 
{
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeHotend_1);
}

void MainWindow::onChangeHotend_btnClick_1(int) 
{
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeHotend_1);
}

void MainWindow::onChangeHotend_btnClick_2(int) 
{
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeHotend_0);
}

void MainWindow::onChangeHotend_btnClick_3(int) 
{
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeHotend_2);
}

void MainWindow::onChangeHotend_btnClick_4(int) 
{
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeHotend_1);
}

void MainWindow::onChangeHotend_btnClick_5(int) 
{
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeHotend_3);
}

void MainWindow::onChangeHotend_btnClick_6(int) 
{
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeHotend_2);
}

void MainWindow::onChangeHotend_btnClick_7(int) 
{
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeHotend_5);
}

void MainWindow::onChangeHotend_btnClick_8(int) 
{
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeHotend_3);
}

void MainWindow::onChangeHotend_btnClick_9(int) 
{
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeHotend_6);
}

void MainWindow::onChangeHotend_btnClick_10(int) 
{
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeHotend_5);
}

void MainWindow::onChangeHotend_btnClick_11(int) 
{
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeHotend_7);
}

void MainWindow::onChangeHotend_btnClick_12(int) 
{
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::onChangeHotend_btnClick_13(int) 
{
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::changeHotendLeftSetTemp()
{
    pdlg_choose_extruder_temp = new ChooseExtruderTemp();
    QByteArray init_data;
    init_data.append(1, 0);
    pdlg_choose_extruder_temp->init(init_data);
    QObject::connect(pdlg_choose_extruder_temp, SIGNAL(hideWidget()), this, SLOT(changeHotendSetTemp()), Qt::QueuedConnection);
    changeFilamentSelectExtruder = 0;
    pdlg_choose_extruder_temp->show();
}

void MainWindow::changeHotendSetTemp()
{
    QList<QByteArray> ret = pdlg_choose_extruder_temp->get_return_value();
    int index = ret.at(0).toUInt();
    if(index == 0)
    {
        ui->qw_heatingUnitChangehotend_L->rootObject()->setProperty("text", ret.at(1) + "°C");
    }
    else
    {
        ui->qw_heatingUnitChangehotend_R->rootObject()->setProperty("text", ret.at(1) + "°C");
    }
    m_port->setHeattingUnit(index, ret.at(1).toUInt());
    delete pdlg_choose_extruder_temp;
}

void MainWindow::changeHotendLeftExtrude()
{
    m_port->ldown();
}

void MainWindow::changeHotendLeftRetract()
{
    m_port->lup();
}

void MainWindow::changeHotendRightSetTemp()
{
    pdlg_choose_extruder_temp = new ChooseExtruderTemp();
    QByteArray init_data;
    init_data.append(1, 1);
    pdlg_choose_extruder_temp->init(init_data);
    QObject::connect(pdlg_choose_extruder_temp, SIGNAL(hideWidget()), this, SLOT(changeHotendSetTemp()), Qt::QueuedConnection);
    changeFilamentSelectExtruder = 1;
    pdlg_choose_extruder_temp->show();
}

void MainWindow::changeHotendRightExtrude()
{
    m_port->rdown();
}

void MainWindow::changeHotendRightRetract()
{
    m_port->rup();
}

