#ifndef CHOOSEBEDTEMP_H
#define CHOOSEBEDTEMP_H

#include "jlwidget.h"
#include <QQuickItem>

namespace Ui {
class ChooseBedTemp;
}

class ChooseBedTemp : public JLWidget
{
    Q_OBJECT

public:
    explicit ChooseBedTemp(QWidget *parent = nullptr);
    ~ChooseBedTemp();
    void init(QByteArray &) override;
    void show() override;

private slots:
    void onTempSelect(int);

private:
    Ui::ChooseBedTemp *ui;
};

#endif // CHOOSEBEDTEMP_H
