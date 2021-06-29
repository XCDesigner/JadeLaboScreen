#include "changefilamentdlg.h"
#include "ui_changefilamentdlg.h"

changeFilamentDlg::changeFilamentDlg(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::changeFilamentDlg)
{
    ui->setupUi(this);

    ui->qw_StatusNotice->setSource(QUrl("qrc:/qml/StatusBarNotice.qml"));
    ui->qw_StatusNotice->setClearColor("#2d2b2c");

    QObject::connect(ui->labLeftHeatingUnit, SIGNAL(chooseTempClicked()), this, SLOT(left_setTemp()));
    QObject::connect(ui->labLeftHeatingUnit, SIGNAL(extrudeClicked()), this, SLOT(left_extrude()));
    QObject::connect(ui->labLeftHeatingUnit, SIGNAL(retractClicked()), this, SLOT(left_retract()));
    ui->labLeftHeatingUnit->setIndicator(0);

    QObject::connect(ui->labRightHeatingUnit, SIGNAL(chooseTempClicked()), this, SLOT(right_setTemp()));
    QObject::connect(ui->labRightHeatingUnit, SIGNAL(extrudeClicked()), this, SLOT(right_extrude()));
    QObject::connect(ui->labRightHeatingUnit, SIGNAL(retractClicked()), this, SLOT(right_retract()));
    ui->labRightHeatingUnit->setIndicator(1);

    autoUpdateStatus = false;

    chooseTempDialog = new chooseTemp(this);
    chooseTempDialog->init();
    chooseTempDialog->hide();
}

changeFilamentDlg::~changeFilamentDlg()
{
    delete ui;
    delete chooseTempDialog;
}

void changeFilamentDlg::init(QByteArray &InitData)
{
    strMachineStatus cur_status;
    m_xhPort->getXhPage()->GetMachineStatus(&cur_status);
    chooseTempDialog = NULL;
    ret_value.clear();
}

void changeFilamentDlg::show()
{
    strScreenStatus status;
    char strtmp[32];

    pscreen_status->getStatus(&status);
    ui->qw_StatusNotice->rootObject()->setProperty("udiskVisible", pscreen_status->getUdiskStatus());
    ui->qw_StatusNotice->rootObject()->setProperty("wifiVisible", pscreen_status->getWifiStatus());
    ui->qw_StatusNotice->rootObject()->setProperty("lightVisible", true);

    sprintf(strtmp, "%03d°C", status.TargetTemp[0]);
    ui->labLeftHeatingUnit->setValue(status.TargetTemp[0]);
    sprintf(strtmp, "%03d°C", status.TargetTemp[1]);
    ui->labRightHeatingUnit->setValue(status.TargetTemp[1]);

    autoUpdateStatus = true;

    QTimer::singleShot(500, this, SLOT(updateStatusBar()));

    QObject::connect(chooseTempDialog, SIGNAL(hideWidget()), this, SLOT(onSetTemp()));
    QWidget::show();
}

void changeFilamentDlg::updateStatusBar()
{
    strScreenStatus status;
    pscreen_status->getStatus(&status);
    char strtmp[32];

    sprintf(strtmp, "%03d|%03d", status.CurrentTemp[0], status.TargetTemp[0]);
    ui->label_131->setText(strtmp);

    sprintf(strtmp, "%03d|%03d", status.CurrentTemp[1], status.TargetTemp[1]);
    ui->label_133->setText(strtmp);

    sprintf(strtmp, "%03d|%03d", status.CurrentTemp[2], status.TargetTemp[2]);
    ui->label_30->setText(strtmp);

    if(autoUpdateStatus == true)
    {
        QTimer::singleShot(500, this, SLOT(updateStatusBar()));
    }
}

void changeFilamentDlg::setXHPort(XhPort *pPort)
{
    m_xhPort = pPort;
}

void changeFilamentDlg::left_setTemp()
{
    extruder_selected = 0;
    chooseTempDialog->show();
}

void changeFilamentDlg::right_setTemp()
{
    extruder_selected = 1;
    chooseTempDialog->show();
}

void changeFilamentDlg::left_extrude()
{
    qDebug()<<"left extrude";
    m_xhPort->LoadFilament(0);
}

void changeFilamentDlg::left_retract()
{
    qDebug()<<"left retract";
    m_xhPort->UnloadFilament(0);

}

void changeFilamentDlg::onSetTemp()
{
    QList<QByteArray> ret = chooseTempDialog->get_return_value();
    if(extruder_selected == 0) {
        ui->labLeftHeatingUnit->setValue(ret[0].toUInt());
        m_xhPort->setHeattingUnit(0, ret[0].toInt());
    }
    else if(extruder_selected == 1)
    {
        ui->labRightHeatingUnit->setValue(ret[0].toUInt());
        m_xhPort->setHeattingUnit(1, ret[0].toInt());
    }
}


void changeFilamentDlg::right_extrude()
{
    qDebug()<<"right extrude";
    m_xhPort->LoadFilament(1);
}

void changeFilamentDlg::right_retract()
{
    qDebug()<<"right retract";
    m_xhPort->UnloadFilament(1);
}

void changeFilamentDlg::on_pushButton_359_clicked()
{
    delete chooseTempDialog;
    emit hideWidget();
    this->hide();
}
