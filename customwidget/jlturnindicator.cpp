#include "jlturnindicator.h"
#include "ui_jlturnindicator.h"

JLTurnIndicator::JLTurnIndicator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JLTurnIndicator)
{
    ui->setupUi(this);
}

JLTurnIndicator::~JLTurnIndicator()
{
    delete ui;
}

QString JLTurnIndicator::leftStyleSheet = "QLabel { \
        border-image: url(:image/turn_left.png); \
}";
QString JLTurnIndicator::rightStyleSheet ="QLabel { \
        border-image: url(:image/turn_right.png); \
}";
QString JLTurnIndicator::normalStyleSheet ="QLabel { \
        border-color: rgb(33, 33, 33) \
}";

void JLTurnIndicator::setText(QString Text)
{

}

void JLTurnIndicator::setValue(int Value)
{
    char str_value[32];
    int abs_value;

    abs_value = Value>=0?Value:-Value;
    sprintf(str_value, "%d", abs_value);
    ui->labText->setText(str_value);

    if(Value > 0)
        ui->labBackground->setStyleSheet(leftStyleSheet);
    else if(Value < 0)
        ui->labBackground->setStyleSheet(rightStyleSheet);
    else
        ui->labBackground->setStyleSheet(normalStyleSheet);
}
