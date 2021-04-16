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
}

PrintSetDlog::~PrintSetDlog()
{
    delete ui;
}

void PrintSetDlog::initnum(QString a, QString b, QString c, QString d, QString e, QString f, QString g)
{

    // ui->pushButton_4->setText("Left Temp / "+a+"°C");
    // ui->pushButton_5->setText("Right Temp / "+b+"°C");

    // ui->pushButton_6->setText("Left Fan Speed "+d+"%");
    // ui->pushButton_7->setText("Right Fan Speed "+e+"%");

    // ui->pushButton_8->setText("Bed Temp "+c+"°C");

    // ui->pushButton_9->setText("Feedrate "+f+"%");
    // ui->pushButton_10->setText("Platform Height "+g+"mm");

    ui->qw_LeftTemp->rootObject()->setProperty("text", "Left Temp / "+a+"°C");

    ui->qw_RightTemp->rootObject()->setProperty("text", "Right Temp / "+b+"°C");

    ui->qw_BedTemp->rootObject()->setProperty("text", "Bed Temp "+c+"°C");

    ui->qw_LeftFan->rootObject()->setProperty("text", "Left Fan Speed "+d+"%");

    ui->qw_RightFan->rootObject()->setProperty("text", "Right Fan Speed "+e+"%");

    ui->qw_FeedRatePercent->rootObject()->setProperty("text", "Feedrate "+f+"%");
    
    ui->qw_PlatformHeight->rootObject()->setProperty("text", "Platform Height "+g+"mm");
}
    
void PrintSetDlog::backupModeChange(int Index)
{
    qDebug()<<Index;
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
    {
        emit closeset(1);
    }
    else {
        emit closeset(0);
    }
}

void PrintSetDlog::on_pushButton_2_clicked()
{
    m_tmr_check_increase->singleShot(200, this, SLOT(IncreaseCheck()));
}

void PrintSetDlog::on_pushButton_3_clicked()
{
    m_tmr_check_increase->singleShot(200, this, SLOT(DecreaseCheck()));
}

void PrintSetDlog::increaseCheck()
{

}

void PrintSetDlog::decreaseCheck()
{

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



