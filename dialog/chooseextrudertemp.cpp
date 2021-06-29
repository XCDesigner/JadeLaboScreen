#include "chooseextrudertemp.h"
#include "ui_chooseextrudertemp.h"

ChooseExtruderTemp::ChooseExtruderTemp(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::ChooseExtruderTemp)
{
    ui->setupUi(this);

    ui->qw_Temp180->rootObject()->setProperty("temperature", 180);
    ui->qw_Temp180->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp180->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));

    ui->qw_Temp200->rootObject()->setProperty("temperature", 200);
    ui->qw_Temp200->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp200->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));

    ui->qw_Temp220->rootObject()->setProperty("temperature", 220);
    ui->qw_Temp220->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp220->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));

    ui->qw_Temp240->rootObject()->setProperty("temperature", 240);
    ui->qw_Temp240->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp240->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));

    ui->qw_Temp260->rootObject()->setProperty("temperature", 260);
    ui->qw_Temp260->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp260->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));

    ui->qw_Temp280->rootObject()->setProperty("temperature", 280);
    ui->qw_Temp280->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_Temp280->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));
}

ChooseExtruderTemp::~ChooseExtruderTemp()
{
    delete ui;
}

void ChooseExtruderTemp::init(QByteArray &InitData)
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
    ret_value.append(QByteArray().setNum(extruder_index));
    ret_value.append(QByteArray().setNum(Value));
    emit hideWidget();
    this->hide();
}

