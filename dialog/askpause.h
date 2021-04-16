#ifndef ASKPAUSE_H
#define ASKPAUSE_H

#include <QWidget>
#include <QDebug>
#include "jlwidget.h"

namespace Ui {
class askPause;
}

class askPause : public JLWidget
{
    Q_OBJECT

public:
    askPause(QWidget *parent = nullptr);
    ~askPause();

    void init(QByteArray) override;
    void show() override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


signals:
    void cancel();
    void m_stop();
    void m_paused();
    void sigHide();

private:
    Ui::askPause *ui;
};

#endif // ASKPAUSE_H
