#ifndef CHOOSEBEDTEMP_H
#define CHOOSEBEDTEMP_H

#include <QWidget>

namespace Ui {
class ChooseBedTemp;
}

class ChooseBedTemp : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseBedTemp(QWidget *parent = nullptr);
    ~ChooseBedTemp();

private:
    Ui::ChooseBedTemp *ui;
};

#endif // CHOOSEBEDTEMP_H
