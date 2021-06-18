#include "jlextruderselect.h"
#include "ui_jlextruderselect.h"

JLExtruderSelect::JLExtruderSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JLExtruderSelect)
{
    ui->setupUi(this);
    indicator = 0;
    ui->btnLeft->setStyleSheet(leftSelectStyleSheet);
    ui->btnRight->setStyleSheet(rightUnselectStyleSheet);
}

JLExtruderSelect::~JLExtruderSelect()
{
    delete ui;
}

QString JLExtruderSelect::leftSelectStyleSheet= "	\
        background-color: \"#2d2c2b\"; \
        font-family: barlow; \
        font-size: 32px; \
        color: \"#f0f0f0\"; \
        border-style: solid; \
        border-color: \"#808080\"; \
        border-width: 5px; \
        border-right-width: 0px; \
        border-top-left-radius: 20px; \
        border-bottom-left-radius: 20px;";

QString JLExtruderSelect::leftUnselectStyleSheet =" \
        background-color: \"#202020\"; \
        font-family: barlow; \
        font-size: 32px; \
        color: \"#8f8f8f\"; \
        border-style: solid; \
        border-color: \"#808080\"; \
        border-width: 5px; \
        border-right-width: 0px; \
        border-top-left-radius: 20px; \
        border-bottom-left-radius: 20px;";

QString JLExtruderSelect::rightSelectStyleSheet= "	\
        background-color: \"#2d2c2b\"; \
        font-family: barlow; \
        font-size: 32px; \
        color: \"#f0f0f0\"; \
        border-style: solid; \
        border-color: \"#808080\"; \
        border-width: 5px; \
        border-left-width: 0px; \
        border-top-right-radius: 20px; \
        border-bottom-right-radius: 20px;";

QString JLExtruderSelect::rightUnselectStyleSheet =" \
        background-color: \"#202020\"; \
        font-family: barlow; \
        font-size: 32px; \
        color: \"#8f8f8f\"; \
        border-style: solid; \
        border-color: \"#808080\"; \
        border-width: 5px; \
        border-left-width: 0px; \
        border-top-right-radius: 20px; \
        border-bottom-right-radius: 20px;";

void JLExtruderSelect::setText(QString)
{

}


void JLExtruderSelect::on_btnLeft_clicked()
{
    if(indicator == 1)
    {
        ui->btnLeft->setStyleSheet(leftSelectStyleSheet);
        ui->btnRight->setStyleSheet(rightUnselectStyleSheet);
        emit clicked(0);
    }
    indicator = 0;
}


void JLExtruderSelect::on_btnRight_clicked()
{
    if(indicator == 0)
    {
        ui->btnLeft->setStyleSheet(leftUnselectStyleSheet);
        ui->btnRight->setStyleSheet(rightSelectStyleSheet);
        emit clicked(1);
    }
    indicator = 1;
}
