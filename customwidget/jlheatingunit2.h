#ifndef JLHEATINGUNIT2_H
#define JLHEATINGUNIT2_H

#include <QWidget>

namespace Ui {
class JLHeatingUnit2;
}

class JLHeatingUnit2 : public QWidget
{
    Q_OBJECT

public:
    explicit JLHeatingUnit2(QWidget *parent = nullptr);
    ~JLHeatingUnit2();
    void setIndicator(int Index);
    void setText(QString);
    void setValue(int);

private slots:
    void on_btnChooseTemp_clicked();
    void on_btnCooldown_clicked();

signals:
    void chooseTempClicked(int);
    void cooldownClicked(int);

private:
    Ui::JLHeatingUnit2 *ui;
    static QString leftBackgroundStyleSheet;
    static QString rightBackgroundStyleSheet;
    static QString leftCooldownStyleSheet;
    static QString rightCooldownStyleSheet;
    int indicator;
};

#endif // JLHEATINGUNIT2_H
