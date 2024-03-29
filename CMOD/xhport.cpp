#include "xhport.h"

// B: int buffer 
// I: Int value
#define FILL_QBYTEARRAY_32(B, I)    do { B[0]=I; \
                                       B[1]=(unsigned char)(I>>8); \
                                       B[2]=(unsigned char)(I>>16); \
                                       B[3]=(unsigned char)(I>>24); \
                                    }while(0)

XhPort::XhPort(QObject *parent) : QObject(parent)
{
    portTimer = new QTimer(this);
    m_package = new XhPage;
    serialOpen =false;
    /*打开串口*/
    QObject::connect(m_package,&XhPage::sendFileArry,this,&XhPort::sendfile);

    QObject::connect(m_package,&XhPage::firstTestResult,this,&XhPort::xhfirstTestResult);
    QObject::connect(m_package,&XhPage::firstTemperatureResult,this,&XhPort::xhfirstTemperatureResult);
    /*tool*/
    QObject::connect(m_package,&XhPage::disUseFilament,this,&XhPort::xhdisUseFilament);
    QObject::connect(m_package,&XhPage::backFactory,this,&XhPort::xhbackFactory);

    /*tool calibration*/
    QObject::connect(m_package,&XhPage::nNozzleCalibration,this,&XhPort::xhnNozzleCalibration);
    QObject::connect(m_package,&XhPage::xPlatformCalibration,this,&XhPort::xhxPlatformCalibration);

    QObject::connect(m_package,&XhPage::fileSendOver,this,&XhPort::fileSendOverSlot);

    QObject::connect(m_package,&XhPage::xNoHeating,this,&XhPort::xhxNoHeating);
    QObject::connect(m_package,&XhPage::xyCheck,this,&XhPort::xhxyCheck);

    QObject::connect(m_package,&XhPage::selfTest1,this,&XhPort::xhselfTest1);
    QObject::connect(m_package,&XhPage::selfTest2,this,&XhPort::xhselfTest2);
    QObject::connect(m_package,&XhPage::selfTest3,this,&XhPort::xhselfTest3);
    QObject::connect(m_package,&XhPage::selfTest4,this,&XhPort::xhselfTest4);
    QObject::connect(m_package,&XhPage::selfTest5,this,&XhPort::xhselfTest5);
    QObject::connect(m_package,&XhPage::selfTest6,this,&XhPort::xhselfTest6);

    QObject::connect(m_package,&XhPage::updateBeginSignls,this,&XhPort::updateBeginSlot);
    QObject::connect(m_package,&XhPage::updateCheck,this,&XhPort::updateCheck);
    QObject::connect(m_package,&XhPage::updateSend,this,&XhPort::updateSend);
    QObject::connect(m_package,&XhPage::updateOver,this,&XhPort::updateOver);
    QObject::connect(m_package,&XhPage::updateSerial,this,&XhPort::updateNum);


}

XhPort::~XhPort()
{
    delete m_serial;
    delete portTimer;
    delete m_package;
}

/*请求温度*/
void XhPort::askTemperature()
{
    QByteArray buff = QByteArray::fromHex("4A4630020002E001000100");
    m_serial->write(buff);
}
/*请求状态*/
void XhPort::askStatus()
{
    QByteArray buff = QByteArray::fromHex("4A4630020002E003000102");
    m_serial->write(buff);
}

void XhPort::isHeating()
{
    QByteArray buff = QByteArray::fromHex("4A4630020002E005000104");
    m_serial->write(buff);
}

void XhPort::calibrationPlatform()
{
    QByteArray buff = QByteArray::fromHex("4A4630020002E006000105");
    m_serial->write(buff);
}

void XhPort::isXYHeating()
{
    QByteArray buff = QByteArray::fromHex("4A4630020002E007000106");
    m_serial->write(buff);
}

