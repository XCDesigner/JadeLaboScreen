#include "choosebedtemp.h"
#include "ui_choosebedtemp.h"

ChooseBedTemp::ChooseBedTemp(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::ChooseBedTemp)
{
    ui->setupUi(this);

    ui->qw_Temp40->rootObject()->setProperty("temperature", 40);
    ui->qw_Temp40->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp40->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));

    ui->qw_Temp60->rootObject()->setProperty("temperature", 60);
    ui->qw_Temp60->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp60->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));

    ui->qw_Temp80->rootObject()->setProperty("temperature", 80);
    ui->qw_Temp80->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp80->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));

    ui->qw_Temp100->rootObject()->setProperty("temperature", 100);
    ui->qw_Temp100->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp100->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));
}

ChooseBedTemp::~ChooseBedTemp()
{
    delete ui;
}

void ChooseBedTemp::init(QByteArray InitData)
{
    ret_value.clear();
}

void ChooseBedTemp::show()
{
    QWidget::show();
}

void ChooseBedTemp::onTempSelect(int Value)
{
    ret_value.append(QByteArray().setNum(Value));
    emit hideWidget();
    this->hide();
}
