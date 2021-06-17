#include "jlcontrolbox.h"
#include "ui_jlcontrolbox.h"

JLControlBox::JLControlBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JLControlBox)
{
    ui->setupUi(this);
}

JLControlBox::~JLControlBox()
{
    delete ui;
}

void JLControlBox::setText(QString Text)
{

}

void JLControlBox::setSettingEnable()
{
    ui->btnSetting->setEnabled(true);
}

void JLControlBox::setStopEnable()
{
    ui->btnStop->setEnabled(true);
}

void JLControlBox::setPauseEnable()
{
    ui->btnPause->setEnabled(true);
}

void JLControlBox::setSettingDisable()
{
    ui->btnSetting->setEnabled(false);
}

void JLControlBox::setStopDisable()
{
    ui->btnStop->setEnabled(false);
}

void JLControlBox::setPauseDisable()
{
    ui->btnPause->setEnabled(false);
}

void JLControlBox::on_btnStop_clicked()
{
    emit stopClicked();
}

void JLControlBox::on_btnPause_clicked()
{
    emit pauseClicked();
}

void JLControlBox::on_btnSetting_clicked()
{
    emit settingClicked();
}
