#ifndef JLHEATINGUNIT_H
#define JLHEATINGUNIT_H

#include <QWidget>

namespace Ui {
class JLHeatingUnit;
}

class JLHeatingUnit : public QWidget
{
    Q_OBJECT

public:
    explicit JLHeatingUnit(QWidget *parent = nullptr);
    ~JLHeatingUnit();

    void setIndicator(int Index);
    void setText(QString);
    void setValue(int);
    void setExtruderEnable(bool);

private slots:
    void on_btnChooseTemp_clicked();
    void on_btnUnload_clicked();
    void on_btnLoad_clicked();

signals:
    void chooseTempClicked();
    void extrudeClicked();
    void retractClicked();

private:
    Ui::JLHeatingUnit *ui;
    int indicator;
    static QString leftBackgroundStyleSheet;
    static QString rightBackgroundStyleSheet;
};

#endif // JLHEATINGUINT_H
