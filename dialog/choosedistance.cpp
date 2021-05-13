#include "choosedistance.h"
#include "ui_choosedistance.h"

ChooseDistance::ChooseDistance(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::ChooseDistance)
{
    ui->setupUi(this);

    ui->qw_001mm->rootObject()->setProperty("distance", "1");
    ui->qw_001mm->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_001mm->rootObject(), SIGNAL(clicked(QString)), this, SLOT(onDistanceSelect(QString)));

    ui->qw_010mm->rootObject()->setProperty("distance", "10");
    ui->qw_010mm->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_010mm->rootObject(), SIGNAL(clicked(QString)), this, SLOT(onDistanceSelect(QString)));

    ui->qw_100mm->rootObject()->setProperty("distance", "100");
    ui->qw_100mm->setClearColor("#2d2b2c");
    QObject::connect(ui->qw_100mm->rootObject(), SIGNAL(clicked(QString)), this, SLOT(onDistanceSelect(QString)));

}

ChooseDistance::~ChooseDistance()
{
    delete ui;
}

void ChooseDistance::init(QByteArray InitData)
{
    extruder_index = (uint8_t)InitData.at(0);
    ret_value.clear();
}

void ChooseDistance::show()
{
    QWidget::show();
}

void ChooseDistance::onDistanceSelect(QString Value)
{
    ret_value.append(QByteArray().setNum(extruder_index));
    ret_value.append(Value.toUtf8());
    emit hideWidget();
    this->hide();
}
