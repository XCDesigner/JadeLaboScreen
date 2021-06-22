#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::LightSettingPageInit()
{
    ui->qw_LightSlider->setSource(QUrl("qrc:/qml/JFSliderBar.qml"));
    ui->qw_LightSlider->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->qw_LightSlider->setClearColor(QColor(qmlColor));

    qw_LightItem = ui->qw_LightSlider->rootObject();
    QObject::connect(qw_LightItem, SIGNAL(released()), this, SLOT(LightSliderReleased()));
    QObject::connect(qw_LightItem, SIGNAL(pressed()), this, SLOT(LightSliderPressed()));
}

void MainWindow::LightSliderPressed()
{
    QTimer::singleShot(200, this, SLOT(LightSettingTimer()));
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
        QTimer::singleShot(200, this, SLOT(LightSettingTimer()));
        // qDebug()<<"Set";
        int bright = qw_LightItem->property("value").toInt() * 2.55f;
        m_port->setRGBLight(bright, bright, bright);
    }
}

void MainWindow::on_pushButton_346_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_MachineSetting);
}

void MainWindow::on_pushButton_350_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_LightSetting);
}
