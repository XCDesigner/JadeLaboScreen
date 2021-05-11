#include "printsetdlog.h"
#include "ui_printsetdlog.h"

PrintSetDlog::PrintSetDlog(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::PrintSetDlog)
{
    ui->setupUi(this);

    m_tmr_check_increase = new QTimer(this);
    m_tmr_check_decrease = new QTimer(this);

    ui->qw_LeftTemp->setSource(QUrl("qrc:/qml/JLPushedButton.qml"));
    ui->qw_LeftTemp->setClearColor(QColor(qmlColor));

    ui->qw_RightTemp->setSource(QUrl("qrc:/qml/JLPushedButton.qml"));
    ui->qw_RightTemp->setClearColor(QColor(qmlColor));

    ui->qw_BedTemp->setSource(QUrl("qrc:/qml/JLPushedButton.qml"));
    ui->qw_BedTemp->setClearColor(QColor(qmlColor));

    ui->qw_LeftFan->setSource(QUrl("qrc:/qml/JLPushedButton.qml"));
    ui->qw_LeftFan->setClearColor(QColor(qmlColor));

    ui->qw_RightFan->setSource(QUrl("qrc:/qml/JLPushedButton.qml"));
    ui->qw_RightFan->setClearColor(QColor(qmlColor));

    ui->qw_FeedRatePercent->setSource(QUrl("qrc:/qml/JLPushedButton.qml"));
    ui->qw_FeedRatePercent->setClearColor(QColor(qmlColor));

    ui->qw_LeftFlowratePercent->setSource(QUrl("qrc:/qml/JLPushedButton.qml"));
    ui->qw_LeftFlowratePercent->setClearColor(QColor(qmlColor));

    ui->qw_RightFlowratePercent->setSource(QUrl("qrc:/qml/JLPushedButton.qml"));
    ui->qw_RightFlowratePercent->setClearColor(QColor(qmlColor));

    ui->qw_PlatformHeight->setSource(QUrl("qrc:/qml/JLPushedButton.qml"));
    ui->qw_PlatformHeight->setClearColor(QColor(qmlColor));

    ui->qw_BackupMode->setSource(QUrl("qrc:/qml/JLPushedButton.qml"));
    ui->qw_BackupMode->setClearColor(QColor(qmlColor));
    ui->qw_BackupMode->rootObject()->setProperty("text", "Backup Mode");

    ui->qw_Increase->setSource(QUrl("qrc:/qml/JLIconButton.qml"));
    ui->qw_Increase->setClearColor(QColor(qmlColor));
    ui->qw_Increase->rootObject()->setProperty("icon", "qrc:/image/Path Copy.png");
    ui->qw_Increase->rootObject()->setProperty("pressIcon", "qrc:/image/Path Copy.png");

    ui->qw_Decrease->setSource(QUrl("qrc:/qml/JLIconButton.qml"));
    ui->qw_Decrease->setClearColor(QColor(qmlColor));
    ui->qw_Decrease->rootObject()->setProperty("icon", "qrc:/image/Path.png");
    ui->qw_Decrease->rootObject()->setProperty("pressIcon", "qrc:/image/Path.png");

    pButtons[0] = ui->qw_LeftTemp;
    pButtons[1] = ui->qw_RightTemp;
    pButtons[2] = ui->qw_BedTemp;
    pButtons[3] = ui->qw_LeftFan;
    pButtons[4] = ui->qw_RightFan;
    pButtons[5] = ui->qw_FeedRatePercent;
    pButtons[6] = ui->qw_PlatformHeight;
    pButtons[7] = ui->qw_LeftFlowratePercent;
    pButtons[8] = ui->qw_RightFlowratePercent;

    for(int i=0;i<9;i++) {
        pButtons[i]->rootObject()->setProperty("index", i);
        pButtons[i]->rootObject()->setProperty("enable", true);
        QObject::connect(pButtons[i]->rootObject(), SIGNAL(click(int)), this, SLOT(buttonClicked(int)));
    }

    ui->qw_BackupMode->rootObject()->setProperty("index", 10);
    QObject::connect(ui->qw_BackupMode->rootObject(), SIGNAL(click(int)), this, SLOT(backupModeChange(int)));

    QObject::connect(ui->qw_Increase->rootObject(), SIGNAL(press()), this, SLOT(onIncreaseClicked()));
    QObject::connect(ui->qw_Decrease->rootObject(), SIGNAL(press()), this, SLOT(onDecreaseClicked()));
    QObject::connect(ui->qw_Increase->rootObject(), SIGNAL(release()), this, SLOT(onIncreaseRelease()));
    QObject::connect(ui->qw_Decrease->rootObject(), SIGNAL(release()), this, SLOT(onDecreaseRelease()));
}

