#include "delete.h"
#include "ui_delete.h"

Delete::Delete(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::Delete)
{
    ui->setupUi(this);
    }

Delete::~Delete()
{
    delete ui;
}

void Delete::show()
{
    QWidget::show();
}

void Delete::init(QString FileName, myListWidgetItem* pItem)
{
    ui->label_2->setText(FileName);
    ui->label_2->setAlignment(Qt::AlignCenter);
    deleteItem = pItem;
    ret_value.clear();
}

myListWidgetItem* Delete::getDeleteItem()
{
    return deleteItem;
}

void Delete::on_pushButton_clicked()
{
    ret_value.append("Confirm");
    emit hideWidget();
    hide();
}

void Delete::on_pushButton_2_clicked()
{
    ret_value.append("Cancel");
    emit hideWidget();
    hide();
}
