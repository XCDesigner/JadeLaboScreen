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
    void getMachineStatus();//开机请求各项温度*
    void askStatus();//开机请求设备状态*
    void isHeating();//正在加热？*
    void calibrationPlatform();//校准平台*
    void isXYHeating();//是否在加热？*
    void XYAdjust();//校准XY轴

    void ExtruderMotion(uint8_t Index, int32_t Distance);
    void prepareChangeFilament();
    void UnloadFilament(uint8_t Index);
    void LoadFilament(uint8_t Index) ;

    /**********PRINT IDER**********/
    QByteArray startPrint(QString);
    void pausePrint();
    void stopPrint();
    void readyprint(int ,QByteArray);

    void setBackupEnableStatus(bool);

    void setPrintTempPercentage(int, uint8_t);
    void setPrintFanPercentage(int, uint8_t);
    void setPrintSpeedPercentage(uint16_t);
    void setFlowratePercentage(uint8_t, uint16_t);
    void setPrintPlatformOffset(int32_t);

    void setExtruderDisable(uint8_t);

    void preparePrint(QString Mode, QByteArray Offset);
    void startPrint();

    /**********TOOL**********/

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

    void getBuildplatThickness();
    void setBuildplatThickness(float);

    void setRGBLight(int, int, int);
    void setLightOnOff(bool);
    void setStepperOnOff(bool);

    void setHeattingUnit(int, int);
    void setHeattingUnit(int, int, int, int);
    void setHeattingUnit(QString, QString);
    void setHeattingUnit(QString, QString, QString);

    void setFilamentSensorEnableStatus(bool);
    void getFilamentSensorEnableStatus();

    void changeToolHead(int);

    void getFirmwareVersion();

    void testdemo();

    void portInit(QString );//初始化串口
    bool serialOpen;//串口是否打开

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

    void trigglePowerLost();
    void triggleFilamentRunout(uint8_t Index);
    void getPowerLostStatus();
    void markPowerLostFlag();
    void getRecoveryInfo();
    void resumeRecovery();

    void getFaultFlag();

    void getTMCValue(uint8_t, QByteArray Address);
    void trigFILSample();
    void getFILValue();

    bool setPrintFile(QString);
    void sendFile(uint32_t Offset);
    uint32_t getPrintFileSize();
    void closeFile();

    void SendTest(QByteArray Datas);

    void writeCustomData(QByteArray Datas);

private:
    void lup();
    void ldown();
    void rup();
    void rdown();

private:
    // QSerialPort *m_serial;
    JLSerialPort *m_serial;

    XhPage *m_package;
    QByteArray ReceiveBuff;

    QFile *print_file;
    QString thisFilePath;
private slots:

    void readData(QByteArray Data);
};

#endif // XHPORT_H
