#include "jlheatingunit.h"
#include "ui_jlheatingunit.h"

JLHeatingUnit::JLHeatingUnit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JLHeatingUnit)
{
    ui->setupUi(this);
}

JLHeatingUnit::~JLHeatingUnit()
{
    delete ui;
}

QString JLHeatingUnit::leftBackgroundStyleSheet = "QLabel { \
        border-image: url(:image/left_heatuint_background.png); \
}";

QString JLHeatingUnit::rightBackgroundStyleSheet ="QLabel { \
        border-image: url(:image/right_heatuint_background.png); \
}";

void JLHeatingUnit::setIndicator(int Index)
{
    if(Index == 0)
    {
        indicator = 0;
        ui->labBackground->setStyleSheet(leftBackgroundStyleSheet);
    }
    else
    {
        indicator = 1;
        ui->labBackground->setStyleSheet(rightBackgroundStyleSheet);
    }
}

void JLHeatingUnit::setText(QString Text)
{

}

void JLHeatingUnit::setExtruderEnable(bool Enable)
{
    ui->btnLoad->setEnabled(Enable);
    ui->btnUnload->setEnabled(Enable);
}

void JLHeatingUnit::setValue(int Value)
{
    char strText[32];
    sprintf(strText, "%03d°C", Value);
    ui->btnChooseTemp->setText(strText);
}

void JLHeatingUnit::on_btnChooseTemp_clicked()
{
    emit chooseTempClicked();
}

void JLHeatingUnit::on_btnUnload_clicked()
{
    emit retractClicked();
}

void JLHeatingUnit::on_btnLoad_clicked()
{
    emit extrudeClicked();
}

