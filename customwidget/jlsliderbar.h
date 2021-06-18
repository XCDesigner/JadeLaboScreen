#ifndef JLSLIDERBAR_H
#define JLSLIDERBAR_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class JLSliderBar;
}

class JLSliderBar : public QWidget
{
    Q_OBJECT

public:
    explicit JLSliderBar(QWidget *parent = nullptr);
    ~JLSliderBar();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;


signals:
    void pressed();

private:
    Ui::JLSliderBar *ui;
    bool isPressed;
    int value;
};

#endif // JLSLIDERBAR_H
