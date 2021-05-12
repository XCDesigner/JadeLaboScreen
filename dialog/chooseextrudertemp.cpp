#include "chooseextrudertemp.h"
#include "ui_chooseextrudertemp.h"

ChooseExtruderTemp::ChooseExtruderTemp(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::ChooseExtruderTemp)
{
    ui->setupUi(this);

    ui->qw_Temp180->rootObject()->setProperty("temperature", 40);
    ui->qw_Temp180->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp180->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));

    ui->qw_Temp200->rootObject()->setProperty("temperature", 60);
    ui->qw_Temp200->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp200->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));

    ui->qw_Temp220->rootObject()->setProperty("temperature", 80);
    ui->qw_Temp220->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp220->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));

    ui->qw_Temp240->rootObject()->setProperty("temperature", 100);
    ui->qw_Temp240->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp240->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));

    ui->qw_Temp260->rootObject()->setProperty("temperature", 80);
    ui->qw_Temp260->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp260->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));

    ui->qw_Temp280->rootObject()->setProperty("temperature", 100);
    ui->qw_Temp280->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp280->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));
}

ChooseExtruderTemp::~ChooseExtruderTemp()
{
    delete ui;
}

void ChooseExtruderTemp::init(QByteArray InitData)
{
    extruder_index = (uint8_t)InitData.at(0);
    ret_value.clear();
}

void ChooseExtruderTemp::show()
{
    QWidget::show();
}

void ChooseExtruderTemp::onTempSelect(int Value)
{
    QByteArray qb_extruder_index;
    qb_extruder_index.append(1, extruder_index);
    ret_value.append(qb_extruder_index);
    ret_value.append(QByteArray().setNum(Value));
    emit hideWidget();
    this->hide();
}

