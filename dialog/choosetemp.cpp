#include "choosetemp.h"
#include "ui_choosetemp.h"

chooseTemp::chooseTemp(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::chooseTemp)
{
    ui->setupUi(this);
}

chooseTemp::~chooseTemp()
{
    delete ui;
}

void chooseTemp::init(QString str)
{
    item[0] = ui->qw_Temp180;
    item[1] = ui->qw_Temp200;
    item[2] = ui->qw_Temp220;
    item[3] = ui->qw_Temp240;
    item[4] = ui->qw_Temp260;
    item[5] = ui->qw_Temp280;

    int itemText[] = {180, 200, 220, 240, 260, 280};

    for(int i=0;i<6;i++)
    {
        item[i]->rootObject()->setProperty("temperature", itemText[i]);
        item[i]->setClearColor("#202020");

        QObject::connect(item[i]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));
    }
}

void chooseTemp::show()
{
    ret_value.clear();
    QWidget::show();
}

void chooseTemp::onTempSelect(int Value)
{
    ret_value.append(QByteArray().setNum(Value));
    emit hideWidget();
    this->hide();
}




