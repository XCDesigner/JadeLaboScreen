#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

#include <QString>
#include <QByteArray>

class MainWindow;
typedef void (MainWindow::*pFunction)(QByteArray);

class ListenerItem
{
public:
    ListenerItem(){}
    ~ListenerItem(){}

    bool operator ==(ListenerItem Inst)
    {
        if((Data == Inst.Data) && (Repeated == Inst.Repeated) && (Callback == Inst.Callback))
            return true;
        else
            return false;
    }

public:
    QByteArray Data;
    bool Repeated;
    pFunction Callback;
};

typedef struct
{
    QString FileName;
    QString Mode;
    QString LeftTemp;
    QString RightTemp;
    QString BedTemp;
    float XOffset;
}strPrintDesc;

#endif // CUSTOM_TYPES_H
