#include "jlbutton.h"
#include "ui_jlbutton.h"

JLButton::JLButton(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::JLButton)
{
    ui->setupUi(this);
}

JLButton::~JLButton()
{
    delete ui;
}


void JLButton::on_pushButton_clicked()
{
    emit leftClicked();
}

void JLButton::on_pushButton_2_clicked()
{
    emit rightClicked();
}
