#include "jlheatedbedunit.h"
#include "ui_jlheatedbedunit.h"

JLHeatedbedUnit::JLHeatedbedUnit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JLHeatedbedUnit)
{
    ui->setupUi(this);
}

JLHeatedbedUnit::~JLHeatedbedUnit()
{
    delete ui;
}

void JLHeatedbedUnit::setText(QString Text)
{

}

void JLHeatedbedUnit::setValue(int Value)
{
    char strText[32];
    sprintf(strText, "%03d°C", Value);
    ui->btnChooseTemp->setText(strText);
}

void JLHeatedbedUnit::on_btnChooseTemp_clicked()
{
    emit chooseTempClicked();
}

void JLHeatedbedUnit::on_btnCooldown_clicked()
{
    emit cooldownClicked();
}
