#include "printmodeselect.h"
#include "ui_printmodeselect.h"

PrintModeSelect::PrintModeSelect(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::PrintModeSelect)
{
    ui->setupUi(this);
    ui->qw_btnDirect->setClearColor("#2d2b2c");
    ui->qw_btnDuplicate->setClearColor("#2d2b2c");
    ui->qw_btnMirror->setClearColor("#2d2b2c");
    ui->qw_btnCancel->setClearColor("#2d2b2c");

    ui->qw_btnDirect->rootObject()->setProperty("text", "Direct");
    ui->qw_btnDuplicate->rootObject()->setProperty("text", "Duplicate");
    ui->qw_btnMirror->rootObject()->setProperty("text", "Mirror");
    ui->qw_btnCancel->rootObject()->setProperty("text", "Cancel");

    QFont *fonts = new QFont("barlow", 10, -1, false);
    fonts->setBold(true);
    fonts->setPixelSize(32);
    ui->qw_btnDirect->rootObject()->setProperty("font", *fonts);
    ui->qw_btnDuplicate->rootObject()->setProperty("font", *fonts);
    ui->qw_btnMirror->rootObject()->setProperty("font", *fonts);
    ui->qw_btnCancel->rootObject()->setProperty("font", *fonts);
    delete fonts;

    QColor *clr = new QColor(255, 255, 0);
    ui->qw_btnCancel->rootObject()->setProperty("border.width", 20);
    ui->qw_btnCancel->rootObject()->setProperty("border.color", *clr);
    delete clr;

    QObject::connect(ui->qw_btnDirect->rootObject(), SIGNAL(clicked(int)), this, SLOT(btnPrintDirect_clicked(int)));
    QObject::connect(ui->qw_btnDuplicate->rootObject(), SIGNAL(clicked(int)), this, SLOT(btnDuplicate_clicked(int)));
    QObject::connect(ui->qw_btnMirror->rootObject(), SIGNAL(clicked(int)), this, SLOT(btnMirror_clicked(int)));
    QObject::connect(ui->qw_btnCancel->rootObject(), SIGNAL(clicked(int)), this, SLOT(btnCancel_clicked(int)));
}

PrintModeSelect::~PrintModeSelect()
{
    delete ui;
}

void PrintModeSelect::init(QByteArray InitData, QString InputFile, QString OutputFile)
{
    input_file = InputFile;
    output_file_name = OutputFile;
    if((InitData == "Origin-Mirror") || (InitData == "Origin-Duplicate") || (InitData == "Unsupport") || (InitData == "Mix"))
    {
        ui->qw_btnDuplicate->rootObject()->setProperty("enable", false);
        ui->qw_btnMirror->rootObject()->setProperty("enable", false);
    }
    else if(InitData == "Duplicate")
    {
        ui->qw_btnMirror->rootObject()->setProperty("enable", false);
    }
}

void PrintModeSelect::init(QByteArray InitData, myListWidgetItem *pSelectItem)
{
    input_mode = InitData;
    p_file_item = pSelectItem;
    input_file = p_file_item->m_filePath;
    output_file_name = p_file_item->m_fileName;
    if((InitData == "Origin-Mirror") || (InitData == "Origin-Duplicate") || (InitData == "Unsupport") || (InitData == "Mix"))
    {
        ui->qw_btnDuplicate->rootObject()->setProperty("enable", false);
        ui->qw_btnMirror->rootObject()->setProperty("enable", false);
    }
    else if(InitData == "Duplicate")
    {
        ui->qw_btnMirror->rootObject()->setProperty("enable", false);
    }
}

void PrintModeSelect::show()
{
    QWidget::show();
}

myListWidgetItem* PrintModeSelect::getFileItem()
{
    return p_file_item;
}

QString PrintModeSelect::getInputFileName()
{
    return input_file;
}

QString PrintModeSelect::getOutputFileName()
{
    return output_file_name;
}

void PrintModeSelect::btnPrintDirect_clicked(int index)
{
    ret_value.append(QByteArray("Direct"));
    ret_value.append(input_mode);
    emit hideWidget();
    hide();
}

void PrintModeSelect::btnDuplicate_clicked(int index)
{
    ret_value.append(QByteArray("Duplicate"));
    ret_value.append(input_mode);
    emit hideWidget();
    hide();
}

void PrintModeSelect::btnMirror_clicked(int index)
{
    ret_value.append(QByteArray("Mirror"));
    ret_value.append(input_mode);
    emit hideWidget();
    hide();
}

void PrintModeSelect::btnCancel_clicked(int index)
{
    ret_value.append(QByteArray("Cancel"));
    emit hideWidget();
    hide();
}
