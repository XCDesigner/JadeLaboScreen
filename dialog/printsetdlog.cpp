#include "printsetdlog.h"
#include "ui_printsetdlog.h"

PrintSetDlog::PrintSetDlog(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::PrintSetDlog)
{
    ui->setupUi(this);

    m_tmr_press_check = new QTimer(this);

    ui->btnBackupMode->setText("Backup Mode");

    pButtons[0] = ui->btnLeftTemp;
    pButtons[1] = ui->btnRightTemp;
    pButtons[2] = ui->btnBedTemp;
    pButtons[3] = ui->btnLeftFan;
    pButtons[4] = ui->btnRightFan;
    pButtons[5] = ui->btnFeedrate;
    pButtons[6] = ui->btnPlatformHeight;
    pButtons[7] = ui->btnLeftFlowrate;
    pButtons[8] = ui->btnRightFlowrate;

    for(int i=0;i<9;i++)
    {
        pButtons[i]->setCheckable(true);
        pButtons[i]->setChecked(false);
    }
    pButtons[0]->setChecked(true);

    decrease_pressed = false;
    increase_pressed = false;
}

PrintSetDlog::~PrintSetDlog()
{
    delete ui;
    delete m_tmr_press_check;
}

void PrintSetDlog::setPrintMode(QString PrintMode)
{
    print_mode = PrintMode;
    if(PrintMode == "Mix")
    {
        ui->btnLeftFlowrate->setGeometry(46, 253, 400, 100);
        ui->btnRightFlowrate->setGeometry(469, 253, 400, 100);
        ui->btnRightFlowrate->setVisible(true);
    }
    else
    {
        ui->btnLeftFlowrate->setGeometry(46, 253, 824, 100);
        ui->btnRightFlowrate->setGeometry(0, 0, 0, 0);
        ui->btnRightFlowrate->setVisible(false);
    }
}

void PrintSetDlog::init(QByteArray &InitData)
{
    int16_t curTemp[3], tarTemp[3];
    pscreen_status->getTemp(curTemp, tarTemp);
    temp_percent[0] = tarTemp[0];
    temp_percent[1] = tarTemp[1];
    temp_percent[2] = tarTemp[2];

    fan_percent[0] = InitData[6];
    fan_percent[1] = InitData[7];
    feedrate_percent = (uint16_t)(((uint8_t)InitData[9] << 8) | (uint8_t)InitData[8]);
    platform_height = (uint32_t)(((uint8_t)InitData[13] << 8) | ((uint8_t)InitData[12] << 8) | ((uint8_t)InitData[11] << 8) | (uint8_t)InitData[10]);
    flowrate_percent[0] = (uint16_t)(((uint8_t)InitData[15] << 8) | (uint8_t)InitData[14]);
    flowrate_percent[1] = (uint16_t)(((uint8_t)InitData[17] << 8) | (uint8_t)InitData[16]);
    QString a, b, c, d, e, f, g, h, i;
    a.setNum(temp_percent[0]);
    b.setNum(temp_percent[1]);
    c.setNum(temp_percent[2]);
    d.setNum(fan_percent[0]);
    e.setNum(fan_percent[1]);
    f.setNum(feedrate_percent);
    g = QString("%1.%2").arg(platform_height/1000).arg((platform_height % 1000) / 100);
    h.setNum(flowrate_percent[0]);
    i.setNum(flowrate_percent[1]);
    initnum(a, b, c, d, e, f, g, h, i);

    ret_value.clear();
}

void PrintSetDlog::initnum(QString a, QString b, QString c, QString d, QString e, QString f, QString g, QString h, QString i)
{
    pButtons[0]->setText(QString("Left Temp / %1°C").arg(a));
    pButtons[1]->setText(QString("Right Temp / %1°C").arg(b));
    pButtons[2]->setText(QString("Bed Temp / %1°C").arg(c));
    pButtons[3]->setText(QString("Left Fan / %1%").arg(d));
    pButtons[4]->setText(QString("Right Fan / %1%").arg(e));
    pButtons[5]->setText(QString("Feedrate / %1%").arg(f));
    pButtons[6]->setText(QString("Platform Height / %1mm").arg(g));

    if(print_mode == "Mix")
        pButtons[7]->setText(QString("Left Flowrate / %1%").arg(h));
    else
        pButtons[7]->setText(QString("Flowrate / %1%").arg(h));
    pButtons[8]->setText(QString("Right Flowrate / %1%").arg(i));

    for(int i=0;i<9;i++)
    {
        pButtons[i]->setChecked(false);
        button_check_status[i] = false;
    }
}

