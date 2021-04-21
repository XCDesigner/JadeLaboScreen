#ifndef CHOOSETEMP_H
#define CHOOSETEMP_H

#include <QWidget>
#include "jlwidget.h"

namespace Ui {
class chooseTemp;
}

class chooseTemp : public JLWidget
{
    Q_OBJECT

public:
    explicit chooseTemp(QWidget *parent = nullptr);
    ~chooseTemp();
    void init(QString str);
    void show() override;

private:
    Ui::chooseTemp *ui;

signals:
    void heatT(QString str);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
};

#endif // CHOOSETEMP_H
