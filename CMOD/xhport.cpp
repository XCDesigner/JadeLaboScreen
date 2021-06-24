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
    m_package = new XhPage;
    serialOpen =false;
}

XhPort::~XhPort()
{
    delete m_serial;
    delete m_package;
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
    m_serial->writeProtocalData(s);
}

void XhPort::ldown()
{
    QByteArray s = QByteArray::fromHex("020500A0860100");
    m_serial->writeProtocalData(s);
}

void XhPort::rup()
{
    QByteArray s = QByteArray::fromHex("0205016079FEFF");
    m_serial->writeProtocalData(s);
}

void XhPort::rdown()
{
    QByteArray s = QByteArray::fromHex("020501A0860100");
    m_serial->writeProtocalData(s);
}

void XhPort::readyprint(int Mode, QByteArray Offset)
{
    QByteArray s;
    char strMode[][7] = {"060D00", "060D01", "060D02", "060D03", "060D04", "060D05", "060D06"};
    s = QByteArray::fromHex(strMode[Mode]);
    s.append(Offset);
    m_serial->writeProtocalData(s);
}

void XhPort::setBackupEnableStatus(bool Enable)
{
    if(Enable == true)
    {
        QByteArray s = QByteArray::fromHex("010F01");
        m_serial->writeProtocalData(s);
    }
    else {
        QByteArray s = QByteArray::fromHex("010F00");
        m_serial->writeProtocalData(s);
    }
}

void XhPort::factoryReset()
{
    m_serial->writeProtocalData(QByteArray::fromHex("0901"));
}

void XhPort::p_nozzleHeating()
{
    QByteArray s = QByteArray::fromHex("030200");
    m_serial->writeProtocalData(s);
}

void XhPort::p_platformCalibration()
{
    m_serial->writeProtocalData(QByteArray::fromHex("0302"));
}

void XhPort::finish()
{
    m_serial->writeProtocalData(QByteArray::fromHex("0309"));
}

void XhPort::cancleCalibration()
{
    m_serial->writeProtocalData(QByteArray::fromHex("030A"));
}

void XhPort::n_nozzleCalibration()
{
    m_serial->writeProtocalData(QByteArray::fromHex("0300"));
}

void XhPort::x_platformCalibration()
{
    m_serial->writeProtocalData(QByteArray::fromHex("0309"));
}

void XhPort::x_xyCalibration()
{
    m_serial->writeProtocalData(QByteArray::fromHex("0305"));
}

/**
  * @brief  Request printer status
  * @retval None
  */
void XhPort::getMachineStatus()
{
    m_serial->writeProtocalData(QByteArray::fromHex("0100"));
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
    m_serial->writeProtocalData(s);
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
    m_serial->writeProtocalData(s);
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
    m_serial->writeProtocalData(s);
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
    m_serial->writeProtocalData(s);
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
    m_serial->writeProtocalData(s);
}

/**
  * @brief  Set stepper onoff
  * @param  OnOff
  * @retval None
  */
void XhPort::setStepperOnOff(bool OnOff)
{
    QByteArray s = QByteArray::fromHex("020B");
    if(OnOff == true)
        s.append(1, 1);
    else
        s.append(1, 0);
    m_serial->writeProtocalData(s);
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
    m_serial->writeProtocalData(s);
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
        m_serial->writeProtocalData(QByteArray::fromHex("010701"));
    else
        m_serial->writeProtocalData(QByteArray::fromHex("010700"));
}

/**
  * @brief  Get filament sensor enable status
  * @retval None
  */
void XhPort::getFilamentSensorEnableStatus()
{
    m_serial->writeProtocalData(QByteArray::fromHex("0701"));
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
    m_serial->writeProtocalData(s);
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
    m_serial->writeProtocalData(s);
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
    m_serial->writeProtocalData(s);
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
    m_serial->writeProtocalData(s);
}

/**
  * @brief  Set extruder flow rate
  * @param  Extruder: Target extruder,0 for left, 1 for right
  * @param  Percent: Percentage
  * @retval None
  */
void XhPort::setFlowratePercentage(uint8_t Extruder, uint16_t Percent)
{
    QByteArray s = QByteArray::fromHex("0616");
    s.append(1, Extruder);
    s.append(1, Percent);
    s.append(1, (Percent >> 8));
    m_serial->writeProtocalData(s);
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
    m_serial->writeProtocalData(s);
}

