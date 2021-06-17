#include "jlnozzleturnindicator.h"
#include "ui_jlnozzleturnindicator.h"

JLNozzleTurnIndicator::JLNozzleTurnIndicator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JLNozzleTurnIndicator)
{
    ui->setupUi(this);
}

JLNozzleTurnIndicator::~JLNozzleTurnIndicator()
{
    delete ui;
}

QString JLNozzleTurnIndicator::upStyleSheet = "QLabel { \
        border-image: url(:image/nozzle_up2.png); \
}";
QString JLNozzleTurnIndicator::downStyleSheet ="QLabel { \
        border-image: url(:image/nozzle_down2.png); \
}";

void JLNozzleTurnIndicator::setText(QString Text)
{

}

void JLNozzleTurnIndicator::setValue(int Value)
{
    char str_value[32];
    int abs_value;
    abs_value = Value>=0?Value:-Value;

    sprintf(str_value, "%d", abs_value);
    if(Value > 0)
    {
        ui->label->setText(str_value);
        ui->labBackground->setStyleSheet(downStyleSheet);
    }
    else if(Value < 0)
    {
        ui->label->setText(str_value);
        ui->labBackground->setStyleSheet(upStyleSheet);
    }
}
