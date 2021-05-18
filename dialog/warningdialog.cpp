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
    tips.insert("PlatformCalibrate", "Platform Calibration fault. Please remove the glass first");
    tips.insert("XYCalibrate", "XY Calibration fault. Please keep the nozzle clean and remove the glass");
    tips.insert("NozzleCalibrate", "Nozzle Calibration fault. Please keep the nozzle clean and remove the glass");
}

WarningDialog::~WarningDialog()
{
    delete ui;
}

void WarningDialog::init(QByteArray InitData)
{
    ui->label->setText(tips.value(QString(InitData)));
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
