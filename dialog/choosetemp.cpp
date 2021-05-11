#include "choosetemp.h"
#include "ui_choosetemp.h"

chooseTemp::chooseTemp(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::chooseTemp)
{
    ui->setupUi(this);

    item[0] = ui->qw_TempOff;
    item[1] = ui->qw_Temp180;
    item[2] = ui->qw_Temp200;
    item[3] = ui->qw_Temp220;
    item[4] = ui->qw_Temp240;
    item[5] = ui->qw_Temp260;

    QString itemText[] = {"OFF", "180°C", "200°C", "220°C", "240°C", "260°C"};
    int radius[] = {90, 20, 20, 20, 20, 20};

    for(int i=0;i<6;i++)
    {
        item[i]->rootObject()->setProperty("text", itemText[i]);
        item[i]->rootObject()->setProperty("radius", radius[i]);
        item[i]->rootObject()->setProperty("index", i);
        item[i]->rootObject()->setProperty("enable", true);
        item[i]->rootObject()->setProperty("isPressed", false);
        item[i]->setClearColor("#202020");
        // item[i]->rootObject()->setProperty("borderWidth", 5);
        // item[i]->rootObject()->setProperty("borderColor", "#f0f0f0");
        // QMetaObject::invokeMethod(item[i]->rootObject(), "setBorder", Q_ARG(int, 5), Q_ARG(QVariant, "#b0b0b0"));
        QObject::connect(item[i]->rootObject(), SIGNAL(clicked(int)), this, SLOT(onTempSelect(int)));
    }
    item[0]->rootObject()->setProperty("enable", false);
}

chooseTemp::~chooseTemp()
{
    delete ui;
}

void chooseTemp::init(QString str)
{

}

void chooseTemp::show()
{
    ret_value.clear();
    QWidget::show();
}

void chooseTemp::onTempSelect(int Index)
{
    QByteArray ret_table[] = {"0", "180", "200", "220", "240", "260"};
    item[Index]->rootObject()->setProperty("isPressed", false);
    ret_value.append(ret_table[Index]);
    emit hideWidget();
    this->hide();
}




