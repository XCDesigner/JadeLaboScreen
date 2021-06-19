#include "jlscrolllabel.h"
#include "ui_jlscrolllabel.h"

JLScrollLabel::JLScrollLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JLScrollLabel)
{
    ui->setupUi(this);
    tmr.setInterval(200);
    QObject::connect(&tmr, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

JLScrollLabel::~JLScrollLabel()
{
    delete ui;
}

void JLScrollLabel::setText(QString Text)
{
    LabelText = Text;
    QFont font;
    font.setFamily("barlow");
    font.setPixelSize(48);
    font.setBold(true);
    QFontMetrics fm(font);
    QRect rec = fm.boundingRect(LabelText);
    ui->labText->setText(LabelText);
    qDebug()<<rec.width();
    if(rec.width() > 600)
    {
        qDebug()<<"Start Scroll";
        ui->labText->setGeometry(0, 0, rec.width(), 80);
        tmr.start();
    }
    else
    {
        qDebug()<<"Stop Scroll";
        tmr.stop();
        ui->labText->setGeometry(0, 0, 600, 80);
    }
}

void JLScrollLabel::onTimeout()
{
    int last_x = ui->labText->x();
    if(last_x <= -ui->labText->width())
    {
        ui->labText->setGeometry(50, 0, ui->labText->width(), ui->labText->height());
    }
    else
    {
        ui->labText->setGeometry(last_x-5, 0, ui->labText->width(), ui->labText->height());
    }
}
