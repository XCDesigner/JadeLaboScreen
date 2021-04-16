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
    QWidget::show();
}

QList<QByteArray> JLWidget::get_return_value()
{
    return ret_value;
}
