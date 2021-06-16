#include "jlonoffswitch.h"
#include "ui_jlonoffswitch.h"

JLOnOffSwitch::JLOnOffSwitch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JLOnOffSwitch)
{
    ui->setupUi(this);
    enableStatus = false;
}

JLOnOffSwitch::~JLOnOffSwitch()
{
    delete ui;
}

bool JLOnOffSwitch::getEnableStatus()
{
    return enableStatus;
}

void JLOnOffSwitch::setText(QString Text)
{

}

void JLOnOffSwitch::on_btnCircle_clicked()
{
    if(enableStatus == false)
    {
        ui->btnCircle->setGeometry(60, 0, 60, 60);
        enableStatus = true;
    }
    else
    {
        ui->btnCircle->setGeometry(0, 0, 60, 60);
        enableStatus = false;
    }
    emit clicked();
}
