#ifndef PARSING_H
#define PARSING_H

#include <QWidget>
#include <QQuickItem>
#include "jlwidget.h"

namespace Ui {
class parsing;
}

class parsing : public JLWidget
{
    Q_OBJECT

public:
    explicit parsing(QWidget *parent = nullptr);
    ~parsing();
    void setNum(int num);
    void show() override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::parsing *ui;
    QQuickItem *item;

signals:
    void cancel();
    void sendSignalToQml(int );
};

#endif // PARSING_H
