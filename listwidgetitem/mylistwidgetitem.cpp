#include "mylistwidgetitem.h"
#include "ui_mylistwidgetitem.h"

myListWidgetItem::myListWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myListWidgetItem)
{
    ui->setupUi(this);
    isUDisk = "";
}

myListWidgetItem::~myListWidgetItem()
{
    delete ui;
}

void myListWidgetItem::m_addItem(const QString &fileName, QString filePath)
{
    QFont font;
    font.setBold(true);
    font.setFamily("barlow");
    font.setPixelSize(36);
    QFontMetrics font_metrics(font);
    QString cut_filename = font_metrics.elidedText(fileName, Qt::TextElideMode::ElideMiddle, 950);


    ui->pushButton_2->setText(cut_filename);
    m_filePath = filePath;
    m_fileName = fileName;
}

void myListWidgetItem::on_pushButton_clicked()
{
    emit deleteItem(this);
}

void myListWidgetItem::on_pushButton_2_clicked()
{
    emit chooseFile(this);
}
