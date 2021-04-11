#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::LightSliderPressed()
{
    timer_light_slider->singleShot(1000, this, SLOT(LightSettingTimer()));
    // qDebug()<<"Pressed";
    // TODO: Add serial port send
}

void MainWindow::LightSliderReleased()
{
    // qDebug()<<"Release";
    // TODO: Add serial port send
}

void MainWindow::LightSettingTimer()
{
    if(qw_LightItem->property("isPressed").toBool() == true) {
        timer_light_slider->singleShot(1000, this, SLOT(LightSettingTimer()));
        // qDebug()<<"Set";
        // TODO: Add serial port send
    }
}

void MainWindow::on_pushButton_346_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_72);
}
