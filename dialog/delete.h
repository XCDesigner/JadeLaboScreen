#ifndef DELETE_H
#define DELETE_H

#include <QWidget>
#include "listwidgetitem/mylistwidgetitem.h"
#include "jlwidget.h"

namespace Ui {
class Delete;
}

class Delete : public JLWidget
{
    Q_OBJECT

public:
    explicit Delete(QWidget *parent = nullptr);
    ~Delete();
    void show() override;

    void init(QString, myListWidgetItem *);
    myListWidgetItem*  getDeleteItem();
    void setName();

private:
    QString fileName;
    QString filePath;
    myListWidgetItem * deleteItem;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void checkDelete(myListWidgetItem * deleteItem);
    void checkCancel(myListWidgetItem * deleteItem);

private:
    Ui::Delete *ui;
};

#endif // DELETE_H
