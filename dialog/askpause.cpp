#include "askpause.h"
#include "ui_askpause.h"

askPause::askPause(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::askPause)
{
    ui->setupUi(this);

    ui->quickWidget->setSource(QUrl("qrc:/qml/PauseDialogItem.qml"));
    ui->quickWidget->setClearColor(QColor("#202020"));
    ui->quickWidget->rootObject()->setProperty("leftEnable", true);
    ui->quickWidget->rootObject()->setProperty("rightEnable", true);

    QQuickItem *item = ui->quickWidget->rootObject();

    QObject::connect(item, SIGNAL(pauseClicked()), this, SLOT(pauseClick()));
    QObject::connect(item, SIGNAL(continueClicked()), this, SLOT(continueClick()));
    QObject::connect(item, SIGNAL(changeFilamentClicked()), this, SLOT(changeFilamentClick()));
    QObject::connect(item, SIGNAL(cancelClicked()), this, SLOT(cancelClick()));
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
        ui->quickWidget->rootObject()->setProperty("curStatus", "running");
        ui->quickWidget->rootObject()->setProperty("nonAvoidEnable", false);
    }
    else if((cur_status.Status == 2) || (cur_status.Status == 4)) {
        ui->quickWidget->rootObject()->setProperty("curStatus", "pause");

        if((pscreen_status->getPrintMode() == 2) || (pscreen_status->getPrintMode() == 3) || (pscreen_status->getPrintMode() == 4) || (pscreen_status->getPrintMode() == 5)) {
            ui->quickWidget->rootObject()->setProperty("nonAvoidEnable", true);
            last_left_extruder_enable = pscreen_status->isExtruderEnabled(0);
            last_right_extruder_enable = pscreen_status->isExtruderEnabled(1);
            qDebug()<<last_left_extruder_enable;
            qDebug()<<last_right_extruder_enable;
            if((last_left_extruder_enable == false) || (last_right_extruder_enable == false)) {
                ui->quickWidget->rootObject()->setProperty("nonAvoidEnable", false);
            }
            ui->quickWidget->rootObject()->setProperty("leftEnable", last_left_extruder_enable);
            ui->quickWidget->rootObject()->setProperty("rightEnable", last_right_extruder_enable);
        }
        else{
            ui->quickWidget->rootObject()->setProperty("nonAvoidEnable", false);
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

void askPause::pauseClick()
{
    QByteArray result = QByteArray("Pause");
    ret_value.append(result);
    emit hideWidget();
    this->hide();
}

void askPause::continueClick()
{
    bool cur_left_extruder_enable, cur_right_extruder_enable;
    QByteArray result = QByteArray("Continue");
    ret_value.append(result);

    cur_left_extruder_enable = ui->quickWidget->rootObject()->property("leftEnable").toBool();
    cur_right_extruder_enable = ui->quickWidget->rootObject()->property("rightEnable").toBool();
    if((cur_left_extruder_enable != last_left_extruder_enable) || (cur_right_extruder_enable != last_right_extruder_enable)) {
        ret_value.append(cur_left_extruder_enable==true?QByteArray("Enable"):QByteArray("Disable"));
        ret_value.append(cur_right_extruder_enable==true?QByteArray("Enable"):QByteArray("Disable"));
    }
    emit hideWidget();
    this->hide();
}

void askPause::changeFilamentClick()
{
    QByteArray result = QByteArray("ChangeFilament");
    ret_value.append(result);
    emit hideWidget();
    this->hide();
}

void askPause::cancelClick()
{
    QByteArray result = QByteArray("Cancel");
    ret_value.append(result);
    emit hideWidget();
    this->hide();
}
