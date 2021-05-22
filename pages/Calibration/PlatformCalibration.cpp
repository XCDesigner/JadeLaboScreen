#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::platformCalibratePageinit()
{
    ui->qw_SetBuildplatThickness->setClearColor("#2d2c2b");
    ui->qw_PlatformCalibrateP1->setClearColor("#202020");
    ui->qw_PlatformCalibrateP2->setClearColor("#202020");
    ui->qw_PlatformCalibrateP3->setClearColor("#202020");
    QObject::connect(ui->qw_SetBuildplatThickness->rootObject(), SIGNAL(clicked(int)), this, SLOT(onSetBuildplatThicknessClicked(int)));
}

void MainWindow::on_pushButton_275_clicked()
{
    m_port->setHeattingUnit(0, 200);
    m_port->setHeattingUnit(1, 200);
    m_port->setHeattingUnit(2, 60);
    ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_1);
    screen_status.setPerformance(PLATFORM_CALIBRATING);
    QTimer::singleShot(500, this, SLOT(platformCalibrationHeating()));
}

void MainWindow::on_pushButton_242_clicked()
{
    AddListen(QByteArray::fromHex("030C00"), &MainWindow::BuildplateProcess, false);
    m_port->getBuildplatThickness();
}

void MainWindow::on_pushButton_243_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::on_pushButton_248_clicked()
{
    m_port->setHeattingUnit(0, 0);
    m_port->setHeattingUnit(1, 0);
    m_port->setHeattingUnit(2, 0);
    screen_status.setPerformance(IDLE);
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::on_pushButton_259_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_2);
    m_port->p_platformCalibration();
    ui->qw_PlatformCalibrateP1->rootObject()->setProperty("value", 99);
    ui->qw_PlatformCalibrateP2->rootObject()->setProperty("value", 99);
    ui->qw_PlatformCalibrateP3->rootObject()->setProperty("value", 99);
}

void MainWindow::on_pushButton_253_clicked()
{
    screen_status.setPerformance(IDLE);
    m_port->cancleCalibration();
}

void MainWindow::on_pushButton_365_clicked()
{
    m_port->carbinfinished();
    m_port->setHeattingUnit(0, 0);
    m_port->setHeattingUnit(1, 0);
    m_port->setHeattingUnit(2, 0);
    screen_status.setPerformance(IDLE);
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
    QObject::disconnect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(platformCalibrationMessageProcess(uint8_t, uint8_t, QByteArray)));
    QThread::msleep(200);
}

void MainWindow::on_pushButton_367_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_4);
}

void MainWindow::on_pushButton_371_clicked()
{
    m_port->setHeattingUnit(0, 0);
    m_port->setHeattingUnit(1, 0);
    m_port->setHeattingUnit(2, 0);
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
    screen_status.setPerformance(IDLE);
    QObject::disconnect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(platformCalibrationMessageProcess(uint8_t, uint8_t, QByteArray)));
    m_port->carbincancel();
    QThread::msleep(20);
}

void MainWindow::on_pushButton_375_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_5);
}

void MainWindow::on_pushButton_373_clicked()
{
    m_port->setHeattingUnit(0, 0);
    m_port->setHeattingUnit(1, 0);
    m_port->setHeattingUnit(2, 0);
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
    screen_status.setPerformance(IDLE);
    QObject::disconnect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(platformCalibrationMessageProcess(uint8_t, uint8_t, QByteArray)));
    m_port->carbincancel();
    QThread::msleep(20);
}

void MainWindow::platformCalibrationHeating()
{
    strMachineStatus new_status;
    m_port->getXhPage()->GetMachineStatus(&new_status);

    if(screen_status.getPerformance() == PLATFORM_CALIBRATING)
    {
        if((new_status.CurTemp[0] > 190) && (new_status.CurTemp[1] > 190))
        {
            m_port->p_platformCalibration();
            ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_2);
            QObject::connect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(platformCalibrationMessageProcess(uint8_t, uint8_t, QByteArray)));
        }
        else
        {
            qDebug()<<"Platform cali heating..";
            QTimer::singleShot(500, this, SLOT(platformCalibrationHeating()));
        }
    }
}

