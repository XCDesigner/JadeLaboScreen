#include "askpause.h"
#include "ui_askpause.h"

askPause::askPause(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::askPause)
{
    ui->setupUi(this);

    ui->quickWidget->setSource(QUrl("qrc:/qml/PauseDialogItem.qml"));
    ui->quickWidget->setClearColor(QColor("#202020"));

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
    qDebug()<<"ask";
    strMachineStatus cur_status;
    m_xhPort->getXhPage()->GetMachineStatus(&cur_status);
    qDebug()<<cur_status.Status;
    if(cur_status.Status == 1)
        ui->quickWidget->rootObject()->setProperty("curStatus", "running");
    else if((cur_status.Status == 2) || (cur_status.Status == 4))
        ui->quickWidget->rootObject()->setProperty("curStatus", "pause");

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
    QByteArray result = QByteArray("Continue");
    ret_value.append(result);
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
