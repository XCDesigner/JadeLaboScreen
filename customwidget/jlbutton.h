#ifndef JLBUTTON_H
#define JLBUTTON_H

#include <QWidget>

namespace Ui {
class JLButton;
}

class JLButton : public QWidget
{
    Q_OBJECT

public:
    explicit JLButton(QWidget *parent = nullptr);
    ~JLButton();

private:
    Ui::JLButton *ui;
};

#endif // JLBUTTON_H
