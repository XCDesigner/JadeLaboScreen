#include "askpause.h"
#include "ui_askpause.h"

askPause::askPause(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::askPause)
{
    ui->setupUi(this);
    ui->btnDisableLeft->setCheckable(true);
    ui->btnDisableRight->setCheckable(true);
    ui->btnDisableLeft->setChecked(true);
    ui->btnDisableRight->setChecked(true);
}

askPause::~askPause()
{
    delete ui;
}

void askPause::init(QByteArray InitData)
{
    strMachineStatus cur_status;
    strScreenStatus cur_screen_status;
    m_xhPort->getXhPage()->GetMachineStatus(&cur_status);
    pscreen_status->getStatus(&cur_screen_status);
    if(cur_status.Status == 1) {
        current_status = "running";
        ui->btnPauseContinue->setText("Pause");
        ui->btnDisableLeft->setVisible(false);
        ui->btnDisableRight->setVisible(false);
        ui->btnCancel->setGeometry(322, 364, 634, 121);
    }
    else if((cur_status.Status == 2) || (cur_status.Status == 4)) {
        current_status = "pause";
        ui->btnPauseContinue->setText("Continue");
        if((pscreen_status->getPrintMode() == "Duplicate") || (pscreen_status->getPrintMode() == "Mirror") || (pscreen_status->getPrintMode() == "Origin-Duplicate") || (pscreen_status->getPrintMode() == "Origin-Mirror")) {
            last_left_extruder_enable = pscreen_status->isExtruderEnabled(0);
            last_right_extruder_enable = pscreen_status->isExtruderEnabled(1);
            if((last_left_extruder_enable == false) || (last_right_extruder_enable == false)) {
                ui->btnDisableLeft->setVisible(false);
                ui->btnDisableRight->setVisible(false);
                ui->btnCancel->setGeometry(322, 364, 634, 121);
            }
            ui->btnDisableLeft->setChecked(last_left_extruder_enable);
            ui->btnDisableRight->setChecked(last_right_extruder_enable);
        }
        else{
            ui->btnDisableLeft->setVisible(true);
            ui->btnDisableRight->setVisible(true);
            ui->btnCancel->setGeometry(322, 535, 634, 121);
            last_left_extruder_enable = true;
            last_right_extruder_enable = true;
        }
    }
    ret_value.clear();
}

void askPause::show()
{
    QWidget::show();
}

void askPause::setXHPort(XhPort *pPort)
{
    m_xhPort = pPort;
}

void askPause::on_btnCancel_clicked()
{
    QByteArray result = QByteArray("Cancel");
    ret_value.append(result);
    emit hideWidget();
    this->hide();
}

void askPause::on_btnChangeFilament_clicked()
{
    QByteArray result = QByteArray("ChangeFilament");
    ret_value.append(result);
    emit hideWidget();
    this->hide();
}

void askPause::on_btnPauseContinue_clicked()
{
    if(current_status == "running")
    {
        QByteArray result = QByteArray("Pause");
        ret_value.append(result);
        emit hideWidget();
        this->hide();
    }
    else if(current_status == "pause")
    {
        bool cur_left_extruder_enable, cur_right_extruder_enable;
        QByteArray result = QByteArray("Continue");
        ret_value.append(result);

        cur_left_extruder_enable = ui->btnDisableLeft->isChecked();
        cur_right_extruder_enable = ui->btnDisableRight->isChecked();
        if((cur_left_extruder_enable != last_left_extruder_enable) || (cur_right_extruder_enable != last_right_extruder_enable)) {
            ret_value.append(cur_left_extruder_enable==true?QByteArray("Enable"):QByteArray("Disable"));
            ret_value.append(cur_right_extruder_enable==true?QByteArray("Enable"):QByteArray("Disable"));
        }
        emit hideWidget();
        this->hide();
    }
}
