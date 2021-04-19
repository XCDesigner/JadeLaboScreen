#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_242_clicked()
{
    m_port->setHeattingUnit("200","200");
    ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_1);
    QObject::connect(&m_timer,&QTimer::timeout,this,&MainWindow::carilbin);
    m_timer.start(1000);
}

void MainWindow::on_pushButton_243_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::on_pushButton_248_clicked()
{
    m_port->setHeattingUnit("0","0");
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::carilbin()
{
    if((ui->label_125->text().left(3).toInt() >190 ) && (ui->label_127->text().left(3).toInt() >190))
    {
         m_port->p_platformCalibration();
         QObject::disconnect(&m_timer,&QTimer::timeout,this,&MainWindow::carilbin);
         m_timer.stop();
         ui->stackedWidget->setCurrentIndex(54);
    }
}

void MainWindow::on_pushButton_259_clicked()
{
    ui->stackedWidget->setCurrentIndex(54);
    m_port->p_platformCalibration();
}

void MainWindow::on_pushButton_253_clicked()
{
    m_port->cancleCalibration();
}

void MainWindow::on_pushButton_365_clicked()
{
    m_port->setHeattingUnit("0","0");
    ui->stackedWidget->setCurrentIndex(51);
    m_port->carbinfinished();
}

void MainWindow::jump21(qint32 a , qint32 b, qint32 c, qint32 d)
{
//    ui->label_133->setNum((int)(c/1000));
//    ui->label_133->setAlignment(Qt::AlignCenter);
    ui->label_253->setNum((int)(a/1000));
    ui->label_253->setAlignment(Qt::AlignCenter);
    ui->label_261->setNum((int)(d/1000));
    ui->label_261->setAlignment(Qt::AlignCenter);
    ui->label_256->setNum((int)(b/1000));
    ui->label_256->setAlignment(Qt::AlignCenter);
    if(a==0&&b==0&&c==0&&d==0)
    {
        ui->stackedWidget->setCurrentIndex(55);
    }
    else {
        ui->stackedWidget->setCurrentIndex(56);
    }

//    m_timer.stop();
//    QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jump21()));
}

void MainWindow::on_pushButton_367_clicked()
{
    ui->stackedWidget->setCurrentIndex(57);
}

void MainWindow::on_pushButton_371_clicked()
{
    m_port->setHeattingUnit("0","0");
    ui->stackedWidget->setCurrentIndex(51);
    m_port->carbincancel();
}

void MainWindow::on_pushButton_375_clicked()
{
    ui->stackedWidget->setCurrentIndex(58);
}

void MainWindow::on_pushButton_373_clicked()
{
    m_port->setHeattingUnit("0","0");
    ui->stackedWidget->setCurrentIndex(51);
    m_port->carbincancel();
}
