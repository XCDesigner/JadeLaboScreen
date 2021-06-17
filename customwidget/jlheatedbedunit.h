#ifndef JLHEATEDBEDUNIT_H
#define JLHEATEDBEDUNIT_H

#include <QWidget>

namespace Ui {
class JLHeatedbedUnit;
}

class JLHeatedbedUnit : public QWidget
{
    Q_OBJECT

public:
    explicit JLHeatedbedUnit(QWidget *parent = nullptr);
    ~JLHeatedbedUnit();
    void setText(QString);
    void setValue(int);

signals:
    void chooseTempClicked();
    void cooldownClicked();

private slots:
    void on_btnChooseTemp_clicked();

    void on_btnCooldown_clicked();

private:
    Ui::JLHeatedbedUnit *ui;
};

#endif // JLHEATEDBEDUNIT_H
