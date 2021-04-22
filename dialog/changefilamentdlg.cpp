#include "changefilamentdlg.h"
#include "ui_changefilamentdlg.h"

changeFilamentDlg::changeFilamentDlg(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::changeFilamentDlg)
{
    ui->setupUi(this);

    ui->qw_StatusNotice->setSource(QUrl("qrc:/qml/StatusBarNotice.qml"));
    ui->qw_StatusNotice->setClearColor("#2d2b2c");

    ui->qw_LeftHeatingItem->setSource(QUrl("qrc:/qml/JLHeatingUnit.qml"));
    QObject::connect(ui->qw_LeftHeatingItem->rootObject(), SIGNAL(choseTempClicked()), this, SLOT(left_setTemp()));
    QObject::connect(ui->qw_LeftHeatingItem->rootObject(), SIGNAL(extruderClicked()), this, SLOT(left_extrude()));
    QObject::connect(ui->qw_LeftHeatingItem->rootObject(), SIGNAL(retackClicked()), this, SLOT(left_retract()));
    ui->qw_LeftHeatingItem->rootObject()->setProperty("indicatorIcon", "qrc:/image/LeftHotendIndecator.png");
    ui->qw_LeftHeatingItem->rootObject()->setProperty("indicatorText", "Left Extruder");

    ui->qw_RightHeatingItem->setSource(QUrl("qrc:/qml/JLHeatingUnit.qml"));
    QObject::connect(ui->qw_RightHeatingItem->rootObject(), SIGNAL(choseTempClicked()), this, SLOT(right_setTemp()));
    QObject::connect(ui->qw_RightHeatingItem->rootObject(), SIGNAL(extruderClicked()), this, SLOT(right_extrude()));
    QObject::connect(ui->qw_RightHeatingItem->rootObject(), SIGNAL(retackClicked()), this, SLOT(right_retract()));
    ui->qw_RightHeatingItem->rootObject()->setProperty("indicatorIcon", "qrc:/image/RightHotendIndecator.png");
    ui->qw_RightHeatingItem->rootObject()->setProperty("indicatorText", "Right Extruder");

    autoUpdateStatus = false;
}

changeFilamentDlg::~changeFilamentDlg()
{
    delete ui;
}

void changeFilamentDlg::init(QByteArray InitData)
{
    strMachineStatus cur_status;
    m_xhPort->getXhPage()->GetMachineStatus(&cur_status);
    chooseTempDialog = NULL;
    ret_value.clear();
}

void changeFilamentDlg::show()
{
    strScreenStatus status;
    char strtmp[20];

    pscreen_status->getStatus(&status);
    ui->qw_StatusNotice->rootObject()->setProperty("udiskVisible", pscreen_status->getUdiskStatus());
    ui->qw_StatusNotice->rootObject()->setProperty("wifiVisible", pscreen_status->getWifiStatus());
    ui->qw_StatusNotice->rootObject()->setProperty("lightVisible", true);

    sprintf(strtmp, "%03d°C", status.TargetTemp[0]);
    ui->qw_LeftHeatingItem->rootObject()->setProperty("text", strtmp);
    sprintf(strtmp, "%03d°C", status.TargetTemp[1]);
    ui->qw_RightHeatingItem->rootObject()->setProperty("text", strtmp);

    chooseTempDialog = new chooseTemp(this);
    chooseTempDialog->hide();
    autoUpdateStatus = true;

    QTimer::singleShot(500, this, SLOT(updateStatusBar()));

    QObject::connect(chooseTempDialog, SIGNAL(hideWidget()), this, SLOT(onSetTemp()));
    QWidget::show();
}

void changeFilamentDlg::updateStatusBar()
{
    strScreenStatus status;
    pscreen_status->getStatus(&status);
    char strtmp[20];

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
    m_xhPort->ldown();
}

void changeFilamentDlg::left_retract()
{
    qDebug()<<"left retract";
    m_xhPort->lup();
}

void changeFilamentDlg::onSetTemp()
{
    QList<QByteArray> ret = chooseTempDialog->get_return_value();
    if(extruder_selected == 0) {
        ui->qw_LeftHeatingItem->rootObject()->setProperty("text", ret[0] + "°C");
        m_xhPort->setHeattingUnit(0, ret[0].toInt());
    }
    else if(extruder_selected == 1)
    {
        ui->qw_RightHeatingItem->rootObject()->setProperty("text", ret[0] + "°C");
        m_xhPort->setHeattingUnit(1, ret[0].toInt());
    }
}


void changeFilamentDlg::right_extrude()
{
    qDebug()<<"right extrude";
    m_xhPort->rdown();
}

void changeFilamentDlg::right_retract()
{
    qDebug()<<"right retract";
    m_xhPort->rup();
}

void changeFilamentDlg::on_pushButton_359_clicked()
{
    delete chooseTempDialog;
    emit hideWidget();
    this->hide();
}
