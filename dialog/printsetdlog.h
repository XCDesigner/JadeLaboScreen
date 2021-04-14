#ifndef PRINTSETDLOG_H
#define PRINTSETDLOG_H

#include <QWidget>
#include <QTimer>
#include <QQuickItem>
#include <QtQuickWidgets>
#include "define/imagePath.h"

namespace Ui {
class PrintSetDlog;
}

class PrintSetDlog : public QWidget
{
    Q_OBJECT

public:
    explicit PrintSetDlog(QWidget *parent = nullptr);
    ~PrintSetDlog();
    void initnum(QString a, QString b, QString c, QString d, QString e, QString f, QString g);
    void backup(int a );
    void updateButtonCheckStatus(int);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void increaseCheck();
    void decreaseCheck();

    void on_pushButton_3_clicked();

    void buttonClicked(int);

    void backupModeChange(int);

private:
    Ui::PrintSetDlog *ui;

    QTimer *m_tmr_check_increase;
    QTimer *m_tmr_check_decrease;

    QQuickWidget *pButtons[7];
    bool button_check_status[7];
signals:
    void closeset(int );


};

#endif // PRINTSETDLOG_H
