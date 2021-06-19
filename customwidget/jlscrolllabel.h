#ifndef JLSCROLLLABEL_H
#define JLSCROLLLABEL_H

#include <QWidget>
#include <QTimer>
#include <QDebug>

namespace Ui {
class JLScrollLabel;
}

class JLScrollLabel : public QWidget
{
    Q_OBJECT

public:
    explicit JLScrollLabel(QWidget *parent = nullptr);
    ~JLScrollLabel();
    void setText(QString);

private slots:
    void onTimeout();

private:
    Ui::JLScrollLabel *ui;
    QString LabelText;
    QTimer tmr;
};

#endif // JLSCROLLLABEL_H
