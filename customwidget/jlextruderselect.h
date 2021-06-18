#ifndef JLEXTRUDERSELECT_H
#define JLEXTRUDERSELECT_H

#include <QWidget>

namespace Ui {
class JLExtruderSelect;
}

class JLExtruderSelect : public QWidget
{
    Q_OBJECT

public:
    explicit JLExtruderSelect(QWidget *parent = nullptr);
    ~JLExtruderSelect();
    void setText(QString);

signals:
    void clicked(int);

private slots:
    void on_btnLeft_clicked();

    void on_btnRight_clicked();

private:
    Ui::JLExtruderSelect *ui;
    int indicator;
    static QString leftSelectStyleSheet;
    static QString leftUnselectStyleSheet;
    static QString rightSelectStyleSheet;
    static QString rightUnselectStyleSheet;
};

#endif // JLEXTRUDERSELECT_H
