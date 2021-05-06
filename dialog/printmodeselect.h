#ifndef PRINTMODESELECT_H
#define PRINTMODESELECT_H

#include "jlwidget.h"
#include <QQuickItem>
#include "listwidgetitem/mylistwidgetitem.h"

namespace Ui {
class PrintModeSelect;
}

class PrintModeSelect : public JLWidget
{
    Q_OBJECT

public:
    explicit PrintModeSelect(QWidget *parent = nullptr);
    ~PrintModeSelect();

    void init(QByteArray, myListWidgetItem*);
    void init(QByteArray InitData, QString InputFile, QString OutputFile);
    void show() override;
    myListWidgetItem* getFileItem();
    QString getInputFileName();
    QString getOutputFileName();

private slots:
    void btnPrintDirect_clicked(int);
    void btnDuplicate_clicked(int);
    void btnMirror_clicked(int);
    void btnCancel_clicked(int);

private:
    QByteArray input_mode;
    myListWidgetItem *p_file_item;
    QString input_file;
    QString output_file_name;

private:
    Ui::PrintModeSelect *ui;
};

#endif // PRINTMODESELECT_H
