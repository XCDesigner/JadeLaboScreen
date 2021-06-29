#ifndef FILAMENTFAULT_H
#define FILAMENTFAULT_H

#include <QWidget>
#include "jlwidget.h"

namespace Ui {
class filamentFault;
}

class filamentFault : public JLWidget
{
    Q_OBJECT

public:
    explicit filamentFault(QWidget *parent = nullptr);
    ~filamentFault();
    void show() override;
    void init(QByteArray &) override;

private:
    Ui::filamentFault *ui;

private slots:
    void on_btnResume_clicked();
    void on_btnChangeFilament_clicked();
    void on_btnAbort_clicked();
};

#endif // FILAMENTFAULT_H
