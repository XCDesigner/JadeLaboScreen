#ifndef XHPORT_H
#define XHPORT_H
/*3D打印机屏幕实例化这个类，并且绑定这个类的信号和屏幕的槽，
 * 这个类构造会打开串口，然后调用接口函数向主控发送串口指令，
 * 这个类会解析回复的信息，然后发送对应信号，操控屏幕*/
#include <QObject>
#include <QByteArray>
#include <QTimer>
#include <QDebug>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "xhpage.h"
#include "jlserialport.h"

#define PORTNAME "COM9"

class XhPort : public QObject
{
    Q_OBJECT
public:
    explicit XhPort(QObject *parent = nullptr);
    ~XhPort();

    /*屏幕主动请求接口函数(*表示指令发出后需要等待主控回复)*/
    /**********Frist Start**********/
    void askTemperature();//开机请求各项温度*
    void askStatus();//开机请求设备状态*
    void isHeating();//正在加热？*
    void calibrationPlatform();//校准平台*
    void isXYHeating();//是否在加热？*
    void XYAdjust();//校准XY轴

    /**********FILAMENT**********/
    void lup();
    void ldown();
    void rup();
    void rdown();

    /**********PRINT IDER**********/
    QByteArray startPrint(QString);
    void AcsPrint(QByteArray);
    void pausePrint();
    void stopPrint();
    void regainPrint();
    void readyprint(int ,QByteArray);

    void enbackup(bool );
    void setBackupEnableStatus(bool);
    void parcom(int );
    void askHotend();
    void askstate();

    void setPrintTempPercentage(int, uint8_t);
    void setPrintFanPercentage(int, uint8_t);
    void setPrintSpeedPercentage(uint16_t);
    void setPrintPlatformOffset(int32_t);

    void setExtruderDisable(uint8_t);
    /*********ERROR*************/
    void resume();
    void abort();
    void testr();
    void testb();

    void preparePrint(QString Mode, QByteArray Offset);
    void startPrint();

    /**********TOOL**********/

    void selfTest();//设备自检*
    void factoryReset();//恢复出厂设置
    /*platfrom*/
    void p_nozzleHeating();
    void p_platformCalibration();

    void finish();
    void cancleCalibration();
    /*nozzle*/
    void n_nozzleCalibration();
    /*xy*/
    void x_platformCalibration();
    void x_xyCalibration();

    void homeMove(QByteArray );//移动到起点
    void moveAxis(int, int, int, int);
    void setDualMode(int);

    void setRGBLight(int, int, int);
    void setLightOnOff(bool);

    void setHeattingUnit(int, int);
    void setHeattingUnit(int, int, int, int);
    void setHeattingUnit(QString, QString);
    void setHeattingUnit(QString, QString, QString);

    void setFilamentSensorEnableStatus(bool);
    void getFilamentSensorEnableStatus();

    void changeToolHead(int);

    void testdemo();

    void portInit(QString );//初始化串口
    bool serialOpen;//串口是否打开

    void selftest1();
    void selftest2();
    void selftest3();
    void selftest4();
    void selftest5();
//    void selftest6();
    void backupsend();
    void backuptsend();

    void carbinfinished();
    void carbincancel();

    void updateBegin(QString );

    XhPage* getXhPage();
    JLSerialPort* getSerialPort();

    void continuePrint();

    void startUpdate();
    void sendUpdateData(QByteArray Data);
    void sendEndUpdate();
    void sendUpdateInfo(QByteArray);
    void sendRebootSystem();

    void getPowerLostStatus();
    void markPowerLostFlag();
    void getRecoveryInfo();
    void resumeRecovery();

    void getFaultFlag();
private:
    // QSerialPort *m_serial;
    JLSerialPort *m_serial;

    XhPage *m_package;
    QByteArray ReceiveBuff;

    QTimer *portTimer;//专门用于测试通讯串口的计时器

signals:

    void firstTestResult(bool ,bool ,bool ,bool ,bool );
    void firstTemperatureResult(int ,int ,int ,int ,int ,int ,int ,QByteArray );
    void platCheck(bool );
    void xNoHeating(bool );
    void xyCheck(bool );
    /*tool*/
    void disUseFilament(bool );
    void backFactory(bool );

    /*tool calibration*/
    void pPlatformCalibration(qint32 ,qint32 ,qint32 ,qint32 );
    void nNozzleCalibration( int );
    void xPlatformCalibration(bool );
    void canelk();

    void fileSendOver();

    void powerlost();

    void selfTest1();
    void selfTest2();
    void selfTest3();
    void selfTest4();
    void selfTest5();
    void selfTest6();
    void updateBeginsignl();
    void xhupdateNum(int );
public slots:

private slots:
    void serialTest();//frsit start 开机测试串口是否打通

    void sendfile(QByteArray );

    void xhfirstTestResult(bool ,bool ,bool ,bool ,bool );
    void xhfirstTemperatureResult(int ,int ,int ,int ,int ,int ,int ,QByteArray );
    /*tool*/
    void xhdisUseFilament(bool );
    void xhbackFactory(bool );

    /*tool calibration*/
    void xhnNozzleCalibration( int );
    void xhxPlatformCalibration(bool );

    void fileSendOverSlot();
    void xhxNoHeating(bool );
    void xhxyCheck(bool );

    void xhpowerlost();

    void xhselfTest1();
    void xhselfTest2();
    void xhselfTest3();
    void xhselfTest4();
    void xhselfTest5();
    void xhselfTest6();

    void updateBeginSlot();
    void updateCheck(QByteArray );
    void updateSend(QByteArray ,int ,QByteArray );
    void updateOver();
    void updateNum(int );

    void readData(QByteArray Data);
};

#endif // XHPORT_H
