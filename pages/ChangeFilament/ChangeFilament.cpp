#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::changeFilamentPageInit()
{
    ui->qw_LeftHeating->rootObject()->setProperty("indicatorIcon", "qrc:/image/LeftHotendIndecator.png");
    ui->qw_LeftHeating->rootObject()->setProperty("indicatorText", "Left Extruder");
    QObject::connect(ui->qw_LeftHeating->rootObject(), SIGNAL(choseTempClicked()), this, SLOT(left_setTemp()));
    QObject::connect(ui->qw_LeftHeating->rootObject(), SIGNAL(extruderClicked()), this, SLOT(left_extrude()));
    QObject::connect(ui->qw_LeftHeating->rootObject(), SIGNAL(retackClicked()), this, SLOT(left_retract()));

    ui->qw_RightHeating->rootObject()->setProperty("indicatorIcon", "qrc:/image/RightHotendIndecator.png");
    ui->qw_RightHeating->rootObject()->setProperty("indicatorText", "Right Extruder");
    QObject::connect(ui->qw_RightHeating->rootObject(), SIGNAL(choseTempClicked()), this, SLOT(right_setTemp()));
    QObject::connect(ui->qw_RightHeating->rootObject(), SIGNAL(extruderClicked()), this, SLOT(right_extrude()));
    QObject::connect(ui->qw_RightHeating->rootObject(), SIGNAL(retackClicked()), this, SLOT(right_retract()));
}

void MainWindow::leftSetTemp()
{
    strMachineStatus new_status;
    char temp[20];
    changeFilamentSelectExtruder = 0;
    m_port->getXhPage()->GetMachineStatus(&new_status);
    sprintf(temp, "%03d", new_status.TarTemp[0]);
    mchoose = new chooseTemp(this);
    mchoose->init(temp);
    QObject::connect(mchoose, SIGNAL(hideWidget()), this, SLOT(onSetTemp()), Qt::QueuedConnection);
}

void MainWindow::onSetTemp()
{
    QList<QByteArray> ret = mchoose->get_return_value();
    m_port->setHeattingUnit(changeFilamentSelectExtruder, ret[0].toUInt());
    delete mchoose;
}

void MainWindow::changeFilamentCheckTemp()
{

    QTimer::singleShot(500, this, SLOT(changeFilamentCheckTemp()));
}

void MainWindow::leftExtrude()
{
    m_port->ldown();
}

void MainWindow::leftRetract()
{
    m_port->lup();
}


void MainWindow::rightSetTemp()
{
    strMachineStatus new_status;
    char temp[20];
    changeFilamentSelectExtruder = 1;
    m_port->getXhPage()->GetMachineStatus(&new_status);
    sprintf(temp, "%03d", new_status.TarTemp[1]);
    mchoose = new chooseTemp(this);
    mchoose->init(temp);
    QObject::connect(mchoose, SIGNAL(hideWidget()), this, SLOT(onSetTemp()));
}

void MainWindow::rightExtrude()
{
    m_port->rdown();
}

void MainWindow::rightRetract()
{
    m_port->rup();
}


void MainWindow::on_pushButton_109_clicked()
{
    mchoose = new chooseTemp(this);
    mchoose->init(ui->pushButton_109->text());
    ui->pushButton_358->setText("Cancel");
#ifdef OLD
    ui->pushButton_111->setStyleSheet("QPushButton{outline:none;\
                                        image: url(:/UnloadButton.png);\
                                      background-color: rgb(45, 44, 43);\
                                      border:none;};");
    ui->pushButton_112->setStyleSheet("QPushButton{outline:none;\
                                        image: url(:/LoadButton.png);\
                                      background-color: rgb(45, 44, 43);\
                                      border:none;};");
    ui->pushButton_114->setStyleSheet("QPushButton{outline:none;\
                                        image: url(:/UnloadButton.png);\
                                      background-color: rgb(45, 44, 43);\
                                      border:none;};");
    ui->pushButton_115->setStyleSheet("QPushButton{outline:none;\
                                        image: url(:/LoadButton.png);\
                                      background-color: rgb(45, 44, 43);\
                                      border:none;};");
#endif
    ui->pushButton_111->setEnabled(false);
    ui->pushButton_112->setEnabled(false);
    ui->pushButton_114->setEnabled(false);
    ui->pushButton_115->setEnabled(false);

    ui->pushButton_105->setEnabled(false);
    ui->pushButton_106->setEnabled(false);
    ui->pushButton_107->setEnabled(false);
    ui->pushButton_108->setEnabled(false);
    QObject::connect(mchoose,&chooseTemp::heatT,this,&MainWindow::ltemp);
    mchoose->show();
}