PrintSetDlog::~PrintSetDlog()
{
    delete ui;
}

void PrintSetDlog::setPrintMode(QString PrintMode)
{
    print_mode = PrintMode;
    if(PrintMode == "Mix")
    {
        ui->qw_LeftFlowratePercent->setGeometry(46, 253, 400, 100);
        ui->qw_RightFlowratePercent->setGeometry(469, 253, 400, 100);
        ui->qw_RightFlowratePercent->setVisible(true);
    }
    else
    {
        ui->qw_LeftFlowratePercent->setGeometry(46, 253, 824, 100);
        ui->qw_RightFlowratePercent->setGeometry(0, 0, 0, 0);
        ui->qw_RightFlowratePercent->setVisible(false);
    }
}

void PrintSetDlog::init(QByteArray InitData)
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
    ui->qw_LeftTemp->rootObject()->setProperty("text", QString("Left Temp / %1°C").arg(a));
    ui->qw_RightTemp->rootObject()->setProperty("text", QString("Right Temp / %1°C").arg(b));
    ui->qw_BedTemp->rootObject()->setProperty("text", QString("Bed Temp / %1°C").arg(c));
    ui->qw_LeftFan->rootObject()->setProperty("text", QString("Left Fan / %1%").arg(d));
    ui->qw_RightFan->rootObject()->setProperty("text", QString("Right Fan / %1%").arg(e));
    ui->qw_FeedRatePercent->rootObject()->setProperty("text", QString("Feedrate / %1%").arg(f));
    ui->qw_PlatformHeight->rootObject()->setProperty("text", QString("Platform Height / %1mm").arg(g));
    if(print_mode == "Mix")
        ui->qw_LeftFlowratePercent->rootObject()->setProperty("text", QString("Left Flowrate / %1%").arg(h));
    else
        ui->qw_LeftFlowratePercent->rootObject()->setProperty("text", QString("Flowrate / %1%").arg(h));
    ui->qw_RightFlowratePercent->rootObject()->setProperty("text", QString("Right Flowrate / %1%").arg(i));

    for(int i=0;i<9;i++)
    {
        pButtons[i]->rootObject()->setProperty("color", "#2d2b2c");
        pButtons[i]->rootObject()->setProperty("isPressed", "false");
        button_check_status[i] = false;
    }
}

void PrintSetDlog::setXHPort(XhPort *pPort)
{
    m_xhPort = pPort;
}
    
void PrintSetDlog::backupModeChange(int Index)
{
    if(ui->qw_BackupMode->rootObject()->property("isPressed").toBool() == true)
    {
        ui->qw_BackupMode->rootObject()->setProperty("isPressed", false);
    }
    else
    {
        ui->qw_BackupMode->rootObject()->setProperty("isPressed", true);
    }
}

void PrintSetDlog::backup(int a )
{
    switch (a) {
    case 0:
        ui->qw_BackupMode->rootObject()->setProperty("isPressed", false);
        break;
    case 1:
        ui->qw_BackupMode->rootObject()->setProperty("isPressed", true);
        break;
    case 2:
        ui->qw_BackupMode->rootObject()->setProperty("enable", false);
        break;
    default:
        break;

    }
}

