#include "xhpage.h"


#ifdef XH_LINUX
#define logPath "/mnt/exUDISK/log.text"
#include "define/linuxPath.h"
#endif

#ifdef XH_WIN
#define logPath QDir::currentPath()+"/log.text"
#include "define/windowsPath.h"
#endif

// #define XH_LITTLE_BIT_MERGE_16(d1, d2)              ((((d2) << 8) & 0xFF00) | ((d1) & 0x00FF))
// #define XH_LITTLE_BIT_MERGE_32(d1, d2, d3, d4)      ( (((d4) << 24) & 0xFF000000) | (((d3) << 16) & 0xFF0000) | (((d2) << 8) & 0xFF00) | ((d1) & 0xFF))


XhPage::XhPage(QObject *parent) : QObject(parent)
{
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
    uint16_t len;
    len = (uint8_t)package.at(4) << 8 | (uint8_t)package.at(3);
    /*根据包长取出内容段*/
    QByteArray data = package.mid(9,len);
    uint16_t dataCheck;
    dataCheck = (uint8_t)package.at(8) << 8 | (uint8_t)package.at(7);
    emit command_received((uint8_t)data.at(0), (uint8_t)data.at(1), data);
    qDebug()<<"emit";
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
        default:
        break;
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
