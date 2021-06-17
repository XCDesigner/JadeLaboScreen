#ifndef JLCONTROLBOX_H
#define JLCONTROLBOX_H

#include <QWidget>

namespace Ui {
class JLControlBox;
}

class JLControlBox : public QWidget
{
    Q_OBJECT

public:
    explicit JLControlBox(QWidget *parent = nullptr);
    ~JLControlBox();
    void setText(QString Text);
    void setSettingEnable();
    void setStopEnable();
    void setPauseEnable();
    void setSettingDisable();
    void setStopDisable();
    void setPauseDisable();

private slots:
    void on_btnStop_clicked();

    void on_btnPause_clicked();

    void on_btnSetting_clicked();

signals:
    void settingClicked();
    void stopClicked();
    void pauseClicked();

private:
    Ui::JLControlBox *ui;
};

#endif // JLCONTROLBOX_H
