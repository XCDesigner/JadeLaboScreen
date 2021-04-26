#include "firststartdialog.h"
#include "ui_firststartdialog.h"

FirstStartDialog::FirstStartDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstStartDialog)
{
    ui->setupUi(this);
}

FirstStartDialog::~FirstStartDialog()
{
    delete ui;
}
