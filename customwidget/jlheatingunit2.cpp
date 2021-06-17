#include "jlheatingunit2.h"
#include "ui_jlheatingunit2.h"

JLHeatingUnit2::JLHeatingUnit2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JLHeatingUnit2)
{
    ui->setupUi(this);
}

JLHeatingUnit2::~JLHeatingUnit2()
{
    delete ui;
}

QString JLHeatingUnit2::leftBackgroundStyleSheet = "QLabel { \
        border-image: url(:image/left_heating_bg.png); \
}";

QString JLHeatingUnit2::rightBackgroundStyleSheet ="QLabel { \
        border-image: url(:image/right_heating_bg.png); \
}";

QString JLHeatingUnit2::leftCooldownStyleSheet = "QPushButton { \
        border-image: url(:image/left_cooldown.png); \
}";
QString JLHeatingUnit2::rightCooldownStyleSheet ="QPushButton { \
        border-image: url(:image/right_cooldown.png); \
}";

void JLHeatingUnit2::setIndicator(int Index)
{
    if(Index == 0)
    {
        indicator = 0;
        ui->labBackground->setStyleSheet(leftBackgroundStyleSheet);
        ui->btnCooldown->setStyleSheet(leftCooldownStyleSheet);
    }
    else
    {
        indicator = 1;
        ui->labBackground->setStyleSheet(rightBackgroundStyleSheet);
        ui->btnCooldown->setStyleSheet(rightCooldownStyleSheet);
    }
}

void JLHeatingUnit2::setText(QString Text)
{

}

void JLHeatingUnit2::setValue(int Value)
{
    char strText[32];
    sprintf(strText, "%03d°C", Value);
    ui->btnChooseTemp->setText(strText);
}

void JLHeatingUnit2::on_btnChooseTemp_clicked()
{
    emit chooseTempClicked(indicator);
}

void JLHeatingUnit2::on_btnCooldown_clicked()
{
    emit cooldownClicked(indicator);
}
