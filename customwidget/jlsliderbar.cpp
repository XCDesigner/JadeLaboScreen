#include "jlsliderbar.h"
#include "ui_jlsliderbar.h"

JLSliderBar::JLSliderBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JLSliderBar)
{
    ui->setupUi(this);
    isPressed = false;
    value = 0;
}

JLSliderBar::~JLSliderBar()
{
    delete ui;
}

void JLSliderBar::mousePressEvent(QMouseEvent *event)
{

}

void JLSliderBar::mouseReleaseEvent(QMouseEvent *event)
{

}

void JLSliderBar::mouseMoveEvent(QMouseEvent *event)
{

}

//void JLSliderBar::on_pushButton_pressed()
//{
//    ui->labSlider->setGeometry(ui->labSlider->x() - 25), 0, 50, 50);

//    isPressed = true;
//    emit pressed();

//    if(mouseX < slider.bigRadius)
//        slider.x = 0
//    else if(mouseX > base.width - slider.bigRadius)
//        slider.x = base.width - slider.bigRadius - slider.bigRadius
//    else
//        slider.x = mouseX - slider.width / 2
//    value = slider.x * 100 / (base.width - slider.bigRadius - slider.bigRadius)
//}

