#include "xhpage.h"


#ifdef XH_LINUX
#define logPath "/mnt/exUDISK/log.text"
#endif

#ifdef XH_WIN
#define logPath QDir::currentPath()+"/log.text"
#endif

#define XH_LITTLE_BIT_MERGE_16(d1, d2)              ((((d2) << 8) & 0xFF00) | ((d1) & 0x00FF))
#define XH_LITTLE_BIT_MERGE_32(d1, d2, d3, d4)      ( (((d4) << 24) & 0xFF000000) | (((d3) << 16) & 0xFF0000) | (((d2) << 8) & 0xFF00) | ((d1) & 0xFF))


XhPage::XhPage(QObject *parent) : QObject(parent)
{
    /*初始化包*/
    pageHead = "";
    pageType = "";
    pageLen = "";
    pageLsc = "";
    pageNature = "";
    pageNature[0] ='\xE0';
    pagedataNature = "";
    /*包头固定为JF*/
    pageHead.append('\x4A');
    pageHead.append('\x46');
    /*版本号为0x30*/
    pageType.append('\x30');
    /*变量初始化*/
    Axistesting = true;
    Heatingtesting = true;
    Platfomcheck = true;
    Nozzleheightcheck = true;
    XYcheck = true;

    Taxistesting = true;
    Theatingtesting = true;
    Tmaterialextrudetest = true;
    Tplatfomcheck = true;
    Tnozzleheightcheck = true;
    TxYcheck = true;

    m_file = nullptr;
    in = nullptr;

    m_updateFile = nullptr;
    inu = nullptr;
    on = true;

    m_timer = new QTimer(this);
    QObject::connect(m_timer,&QTimer::timeout,this,&XhPage::timeEimt);

    logTime = new QTime();
    logFind = new QTimer(this);
    logText = new QFile(logPath);
    QFileInfo fi("/mnt/exUDISK/gcode");

    cur_machine_status.CurTemp[0] = 0;
    cur_machine_status.CurTemp[1] = 0;
    cur_machine_status.CurTemp[2] = 0;
    cur_machine_status.TarTemp[0] = 0;
    cur_machine_status.TarTemp[1] = 0;
    cur_machine_status.TarTemp[2] = 0;
    cur_machine_status.Percent = 0;
    cur_machine_status.ZHeight = 0;
    cur_machine_status.Status = 0;

    if(fi.isDir())
    {
        QObject::connect(logFind,&QTimer::timeout,this,&XhPage::logFindSlot);
        if(!logText->open(QIODevice::WriteOnly| QIODevice::Text| QIODevice::Append))
        {
            logFind->start(1000);
        }
    }
}

XhPage::~XhPage()
{
    logText->close();
    delete logText;
}

