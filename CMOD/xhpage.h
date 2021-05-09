#ifndef XHPAGE_H
#define XHPAGE_H

#include <QObject>
#include <QByteArray>
#include <QDebug>

#include <QTime>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>

#include <QtEndian>
#include <QDataStream>

#include "XhUpdater.h"

typedef struct {
    float ZHeight;
    int16_t CurTemp[3];
    int16_t TarTemp[3];
    uint16_t Percent;
    uint8_t Status;
}strMachineStatus;

class XhPage : public QObject
{
    Q_OBJECT
public:
    explicit XhPage(QObject *parent = nullptr);
    ~XhPage();

    /*****************解包******************/
    int analysis(QByteArray package);
    /*frist start页面*/
    void fSelfTest(QByteArray data);//自检
    void fTGet(QByteArray data);//温度获取
    /*TOOL页面*/
    void tSelfTest(QByteArray data);//自检

    /*****************组包******************/
    QByteArray groupPage(QByteArray );

    QByteArray chooseFile(QString );
    QByteArray analysisFile();
    void sendfile(quint32 );

    void updateBegin(QString );
    void sendUpdate(quint16 ,QByteArray );
    void GetMachineStatus(strMachineStatus *pStatus);

    bool setPrintFile(QString);
    uint32_t getPrintFileSize();
private:
    /*包体*/
    QByteArray pageHead;//头
    QByteArray pageType;//版本
    QByteArray pageLen;//长度
    QByteArray pageLsc;//长度校验
    QByteArray pageNature;//属性
    QByteArray pagedataNature;//数据校验
    QByteArray pageData;//内容

    /*first start自检变量*/
    bool Axistesting;
    bool Heatingtesting ;
    bool Platfomcheck;
    bool Nozzleheightcheck;
    bool XYcheck;

    /*tool 自检变量*/
    /*first start自检变量*/
    bool Taxistesting;
    bool Theatingtesting ;
    bool Tmaterialextrudetest;
    bool Tplatfomcheck;
    bool Tnozzleheightcheck;
    bool TxYcheck;

    /*当前文件打印文件路径*/
    QString thisFilePath;
    /*当前打印文件*/
    QFile *m_file;
    QTextStream *in;
    /*当前升级文件*/
    QFile *m_updateFile;
    /*LOG*/
    QFile *logText;
    QTime *logTime;
    QTimer *logFind;
    QTextStream *inu;
    QByteArray updateCheckSend;
    int mode[512];
    int offset[512];
    int size[512];
    int modenum;
    bool on;
    QTimer *m_timer;

    XhUpdater *m_upDater;

    strMachineStatus cur_machine_status;
signals:
    void command_received(uint8_t, uint8_t, QByteArray);
    /*first start*/
    void firstTestResult(bool ,bool ,bool ,bool ,bool );
    void firstTemperatureResult(int ,int ,int ,int ,int ,int ,int ,QByteArray );
    void xNoHeating(bool );
    void xyCheck(bool );
    /*tool*/
    void disUseFilament(bool );
    void backFactory(bool );

    /*tool calibration*/
    void pPlatformCalibration(qint32 ,qint32 ,qint32 ,qint32 );

    void nNozzleCalibration(int  );
    void xPlatformCalibration(bool );

    void sendFileArry(QByteArray );
    /*print*/
    void fileSendOver();//文件传输结束
    void goOnOk();

    void selfTest1();
    void selfTest2();
    void selfTest3();
    void selfTest4();
    void selfTest5();
    void selfTest6();

    void updateBeginSignls();
    void updateSerial(int );
    void updateCheck(QByteArray );
    void updateOver();
    void updateSend(QByteArray ,int ,QByteArray );

public slots:
    void timeEimt();
    void updaterOver();
    void logFindSlot();
};

#endif // XHPAGE_H