void PrintSetDlog::on_pushButton_clicked()
{
    if(ui->qw_BackupMode->rootObject()->property("isPressed").toBool() == true)
        ret_value.append(QByteArray("Enable Backup"));
    else
        ret_value.append(QByteArray("Disable Backup"));

    emit hideWidget();
    this->hide();
}

void PrintSetDlog::onIncreaseClicked()
{
    press_counter = 0;
    step_direction = 1;
    step_value = getStepValue();
    change_value = step_value * step_direction;
    sendSetting();
    if(button_check_status[6] == false)
        m_tmr_check_increase->singleShot(50, this, SLOT(increaseCheck()));
}

void PrintSetDlog::onIncreaseRelease()
{
    press_counter = 0;
    step_value = 0;
}

void PrintSetDlog::onDecreaseClicked()
{
    press_counter = 0;
    step_direction = -1;
    step_value = getStepValue();
    change_value = step_value * step_direction;
    sendSetting();
    if(button_check_status[6] == false)
        m_tmr_check_increase->singleShot(50, this, SLOT(decreaseCheck()));
}

void PrintSetDlog::onDecreaseRelease()
{
    press_counter = 0;
    step_value = 0;
}

void PrintSetDlog::increaseCheck()
{
    if(ui->qw_Increase->rootObject()->property("isPressed").toBool() == true) {
        change_value = getLongPressStepValue() * step_direction;
        m_tmr_check_increase->singleShot(50, this, SLOT(increaseCheck()));
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
    if(ui->qw_Decrease->rootObject()->property("isPressed").toBool() == true) {
        change_value = getLongPressStepValue() * step_direction;
        m_tmr_check_increase->singleShot(50, this, SLOT(decreaseCheck()));
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
    bool new_status = pButtons[Index]->rootObject()->property("isPressed").toBool();
    if(new_status == true)
    {
        pButtons[Index]->rootObject()->setProperty("isPressed", false);
        button_check_status[Index] = false;
    }
    else
    {
        pButtons[Index]->rootObject()->setProperty("isPressed", true);
        button_check_status[Index] = true;
        updateButtonCheckStatus(Index);
    }
}

void PrintSetDlog::updateButtonCheckStatus(int Index)
{
    if((Index == 0) || (Index == 1) || (Index == 2)) 
    {
        button_check_status[3] = button_check_status[4] = button_check_status[5] = button_check_status[6] = button_check_status[7] = button_check_status[8] = false;
        pButtons[3]->rootObject()->setProperty("isPressed", false);
        pButtons[4]->rootObject()->setProperty("isPressed", false);
        pButtons[5]->rootObject()->setProperty("isPressed", false);
        pButtons[6]->rootObject()->setProperty("isPressed", false);
        pButtons[7]->rootObject()->setProperty("isPressed", false);
        pButtons[8]->rootObject()->setProperty("isPressed", false);
    }
    else if((Index == 3) || (Index == 4))
    {
        button_check_status[0] = button_check_status[1] = button_check_status[2] = button_check_status[5] = button_check_status[6] = button_check_status[7] = button_check_status[8] = false;
        pButtons[0]->rootObject()->setProperty("isPressed", false);
        pButtons[1]->rootObject()->setProperty("isPressed", false);
        pButtons[2]->rootObject()->setProperty("isPressed", false);
        pButtons[5]->rootObject()->setProperty("isPressed", false);
        pButtons[6]->rootObject()->setProperty("isPressed", false);
        pButtons[7]->rootObject()->setProperty("isPressed", false);
        pButtons[8]->rootObject()->setProperty("isPressed", false);
    }
    else if(Index == 5)
    {
        button_check_status[0] = button_check_status[1] = button_check_status[2] = button_check_status[3] = button_check_status[4] = button_check_status[6] = button_check_status[7] = button_check_status[8] = false;
        pButtons[0]->rootObject()->setProperty("isPressed", false);
        pButtons[1]->rootObject()->setProperty("isPressed", false);
        pButtons[2]->rootObject()->setProperty("isPressed", false);
        pButtons[3]->rootObject()->setProperty("isPressed", false);
        pButtons[4]->rootObject()->setProperty("isPressed", false);
        pButtons[6]->rootObject()->setProperty("isPressed", false);
        pButtons[7]->rootObject()->setProperty("isPressed", false);
        pButtons[8]->rootObject()->setProperty("isPressed", false);
    }
    else if(Index == 6)
    {
        button_check_status[0] = button_check_status[1] = button_check_status[2] = button_check_status[3] = button_check_status[4] = button_check_status[5] = button_check_status[7] = button_check_status[8] = false;
        pButtons[0]->rootObject()->setProperty("isPressed", false);
        pButtons[1]->rootObject()->setProperty("isPressed", false);
        pButtons[2]->rootObject()->setProperty("isPressed", false);
        pButtons[3]->rootObject()->setProperty("isPressed", false);
        pButtons[4]->rootObject()->setProperty("isPressed", false);
        pButtons[5]->rootObject()->setProperty("isPressed", false);
        pButtons[7]->rootObject()->setProperty("isPressed", false);
        pButtons[8]->rootObject()->setProperty("isPressed", false);
    }
    else if((Index == 7) || (Index == 8))
    {
        button_check_status[0] = button_check_status[1] = button_check_status[2] = button_check_status[3] = button_check_status[4] = button_check_status[5] = button_check_status[6] = false;
        pButtons[0]->rootObject()->setProperty("isPressed", false);
        pButtons[1]->rootObject()->setProperty("isPressed", false);
        pButtons[2]->rootObject()->setProperty("isPressed", false);
        pButtons[3]->rootObject()->setProperty("isPressed", false);
        pButtons[4]->rootObject()->setProperty("isPressed", false);
        pButtons[5]->rootObject()->setProperty("isPressed", false);
        pButtons[6]->rootObject()->setProperty("isPressed", false);
    }
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
        ui->qw_LeftTemp->rootObject()->setProperty("text", QString("Left Temp / %1°C").arg(temp_percent[0]));
        ui->qw_RightTemp->rootObject()->setProperty("text", QString("Right Temp / %1°C").arg(temp_percent[1]));
        ui->qw_BedTemp->rootObject()->setProperty("text", QString("Bed Temp / %1°C").arg(temp_percent[2]));
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
        ui->qw_LeftFan->rootObject()->setProperty("text", QString("Left Fan / %1%").arg(fan_percent[0]));
        ui->qw_RightFan->rootObject()->setProperty("text", QString("Right Fan / %1%").arg(fan_percent[1]));
    }
    else if(button_check_status[5] == true)
    {
        feedrate_percent += change_value;
        if(feedrate_percent > 200)
            feedrate_percent = 200;
        else if(feedrate_percent < 10)
            feedrate_percent = 10;
        m_xhPort->setPrintSpeedPercentage(feedrate_percent);
        ui->qw_FeedRatePercent->rootObject()->setProperty("text", QString("Feedrate / %1%").arg(feedrate_percent));
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
        // QString g = QString("%1.%2").arg(platform_height/1000).arg((platform_height % 1000) / 10);
        ui->qw_PlatformHeight->rootObject()->setProperty("text", QString("Platform Height / %1mm").arg(dis));
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
                ui->qw_LeftFlowratePercent->rootObject()->setProperty("text", QString("Left Flowrate / %1%").arg(flowrate_percent[0]));
            else
                ui->qw_LeftFlowratePercent->rootObject()->setProperty("text", QString("Flowrate / %1%").arg(flowrate_percent[0]));
        }
        if(button_check_status[8] == true)
        {
            m_xhPort->setFlowratePercentage(1, flowrate_percent[1]);
            ui->qw_RightFlowratePercent->rootObject()->setProperty("text", QString("Right Flowrate / %1%").arg(flowrate_percent[1]));
        }
    }
}