/**
  * @brief  Pause printing
  * @retval None
  */
void XhPort::pausePrint()
{
    QByteArray s = QByteArray::fromHex("0602");
    m_serial->writeProtocalData(s);
}

/**
  * @brief  Continue printing
  * @retval None
  */
void XhPort::continuePrint()
{
    QByteArray s = QByteArray::fromHex("060C");
    m_serial->writeProtocalData(s);
}

/**
  * @brief  Stop printing
  * @retval None
  */
void XhPort::stopPrint()
{
    QByteArray s = QByteArray::fromHex("0601");
    m_serial->writeProtocalData(s);
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
        m_serial->writeProtocalData(QByteArray::fromHex("010700"));
    else if(Index == 1)
        m_serial->writeProtocalData(QByteArray::fromHex("010701"));
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
  * @brief  Triggle power lost event
  * @retval None
  */
void XhPort::trigglePowerLost()
{
    m_serial->writeProtocalData(QByteArray::fromHex("0B03"));
}

/**
  * @brief  Triggle filament runout event
  * @retval None
  */
void XhPort::triggleFilamentRunout(uint8_t Index)
{
    if(Index == 0)
        m_serial->writeProtocalData(QByteArray::fromHex("0B0800"));
    else
        m_serial->writeProtocalData(QByteArray::fromHex("0B0801"));
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
    qDebug()<<"prepare mode:" << Mode;
    map["Direct"] = QByteArray::fromHex("060D00");
    map["Mix"] = QByteArray::fromHex("060D01");
    map["Duplicate"] = QByteArray::fromHex("060D02");
    map["Mirror"] = QByteArray::fromHex("060D03");
    map["Origin-Duplicate"] = QByteArray::fromHex("060D04");
    map["Origin-Mirror"] = QByteArray::fromHex("060D05");
    map["Unsupport"] = QByteArray::fromHex("060D00");
    map["Unknown"] = QByteArray::fromHex("060D00");

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
    uint32_t file_size = getPrintFileSize();
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

/**
  * @brief  Send file package
  * @param  Offset: File position
  * @retval None
  */
void XhPort::sendFile(uint32_t Offset)
{
    if(print_file == nullptr)
    {
        print_file = new QFile(thisFilePath);
        if(!print_file->open(QIODevice::ReadOnly)) {
            qDebug()<<"File open fail!!";
            print_file->close();
            delete print_file;
            return;
        }
    }
    if(!print_file->isOpen())
    {
        qDebug()<<"File closed";
        print_file->close();
        // m_file = new QFile(thisFilePath);
        if(!print_file->open(QIODevice::ReadOnly)) {
            qDebug()<<"File reopen fail!!";
            return;
        }

    }
    if(print_file->pos() != Offset)
        print_file->seek(Offset);

    QByteArray data = print_file->read(128);
    int len= data.size();
    QByteArray datalen;
    datalen.resize(0);
    datalen.append(1, (len & 0xff));
    datalen.append(1, ((len >> 8) & 0xff));
    QByteArray pageData;
    pageData = QByteArray::fromHex("060400");
    pageData.append(1, Offset);
    pageData.append(1, Offset >> 8);
    pageData.append(1, Offset >> 16);
    pageData.append(1, Offset >> 24);
    pageData.append(datalen);
    pageData.append(data);
    m_serial->writeProtocalData(pageData);
}

/**
  * @brief  Set print file. This is called when powered with power lost event
  * @param  FileName: The file name of last print job
  * @retval True if the file is opened successfully
  */
bool XhPort::setPrintFile(QString FileName)
{
    thisFilePath = FileName;
    if(print_file != nullptr)
    {
        qDebug()<<"Delete old file!";
        if(print_file->isOpen() == true)
            print_file->close();
        delete print_file;
    }
    qDebug()<<"Create new File";
    print_file = new QFile(thisFilePath);
    return print_file->open(QIODevice::ReadOnly);
}

/**
  * @brief  Get the size of the file
  * @retval Size of the file
  */
uint32_t XhPort::getPrintFileSize()
{
    qDebug()<<print_file->size();
    if(print_file->isOpen() == true)
        return print_file->size();
    else
        return 0;
}

/**
  * @brief  Close the print file
  * @retval None
  */
void XhPort::closeFile()
{
    if(print_file != nullptr)
    {
        print_file->close();
        delete print_file;
    }
}

/**
  * @brief  Get firmware version
  * @param  Mode:
  * @retval None
  */
void XhPort::getFirmwareVersion()
{
    QByteArray s = QByteArray::fromHex("0503");
    m_serial->writeProtocalData(s);
}

/**
  * @brief  Extruder action. Extrude or retract
  * @param  Index: Extruder index
  * @param  Distance: Distance in um
  * @retval None
  */
void XhPort::ExtruderMotion(uint8_t Index, int32_t Distance)
{
    QByteArray s = QByteArray::fromHex("0205");
    s.append(1, Index);
    s.append(1, Distance);
    s.append(1, Distance >> 8);
    s.append(1, Distance >> 16);
    s.append(1, Distance >> 24);
    m_serial->writeProtocalData(s);
}

/**
  * @brief  Extrude for changing filament
  * @param  Index: Extruder index
  * @retval None
  */
void XhPort::LoadFilament(uint8_t Index)
{
    if(Index == 0)
        ldown();
    else
        rdown();
}

/**
  * @brief  Retract for changing filament
  * @param  Index: Extruder index
  * @retval None
  */
void XhPort::UnloadFilament(uint8_t Index)
{
    if(Index == 0)
        lup();
    else
        rup();
}

/**
  * @brief  Get buildplat thickness
  * @retval None
  */
void XhPort::getBuildplatThickness()
{
    m_serial->writeProtocalData(QByteArray::fromHex("030C"));
}

/**
  * @brief  Set buildplat thickness
  * @retval None
  */
void XhPort::setBuildplatThickness(float Thickness)
{
    QByteArray buff = QByteArray::fromHex("030D");
    uint32_t int_value = Thickness * 1000.0f;
    buff.append(1, int_value);
    buff.append(1, int_value >> 8);
    buff.append(1, int_value >> 16);
    buff.append(1, int_value >> 24);
    m_serial->writeProtocalData(buff);
}

/**
  * @brief  Prepare change filament
  * @param  Mode:
  * @retval None
  */
void XhPort::prepareChangeFilament()
{
    QByteArray buff = QByteArray::fromHex("020A");
    m_serial->writeProtocalData(buff);
}

/**
  * @brief  Send test
  * @param  Datas: Data to send
  * @retval None
  */
void XhPort::SendTest(QByteArray Datas)
{
    QByteArray buff = QByteArray::fromHex("0b0f");
    buff.append(Datas);
    m_serial->writeProtocalData(buff);
}

void XhPort::testdemo()
{
    QByteArray s = QByteArray::fromHex("84654875294581");
    m_serial->writeProtocalData(s);
}

/*打开串口*/
void XhPort::portInit(QString portname)
{
    m_serial = new JLSerialPort();
    if(m_serial->openPort(portname, 115200))
    {
        QObject::connect(m_serial, SIGNAL(sigDataParsed(QByteArray)), this, SLOT(readData(QByteArray)));//连接信号槽
    }
    else
    {
        qDebug()<<"serial open false!";
    }
}

void XhPort::carbinfinished()
{
    m_serial->writeProtocalData(QByteArray::fromHex("0309"));
}

void XhPort::carbincancel()
{
    m_serial->writeProtocalData(QByteArray::fromHex("030A"));
}

void XhPort::readData(QByteArray Data) {
    m_package->analysis(Data);
}

XhPage* XhPort::getXhPage()
{
    return m_package;
}

JLSerialPort* XhPort::getSerialPort()
{
    return m_serial;
}

void XhPort::getTMCValue(uint8_t MotorIndex, QByteArray Address) {
    QByteArray s = QByteArray::fromHex("0B01");
    s.append(1, MotorIndex);
    s.append(Address);
    m_serial->writeProtocalData(s);
}

void XhPort::trigFILSample() {
    QByteArray s = QByteArray::fromHex("0B06");
    m_serial->writeProtocalData(s);
}

void XhPort::getFILValue() {
    QByteArray s = QByteArray::fromHex("0B07");
    m_serial->writeProtocalData(s);
}

void XhPort::writeCustomData(QByteArray Datas)
{
    m_serial->writeProtocalData(Datas);
}
