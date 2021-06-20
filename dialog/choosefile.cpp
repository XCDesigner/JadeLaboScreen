#include "choosefile.h"
#include "ui_choosefile.h"

chooseFile::chooseFile(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::chooseFile)
{
    ui->setupUi(this);
}

chooseFile::~chooseFile()
{
    delete ui;
}

void chooseFile::show()
{
    QWidget::show();
}

void chooseFile::init(myListWidgetItem* pItem)
{
    QFont font;
    font.setBold(true);
    font.setFamily("barlow");
    font.setPixelSize(36);
    QFontMetrics font_metrics(font);
    QString cut_filename = font_metrics.elidedText(pItem->m_fileName, Qt::TextElideMode::ElideMiddle, 850);

    ui->label_2->setText(pItem->m_fileName + "?");
    ui->label_2->setAlignment(Qt::AlignCenter);
    m_fileName = pItem->m_fileName;
    m_filePath = pItem->m_filePath;
    file_source = pItem->isUDisk;
    select_item = pItem;
    ret_value.clear();
}

myListWidgetItem* chooseFile::getSelectItem()
{
    return select_item;
}

void chooseFile::setFileName(QString fileName)
{
    ui->label_2->setText(fileName+"?");
    ui->label_2->setAlignment(Qt::AlignCenter);
    m_fileName = fileName;
}

void chooseFile::on_pushButton_clicked()
{
    ret_value.append("Confirm");
    ret_value.append(file_source);
    emit hideWidget();
    hide();
}

void chooseFile::on_pushButton_2_clicked()
{
    ret_value.append("Cancel");
    emit hideWidget();
    hide();
}