void MainWindow::platformCalibrationMessageProcess(uint8_t Command, uint8_t SubCode, QByteArray Datas)
{
    uint8_t result = (uint8_t)Datas.at(2);
    if(Command == 0x03)
    {
        if(SubCode == 0x02) {
            if(result == 0) {
                float z_diff[4];
                z_diff[0] = (int32_t)(((uint8_t)Datas.at(6) << 24) | ((uint8_t)Datas.at(5) << 16) | ((uint8_t)Datas.at(4) << 8) | (uint8_t)Datas.at(3)) / 1000.0f;
                z_diff[1] = (int32_t)(((uint8_t)Datas.at(10) << 24) | ((uint8_t)Datas.at(9) << 16) | ((uint8_t)Datas.at(8) << 8) | (uint8_t)Datas.at(7)) / 1000.0f;
                z_diff[2] = (int32_t)(((uint8_t)Datas.at(14) << 24) | ((uint8_t)Datas.at(13) << 16) | ((uint8_t)Datas.at(12) << 8) | (uint8_t)Datas.at(11)) / 1000.0f;
                z_diff[3] = (int32_t)(((uint8_t)Datas.at(18) << 24) | ((uint8_t)Datas.at(17) << 16) | ((uint8_t)Datas.at(16) << 8) | (uint8_t)Datas.at(15)) / 1000.0f;
                if((z_diff[0] == 0) && (z_diff[1] == 0) && (z_diff[2] == 0) && (z_diff[3] == 0))
                {
                    ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_6);
                    QObject::disconnect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(platformCalibrationMessageProcess(uint8_t, uint8_t, QByteArray)));
                }
                else
                {
                    ui->qw_PlatformCalibrateP1->rootObject()->setProperty("value", (int)z_diff[0]);
                    ui->qw_PlatformCalibrateP2->rootObject()->setProperty("value", (int)z_diff[1]);
                    ui->qw_PlatformCalibrateP3->rootObject()->setProperty("value", (int)z_diff[3]);
                    ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_3);
                }
            }
            else {
                m_port->carbincancel();
                QThread::msleep(20);
                ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_0);
                m_port->setHeattingUnit(0, 0);
                m_port->setHeattingUnit(1, 0);
                m_port->setHeattingUnit(2, 0);
                pdlg_warning->init(QByteArray("PlatformCalibrate"));
                pdlg_warning->show();

            }
        }
    }
}

void MainWindow::onSetBuildplatThicknessClicked(int Index)
{
    pdlg_Input = new InputDialog();
    QString init_data;
    init_data = ui->qw_SetBuildplatThickness->rootObject()->property("text").toString();
    init_data = init_data.left(init_data.length() - 2);
    pdlg_Input->init(init_data.toUtf8());
    QObject::connect(pdlg_Input, SIGNAL(hideWidget()), this, SLOT(onSetBuildplatThicknessReturn()), Qt::QueuedConnection);
    pdlg_Input->show();
}

void MainWindow::onSetBuildplatThicknessReturn()
{
    QList<QByteArray> ret = pdlg_Input->get_return_value();
    QString str_value = QString(ret.at(0));
    float value = str_value.toFloat();
    ui->qw_SetBuildplatThickness->rootObject()->setProperty("text", str_value + "mm");
    m_port->setBuildplatThickness(value);
    delete pdlg_Input;
}

void MainWindow::BuildplateProcess(QByteArray Datas)
{
    if((Datas.at(0) == 0x03) && (Datas.at(1) == 0x0C)) {
        float thickness = ((uint8_t)Datas.at(6) << 24 | (uint8_t)Datas.at(5) << 16 | (uint8_t)Datas.at(4) << 8 | (uint8_t)Datas.at(3)) / 1000.0f;
        char str_value[10];
        sprintf(str_value, "%0.2fmm", thickness);
        qDebug()<<str_value;
        ui->qw_SetBuildplatThickness->rootObject()->setProperty("text", str_value);
        ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_7);
    }
}

void MainWindow::on_pushButton_276_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_0);
}
