#include "jlextruderunit.h"
#include "ui_jlextruderunit.h"

JLExtruderUnit::JLExtruderUnit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JLExtruderUnit)
{
    ui->setupUi(this);
    indicator = 0;
    distance[0] = distance[1] = "1";
    temp[0] = temp[1] = 0;
}

JLExtruderUnit::~JLExtruderUnit()
{
    delete ui;
}

void JLExtruderUnit::setText(QString Text)
{

}

void JLExtruderUnit::setIndicator(int Index)
{
    indicator = Index;
    setTemperatureValue(temp[indicator]);
    setDistanceValue(distance[indicator]);
}

int JLExtruderUnit::getIndicator()
{
    return indicator;
}

void JLExtruderUnit::setExtruderEnable(bool Enable)
{
    ui->btnLoad->setEnabled(Enable);
    ui->btnUnload->setEnabled(Enable);
}

void JLExtruderUnit::setTemperatureValue(int Value)
{
    char strText[32];
    temp[indicator] = Value;
    sprintf(strText, "%03d°C", Value);
    ui->btnChooseTemp->setText(strText);
}

QString JLExtruderUnit::getDistance()
{
    return distance[indicator];
}

int JLExtruderUnit::getTemp()
{
    return temp[indicator];
}

void JLExtruderUnit::setDistanceValue(QString Distance)
{
    distance[indicator] = Distance;
    ui->btnChooseDistance->setText(Distance + "mm");
}

void JLExtruderUnit::on_btnUnload_clicked()
{
    emit retractClicked(indicator);
}

void JLExtruderUnit::on_btnLoad_clicked()
{
    emit extrudeClicked(indicator);
}

void JLExtruderUnit::on_btnCooldown_clicked()
{
    emit cooldownClicked(indicator);
}

void JLExtruderUnit::on_btnChooseTemp_clicked()
{
    emit chooseTempClicked(indicator);
}

void JLExtruderUnit::on_btnChooseDistance_clicked()
{
    emit chooseDistanceClicked(indicator);
}
