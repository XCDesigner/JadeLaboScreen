#include "inputdialog.h"
#include "ui_inputdialog.h"

InputDialog::InputDialog(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);

    ui->qw_KeyBoard->setClearColor("#2d2c2b");
    ui->qw_Default->setClearColor("#2d2c2b");
    ui->qw_Confirm->setClearColor("#2d2c2b");
    ui->qw_Value->setClearColor("#2d2c2b");

    ui->qw_Default->rootObject()->setProperty("text",  "Default");
    ui->qw_Confirm->rootObject()->setProperty("text",  "Confirm");

    QObject::connect(ui->qw_KeyBoard->rootObject(), SIGNAL(keyEnter(QString)), this, SLOT(onKeyPress(QString)));
    QObject::connect(ui->qw_Default->rootObject(), SIGNAL(clicked(int)), this, SLOT(onDefaultPress(int)));
    QObject::connect(ui->qw_Confirm->rootObject(), SIGNAL(clicked(int)), this, SLOT(onConfirmPress(int)));
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::init(QByteArray InitData)
{
    QString value = QString(InitData);
    accept_string = value;
    ui->qw_Value->rootObject()->setProperty("text", accept_string + "mm");
    ret_value.clear();
}

void InputDialog::show()
{
    QWidget::show();
}

void InputDialog::onKeyPress(QString Key)
{
    if(Key != "bk")
    {
        QString try_string = accept_string + Key;
        bool ok;
        float try_value;
        try_value = try_string.toFloat(&ok);
        if((ok == true) && (try_value < 10)) {
            if((accept_string == "0") && (Key != ".")) {
                accept_string = Key;
            }
            else {
                accept_string = try_string;
            }
            ui->qw_Value->rootObject()->setProperty("text", accept_string + "mm");
        }
    }
    else
    {
        if(accept_string.length() > 0) {
            accept_string = accept_string.left(accept_string.length() - 1);
            if(accept_string.length() == 0)
                accept_string = "0";
            ui->qw_Value->rootObject()->setProperty("text", accept_string + "mm");
        }
    }

}

void InputDialog::onDefaultPress(int Index)
{
    accept_string = "5";
    ui->qw_Value->rootObject()->setProperty("text", accept_string + "mm");
}

void InputDialog::onConfirmPress(int Index)
{
    QByteArray value;
    value = accept_string.toUtf8();
    ret_value.append(value);
    emit hideWidget();
    hide();
}
