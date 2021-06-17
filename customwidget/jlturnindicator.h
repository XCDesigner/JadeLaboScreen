#ifndef JLTURNINDICATOR_H
#define JLTURNINDICATOR_H

#include <QWidget>

namespace Ui {
class JLTurnIndicator;
}

class JLTurnIndicator : public QWidget
{
    Q_OBJECT

public:
    explicit JLTurnIndicator(QWidget *parent = nullptr);
    ~JLTurnIndicator();
    void setValue(int);
    void setText(QString);

private:
    Ui::JLTurnIndicator *ui;
    static QString leftStyleSheet;
    static QString rightStyleSheet;
    static QString normalStyleSheet;
};

#endif // JLTURNINDICATOR_H
