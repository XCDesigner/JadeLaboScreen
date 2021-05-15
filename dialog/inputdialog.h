#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include "jlwidget.h"
#include <QQuickItem>

namespace Ui {
class InputDialog;
}

class InputDialog : public JLWidget
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);
    ~InputDialog();

    void init(QByteArray) override;
    void show() override;

private slots:
    void onKeyPress(QString);
    void onDefaultPress(int);
    void onConfirmPress(int);

private:
    Ui::InputDialog *ui;
    QString accept_string;
};

#endif // INPUTDIALOG_H
