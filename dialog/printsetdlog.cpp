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

    ui->qw_PlatformHeight->setSource(QUrl("qrc:/qml/JLPushedButton.qml"));
    ui->qw_PlatformHeight->setClearColor(QColor(qmlColor));

    ui->qw_BackupMode->setSource(QUrl("qrc:/qml/JLPushedButton.qml"));
    ui->qw_BackupMode->setClearColor(QColor(qmlColor));
    ui->qw_BackupMode->rootObject()->setProperty("text", "Backup Mode");

    ui->qw_Increase->setSource(QUrl("qrc:/qml/JLIconButton.qml"));
    ui->qw_Increase->setClearColor(QColor(qmlColor));
    ui->qw_BackupMode->rootObject()->setProperty("icon", "qrc:/image/Path Copy.png");
    ui->qw_BackupMode->rootObject()->setProperty("pressIcon", "qrc:/image/Path Copy.png");

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

    for(int i=0;i<7;i++) {
        pButtons[i]->rootObject()->setProperty("index", i);
        pButtons[i]->rootObject()->setProperty("enable", true);
        QObject::connect(pButtons[i]->rootObject(), SIGNAL(clicked(int)), this, SLOT(buttonClicked(int)));
    }

    ui->qw_BackupMode->rootObject()->setProperty("index", 10);
    QObject::connect(ui->qw_BackupMode->rootObject(), SIGNAL(clicked(int)), this, SLOT(backupModeChange(int)));

    QObject::connect(ui->qw_Increase->rootObject(), SIGNAL(press()), this, SLOT(onIncreaseClicked()));
    QObject::connect(ui->qw_Decrease->rootObject(), SIGNAL(press()), this, SLOT(onDecreaseClicked()));
}

PrintSetDlog::~PrintSetDlog()
{
    delete ui;
}

void PrintSetDlog::init(QByteArray InitData)
{
    temp_percent[0] = InitData[3];
    temp_percent[1] = InitData[4];
    temp_percent[2] = InitData[5];
    fan_percent[0] = InitData[6];
    fan_percent[1] = InitData[7];
    feedrate_percent = (uint16_t)(((uint8_t)InitData[9] << 8) | (uint8_t)InitData[8]);
    platform_height = (uint32_t)(((uint8_t)InitData[13] << 8) | ((uint8_t)InitData[12] << 8) | ((uint8_t)InitData[11] << 8) | (uint8_t)InitData[10]);
    QString a, b, c, d, e, f, g;
    a.setNum(temp_percent[0]);
    b.setNum(temp_percent[1]);
    c.setNum(temp_percent[2]);
    d.setNum(fan_percent[0]);
    e.setNum(fan_percent[1]);
    f.setNum(feedrate_percent);
    g.setNum(platform_height, 'g', 2);
    initnum(a, b, c, d, e, f, g);
    ret_value.clear();
}

void PrintSetDlog::initnum(QString a, QString b, QString c, QString d, QString e, QString f, QString g)
{
//    ui->qw_LeftTemp->rootObject()->setProperty("text", "Left Temp / "+a+"°C");
//    ui->qw_LeftTemp->rootObject()->setProperty("text", "Left Temp / "+a+"°C");
//    ui->qw_RightTemp->rootObject()->setProperty("text", "Right Temp / "+b+"°C");
//    ui->qw_BedTemp->rootObject()->setProperty("text", "Bed Temp "+c+"°C");
//    ui->qw_LeftFan->rootObject()->setProperty("text", "Left Fan Speed "+d+"%");
//    ui->qw_RightFan->rootObject()->setProperty("text", "Right Fan Speed "+e+"%");
//    ui->qw_FeedRatePercent->rootObject()->setProperty("text", "Feedrate "+f+"%");
//    ui->qw_PlatformHeight->rootObject()->setProperty("text", "Platform Height "+g+"mm");

    ui->qw_LeftTemp->rootObject()->setProperty("text", "Left Temp / "+a+"%");
    ui->qw_RightTemp->rootObject()->setProperty("text", "Right Temp / "+b+"%");
    ui->qw_BedTemp->rootObject()->setProperty("text", "Bed Temp "+c+"%");
    ui->qw_LeftFan->rootObject()->setProperty("text", "Left Fan Speed "+d+"%");
    ui->qw_RightFan->rootObject()->setProperty("text", "Right Fan Speed "+e+"%");
    ui->qw_FeedRatePercent->rootObject()->setProperty("text", "Feedrate "+f+"%");
    ui->qw_PlatformHeight->rootObject()->setProperty("text", "Platform Height "+g+"mm");
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
    m_tmr_check_increase->singleShot(200, this, SLOT(IncreaseCheck()));
    press_counter = 0;
    sendSetting();
}

