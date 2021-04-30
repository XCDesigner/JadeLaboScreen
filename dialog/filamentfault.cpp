#include "filamentfault.h"
#include "ui_filamentfault.h"

filamentFault::filamentFault(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::filamentFault)
{
    ui->setupUi(this);
}

filamentFault::~filamentFault()
{
    delete ui;
}

void filamentFault::init(QByteArray)
{

}

void filamentFault::show()
{
    QWidget::show();
}

void filamentFault::on_btnResume_clicked()
{

}

void filamentFault::on_btnChangeFilament_clicked()
{

}

void filamentFault::on_btnAbort_clicked()
{

}
