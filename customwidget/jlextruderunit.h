#ifndef JLEXTRUDERUNIT_H
#define JLEXTRUDERUNIT_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class JLExtruderUnit;
}

class JLExtruderUnit : public QWidget
{
    Q_OBJECT

public:
    explicit JLExtruderUnit(QWidget *parent = nullptr);
    ~JLExtruderUnit();
    void setIndicator(int);
    int getIndicator();
    void setExtruderEnable(bool);

    void setText(QString);
    void setTemperatureValue(int);
    void setDistanceValue(QString);
    QString getDistance();
    int getTemp();
signals:
    void chooseTempClicked(int);
    void chooseDistanceClicked(int);
    void cooldownClicked(int);
    void extrudeClicked(int);
    void retractClicked(int);

private slots:
    void on_btnUnload_clicked();

    void on_btnLoad_clicked();

    void on_btnCooldown_clicked();

    void on_btnChooseTemp_clicked();

    void on_btnChooseDistance_clicked();

private:
    Ui::JLExtruderUnit *ui;
    int indicator;
    QString distance[2];
    int temp[2];
};

#endif // JLEXTRUDERUNIT_H
