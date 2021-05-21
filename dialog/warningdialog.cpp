#include "warningdialog.h"
#include "ui_warningdialog.h"

WarningDialog::WarningDialog(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::WarningDialog)
{
    ui->setupUi(this);

    ui->qw_Icon->rootObject()->setProperty("icon", "qrc:/image/warning.png");
    ui->qw_Icon->rootObject()->setProperty("pressedIcon", "qrc:/image/warning.png");
    ui->qw_Icon->setClearColor(QColor(32, 32, 32));

    tips.insert("Filament", "Filament fault error!");
    tips.insert("Movement", "Axis movement fault");
    tips.insert("PlatformCalibrate", "Glass collision detected Please remove print plate");
    tips.insert("XYCalibrate", "Glass collision detected Please remove print plate");
    tips.insert("NozzleCalibrate", "Glass collision detected Please remove print plate");

    images.insert("Filament", "");
    images.insert("Movement", "");
    images.insert("PlatformCalibrate", "qrc:/image/platform_warning.png");
    images.insert("XYCalibrate", "qrc:/image/xy_warning.png");
    images.insert("NozzleCalibrate", "qrc:/image/nozzle_warning.png");

    ui->label->setWordWrap(true);
}

WarningDialog::~WarningDialog()
{
    delete ui;
}

void WarningDialog::init(QByteArray InitData)
{
    ui->label->setText(tips.value(QString(InitData)));
    qDebug()<<images.value(QString(InitData));
    ui->qw_Icon->rootObject()->setProperty("icon", images.value(QString(InitData)));
    ui->qw_Icon->rootObject()->setProperty("pressedIcon", images.value(QString(InitData)));
}

void WarningDialog::show()
{
    QWidget::show();
}

void WarningDialog::on_pushButton_359_clicked()
{
    emit hideWidget();
    hide();
}
