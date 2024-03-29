#ifndef PRINTSETDLOG_H
#define PRINTSETDLOG_H

#include <QWidget>
#include <QTimer>
#include <QQuickItem>
#include <QtQuickWidgets>
#include "jlwidget.h"
#include "define/imagePath.h"

namespace Ui {
class PrintSetDlog;
}

class PrintSetDlog : public JLWidget
{
    Q_OBJECT

public:
    explicit PrintSetDlog(QWidget *parent = nullptr);
    ~PrintSetDlog();
    void initnum(QString a, QString b, QString c, QString d, QString e, QString f, QString g);
    void backup(int a );
    void updateButtonCheckStatus(int);
    void setXHPort(XhPort *pPort);
    void sendSetting();
    void init(QByteArray) override;

private slots:
    void on_pushButton_clicked();

    void onIncreaseClicked();
    void onDecreaseClicked();

    void increaseCheck();
    void decreaseCheck();
    void onIncreaseRelease();
    void onDecreaseRelease();

    void buttonClicked(int);

    void backupModeChange(int);

private:
    int getStepValue();
    int getLongPressStepValue();

private:
    Ui::PrintSetDlog *ui;

    QTimer *m_tmr_check_increase;
    QTimer *m_tmr_check_decrease;

    QQuickWidget *pButtons[8];
    bool button_check_status[8];

    int16_t temp_percent[3];
    int8_t fan_percent[2];
    int16_t feedrate_percent;
    int platform_height;

    int step_value;
    int change_value;
    int step_direction;

    int press_counter;
signals:
    void closeset(int );


};

#endif // PRINTSETDLOG_H
