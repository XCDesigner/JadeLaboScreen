#include "jlbutton.h"
#include "ui_jlbutton.h"

JLButton::JLButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JLButton)
{
    ui->setupUi(this);
}

JLButton::~JLButton()
{
    delete ui;
}
