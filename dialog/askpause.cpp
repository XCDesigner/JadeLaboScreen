#include "askpause.h"
#include "ui_askpause.h"

askPause::askPause(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::askPause)
{
    ui->setupUi(this);
}

askPause::~askPause()
{
    delete ui;
}

void askPause::init(QByteArray InitData)
{
    qDebug()<<"ask";
    ret_value.clear();
}

void askPause::show()
{
    QWidget::show();
}

void askPause::on_pushButton_clicked()
{
    QByteArray result = QByteArray("Stop");
    ret_value.append(result);
    emit hideWidget();
}

void askPause::on_pushButton_2_clicked()
{
    QByteArray result = QByteArray("Pause");
    ret_value.append(result);
    emit hideWidget();
}

void askPause::on_pushButton_3_clicked()
{
    QByteArray result = QByteArray("Cancel");
    ret_value.append(result);
    emit hideWidget();
    this->hide();
}
