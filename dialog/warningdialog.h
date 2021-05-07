#ifndef WARNINGDIALOG_H
#define WARNINGDIALOG_H

#include <QWidget>

namespace Ui {
class WarningDialog;
}

class WarningDialog : public QWidget
{
    Q_OBJECT

public:
    explicit WarningDialog(QWidget *parent = nullptr);
    ~WarningDialog();

private:
    Ui::WarningDialog *ui;
};

#endif // WARNINGDIALOG_H
