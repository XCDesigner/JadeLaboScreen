#ifndef WARNINGDIALOG_H
#define WARNINGDIALOG_H

#include "jlwidget.h"
#include <QQuickItem>

namespace Ui {
class WarningDialog;
}

class WarningDialog : public JLWidget
{
    Q_OBJECT

public:
    explicit WarningDialog(QWidget *parent = nullptr);
    ~WarningDialog();

    void init(QByteArray) override;
    void show() override;

private slots:
    void on_pushButton_359_clicked();

private:
    Ui::WarningDialog *ui;
    QMap<QString, QString> tips;
};

#endif // WARNINGDIALOG_H
