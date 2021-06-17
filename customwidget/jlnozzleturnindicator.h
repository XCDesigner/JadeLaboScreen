#ifndef JLNOZZLETURNINDICATOR_H
#define JLNOZZLETURNINDICATOR_H

#include <QWidget>

namespace Ui {
class JLNozzleTurnIndicator;
}

class JLNozzleTurnIndicator : public QWidget
{
    Q_OBJECT

public:
    explicit JLNozzleTurnIndicator(QWidget *parent = nullptr);
    ~JLNozzleTurnIndicator();
    void setText(QString);
    void setValue(int);


private:
    Ui::JLNozzleTurnIndicator *ui;
    static QString upStyleSheet;
    static QString downStyleSheet;
};

#endif // JLNOZZLETURNINDICATOR_H
