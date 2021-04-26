#ifndef FIRSTSTARTDIALOG_H
#define FIRSTSTARTDIALOG_H

#include <QWidget>

namespace Ui {
class FirstStartDialog;
}

class FirstStartDialog : public QWidget
{
    Q_OBJECT

public:
    explicit FirstStartDialog(QWidget *parent = nullptr);
    ~FirstStartDialog();

private:
    Ui::FirstStartDialog *ui;
};

#endif // FIRSTSTARTDIALOG_H