void XhPort::XYAdjust()
{
    QByteArray buff = QByteArray::fromHex("4A4630020002E008000107");
    m_serial->write(buff);
}

void XhPort::lup()
{
    QByteArray s = QByteArray::fromHex("0205006079FEFF");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::ldown()
{
    QByteArray s = QByteArray::fromHex("020500A0860100");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::rup()
{
    QByteArray s = QByteArray::fromHex("0205016079FEFF");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::rdown()
{
    QByteArray s = QByteArray::fromHex("020501A0860100");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

QByteArray XhPort::startPrint(QString m_filePath)
{
    QByteArray buff = m_package->chooseFile(m_filePath);
    return  buff;
}

void XhPort::AcsPrint(QByteArray a)
{
    m_serial->write(a);
}

void XhPort::regainPrint()
{
    QByteArray s = QByteArray::fromHex("060C");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::readyprint(int Mode, QByteArray Offset)
{
    QByteArray s;
    char strMode[][7] = {"060D00", "060D01", "060D02", "060D03", "060D04", "060D05", "060D06"};
    s = QByteArray::fromHex(strMode[Mode]);
    s.append(Offset);
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::enbackup(bool a )
{
    if(a)
    {
        QByteArray s = QByteArray::fromHex("011101");
        QByteArray buff = m_package->groupPage(s);
        m_serial->write(buff);
    }
    else {
        QByteArray s = QByteArray::fromHex("011100");
        QByteArray buff = m_package->groupPage(s);
        m_serial->write(buff);
    }
}

void XhPort::setBackupEnableStatus(bool Enable)
{
    if(Enable == true)
    {
        QByteArray s = QByteArray::fromHex("010F01");
        QByteArray buff = m_package->groupPage(s);
        m_serial->write(buff);
    }
    else {
        QByteArray s = QByteArray::fromHex("010F00");
        QByteArray buff = m_package->groupPage(s);
        m_serial->write(buff);
    }
}

void XhPort::parcom(int a )
{
    if(a == 0)
    {
        QByteArray s = QByteArray::fromHex("010F00");
        QByteArray buff = m_package->groupPage(s);
        m_serial->write(buff);
    }
    else {
        QByteArray s = QByteArray::fromHex("010F01");
        QByteArray buff = m_package->groupPage(s);
        m_serial->write(buff);
    }
}

void XhPort::askHotend()
{
    QByteArray s = QByteArray::fromHex("0106");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::askstate()
{
    QByteArray s = QByteArray::fromHex("010D");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::resume()
{
    QByteArray buff = QByteArray::fromHex("4A4630020002001200060C");
    m_serial->write(buff);
}

void XhPort::abort()
{
    QByteArray buff = QByteArray::fromHex("4A46300200020007000601");
    m_serial->write(buff);
}

void XhPort::testr()
{
    QByteArray buff = QByteArray::fromHex("4A4630060006001D000B0210000000");
    m_serial->write(buff);
}

void XhPort::testb()
{
    QByteArray buff = QByteArray::fromHex("4A4630020002000E000B03");
    m_serial->write(buff);
}

/*设备自检*/
void XhPort::selfTest()
{
    QByteArray s = QByteArray::fromHex("050A");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);

}

void XhPort::factoryReset()
{
    QByteArray s = QByteArray::fromHex("0901");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::p_nozzleHeating()
{
    QByteArray s = QByteArray::fromHex("030200");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::p_platformCalibration()
{
    QByteArray s = QByteArray::fromHex("0302");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::finish()
{
    QByteArray s = QByteArray::fromHex("0309");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::cancleCalibration()
{
    QByteArray s = QByteArray::fromHex("030A");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::n_nozzleCalibration()
{
    QByteArray s = QByteArray::fromHex("0300");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::x_platformCalibration()
{
    QByteArray s = QByteArray::fromHex("0309");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::x_xyCalibration()
{
    QByteArray s = QByteArray::fromHex("0305");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Request home aixs 
  * @param  AxisFlag: Flags, {XAxis, YAxis, ZAxis}. 1 for home
  * @retval None
  */
void XhPort::homeMove(QByteArray AxisFlag)
{
    QByteArray s = QByteArray::fromHex("0203");
    s.append(AxisFlag);
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Request move axis
  * @param  Mode: 0 for absolute mode. 1 for relative mode
  * @param  X: X distance in micron meter
  * @param  Y: Y distance in micron meter
  * @param  Z: Z distance in micron meter
  * @retval None
  */
void XhPort::moveAxis(int Mode, int X, int Y, int Z)
{
    QByteArray s = QByteArray::fromHex("0202");
    s.append(1, Mode);
    QByteArray value;
    value.resize(4);
    FILL_QBYTEARRAY_32(value, X);
    s.append(value);
    FILL_QBYTEARRAY_32(value, Y);
    s.append(value);
    FILL_QBYTEARRAY_32(value, Z);
    s.append(value);
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Set dual carrier mode 
  * @param  Mode: 0 for full control, 1 for auto park, 2 for duplicate, 3 for mirror.
  * @retval None
  */
void XhPort::setDualMode(int Mode)
{
    QByteArray s = QByteArray::fromHex("0206");
    s.append(1, Mode);
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Set light 
  * @param  R: Value for channel R
  * @param  G: Value for channel G
  * @param  B: Value for channel B
  * @retval None
  */
void XhPort::setRGBLight(int R, int G, int B)
{
    QByteArray s = QByteArray::fromHex("0204");
    s.append(1, R);
    s.append(1, G);
    s.append(1, B);
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Set light onoff
  * @param  OnOff
  * @retval None
  */
void XhPort::setLightOnOff(bool OnOff)
{
    QByteArray s = QByteArray::fromHex("0207");
    if(OnOff == true)
        s.append(1, 1);
    else
        s.append(1, 0);
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Set temperature to the heating unit
  * @param  Index: Index of the heating unit. 0 for left extruder, 1 for right extruder, 2 for heatedbed
  * @param  Temp: Target temperature
  * @retval None
  */
void XhPort::setHeattingUnit(int Index, int Temp)
{
    QByteArray s = QByteArray::fromHex("0200");
    s.append(1, Index);
    s.append(1, (Temp));
    s.append(1, (Temp >> 8));
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Set temperature to the heating unit
  * @param  Index(n): Index of the heating unit. 0 for left extruder, 1 for right extruder, 2 for heatedbed
  * @param  Temp(n): Target temperature
  * @retval None
  */
void XhPort::setHeattingUnit(int Index0, int Temp0, int Index1, int Temp1)
{
    setHeattingUnit(Index0, Temp0);
    setHeattingUnit(Index1, Temp1);
}

/**
  * @brief  Set temperature to the heating unit
  * @param  strLeftTemp: Temperature of the left nozzle, etc "200"
  * @param  strRightTemp: Temperature of the right nozzle
  * @retval None
  */
void XhPort::setHeattingUnit(QString strLeftTemp, QString strRightTemp)
{
    setHeattingUnit(0, strLeftTemp.toFloat());
    setHeattingUnit(1, strRightTemp.toFloat());
}

/**
  * @brief  Set temperature to the heating unit
  * @param  strLeftTemp: Temperature of the left nozzle, etc "200"
  * @param  strRightTemp: Temperature of the right nozzle
  * @retval None
  */
void XhPort::setHeattingUnit(QString strLeftTemp, QString strRightTemp, QString strBedTemp)
{
    setHeattingUnit(0, strLeftTemp.toFloat());
    setHeattingUnit(1, strRightTemp.toFloat());
    setHeattingUnit(2, strBedTemp.toFloat());
}

/**
  * @brief  Set filament sensor enable status
  * @param  NewStatus: True for enable sensor. False for disable sensor
  * @retval None
  */
void XhPort::setFilamentSensorEnableStatus(bool NewStatus)
{
    QByteArray buff;
    if (NewStatus == true)
        buff = m_package->groupPage(QByteArray::fromHex("070001"));
    else
        buff = m_package->groupPage(QByteArray::fromHex("070000"));
    m_serial->write(buff);
}

/**
  * @brief  Get filament sensor enable status
  * @retval None
  */
void XhPort::getFilamentSensorEnableStatus()
{
    QByteArray buff = m_package->groupPage(QByteArray::fromHex("0701"));
    m_serial->write(buff);
}

/**
  * @brief  Change tool head
  * @param  Index: Index of the x carrier. 0 for left, 1 for right
  * @retval None
  */
void XhPort::changeToolHead(int Index)
{
    QByteArray s = QByteArray::fromHex("0208");
    s.append(1, Index);
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Set Temperaure percent
  * @param  Index: Index of the x carrier. 0 for left, 1 for right
  * @param  Percent: Percentage
  * @retval None
  */
void XhPort::setPrintTempPercentage(int Index, uint8_t Percent)
{
    QByteArray s = QByteArray::fromHex("0610");
    s.append(1, Index);
    s.append(1, Percent);
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Set fan percent
  * @param  Index: Index of the x carrier. 0 for left, 1 for right
  * @param  Percent: Percentage
  * @retval None
  */
void XhPort::setPrintFanPercentage(int Index, uint8_t Percent)
{
    QByteArray s = QByteArray::fromHex("0611");
    s.append(1, Index);
    s.append(1, Percent);
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Set print speed percent
  * @param  Percent: Percentage
  * @retval None
  */
void XhPort::setPrintSpeedPercentage(uint16_t Percent)
{
    QByteArray s = QByteArray::fromHex("0612");
    s.append(1, Percent);
    s.append(1, (Percent >> 8));
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Set print platform offset
  * @param  Height: Offset in micronmeters
  * @retval None
  */
void XhPort::setPrintPlatformOffset(int32_t Height)
{
    QByteArray s = QByteArray::fromHex("0613");
    s.append(1, Height);
    s.append(1, (Height >> 8));
    s.append(1, (Height >> 16));
    s.append(1, (Height >> 24));
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Pause printing
  * @retval None
  */
void XhPort::pausePrint()
{
    QByteArray s = QByteArray::fromHex("0602");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Continue printing
  * @retval None
  */
void XhPort::continuePrint()
{
    QByteArray s = QByteArray::fromHex("060C");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Stop printing
  * @retval None
  */
void XhPort::stopPrint()
{
    QByteArray s = QByteArray::fromHex("0601");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/**
  * @brief  Set extruder enable. This function can be called in Duplicate Mode or Mirror Mode
  * @param  Index: The index of the extuder. 0 for left, 1 for right
  * @retval None
  */
void XhPort::setExtruderDisable(uint8_t Index)
{
    QByteArray buff;
    if(Index == 0)
        buff = m_package->groupPage(QByteArray::fromHex("010700"));
    else if(Index == 1)
        buff = m_package->groupPage(QByteArray::fromHex("010701"));
    m_serial->write(buff);
}

/**
  * @brief  Request print to start update
  * @retval None
  */
void XhPort::startUpdate()
{
    m_serial->writeProtocalData(QByteArray::fromHex("0500"));
}

/**
  * @brief  Set extruder enable. This function can be called in Duplicate Mode or Mirror Mode
  * @param  Data: The datas to send
  * @retval None
  */
void XhPort::sendUpdateData(QByteArray Data)
{
    QByteArray s = QByteArray::fromHex("050100");
    s.append(Data);
    m_serial->writeProtocalData(s);
}

/**
  * @brief  End update.Send this command when there is no package left
  * @retval None
  */
void XhPort::sendEndUpdate()
{
    m_serial->writeProtocalData(QByteArray::fromHex("050200"));
}

/**
  * @brief  Send printer update information to write to the flash
  * @retval None
  */
void XhPort::sendUpdateInfo(QByteArray InfoData)
{
    QByteArray s = QByteArray::fromHex("050B");
    s.append(InfoData);
    m_serial->writeProtocalData(s);
}

/**
  * @brief  Send reboot system
  * @retval None
  */
void XhPort::sendRebootSystem()
{
    m_serial->writeProtocalData(QByteArray::fromHex("050C"));
}

/**
  * @brief  Get power lost status
  * @retval None
  */
void XhPort::getPowerLostStatus()
{
    m_serial->writeProtocalData(QByteArray::fromHex("0103"));
}

/**
  * @brief  Mark power lost flag
  * @retval None
  */
void XhPort::markPowerLostFlag()
{
    m_serial->writeProtocalData(QByteArray::fromHex("060F"));
}

/**
  * @brief  Get recovery info
  * @retval None
  */
void XhPort::getRecoveryInfo()
{
    m_serial->writeProtocalData(QByteArray::fromHex("0615"));
}

/**
  * @brief  Start recovery print
  * @retval None
  */
void XhPort::resumeRecovery()
{
    m_serial->writeProtocalData(QByteArray::fromHex("060E"));
}

/**
  * @brief  Get fault flag
  * @retval None
  */
void XhPort::getFaultFlag()
{
    m_serial->writeProtocalData(QByteArray::fromHex("0101"));
}

/**
  * @brief  Prepare printing
  * @param  Mode:
  * @retval None
  */
void XhPort::preparePrint(QString Mode, QByteArray Offset)
{
    QByteArray s;
    QMap<QString, QByteArray> map;
    map["Direct"] = QByteArray::fromHex("060D00");
    map["Duplicate"] = QByteArray::fromHex("060D02");
    map["Mirror"] = QByteArray::fromHex("060D03");
    map["Origin-Duplicate"] = QByteArray::fromHex("060D04");
    map["Origin-Mirror"] = QByteArray::fromHex("060D05");
    map["Origin-Mix"] = QByteArray::fromHex("060D06");
    map["Unsupport"] = QByteArray::fromHex("060D00");

    s = map[Mode];
    s.append(Offset);
    qDebug()<<"send:" << s;
    m_serial->writeProtocalData(s);
}

/**
  * @brief  Start printing
  * @param  Mode:
  * @retval None
  */
void XhPort::startPrint()
{
    QByteArray s = QByteArray::fromHex("0606");
    uint32_t file_size = m_package->getPrintFileSize();
    qDebug()<<"Size:" << file_size;
    s.append(1, file_size);
    s.append(1, file_size >> 8);
    s.append(1, file_size >> 16);
    s.append(1, file_size >> 24);
    s.append(1, 0xff);
    s.append(1, 0xff);
    s.append(1, 0xff);
    s.append(1, 0xff);
    qDebug()<<"Start print:" << s;
    m_serial->writeProtocalData(s);
}

void XhPort::testdemo()
{
    QByteArray s = QByteArray::fromHex("84654875294581");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

/*打开串口*/
void XhPort::portInit(QString portname)
{
    m_serial = new JLSerialPort();
    if(m_serial->openPort(portname, 115200))
    {
        QObject::connect(m_serial, SIGNAL(sigDataParsed(QByteArray)), this, SLOT(readData(QByteArray)));//连接信号槽
        // QObject::connect(portTimer, &QTimer::timeout, this, &XhPort::serialTest);//连接信号槽
        // portTimer->start(500);
    }
    else
    {
        qDebug()<<"serial open false!";
    }
}

void XhPort::selftest2()
{
    QByteArray s = QByteArray::fromHex("0506");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::selftest3()
{
    QByteArray s = QByteArray::fromHex("0507");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::selftest4()
{
    QByteArray s = QByteArray::fromHex("0508");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::selftest5()
{
    QByteArray s = QByteArray::fromHex("0509");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::backupsend()
{
    QByteArray s = QByteArray::fromHex("010E");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::backuptsend()
{
    QByteArray s = QByteArray::fromHex("0110");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::carbinfinished()
{
    QByteArray s = QByteArray::fromHex("0309");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::carbincancel()
{
    QByteArray s = QByteArray::fromHex("030A");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::updateBegin(QString update)
{
    m_package->updateBegin(update);
}

void XhPort::selftest1()
{
    QByteArray s = QByteArray::fromHex("05050F");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::readData(QByteArray Data) {
    m_package->analysis(Data);
}

/*测试串口通讯*/
void XhPort::serialTest()
{
    QByteArray buff = QByteArray::fromHex("4A4630020002E002000101");
    m_serial->write(buff);
    if(serialOpen)
    {
        QObject::disconnect(portTimer, &QTimer::timeout, this, &XhPort::serialTest);//dis连接信号槽
        portTimer->stop();
    }
}

void XhPort::sendfile(QByteArray sendData)
{
    m_serial->write(sendData);
}

void XhPort::xhfirstTestResult(bool a, bool b, bool c, bool d, bool e)
{
    emit firstTestResult(a,b,c,d,e);
}

void XhPort::xhfirstTemperatureResult(int a, int b, int c, int d , int e, int f, int g, QByteArray data )
{
    emit firstTemperatureResult(a,b,c,d,e,f,g,data);
}

void XhPort::xhdisUseFilament(bool a)
{
    emit disUseFilament(a);
}

void XhPort::xhbackFactory(bool a)
{
    emit backFactory(a);
}

void XhPort::xhnNozzleCalibration(int b)
{
    emit nNozzleCalibration(b);
}

void XhPort::xhxPlatformCalibration(bool a )
{
    emit xPlatformCalibration(a);
}

void XhPort::fileSendOverSlot()
{
    emit fileSendOver();
}

void XhPort::xhxNoHeating(bool a)
{
    emit xNoHeating(a);
}

void XhPort::xhxyCheck(bool a)
{
    emit xyCheck(a);
}

void XhPort::xhpowerlost()
{
    emit powerlost();
}

void XhPort::xhselfTest1()
{
    emit selfTest1();
}

void XhPort::xhselfTest2()
{
    emit selfTest2();
}

void XhPort::xhselfTest3()
{
    emit selfTest3();
}

void XhPort::xhselfTest4()
{
    emit selfTest4();
}

void XhPort::xhselfTest5()
{
    emit selfTest5();
}

void XhPort::xhselfTest6()
{
    emit selfTest6();
}

void XhPort::updateBeginSlot()
{
    /*开始更新*/
    QByteArray s = QByteArray::fromHex("0500");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
    emit updateBeginsignl();
}

void XhPort::updateCheck(QByteArray a)
{
    m_serial->write(a);
}

void XhPort::updateSend(QByteArray a, int b, QByteArray c)
{
    if(b == 1)
    {
        m_serial->write(a);
    }
    if(b == 0)
    {
        m_serial->write(a);
        QByteArray s = QByteArray::fromHex("0502");
        s.append(c);
        QByteArray buff = m_package->groupPage(s);
        m_serial->write(buff);
    }
    if(b == 2)
    {
        QByteArray s = QByteArray::fromHex("0502");
        s.append(c);
        QByteArray buff = m_package->groupPage(s);
        m_serial->write(buff);
    }
}

void XhPort::updateOver()
{
    QByteArray s = QByteArray::fromHex("050C");
    QByteArray buff = m_package->groupPage(s);
    m_serial->write(buff);
}

void XhPort::updateNum(int a)
{
    emit xhupdateNum(a);
}

XhPage* XhPort::getXhPage()
{
    return m_package;
}

JLSerialPort* XhPort::getSerialPort()
{
    return m_serial;
}
