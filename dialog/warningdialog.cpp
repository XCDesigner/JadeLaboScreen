#include "warningdialog.h"
#include "ui_warningdialog.h"

WarningDialog::WarningDialog(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::WarningDialog)
{
    ui->setupUi(this);

    tips.insert("Filament", "Filament fault error!");
    tips.insert("Movement", "Axis movement fault");
    tips.insert("PlatformCalibrate", "Glass collision detected Please remove print plate");
    tips.insert("XYCalibrate", "Glass collision detected Please remove print plate");
    tips.insert("NozzleCalibrate", "Glass collision detected Please remove print plate");

    images.insert("Filament", "");
    images.insert("Movement", "");
    images.insert("PlatformCalibrate", "url(:/image/platform_warning.png)");
    images.insert("XYCalibrate", "url(:/image/xy_warning.png)");
    images.insert("NozzleCalibrate", "url(:/image/nozzle_warning.png)");

    ui->label->setWordWrap(true);
}

WarningDialog::~WarningDialog()
{
    delete ui;
}

void WarningDialog::init(QByteArray &InitData)
{
    ui->label->setText(tips.value(QString(InitData)));
    qDebug()<<images.value(QString(InitData));
    char stylesheet[128];
    sprintf(stylesheet, "border-image: %s;", images.value(QString(InitData)).data());
    ui->labIcon->setStyleSheet(stylesheet);
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