void MainWindow::on_pushButton_110_clicked()
{
        mchoose = new chooseTemp(this);
        mchoose->init(ui->pushButton_110->text());
        ui->pushButton_358->setText("Cancel");
#ifdef OLD
        ui->pushButton_111->setStyleSheet("QPushButton{outline:none;\
                                            image: url(:/UnloadButton.png);\
                                          background-color: rgb(45, 44, 43);\
                                          border:none;};");
        ui->pushButton_112->setStyleSheet("QPushButton{outline:none;\
                                            image: url(:/LoadButton.png);\
                                          background-color: rgb(45, 44, 43);\
                                          border:none;};");
        ui->pushButton_114->setStyleSheet("QPushButton{outline:none;\
                                            image: url(:/UnloadButton.png);\
                                          background-color: rgb(45, 44, 43);\
                                          border:none;};");
        ui->pushButton_115->setStyleSheet("QPushButton{outline:none;\
                                            image: url(:/LoadButton.png);\
                                          background-color: rgb(45, 44, 43);\
                                          border:none;};");
#endif
        ui->pushButton_111->setEnabled(false);
        ui->pushButton_112->setEnabled(false);
        ui->pushButton_114->setEnabled(false);
        ui->pushButton_115->setEnabled(false);

        ui->pushButton_105->setEnabled(false);
        ui->pushButton_107->setEnabled(false);
        ui->pushButton_108->setEnabled(false);
        mchoose->show();
        QObject::connect(mchoose,&chooseTemp::heatT,this,&MainWindow::rtemp);
}

void MainWindow::on_pushButton_111_clicked()
{
    m_port->lup();
}

void MainWindow::on_pushButton_112_clicked()
{
    m_port->ldown();
}

void MainWindow::on_pushButton_114_clicked()
{
    m_port->rup();
}

void MainWindow::on_pushButton_115_clicked()
{
    m_port->rdown();
}

void MainWindow::on_pushButton_358_clicked()
{
    ui->pushButton_109->setText("000°C");
    ui->pushButton_110->setText("000°C");
    m_port->setHeattingUnit("0","0");
#ifdef OLD
    ui->pushButton_111->setStyleSheet("QPushButton{outline:none;\
                                        image: url(:/UnloadButton.png);\
                                      background-color: rgb(45, 44, 43);\
                                      border:none;};");
    ui->pushButton_112->setStyleSheet("QPushButton{outline:none;\
                                        image: url(:/LoadButton.png);\
                                      background-color: rgb(45, 44, 43);\
                                      border:none;};");
    ui->pushButton_114->setStyleSheet("QPushButton{outline:none;\
                                        image: url(:/UnloadButton.png);\
                                      background-color: rgb(45, 44, 43);\
                                      border:none;};");
    ui->pushButton_115->setStyleSheet("QPushButton{outline:none;\
                                        image: url(:/LoadButton.png);\
                                      background-color: rgb(45, 44, 43);\
                                      border:none;};");
#endif
    ui->pushButton_111->setEnabled(false);
    ui->pushButton_112->setEnabled(false);
    ui->pushButton_114->setEnabled(false);
    ui->pushButton_115->setEnabled(false);

    ui->pushButton_105->setEnabled(true);
    ui->pushButton_107->setEnabled(true);
    ui->pushButton_108->setEnabled(true);
}

