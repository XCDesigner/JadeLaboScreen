#ifndef UPDATEPROGREBAR_H
#define UPDATEPROGREBAR_H

#include <QWidget>
#include <QQuickItem>
#include "jlwidget.h"

namespace Ui {
class updateProgreBar;
}

class updateProgreBar : public JLWidget
{
    Q_OBJECT

public:
    explicit updateProgreBar(QWidget *parent = nullptr);
    ~updateProgreBar();
    void show() override;

private:
    Ui::updateProgreBar *ui;
    QQuickItem *item;

public slots:
    void change(int );
signals:
    void sendSignalToQml(int );

};

#endif // UPDATEPROGREBAR_H
