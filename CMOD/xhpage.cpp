#include "xhpage.h"


#ifdef XH_LINUX
#define logPath "/mnt/exUDISK/log.text"
#include "define/linuxPath.h"
#endif

#ifdef XH_WIN
#define logPath QDir::currentPath()+"/log.text"
#include "define/windowsPath.h"
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
    pageHead.append(0x4a);
    pageHead.append(0x46);
    /*版本号为0x30*/
    pageType.append(0x30);
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

    logTime = new QTime();
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
}

XhPage::~XhPage()
{
    logText->close();
    delete logText;
}

int XhPage::analysis(QByteArray package)
{
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
                    emit command_received((uint8_t)data.at(0), (uint8_t)data.at(1), data);
                    switch (data[0]) {
                    /*判断是哪一个页面族*/
                    /********first start********/
                        case '\x01':
                            switch (data[1]) {
                                case '\x00':
                                    fTGet(data);
                                    break;
                            default:
                                break;
                            }
                        break;
                    /*******tool machine set*********/
                        case '\x09':
                        switch (data[1]) {
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
                            case '\x01':
                            if(data[2]=='\x00')
                                if(m_file!= nullptr)
                                {
                                    m_file->close();
                                    m_file = nullptr;
                                }
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
        cur_machine_status.Percent = ((uint8_t)data[21] << 8) | (uint8_t)data[20];
        cur_machine_status.StepperHold = (uint8_t)data[22];
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

bool XhPage::setPrintFile(QString FileName)
{
    thisFilePath = FileName;
    if(m_file != nullptr)
    {
        if(m_file->isOpen() == true)
            m_file->close();
        delete m_file;
    }
    m_file = new QFile(thisFilePath);
    return m_file->open(QIODevice::ReadOnly);
}

uint32_t XhPage::getPrintFileSize()
{
    qDebug()<<m_file->size();
    if(m_file->isOpen() == true)
        return m_file->size();
    else
        return 0;
}