void MainWindow::filamentTimeout()
{
    //m_port->askTemperature();
    if(ui->stackedWidget->currentIndex() == 30)
    {
        int l1 = ui->label_125->text().left(3).toInt();
        int l2 = ui->label_125->text().mid(4,3).toInt();
        int r = ui->label_127->text().left(3).toInt();
        int r2 = ui->label_127->text().mid(4,3).toInt();

        if(l2 != 0&& r2 != 0)
        {
            if(l1>(l2-5) && r>(r2-5))
            {
                m_timer.stop();
                ui->pushButton_358->setText("Complete");
                QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(filamentTimeout()));
                lheatend =false;
                rheatend =false;
#ifdef OLD
                ui->pushButton_111->setStyleSheet("QPushButton{outline:none;\
                                                  image: url(:/UnloadButtonActive.png);\
                                                  background-color: rgb(45, 44, 43);\
                                                  border:none;};");
                ui->pushButton_112->setStyleSheet("QPushButton{outline:none;\
                                                  image: url(:/LoadButtonActive.png);\
                                                  background-color: rgb(45, 44, 43);\
                                                  border:none;};");
                ui->pushButton_114->setStyleSheet("QPushButton{outline:none;\
                                                image: url(:/UnloadButtonActive.png);\
                                                background-color: rgb(45, 44, 43);\
                                                border:none;};");
                ui->pushButton_115->setStyleSheet("QPushButton{outline:none;\
                                                image: url(:/LoadButtonActive.png);\
                                                background-color: rgb(45, 44, 43);\
                                                border:none;};");
#endif
                ui->pushButton_111->setEnabled(true);
                ui->pushButton_112->setEnabled(true);
                ui->pushButton_114->setEnabled(true);
                ui->pushButton_115->setEnabled(true);

                ui->pushButton_105->setEnabled(true);
                ui->pushButton_106->setEnabled(true);
                ui->pushButton_107->setEnabled(true);
                ui->pushButton_108->setEnabled(true);

            }
        }
        if(l2 !=0 &&r2 == 0)
        {
            if(l1>(l2-5))
            {
                m_timer.stop();
                QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(filamentTimeout()));
                lheatend =false;
                rheatend =false;
                ui->pushButton_358->setText("Complete");
#ifdef OLD
                ui->pushButton_111->setStyleSheet("QPushButton{outline:none;\
                                                  image: url(:/UnloadButtonActive.png);\
                                                  background-color: rgb(45, 44, 43);\
                                                  border:none;};");
                ui->pushButton_112->setStyleSheet("QPushButton{outline:none;\
                                                  image: url(:/LoadButtonActive.png);\
                                                  background-color: rgb(45, 44, 43);\
                                                  border:none;};");
                ui->pushButton_114->setStyleSheet("QPushButton{outline:none;\
                                                    image: url(:/UnloadButton.png);\
                                                  background-color: rgb(45, 44, 43);\
                                                  border:none;};");
                ui->pushButton_115->setStyleSheet("QPushButton{outline:none;\
                                                    image: url(:/LoadButton.png);\
                                                  background-color: rgb(45, 44, 43);\
                                                  border:none;};");
#endif
                ui->pushButton_111->setEnabled(true);
                ui->pushButton_112->setEnabled(true);
                ui->pushButton_114->setEnabled(false);
                ui->pushButton_115->setEnabled(false);

                ui->pushButton_105->setEnabled(true);
                ui->pushButton_106->setEnabled(true);
                ui->pushButton_107->setEnabled(true);
                ui->pushButton_108->setEnabled(true);

            }
        }
        if(l2 == 0&&r2 != 0)
        {
            if(r>(r2-5))
            {
                m_timer.stop();
                QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(filamentTimeout()));

                lheatend =false;
                rheatend =false;
                ui->pushButton_358->setText("Complete");
#ifdef OLD
                ui->pushButton_114->setStyleSheet("QPushButton{outline:none;\
                                                  image: url(:/UnloadButtonActive.png);\
                                                  background-color: rgb(45, 44, 43);\
                                                  border:none;};");
                ui->pushButton_115->setStyleSheet("QPushButton{outline:none;\
                                                  image: url(:/LoadButtonActive.png);\
                                                  background-color: rgb(45, 44, 43);\
                                                  border:none;};");
                ui->pushButton_111->setStyleSheet("QPushButton{outline:none;\
                                                    image: url(:/UnloadButton.png);\
                                                  background-color: rgb(45, 44, 43);\
                                                  border:none;};");
                ui->pushButton_112->setStyleSheet("QPushButton{outline:none;\
                                                    image: url(:/LoadButton.png);\
                                                  background-color: rgb(45, 44, 43);\
                                                  border:none;};");
#endif
                ui->pushButton_111->setEnabled(false);
                ui->pushButton_112->setEnabled(false);
                ui->pushButton_114->setEnabled(true);
                ui->pushButton_115->setEnabled(true);

                ui->pushButton_105->setEnabled(false);
                ui->pushButton_107->setEnabled(false);
                ui->pushButton_108->setEnabled(false);
            }
        }
        if(l2== 0&&r2==0)
        {
            lheatend =false;
            rheatend =false;
            m_timer.stop();
            QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(filamentTimeout()));
            ui->pushButton_358->setText("Cancel");
#ifdef OLD
            ui->pushButton_111->setStyleSheet("QPushButton{outline:none;\
                                                image: url(:/UnloadButton.png);\
                                              background-color: rgb(45, 44, 43);\
                                              border:none;};");
            ui->pushButton_112->setStyleSheet("QPushButton{outline:none;\
                                                image: url(:/LoadButton.png);\
                                              background-color: rgb(45, 44, 43);\
                                              border:none;};");
            ui->pushButton_114->setStyleSheet("QPushButton{outline:none;\
                                                image: url(:/UnloadButton.png);\
                                              background-color: rgb(45, 44, 43);\
                                              border:none;};");
            ui->pushButton_115->setStyleSheet("QPushButton{outline:none;\
                                                image: url(:/LoadButton.png);\
                                              background-color: rgb(45, 44, 43);\
                                              border:none;};");
#endif
            ui->pushButton_111->setEnabled(false);
            ui->pushButton_112->setEnabled(false);
            ui->pushButton_114->setEnabled(false);
            ui->pushButton_115->setEnabled(false);

            ui->pushButton_105->setEnabled(true);
            ui->pushButton_107->setEnabled(true);
            ui->pushButton_108->setEnabled(true);
        }
    }

}

void MainWindow::filamentOK(bool a)
{
    if(a)
    {
        m_timer.stop();
        QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(filamentTimeout()));
        ui->stackedWidget->setCurrentIndex(32);
    }
}

void MainWindow::on_pushButton_105_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_107_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::on_pushButton_108_clicked()
{
    ui->stackedWidget->setCurrentIndex(24);
#ifdef XH_VIS
    ui->m_StatusBar->setVisible(false);
#endif
}
