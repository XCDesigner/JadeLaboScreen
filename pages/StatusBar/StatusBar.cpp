#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setUSBpic(bool isVisible)
{
    ui->qw_StatusNotice->rootObject()->setProperty("udiskVisible", isVisible);
}

void MainWindow::setLightPic(bool isVisible)
{
    ui->qw_StatusNotice->rootObject()->setProperty("lightVisible", isVisible);
}

void MainWindow::setWinPic(bool isVisible)
{
    ui->qw_StatusNotice->rootObject()->setProperty("wifiVisible", isVisible);
}

void MainWindow::StatusNotice_Light_clicked()
{
    QQuickItem *item;
    item = ui->qw_StatusNotice->rootObject();
    if(item->property("lightChecked").toBool() == true)
        m_port->setLightOnOff(true);
    else
        m_port->setLightOnOff(false);
}

void MainWindow::updateStatusBar()
{
    strMachineStatus new_status;
    m_port->getXhPage()->GetMachineStatus(&new_status);

    char m_string[20] ="";
    sprintf(m_string,"%03d|%03d°C",new_status.CurTemp[0], new_status.TarTemp[0]);
    ui->label_125->setText(m_string);

    sprintf(m_string,"%03d|%03d°C",new_status.CurTemp[1], new_status.TarTemp[1]);
    ui->label_127->setText(m_string);

    sprintf(m_string,"%03d|%03d°C",new_status.CurTemp[2], new_status.TarTemp[2]);
    ui->label_29->setText(m_string);

    sprintf(m_string,"%05.1f", new_status.ZHeight);
    ui->label_129->setText(m_string);

    if(new_status.Status != 0) {
        ui->quickWidget_3->rootObject()->setProperty("currentPercent", new_status.Percent);
    }

    if(new_status.CurTemp[0] > 70 || new_status.TarTemp[0] > 0) {
        ui->label_124->setPixmap(QPixmap(lHotEndActive));
    }else {
        ui->label_124->setPixmap(QPixmap(lHotEndInactive));
    }
    if(new_status.CurTemp[1] > 70 || new_status.TarTemp[1] > 0) {
        ui->label_126->setPixmap(QPixmap(rHotEndActive));
    }else {
        ui->label_126->setPixmap(QPixmap(rHotEndInactive));
    }
    if(new_status.CurTemp[2]) {
        ui->label_128->setPixmap(QPixmap(bedActive));
    }
    else {
        ui->label_128->setPixmap(QPixmap(bedInactive));
    }
    QTimer::singleShot(1000, this, SLOT(updateStatusBar()));

    #ifdef XH_LINUX
        currentState.clear();
        currentState = data;
    #endif
}
