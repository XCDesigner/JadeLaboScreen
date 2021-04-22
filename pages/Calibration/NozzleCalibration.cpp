#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_286_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_NozzleCali_1);
     m_port->setHeattingUnit("200","200");
     QObject::connect(&m_timer,&QTimer::timeout,this,&MainWindow::nozzled);
     m_timer.start(1000);
}

void MainWindow::on_pushButton_308_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
    m_port->setHeattingUnit("0","0");
}

void MainWindow::on_pushButton_303_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_NozzleCali_2);
//    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(jump23()));
//    m_timer.start(2000);
    m_port->n_nozzleCalibration();
}

void MainWindow::on_pushButton_302_clicked()
{
    m_port->setHeattingUnit("0","0");
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::on_pushButton_292_clicked()
{
    m_port->setHeattingUnit("0","0");
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::on_pushButton_287_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow:: nozzled()
{
    int16_t cur_temp[3], tar_temp[3];
    screen_status.getTemp(cur_temp, tar_temp);

    if((cur_temp[0] >190 ) && (cur_temp[1] >190))
    {
         m_port->n_nozzleCalibration();
         QObject::disconnect(&m_timer,&QTimer::timeout,this,&MainWindow::nozzled);
         m_timer.stop();
         ui->stackedWidget->setCurrentWidget(ui->page_NozzleCali_2);
    }
}


void MainWindow::jump23(int b)
{
    if(b==0)
    {
        ui->stackedWidget->setCurrentWidget(ui->page_NozzleCali_4);
    }
    else {
        ui->stackedWidget->setCurrentWidget(ui->page_NozzleCali_3);
    }

    ui->label_151->setNum(b/1000);
    ui->label_151->setAlignment(Qt::AlignCenter);
//    if(a)
//    {
//        ui->pushButton_304->setIcon(QPixmap(":/9.png"));
//        ui->pushButton_305->setIcon(QPixmap(":/11.png"));
//    }
//    else {
//        ui->pushButton_305->setIcon(QPixmap(":/9.png"));
//        ui->pushButton_304->setIcon(QPixmap(":/11.png"));
//    }
//    m_timer.stop();
//    QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jump23()));
}
