#include "tcpcontroler.h"
#include "define/imagePath.h"

strTCPMessageMap TcpControler::static_maps[] = {
    {0x0600, &TcpControler::startDownloadProcess},
    {0x0601, &TcpControler::downloadPackReceived},
    {0x0602, &TcpControler::endDownloadProcess},
    {0x0603, &TcpControler::startPrintProcess},
    {0x0604, &TcpControler::stopPrint},
    {0x0605, &TcpControler::pausePrint},
    {0x0606, &TcpControler::resumePrint},
    {0xffff, 0}
};

TcpControler::TcpControler()
{
    p_Socket = new QTcpSocket(this);
    p_Socket->bind(QHostAddress::AnyIPv4, 1235);
    StartWork();
}

TcpControler::~TcpControler()
{
    StopWork();
    delete p_Socket;
}

QByteArray TcpControler::readData()
{
    if(p_Socket == nullptr)
        return QByteArray();
    QByteArray ret = ((QTcpSocket*)p_Socket)->readAll();
    qDebug()<<ret.size();
    return ret;
}

bool TcpControler::connectServer(QString IP, int Port)
{
    ((QTcpSocket*)p_Socket)->connectToHost(IP, 8888, QIODevice::ReadWrite, QAbstractSocket::IPv4Protocol);
    bool ret = ((QTcpSocket*)p_Socket)->waitForConnected(30000);
    if(ret == true)
    {
        qDebug()<<"TCP Connect success";
        QObject::connect(this, SIGNAL(sigDataParsed(QByteArray)), this, SLOT(DataProcess(QByteArray)), Qt::QueuedConnection);
        // ((QTcpSocket*)p_Socket)->write("Hello");
    }
    return ret;
}

void TcpControler::disconnectServer()
{
    if(((QTcpSocket*)p_Socket)->isOpen() == true)
        ((QTcpSocket*)p_Socket)->close();
}

void TcpControler::writeProtocalData(QByteArray SourceData)
{
    QByteArray send_buff = protocal->setupPackage(SourceData);
    ((QTcpSocket*)p_Socket)->write(send_buff);
}

void TcpControler::DataProcess(QByteArray Data)
{
    QByteArray content = Data.mid(11, -1);
    uint16_t command = (uint8_t)content.at(0) << 8 | (uint8_t)content.at(1);
    uint32_t i = 0;
    qDebug()<<command;
    while(true)
    {
        if(static_maps[i].Command == 0xffff)
            break;
        if(static_maps[i].Command == command)
        {
            (this->*static_maps[i].pProcessFunction)(content);
            return;
        }
        i++;
    }
}

void TcpControler::startPrintProcess(QByteArray Datas) 
{
    qDebug()<<"wifi: Start print";
}

void TcpControler::resumePrint(QByteArray Datas) 
{
    qDebug()<<"wifi: Resume";
}

void TcpControler::stopPrint(QByteArray Datas) 
{
    qDebug()<<"wifi: Stop";
}

void TcpControler::pausePrint(QByteArray Datas) 
{
    qDebug()<<"wifi: Pause";
}

void TcpControler::startDownloadProcess(QByteArray Datas) 
{
    QByteArray file_info;

    download_file_type = (uint8_t)Datas.at(2);
    download_file_size = ((uint8_t)Datas.at(6) << 24) | ((uint8_t)Datas.at(5) << 16) | ((uint8_t)Datas.at(4) << 8) | (uint8_t)Datas.at(3);
    download_file_packs = ((uint8_t)Datas.at(10) << 24) | ((uint8_t)Datas.at(9) << 16) | ((uint8_t)Datas.at(8) << 8) | (uint8_t)Datas.at(7);
    download_file_checksum = ((uint8_t)Datas.at(14) << 24) | ((uint8_t)Datas.at(13) << 16) | ((uint8_t)Datas.at(12) << 8) | (uint8_t)Datas.at(11);
    download_file_name = QString(Datas.mid(15, -1));
    download_status = "Processing";
    request_pack_index = 0;
    download_retry = 6;
    writeProtocalData(QByteArray(QByteArray::fromHex("0680")));
    requestDownloadPack(0);
    QTimer::singleShot(6000, this, SLOT(downloadRetryThread()));

    file_info.resize(0);
    file_info.append(1, download_file_type);
    file_info.append(download_file_name);
    emit downloadEvent("Start", file_info);
    if(QFile::exists(downloadFile) == true)
        QFile::remove(downloadFile);
    QFile new_file(downloadFile);
    new_file.open(QIODevice::ReadWrite);
    new_file.close();
}

void TcpControler::requestDownloadPack(uint32_t PackIndex)
{
    QByteArray send_buff = QByteArray::fromHex("0681");
    send_buff.append(1, PackIndex);
    send_buff.append(1, PackIndex >> 8);
    send_buff.append(1, PackIndex >> 16);
    send_buff.append(1, PackIndex >> 24);
    writeProtocalData(send_buff);
}

void TcpControler::downloadPackReceived(QByteArray Datas) 
{
    uint32_t recv_pack_index;
    recv_pack_index = ((uint8_t)Datas.at(6) << 24) | ((uint8_t)Datas.at(5) << 16) | ((uint8_t)Datas.at(4) << 8) | (uint8_t)Datas.at(3);
    if(download_status == "Processing") {
        if(recv_pack_index == request_pack_index) {
            download_buffer.append(Datas.mid(7, -1));
            download_retry = 6;
            request_pack_index = request_pack_index + 1;
            requestDownloadPack(request_pack_index);
            QByteArray event_arg;
            uint32_t percent = request_pack_index * 1000 / download_file_packs;
            event_arg.append(1, percent);
            event_arg.append(1, percent >> 8);
            emit downloadEvent("PackReceived", event_arg);

            if(recv_pack_index % 10 == 0)
            {
                QFile new_file(downloadFile);
                new_file.open(QIODevice::ReadWrite);
                int file_size = new_file.size();
                new_file.seek(file_size);
                new_file.write(download_buffer);
                new_file.close();
                download_buffer.clear();
            }
        }
    }
}

void TcpControler::endDownloadProcess(QByteArray Datas) 
{
    writeProtocalData(QByteArray(QByteArray::fromHex("068200")));
    download_status = "Idle";
    emit downloadEvent("End", QByteArray());
    QFile new_file(downloadFile);
    new_file.open(QIODevice::ReadWrite);
    int file_size = new_file.size();
    new_file.seek(file_size);
    new_file.write(download_buffer);
    new_file.close();
    download_buffer.clear();
}

void TcpControler::downloadRetryThread()
{
    if(download_status == "Processing") {
        if(download_retry > 0)
        {
            download_retry--;
            requestDownloadPack(request_pack_index);
            QTimer::singleShot(6000, this, SLOT(downloadRetryThread()));
        }
    }
}