void PrintSetDlog::onDecreaseClicked()
{
    m_tmr_check_increase->singleShot(200, this, SLOT(DecreaseCheck()));
    press_counter = 0;
    sendSetting();
}

void PrintSetDlog::increaseCheck()
{
    if(ui->qw_Increase->rootObject()->property("isPressed").toBool() == true) {
        m_tmr_check_increase->singleShot(200, this, SLOT(IncreaseCheck()));
        if(press_counter < 100)
            press_counter++;
        if(press_counter > 30) {
           sendSetting();
           press_counter = 0;
        }
    }
}

void PrintSetDlog::decreaseCheck()
{
    if(ui->qw_Decrease->rootObject()->property("isPressed").toBool() == true) {
        m_tmr_check_increase->singleShot(200, this, SLOT(DecreaseCheck()));
        if(press_counter < 100)
            press_counter++;
        if(press_counter > 30) {
           sendSetting();
           press_counter = 0;
        }
    }
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
    qDebug()<<"Clicked:";
    qDebug()<<Index;
    if((Index == 0) || (Index == 1) || (Index == 2)) 
    {
        button_check_status[3] = button_check_status[4] = button_check_status[5] = button_check_status[6] = false;
        pButtons[3]->rootObject()->setProperty("isPressed", false);
        pButtons[4]->rootObject()->setProperty("isPressed", false);
        pButtons[5]->rootObject()->setProperty("isPressed", false);
        pButtons[6]->rootObject()->setProperty("isPressed", false);
    }
    else if((Index == 3) || (Index == 4))
    {
        button_check_status[0] = button_check_status[1] = button_check_status[2] = button_check_status[5] = button_check_status[6] = false;
        pButtons[0]->rootObject()->setProperty("isPressed", false);
        pButtons[1]->rootObject()->setProperty("isPressed", false);
        pButtons[2]->rootObject()->setProperty("isPressed", false);
        pButtons[5]->rootObject()->setProperty("isPressed", false);
        pButtons[6]->rootObject()->setProperty("isPressed", false);
    }
    else if(Index == 5)
    {
        button_check_status[0] = button_check_status[1] = button_check_status[2] = button_check_status[3] = button_check_status[4] = button_check_status[6] = false;
        pButtons[0]->rootObject()->setProperty("isPressed", false);
        pButtons[1]->rootObject()->setProperty("isPressed", false);
        pButtons[2]->rootObject()->setProperty("isPressed", false);
        pButtons[3]->rootObject()->setProperty("isPressed", false);
        pButtons[4]->rootObject()->setProperty("isPressed", false);
        pButtons[6]->rootObject()->setProperty("isPressed", false);
    }
    else if(Index == 6)
    {
        button_check_status[0] = button_check_status[1] = button_check_status[2] = button_check_status[3] = button_check_status[4] = button_check_status[5] = false;
        pButtons[0]->rootObject()->setProperty("isPressed", false);
        pButtons[1]->rootObject()->setProperty("isPressed", false);
        pButtons[2]->rootObject()->setProperty("isPressed", false);
        pButtons[3]->rootObject()->setProperty("isPressed", false);
        pButtons[4]->rootObject()->setProperty("isPressed", false);
        pButtons[5]->rootObject()->setProperty("isPressed", false);
    }
}

void PrintSetDlog::sendSetting()
{
    if((button_check_status[0] == true) || (button_check_status[1] == true) ||(button_check_status[2] == true))
    {
        m_xhPort->setPrintTempPercentage(0, temp_percent[0]);
        m_xhPort->setPrintTempPercentage(1, temp_percent[1]);
        m_xhPort->setPrintTempPercentage(2, temp_percent[2]);
    }
    else if(((button_check_status[3] == true)) || ((button_check_status[4] == true)))
    {
        m_xhPort->setPrintFanPercentage(0, fan_percent[0]);
        m_xhPort->setPrintFanPercentage(1, fan_percent[1]);
    }
    else if(button_check_status[5] == true)
    {
       m_xhPort->setPrintSpeedPercentage(feedrate_percent);
    }
    else if(button_check_status[6] == true)
    {
       m_xhPort->setPrintPlatformOffset(platform_height * 1000);
    }
}



