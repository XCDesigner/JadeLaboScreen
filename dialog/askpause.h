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

    void init(QByteArray &) override;
    void show() override;
    void setXHPort(XhPort *pPort);

private slots:
    void on_btnCancel_clicked();
    void on_btnChangeFilament_clicked();
    void on_btnPauseContinue_clicked();

private:
    Ui::askPause *ui;
    bool last_left_extruder_enable;
    bool last_right_extruder_enable;
    QString current_status;
};

#endif // ASKPAUSE_H
