#ifndef CHOOSEEXTRUDERTEMP_H
#define CHOOSEEXTRUDERTEMP_H

#include "jlwidget.h"
#include <QObject>
#include <QQuickItem>

namespace Ui {
class ChooseExtruderTemp;
}

class ChooseExtruderTemp : public JLWidget
{
    Q_OBJECT

public:
    explicit ChooseExtruderTemp(QWidget *parent = nullptr);
    ~ChooseExtruderTemp();
    void init(QByteArray &) override;
    void show() override;

private slots:
    void onTempSelect(int);

private:
    Ui::ChooseExtruderTemp *ui;
    uint8_t extruder_index;
};

#endif // CHOOSEEXTRUDERTEMP_H
