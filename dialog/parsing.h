#ifndef PARSING_H
#define PARSING_H

#include <QWidget>
#include <QQuickItem>
#include "jlwidget.h"
#include "CMOD/XhGcodeFileParser.h"

namespace Ui {
class parsing;
}

class parsing : public JLWidget
{
    Q_OBJECT

public:
    explicit parsing(QWidget *parent = nullptr);
    ~parsing();
    void init(QByteArray, QString, QString, QString);
    void show() override;

private slots:
    void on_pushButton_clicked();
    void updateParsingStatus();
    void onParseComplete(QString);
    void onDelayReturn();

private:
    Ui::parsing *ui;
    QQuickItem *item;
    XhGcodeFileParser *m_file_parser;
    bool is_parsing;
    QString output_file_name;
    QString req_mode;

signals:
    void cancel();
    void sendSignalToQml(int );
};

#endif // PARSING_H
