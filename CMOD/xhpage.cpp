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
        mtxMachineStatus.lock();
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
        mtxMachineStatus.unlock();
    }
}

/**
  * @brief  Get current machine status
  * @param  pStatus: The buffer to store current status
  * @retval None
  */
void XhPage::GetMachineStatus(strMachineStatus *pStatus)
{
    mtxMachineStatus.lock();
    *pStatus = cur_machine_status;
    mtxMachineStatus.unlock();
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

