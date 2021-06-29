#include "powerlost.h"
#include "ui_powerlost.h"

powerLost::powerLost(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::powerLost)
{
    ui->setupUi(this);
}

void powerLost::init(QByteArray &InitData)
{

}

void powerLost::show()
{
    QWidget::show();
}

powerLost::~powerLost()
{
    delete ui;
}

void powerLost::on_btnResume_clicked()
{
    ret_value.append(QByteArray("Recovery"));
    hide();
    emit hideWidget();
}

void powerLost::on_btnCancel_clicked()
{
    ret_value.append(QByteArray("Cancel"));
    hide();
    emit hideWidget();
}
