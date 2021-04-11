#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::LightSliderPressed()
{
    timer_light_slider->singleShot(200, this, SLOT(LightSettingTimer()));
    // qDebug()<<"Pressed";
    int bright = qw_LightItem->property("value").toInt() * 2.55f;
    m_port->setRGBLight(bright, bright, bright);
}

void MainWindow::LightSliderReleased()
{
    // qDebug()<<"Release";
    int bright = qw_LightItem->property("value").toInt() * 2.55f;
    m_port->setRGBLight(bright, bright, bright);
}

void MainWindow::LightSettingTimer()
{
    if(qw_LightItem->property("isPressed").toBool() == true) {
        timer_light_slider->singleShot(200, this, SLOT(LightSettingTimer()));
        // qDebug()<<"Set";
        int bright = qw_LightItem->property("value").toInt() * 2.55f;
        m_port->setRGBLight(bright, bright, bright);
    }
}

void MainWindow::on_pushButton_346_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_72);
}
