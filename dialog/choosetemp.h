#ifndef CHOOSETEMP_H
#define CHOOSETEMP_H

#include <QWidget>
#include "jlwidget.h"
#include <QQuickWidget>
#include <QQuickItem>
#include <QMetaObject>

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
    void onTempSelect(int Index);
};

#endif // CHOOSETEMP_H
