#ifndef JLONOFFSWITCH_H
#define JLONOFFSWITCH_H

#include <QWidget>

namespace Ui {
class JLOnOffSwitch;
}

class JLOnOffSwitch : public QWidget
{
    Q_OBJECT

public:
    explicit JLOnOffSwitch(QWidget *parent = nullptr);
    ~JLOnOffSwitch();
    bool getEnableStatus();
    void setText(QString);

signals:
    void clicked();

private slots:
    void on_btnCircle_clicked();

private:
    Ui::JLOnOffSwitch *ui;
    bool enableStatus;
};

#endif // JLONOFFSWITCH_H
