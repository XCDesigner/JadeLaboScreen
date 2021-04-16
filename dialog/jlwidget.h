#ifndef JLWIDGET_H
#define JLWIDGET_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QByteArray>

class JLWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JLWidget(QWidget *parent = nullptr);

    virtual void init(QByteArray);
    virtual void show();
    virtual QList<QByteArray> get_return_value();

protected:
    QList<QByteArray> ret_value;

signals:
    void hideWidget();
};

#endif // JLWIDGET_H
