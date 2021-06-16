#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::JodMovePageInit()
{
    QObject::connect(ui->label_7, SIGNAL(clicked()), this, SLOT(ExtruderChange()));
}

void MainWindow::on_pushButton_698_clicked()
{
    QVariant i = qw_DistanceItem->property("distance");
    m_port->moveAxis(1, i.toInt(), 0, 0);
}

void MainWindow::on_pushButton_697_clicked()
{
    QVariant i = qw_DistanceItem->property("distance");
    m_port->moveAxis(1, -(i.toInt()), 0, 0);
}

void MainWindow::on_pushButton_694_clicked()
{
    QVariant i = qw_DistanceItem->property("distance");
    m_port->moveAxis(1, 0, i.toUInt(), 0);
}

void MainWindow::on_pushButton_696_clicked()
{
    QVariant i = qw_DistanceItem->property("distance");
    m_port->moveAxis(1, 0, -(i.toInt()), 0);
}

void MainWindow::on_pushButton_699_clicked()
{
    QVariant i = qw_DistanceItem->property("distance");
    m_port->moveAxis(1, 0, 0, i.toInt());
}

void MainWindow::on_pushButton_701_clicked()
{
    QVariant i = qw_DistanceItem->property("distance");
    qDebug()<<-(i.toInt());
    m_port->moveAxis(1, 0, 0, -(i.toInt()));
}

void MainWindow::on_pushButton_695_clicked()
{
    QByteArray flag;
    flag = QByteArray::fromHex("010100");
    m_port->homeMove(flag);
}

void MainWindow::on_pushButton_700_clicked()
{
    QByteArray flag;
    flag = QByteArray::fromHex("000001");
    m_port->homeMove(flag);
}

void MainWindow::on_pushButton_693_clicked()
{
    m_port->setDualMode(0);
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::ExtruderChange()
{
    if(ui->label_7->getEnableStatus() == true) {
        m_port->changeToolHead(0);
        qDebug()<<"Left";
    }
    else {
        m_port->changeToolHead(1);
        qDebug()<<"Right";
    }
}
