#include "choosebedtemp.h"
#include "ui_choosebedtemp.h"

ChooseBedTemp::ChooseBedTemp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseBedTemp)
{
    ui->setupUi(this);
}

ChooseBedTemp::~ChooseBedTemp()
{
    delete ui;
}
