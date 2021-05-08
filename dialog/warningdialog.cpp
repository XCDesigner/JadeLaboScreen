#include "warningdialog.h"
#include "ui_warningdialog.h"

WarningDialog::WarningDialog(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::WarningDialog)
{
    ui->setupUi(this);
    tips.insert("Filament", "Filament fault error!");
    tips.insert("Axis", "Axis fault");
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
