#ifndef CHANGEFILAMENTDLG_H
#define CHANGEFILAMENTDLG_H

#include <QWidget>
#include <QDebug>
#include <QObject>
#include <QQuickItem>
#include "jlwidget.h"
#include "choosetemp.h"

namespace Ui {
class changeFilamentDlg;
}

class changeFilamentDlg : public JLWidget
{
    Q_OBJECT

public:
    explicit changeFilamentDlg(QWidget *parent = nullptr);
    ~changeFilamentDlg();
    void init(QByteArray) override;
    void show() override;
    void setXHPort(XhPort *pPort);

private:
    chooseTemp *chooseTempDialog;
    uint8_t extruder_selected;
    bool autoUpdateStatus;

public slots:
    void updateStatusBar();
    void left_setTemp();
    void left_extrude();
    void left_retract();
    void right_setTemp();
    void right_extrude();
    void right_retract();
    void onSetTemp();
private slots:
    void on_pushButton_359_clicked();

private:
    Ui::changeFilamentDlg *ui;
};

#endif // CHANGEFILAMENTDLG_H
