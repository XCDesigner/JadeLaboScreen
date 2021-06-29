#ifndef CHOOSEDISTANCE_H
#define CHOOSEDISTANCE_H

#include "jlwidget.h"
#include <QObject>
#include <QQuickItem>

namespace Ui {
class ChooseDistance;
}

class ChooseDistance : public JLWidget
{
    Q_OBJECT

public:
    explicit ChooseDistance(QWidget *parent = nullptr);
    ~ChooseDistance();
    void init(QByteArray &) override;
    void show() override;

private slots:
    void onDistanceSelect(QString);

private:
    Ui::ChooseDistance *ui;
    uint8_t extruder_index;
};

#endif // CHOOSEDISTANCE_H
