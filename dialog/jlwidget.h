#ifndef JLWIDGET_H
#define JLWIDGET_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QByteArray>
#include "CMOD/xhport.h"
#include "CMOD/screenstatus.h"

class JLWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JLWidget(QWidget *parent = nullptr);

    virtual void init(QByteArray);
    virtual void show();
    virtual QList<QByteArray> get_return_value();
    void setScreenStausContext(ScreenStatus *pContext);

protected:
    QList<QByteArray> ret_value;
    XhPort *m_xhPort;
    ScreenStatus *pscreen_status;

signals:
    void hideWidget();
};

#endif // JLWIDGET_H
