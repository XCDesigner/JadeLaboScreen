#ifndef CHOOSEFILE_H
#define CHOOSEFILE_H

#include <QWidget>
#include <QString>
#include "listwidgetitem/mylistwidgetitem.h"
#include "jlwidget.h"

namespace Ui {
class chooseFile;
}

class chooseFile : public JLWidget
{
    Q_OBJECT

public:
    explicit chooseFile(QWidget *parent = nullptr);
    ~chooseFile();

    void init(myListWidgetItem *);
    void show() override;
    myListWidgetItem*  getSelectItem();

    void setFileName(QString fileName);
    QString m_fileName;
    QString m_filePath;

private:
    QByteArray file_source;
    myListWidgetItem *select_item;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void choose();
private:
    Ui::chooseFile *ui;
};

#endif // CHOOSEFILE_H
