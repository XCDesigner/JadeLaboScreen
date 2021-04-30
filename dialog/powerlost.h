#ifndef POWERLOST_H
#define POWERLOST_H

#include <QWidget>
#include "jlwidget.h"

namespace Ui {
class powerLost;
}

class powerLost : public JLWidget
{
    Q_OBJECT

public:
    explicit powerLost(QWidget *parent = nullptr);
    ~powerLost();
    void show() override;
    void init(QByteArray) override;

private slots:
    void on_btnResume_clicked();
    void on_btnCancel_clicked();

private:
    Ui::powerLost *ui;
};

#endif // POWERLOST_H