int XhPage::analysis(QByteArray package)
{
    QFileInfo fi("/mnt/exUDISK/gcode");
    if(fi.isDir())
    {
        if(!logText->isOpen())
        {
            logText->open(QIODevice::WriteOnly| QIODevice::Text| QIODevice::Append);
        }
        if(logText->isOpen())
        {
            QByteArray packLog = logTime->currentTime().toString().toLatin1();
            packLog.append('\n');
            packLog.append(package.toHex());
            packLog.append('\n');
            int i = logText->write(packLog);
            logText->flush();
        }
        else {
            qDebug()<<"log text not open";
        }
        logText->close();
    }
    /*判断包头及版本号是否正确*/
    if(package[0]== '\x4A' && package[1]== '\x46')
    {
        /*判断版本号*/
        if(package[2] == '\x30')
        {
            /*判断包长和包长校验位*/
            if(package[3]^package[4] == package[5])
            {
                quint16 len = (quint16)package[4];
                len = (len << 8) + (quint16)package[3];

                /*判断属性位是否为主控应答帧*/
                if(package[6] == '\x00')
                {
                    /*根据包长取出内容段*/
                    QByteArray data = package.mid(9,len);
                    quint16 dataCheck = (quint16)package[8];
                    dataCheck = (dataCheck << 8)+(quint16)package[7];
                    emit command_received(data[0], data[1], data);
                    switch (data[0]) {
                    /*判断是哪一个页面族*/
                    /********first start********/
                        case '\x01':
                            switch (data[1]) {
                                case '\x02':
                                    fSelfTest(data);
                                    break;
                                case '\x00':
                                    fTGet(data);
                                    break;

                                case '\x04':

                                break;
                                case '\x05':
                                break;
                                case '\x06':
                                if(data[2]=='\x00')
                                {
                                    if(data[3]=='\x03')
                                    {
                                        emit xNoHeating(true);
                                    }
                                }
                                break;
                                case '\x07':
                                if(data[2]=='\x00')
                                    emit xyCheck(true);
                                break;
                                case '\x01':
                                    errorLog(data);
                                break;
                                case '\x03':
                                   if(data[3]=='\x01')
                                    emit powerlost();
                                break;
                                case '\x0D':
                                    if(data[2]=='\x00')
                                    askstate(data);
                                break;
                                case '\x0E':
                                    if(data[2]=='\x00')
                                    {
                                        if(data[3] == '\x00')
                                        {
                                            emit canone(0);
                                        }
                                        if(data[3] == '\x01')
                                        {
                                            emit canone(1);
                                        }
                                        if(data[3] == '\x02')
                                        {
                                            emit canone(2);
                                        }
                                    }
                                break;
                                case '\x10':
                                if(data[2]=='\x00')
                                {
                                    if(data[3] == '\x00')
                                    {
                                        emit cantwo(0);
                                    }
                                    if(data[3] == '\x01')
                                    {
                                        emit cantwo(1);

                                    }
                                    if(data[3] == '\x02')
                                    {
                                        emit cantwo(2);
                                    }
                                }
                            break;

                            default:
                                break;
                            }
                        break;
                    /*******tool machine set*********/
                        case '\x09':
                        switch (data[1]) {
                            case '\x00':
                            {
                                if(data[2] == '\x00')
                                {
                                    emit disUseFilament(true);
                                }
                                if (data[2] == '\xFF')
                                {
                                    emit disUseFilament(true);
                                }

                                break;
                            }
                            case '\x01':
                                if(data[2] == '\x00')
                                {
                                    emit backFactory(true);
                                }
                                if (data[2] == '\xFF')
                                {
                                    emit backFactory(true);
                                }
                                break;

                            case '\x03':
                                tSelfTest(data);
                                break;

                        default:
                            break;

                        }
                        break;
                    /*******tool*********/
                        case '\x03':
                            if(data[1]== '\x0A')
                            {
                                if(data[2] == '\x00')
                                {
                                    emit cancle();
                                }
                            }
                            if(data[1] == '\x00')
                            {
                                if(data[2] == '\x00')
                                {
                                    qint32 num = (((static_cast< qint32>(data[6])) &  0x0000000000FF) << 24)|(((static_cast< qint32>(data[5])) &  0x0000000000FF) << 16)|(((static_cast< qint32>(data[4])) &  0x0000000000FF) << 8)|(((static_cast< qint32>(data[3])) &  0x0000000000FF) << 0);
                                    emit nNozzleCalibration(num);
                                }
                            }
                        break;
                    /**************05族**************/
                    case '\x05':
                        switch (data[1]) {
                        /*更新程序*/
                        case '\x00':
                            if(data[2] == '\x00')
                            {
                            }
                            break;
                        case '\x01':
                           {
                                quint16 pakeNum= XH_LITTLE_BIT_MERGE_16(data[2],data[3]);
                                QByteArray pack;
                                pack.append(data[2]);
                                pack.append(data[3]);
                                sendUpdate(pakeNum,pack);
                           }
                            break;
                        case '\x02':
                            {
                                    m_timer->start(1000);
                            }
                            break;
                        case '\x0B':
                            {
                                if(data[2] == '\x00')
                                {
                                    emit updateOver();
                                }
                            }
                            break;
                        /*******/
                        case '\x05':
                            if(data[2] == '\x00')
                            {
                                emit selfTest1();
                            }
                            break;
                        case '\x06':
                            if(data[2] == '\x00')
                            {
                                emit selfTest2();
                            }
                            break;
                        case '\x07':
                            if(data[2] == '\x00')
                            {
                                emit selfTest3();
                            }
                            break;
                        case '\x08':
                            if(data[2] == '\x00')
                            {
                                emit selfTest4();
                            }
                            break;
                        case '\x09':
                            if(data[2] == '\x00')
                            {
                                emit selfTest5();
                            }
                            break;
                        case '\x0A':
                            if(data[2] == '\x00')
                            {
                                emit selfTest6();
                            }
                            break;
                        default:
                            break;

                        }
                        break;

                    /*******print idel*********/
                        case '\x06':
                        switch (data[1]) {
                            case '\x06':

                            break;

                            case '\x04':
                                {
                                    quint32 offset  = ((uint8_t)data[5]<<24 ) | ((uint8_t)data[4]<<16 ) | ((uint8_t)data[3]<<8 )| ((uint8_t)data[2]);
                                    sendfile(offset);
                            break;
                                }
                            case '\x0D':
                            if(data[2] == '\x00')
                            {
                                 emit fileSendOver();
                            }
                            break;
                            case '\x02':

                            break;
                            case '\x01':
                            if(data[2]=='\x00')
                                if(m_file!= nullptr)
                                {
                                    m_file->close();
                                    m_file = nullptr;
                                }
                            break;
                            case '\x0C':

                            break;
                            case '\x07':
                            if(data[2]=='\x00')
                            {
                                // emit printend();
                                if(m_file!= nullptr)
                                {
                                   m_file->close();
                                   m_file = nullptr;
                                }
                            }
                            break;
                            case '\x08':
                            emit filamentlost();
                            break;

                        }
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    return  -4;//属性验证错误
                }

            }
            else
            {
                return -3;//包长校验错误
            }

        }
        else
        {
            return -2;//版本不对
        }

    }
    else
    {
        return -1;//包头不对
    }
    return 0;
}

void XhPage::fSelfTest(QByteArray data)
{
    switch(data[2]){
        case '\x00':
        break;

    default:
        for (int i = 0; i < 8; ++i) {
            if ((data[2] >> i) & 0x01) {
                if(i == 0)
                {
                    Axistesting = false;
                }
                if(i == 1)
                {
                    qDebug()<<" Heating test error";
                    Heatingtesting = false;
                }
                if(i == 2)
                {
                    qDebug()<<"  Platfom check error";
                    Platfomcheck = false;
                }
                if(i == 3)
                {
                    qDebug()<<" Nozzle height check error";
                    Nozzleheightcheck = false;
                }
                if(i == 4)
                {
                    qDebug()<<" XY check error";
                    XYcheck = false;
                }
            }
        }
        break;

    }
    //发送自检结果
    emit firstTestResult(Axistesting,Heatingtesting,Platfomcheck,Nozzleheightcheck,XYcheck);
}

void XhPage::fTGet(QByteArray data)
{
    if(data[2] == '\x00')
    {
        cur_machine_status.CurTemp[0] = (int16_t)(((uint16_t)(data[5] << 8)) | (uint8_t)data[4]);
        cur_machine_status.TarTemp[0] = (int16_t)(((uint16_t)(data[7] << 8)) | (uint8_t)data[6]);
        cur_machine_status.CurTemp[1] = (int16_t)(((uint16_t)(data[9] << 8)) | (uint8_t)data[8]);
        cur_machine_status.TarTemp[1] = (int16_t)(((uint16_t)(data[11] << 8)) | (uint8_t)data[10]);
        cur_machine_status.CurTemp[2] = (int16_t)(((uint16_t)(data[13] << 8)) | (uint8_t)data[12]);
        cur_machine_status.TarTemp[2] = (int16_t)(((uint16_t)(data[15] << 8)) | (uint8_t)data[14]);
        cur_machine_status.ZHeight = ((int32_t)(((uint8_t)data.at(19) << 24) | ((uint8_t)data.at(18) << 16) | ((uint8_t)data.at(17) << 8) | (uint8_t)data.at(16))) / 1000.0f;
        cur_machine_status.Status = data[3];
        cur_machine_status.Percent = ((uint8_t)data[21] << 8) | data[20] ;
    }
}

/**
  * @brief  Get current machine status
  * @param  pStatus: The buffer to store current status
  * @retval None
  */
void XhPage::GetMachineStatus(strMachineStatus *pStatus)
{
    *pStatus = cur_machine_status;
}

void XhPage::tSelfTest(QByteArray data)
{
    switch(data[2]){
        case '\x00':
        break;

    default:
        for (int i = 0; i < 8; ++i) {
            if ((data[2] >> i) & 0x01) {
                if(i == 0)
                {
                    qDebug()<<" Axis test error";
                    Taxistesting = false;
                }
                if(i == 1)
                {
                    qDebug()<<" Heating test error";
                    Theatingtesting = false;
                }
                if(i == 2)
                {
                    qDebug()<<"  Material extrude test";
                    Tmaterialextrudetest = false;
                }
                if(i == 3)
                {
                    qDebug()<<"  Platfom check error";
                    Tplatfomcheck = false;
                }
                if(i == 4)
                {
                    qDebug()<<" Nozzle height check error";
                    Tnozzleheightcheck = false;
                }
                if(i == 5)
                {
                    qDebug()<<" XY check error";
                    TxYcheck = false;
                }
            }
        }
        break;

    }
    //发送自检结果
}

void XhPage::errorLog(QByteArray data)
{
    if(data[3] == '\x01')
    {
        emit error(0);
    }
    if(data[3] == '\x02')
    {
        emit error(1);
    }
    if(data[3] == '\x04')
    {
        emit error(2);
    }
    if(data[3] == '\x08')
    {
        emit error(3);
    }
    if(data[3] == '\x10')
    {
        emit error(4);
    }
    if(data[3] == '\x20')
    {
        emit error(5);
    }
    if(data[3] == '\x40')
    {
        emit error(6);
    }
    if(data[3] == '\x80')
    {
        emit error(7);
    }
    if(data[4] == '\x01')
    {
        emit error(8);
    }
    if(data[4] == '\x02')
    {
        emit error(9);
    }
    if(data[4] == '\x04')
    {
        emit error(10);
    }
    if(data[4] == '\x08')
    {
        emit error(11);
    }
    if(data[6] == '\x01')
    {
        emit error(31);
    }
}

QByteArray XhPage::lightPage(bool type, QString str)
{
    if(type)
    {
        QByteArray data = "";
    }
    else
    {
        QByteArray m_data = "";
    }
}

QByteArray XhPage::groupPage(QByteArray data)
{
    quint16 nature=0;
    pagedataNature.resize(0);
    for (int i = 0;i<data.size();i++) {
      nature = nature +(quint8)data[i];
    }
    char checkData[2]  = {0};
    checkData[1] = static_cast< char>((nature >> 8) & 0xFF);
    checkData[0] = static_cast< char>((nature >> 0) & 0xFF);

    pagedataNature.append(checkData,2);

    pageLen.resize(2);
    pageLen[0]='\x00';
    pageLen[1]='\x00';
    int len = data.size();
    while (len>255) {
        len = len-256;
        if(pageLen[1]== '\xFF')
        {
            pageLen[1] = pageLen[1] - '\xFF';
        }
        pageLen[1] = pageLen[1] +'\x01';
    }
    while (len>0) {
        pageLen[0] = pageLen[0] +'\x01';
        len--;
    }
    pageLsc.resize(1);
    pageLsc[0] = pageLen[0]^pageLen[1];

    QByteArray sendPage = "";
    sendPage.resize(0);
    sendPage.append(pageHead);
    sendPage.append(pageType);
    sendPage.append(pageLen);
    sendPage.append(pageLsc);
    sendPage.append(pageNature);
    sendPage.append(pagedataNature);
    sendPage.append(data);
    return sendPage;
}

QByteArray XhPage::chooseFile(QString m_filePath)
{

    QByteArray sendComd="";
    QFile m_sendFile(m_filePath);
    if(m_sendFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"file open :"<<m_filePath;
        QByteArray m_filedata = m_sendFile.readAll();
#ifdef OLD
        quint32 filecheck = 0;
        for (int i = 0;i<m_sendFile.size();i++) {
            filecheck= filecheck + (quint32) m_filedata[i];
        }
        char checkNum[4]  = {0};
        checkNum[3] = static_cast< char>((filecheck >> 24) & 0x000000FF);
        checkNum[2] = static_cast< char>((filecheck >> 16) & 0x000000FF);
        checkNum[1] = static_cast< char>((filecheck >> 8) & 0x000000FF);
        checkNum[0] = static_cast< char>((filecheck >> 0) & 0x000000FF);

        QByteArray abcd;
        abcd.append(checkNum, 4);
#endif
        qint64 m_fileSize= m_sendFile.size();

        QByteArray m_fileSizeArray = "";
        char sizeNum[4]  = {0};
        sizeNum[3] = static_cast< char>((m_fileSize >> 24) & 0x0000000000FF);
        sizeNum[2] = static_cast< char>((m_fileSize >> 16) & 0x0000000000FF);
        sizeNum[1] = static_cast< char>((m_fileSize >> 8) & 0x0000000000FF);
        sizeNum[0] = static_cast< char>((m_fileSize >> 0) & 0x0000000000FF);

        m_fileSizeArray.append(sizeNum,4);
        QByteArray data = QByteArray::fromHex("0606");
        QByteArray abcd = QByteArray::fromHex("00000000");
        data.append(m_fileSizeArray);
        data.append(abcd);
        sendComd=groupPage(data);
    }
    m_sendFile.close();

    thisFilePath = m_filePath;
    return  sendComd;
}

QByteArray XhPage::analysisFile()
{
    QFile m_file(thisFilePath);
    m_file.open(QIODevice::ReadOnly);

    m_file.close();
    QByteArray A;
    return A;
}



void XhPage::askstate(QByteArray data)
{
    quint16 ltemp = XH_LITTLE_BIT_MERGE_16(data[3], data[4]);
    quint16 rtemp = XH_LITTLE_BIT_MERGE_16(data[5], data[6]);
    quint16 bedtemp = XH_LITTLE_BIT_MERGE_16(data[7], data[8]);
    quint8 lfan = data[9];
    quint8 rfan = data[10];
    quint16 FeedRate = XH_LITTLE_BIT_MERGE_16(data[11], data[12]);
    qint32 PlatformZ = XH_LITTLE_BIT_MERGE_32(data[13], data[14], data[15], data[16]);

    emit state(QString::asprintf("%d",ltemp),QString::asprintf("%d",rtemp),\
                QString::asprintf("%d",bedtemp),QString::asprintf("%d",lfan),\
                QString::asprintf("%d",rfan),QString::asprintf("%d",FeedRate),QString::asprintf("%0.1f",PlatformZ/1000.0f));

}

void XhPage::sendfile(quint32 offset)
{
    if(m_file == nullptr)
    {
        m_file = new QFile(thisFilePath);
        //in = new QTextStream(m_file);
        if(!m_file->open(QIODevice::ReadOnly)) {
            qDebug()<<"File open fail!!";
            return;
        }
    }
    if(!m_file->isOpen())
    {
        qDebug()<<"File closed";
        m_file = new QFile(thisFilePath);
        if(!m_file->open(QIODevice::ReadOnly)) {
            qDebug()<<"File reopen fail!!";
            return;
        }

    }
    //qDebug()<<"Offset:";
    //qDebug()<<offset;
    //qDebug()<<arrayOffset;
    //QString data1 = in->read(128);
    m_file->seek(offset);
    QByteArray data = m_file->read(128);

    int len= data.size();
    QByteArray datalen;
    datalen.resize(0);
    datalen.append(1, (len & 0xff));
    datalen.append(1, ((len >> 8) & 0xff));
    QByteArray pageData;
    pageData = QByteArray::fromHex("060400");
    pageData.append(1, offset);
    pageData.append(1, offset >> 8);
    pageData.append(1, offset >> 16);
    pageData.append(1, offset >> 24);
    pageData.append(datalen);
    pageData.append(data);
    emit sendFileArry(groupPage(pageData));
}

void XhPage::updateBegin(QString updateFile)
{
    if(m_updateFile == nullptr)
    {
        m_updateFile = new QFile(updateFile);

        if(!m_updateFile->open(QIODevice::ReadOnly))
        {
            qDebug()<<"cant open update 1";
            return;
        }
    }
    else
    {
        m_updateFile->close();
        delete m_updateFile;

        m_updateFile = new QFile(updateFile);

        if(!m_updateFile->open(QIODevice::ReadOnly))
        {
            qDebug()<<"cant open update 2";
            return;
        }
    }
    if(!m_updateFile->isOpen())
    {
        qDebug()<<"file cant open";
        return;
    }
    QByteArray allData;
    allData =  m_updateFile->readAll();
    quint32 num = XH_LITTLE_BIT_MERGE_32(allData[0],allData[1],allData[2],allData[3]);
    modenum = num;
    memset(mode,5,sizeof (mode));
    memset(offset,5,sizeof (mode));
    memset(size,5,sizeof (mode));

    for (quint32 var = 0; var < num; var++) {
        mode[var] = XH_LITTLE_BIT_MERGE_32(allData[(var*12)+4],allData[(var*12)+5],allData[(var*12)+6],allData[(var*12)+7]);
        offset[var] = XH_LITTLE_BIT_MERGE_32(allData[(var*12)+8],allData[(var*12)+9],allData[(var*12)+10],allData[(var*12)+11]);
        size[var] = XH_LITTLE_BIT_MERGE_32(allData[(var*12)+12],allData[(var*12)+13],allData[(var*12)+14],allData[(var*12)+15]);
    }

    bool printNeedUpdate = false;

    for (quint32  i= 0;  i< num; i++)
    {
        if(mode[i] == 0)
        {
            QByteArray localData = allData.mid((offset[i]+512),size[i]);

            QFile upDateGz("/usr/share/3d_printer/tmp/qt-3dprint.tar");
            if(upDateGz.open(QIODevice::ReadWrite))
            {
                upDateGz.write(localData);
                upDateGz.flush();
                upDateGz.close();
            }
            else
            {
                qDebug()<<"file info false";
            }
            m_upDater = new XhUpdater(this);
            m_upDater->startUpdate("/usr/share/3d_printer/tmp/qt-3dprint.tar");
            QObject::connect(m_upDater,&XhUpdater::completed,this,&XhPage::updaterOver);
        }
        if(mode[i] == 1)
        {
            qDebug()<<"print update begin";
            emit updateBeginSignls();
            printNeedUpdate = true;
        }
        if(mode[i] == 2)
        {

        }
    }
    if(printNeedUpdate != true)
    {
        /*机器不需要升级，直接重启*/
        emit updateOver();
    }
    inu = new QTextStream(m_updateFile);
}

void XhPage::sendUpdate(quint16 packnum, QByteArray pack)
{
    int dataSize = 0;
    for (int i = 0;i<modenum;i++)
    {
        if(mode[i] == 1)
        {
            inu->seek(offset[i]);
            dataSize = size[i];
        }
    }
    QString dataHeat = inu->read(512);
    QString data = inu->read(dataSize-512);
    if(packnum<((dataSize/512)-1))
    {
        QByteArray sendData = data.mid(packnum*512,512).toLatin1();
        QByteArray send = QByteArray::fromHex("050100");
        send.append(pack);
        send.append(sendData);
        emit updateSend(groupPage(send),1,pack);
        on=true;
    }
    else
    {
        QByteArray sendData = data.mid(packnum*512,(dataSize-512)-(packnum*512)).toLatin1();
        QByteArray send = QByteArray::fromHex("050100");
        send.append(pack);
        send.append(sendData);
        if(on)
        {
            emit updateSend(groupPage(send),0,pack);
        }
        else
        {
            emit updateSend("",2,pack);
        }
        on = false;
        int n = 0;
        QByteArray a  = dataHeat.toLatin1();
        for (int i =a.size()-1 ; i>0;i--) {
            if(a[i] == '\x00')
            {
                n = i;
                break;
            }
        }
        QString checked = dataHeat.left(n+1);
        QByteArray check = checked.toLatin1();
        updateCheckSend = QByteArray::fromHex("050B");
        updateCheckSend.append(check);
    }
    int  k = (dataSize-512)/512;
    if(packnum == 0)
    {
        emit updateSerial(0);
    }
    else
    {
        float x = (float)packnum/(float)k;
        x = x*1000;
        qDebug()<<x;
        emit updateSerial((int)x);
    }
    m_timer->start(1000);
}

void XhPage::timeEimt()
{
    emit updateCheck(groupPage(updateCheckSend));
    m_timer->stop();
}

void XhPage::updaterOver()
{
    delete  m_upDater;
}

void XhPage::logFindSlot()
{
    if(logText->open(QIODevice::WriteOnly| QIODevice::Text| QIODevice::Append))
        {
            logFind->stop();
        }
}