void PrintSetDlog::setXHPort(XhPort *pPort)
{
    m_xhPort = pPort;
}
    
void PrintSetDlog::backup(int a)
{
    switch (a) {
    case 0:
        ui->btnBackupMode->setChecked(false);
        break;
    case 1:
        ui->btnBackupMode->setChecked(true);
        break;
    case 2:
        ui->btnBackupMode->setChecked(false);
        break;
    default:
        break;

    }
}

void PrintSetDlog::on_pushButton_clicked()
{
    if(ui->btnBackupMode->isChecked() == true)
        ret_value.append(QByteArray("Enable Backup"));
    else
        ret_value.append(QByteArray("Disable Backup"));

    emit hideWidget();
    this->hide();
}

void PrintSetDlog::onIncreaseClicked()
{
    increase_pressed = true;
    press_counter = 0;
    step_direction = 1;
    step_value = getStepValue();
    change_value = step_value * step_direction;
    sendSetting();
    if(button_check_status[6] == false)
        m_tmr_press_check->singleShot(50, this, SLOT(increaseCheck()));
}

void PrintSetDlog::onIncreaseRelease()
{
    increase_pressed = false;
    press_counter = 0;
    step_value = 0;
}

void PrintSetDlog::onDecreaseClicked()
{
    decrease_pressed = true;
    press_counter = 0;
    step_direction = -1;
    step_value = getStepValue();
    change_value = step_value * step_direction;
    sendSetting();
    if(button_check_status[6] == false)
        m_tmr_press_check->singleShot(50, this, SLOT(decreaseCheck()));
}

void PrintSetDlog::onDecreaseRelease()
{
    decrease_pressed = false;
    press_counter = 0;
    step_value = 0;
}

void PrintSetDlog::increaseCheck()
{
    if(increase_pressed == true) {
        change_value = getLongPressStepValue() * step_direction;
        m_tmr_press_check->singleShot(50, this, SLOT(increaseCheck()));
        if(press_counter < 400)
            press_counter++;
        if(press_counter > 10) {
           sendSetting();
           press_counter = 0;
        }
    }
}

void PrintSetDlog::decreaseCheck()
{
    if(decrease_pressed == true) {
        change_value = getLongPressStepValue() * step_direction;
        m_tmr_press_check->singleShot(50, this, SLOT(decreaseCheck()));
        if(press_counter < 400)
            press_counter++;
        if(press_counter > 10) {
           sendSetting();
           press_counter = 0;
        }
    }
}

int PrintSetDlog::getStepValue()
{
    if((button_check_status[0] == true) || (button_check_status[1] == true) || (button_check_status[2] == true))
        return 1;
    else if((button_check_status[3] == true) || (button_check_status[4] == true))
        return 1;
    else if(button_check_status[5] == true)
        return 1;
    else if(button_check_status[6] == true)
        return 50;
    else if((button_check_status[7] == true)|| (button_check_status[8] == true))
        return 1;
    else
        return 0;
}

int PrintSetDlog::getLongPressStepValue()
{
    if((button_check_status[0] == true) || (button_check_status[1] == true) || (button_check_status[2] == true))
        return 5;
    else if((button_check_status[3] == true) || (button_check_status[4] == true))
        return 5;
    else if(button_check_status[5] == true)
        return 10;
    else if(button_check_status[6] == true)
        return 50;
    else if((button_check_status[7] == true)|| (button_check_status[8] == true))
        return 10;
    else
        return 0;
}

void PrintSetDlog::buttonClicked(int Index)
{
    bool new_status = pButtons[Index]->isChecked();
    qDebug()<<new_status;
    UncheckAllButton();
    if(new_status == true)
        pButtons[Index]->setChecked(true);
    button_check_status[Index] = new_status;
}

void PrintSetDlog::UncheckAllButton()
{
    for(int i=0;i<9;i++)
    {
        button_check_status[i] = false;
        pButtons[i]->setChecked(false);
    }
}

void PrintSetDlog::updateButtonCheckStatus(int Index)
{
    UncheckAllButton();
    pButtons[Index]->setChecked(true);
}

