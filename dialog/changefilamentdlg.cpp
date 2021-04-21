#include "changefilamentdlg.h"
#include "ui_changefilamentdlg.h"

changeFilamentDlg::changeFilamentDlg(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::changeFilamentDlg)
{
    ui->setupUi(this);

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
    chooseTempDialog = new chooseTemp(this);
    QWidget::show();
}

void changeFilamentDlg::setXHPort(XhPort *pPort)
{
    m_xhPort = pPort;
}


void changeFilamentDlg::left_setTemp()
{
    QObject::disconnect(chooseTempDialog, SIGNAL(hideWidget()), this, SLOT(onSetRightTemp()));
    QObject::connect(chooseTempDialog, SIGNAL(hideWidget()), this, SLOT(onSetLeftTemp()));
    chooseTempDialog->show();
}

void changeFilamentDlg::left_extrude()
{
    m_xhPort->ldown();
}

void changeFilamentDlg::left_retract()
{
    m_xhPort->lup();
}

void changeFilamentDlg::right_setTemp()
{
    QObject::disconnect(chooseTempDialog, SIGNAL(hideWidget()), this, SLOT(onSetLeftTemp()));
    QObject::connect(chooseTempDialog, SIGNAL(hideWidget()), this, SLOT(onSetRightTemp()));
    chooseTempDialog->show();
}

void changeFilamentDlg::onSetLeftTemp()
{
    QList<QByteArray> ret = chooseTempDialog->get_return_value();
    qDebug()<<ret[0];
    ui->qw_LeftHeatingItem->rootObject()->setProperty("text", ret[0] + "°C");
    m_xhPort->setHeattingUnit(0, ret[0].toInt());
}

void changeFilamentDlg::onSetRightTemp()
{
    QList<QByteArray> ret = chooseTempDialog->get_return_value();
    qDebug()<<ret[0];
    ui->qw_RightHeatingItem->rootObject()->setProperty("text", ret[0] + "°C");
    m_xhPort->setHeattingUnit(1, ret[0].toInt());
}

void changeFilamentDlg::right_extrude()
{
    m_xhPort->rdown();
}

void changeFilamentDlg::right_retract()
{
    m_xhPort->rup();
}

void changeFilamentDlg::on_pushButton_359_clicked()
{
    delete chooseTempDialog;
    emit hideWidget();
    this->hide();
}
