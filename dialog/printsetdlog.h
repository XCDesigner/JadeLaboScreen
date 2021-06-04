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
    void initnum(QString, QString, QString, QString, QString, QString, QString, QString, QString);
    void backup(int a );
    void updateButtonCheckStatus(int);
    void setXHPort(XhPort *pPort);
    void sendSetting();
    void init(QByteArray) override;
    void setPrintMode(QString);

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
    void UncheckAllButton();

private:
    Ui::PrintSetDlog *ui;

    QTimer *m_tmr_press_check;
    QString print_mode;

    QQuickWidget *pButtons[9];
    bool button_check_status[9];

    int16_t temp_percent[3];
    int8_t fan_percent[2];
    int16_t feedrate_percent;
    int platform_height;
    uint16_t flowrate_percent[2];

    int step_value;
    int change_value;
    int step_direction;

    int press_counter;
signals:
    void closeset(int );


};

#endif // PRINTSETDLOG_H