void PrintSetDlog::sendSetting()
{
    if((button_check_status[0] == true) || (button_check_status[1] == true) ||(button_check_status[2] == true))
    {
        for(int i=0;i<3;i++)
        {
            temp_percent[i] += button_check_status[i]==true?change_value:0;
            if(temp_percent[i] > 300)
                temp_percent[i] = 300;
            else if(temp_percent[i] < 0)
                temp_percent[i] = 0;
        }
        m_xhPort->setHeattingUnit(0, temp_percent[0]);
        m_xhPort->setHeattingUnit(1, temp_percent[1]);
        m_xhPort->setHeattingUnit(2, temp_percent[2]);
        pButtons[0]->setText(QString("Left Temp / %1°C").arg(temp_percent[0]));
        pButtons[1]->setText(QString("Right Temp / %1°C").arg(temp_percent[1]));
        pButtons[2]->setText(QString("Bed Temp / %1°C").arg(temp_percent[2]));
    }
    else if((button_check_status[3] == true) || (button_check_status[4] == true))
    {
        for(int i=0;i<2;i++)
        {
            fan_percent[i] += button_check_status[i+3]==true?change_value:0;
            if(fan_percent[i] > 100)
                fan_percent[i] = 100;
            else if(fan_percent[i] < 0)
                fan_percent[i] = 0;
        }
        m_xhPort->setPrintFanPercentage(0, fan_percent[0]);
        m_xhPort->setPrintFanPercentage(1, fan_percent[1]);
        pButtons[3]->setText(QString("Left Fan / %1%").arg(fan_percent[0]));
        pButtons[4]->setText(QString("Right Fan / %1%").arg(fan_percent[1]));
    }
    else if(button_check_status[5] == true)
    {
        feedrate_percent += change_value;
        if(feedrate_percent > 300)
            feedrate_percent = 300;
        else if(feedrate_percent < 10)
            feedrate_percent = 10;
        m_xhPort->setPrintSpeedPercentage(feedrate_percent);
        ui->btnFeedrate->setText(QString("Feedrate / %1%").arg(feedrate_percent));
    }
    else if(button_check_status[6] == true)
    {
        platform_height += change_value;
        if(platform_height > 1000)
           platform_height = 1000;
        else if(platform_height < -1000)
           platform_height = -1000;
        char dis[20];
        sprintf(dis, "%0.2f", platform_height / 1000.0f);
        m_xhPort->setPrintPlatformOffset(platform_height);
        pButtons[6]->setText(QString("Platform Height / %1mm").arg(dis));
    }
    else if((button_check_status[7] == true) || (button_check_status[8] == true))
    {
        for(int i=0;i<2;i++)
        {
           flowrate_percent[i] += button_check_status[i+7]==true?change_value:0;
           if(flowrate_percent[i] > 150)
               flowrate_percent[i] = 150;
           else if(flowrate_percent[i] < 50)
               flowrate_percent[i] = 50;
        }
        if(button_check_status[7] == true)
        {
            m_xhPort->setFlowratePercentage(0, flowrate_percent[0]);
            if(print_mode == "Mix")
                pButtons[7]->setText(QString("Left Flowrate / %1%").arg(flowrate_percent[0]));
            else
                pButtons[7]->setText(QString("Flowrate / %1%").arg(flowrate_percent[0]));
        }
        if(button_check_status[8] == true)
        {
            m_xhPort->setFlowratePercentage(1, flowrate_percent[1]);
            pButtons[8]->setText(QString("Right Flowrate / %1%").arg(flowrate_percent[1]));
        }
    }
}

void PrintSetDlog::on_btnIncrease_released()
{
    onIncreaseRelease();
}

void PrintSetDlog::on_btnDecrease_released()
{
    onDecreaseRelease();
}

void PrintSetDlog::on_btnLeftTemp_clicked()
{
    buttonClicked(0);
}

void PrintSetDlog::on_btnRightTemp_clicked()
{
    buttonClicked(1);
}

void PrintSetDlog::on_btnLeftFan_clicked()
{
    buttonClicked(3);
}

void PrintSetDlog::on_btnRightFan_clicked()
{
    buttonClicked(4);
}

void PrintSetDlog::on_btnLeftFlowrate_clicked()
{
    buttonClicked(7);
}

void PrintSetDlog::on_btnRightFlowrate_clicked()
{
    buttonClicked(8);
}

void PrintSetDlog::on_btnFeedrate_clicked()
{
    buttonClicked(5);
}

void PrintSetDlog::on_btnBedTemp_clicked()
{
    buttonClicked(2);
}

void PrintSetDlog::on_btnPlatformHeight_clicked()
{
    buttonClicked(6);
}

void PrintSetDlog::on_btnBackupMode_clicked()
{

}

void PrintSetDlog::on_btnIncrease_pressed()
{
    onIncreaseClicked();
}

void PrintSetDlog::on_btnDecrease_pressed()
{
    onDecreaseClicked();
}
