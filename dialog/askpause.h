#ifndef ASKPAUSE_H
#define ASKPAUSE_H

#include <QWidget>
#include <QDebug>
#include <QObject>
#include <QQuickItem>
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
    void setXHPort(XhPort *pPort);

private slots:
    void pauseClick();
    void continueClick();
    void changeFilamentClick();
    void cancelClick();


signals:
    void cancel();

private:
    Ui::askPause *ui;
};

#endif // ASKPAUSE_H
