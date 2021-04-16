#include "jlwidget.h"

JLWidget::JLWidget(QWidget *parent) : QWidget(parent)
{

}

void JLWidget::init(QByteArray InitData)
{
    qDebug()<<"init() Unremap";
}

void JLWidget::show()
{
    qDebug()<<"show() Unremap";
}

QList<QByteArray> JLWidget::get_return_value()
{
    ret_value.clear();
    return ret_value;
    qDebug()<<"get_return_value() Unremap";
}
