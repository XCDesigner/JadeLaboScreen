#ifndef JLBUTTON_H
#define JLBUTTON_H

#include <QLabel>
#include <QtDebug>

namespace Ui {
class JLButton;
}

class JLButton : public QLabel
{
    Q_OBJECT

public:
    explicit JLButton(QWidget *parent = nullptr);
    ~JLButton();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void leftClicked();
    void rightClicked();

private:
    Ui::JLButton *ui;
};

#endif // JLBUTTON_H
