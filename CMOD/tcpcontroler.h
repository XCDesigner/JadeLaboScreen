#ifndef TCPCONTROLER_H
#define TCPCONTROLER_H

#include "jlnetport.h"
#include "customTypes.h"

class TcpControler : public JLNetPort
{
    Q_OBJECT
public:
    TcpControler();
    ~TcpControler();

    void writeProtocalData(QByteArray);
    bool connectServer(QString, int);
    void disconnectServer();

protected:
    QByteArray readData() override;
    void startPrintProcess(QByteArray);
    void resumePrint(QByteArray);
    void stopPrint(QByteArray);
    void pausePrint(QByteArray);
    void startDownloadProcess(QByteArray);
    void requestDownloadPack(uint32_t);
    void downloadPackReceived(QByteArray);
    void endDownloadProcess(QByteArray);

private slots:
    void DataProcess(QByteArray);
    void downloadRetryThread();

private:
    uint32_t request_pack_index;
    uint32_t download_file_size;
    uint32_t download_file_packs;
    uint32_t download_file_checksum;
    QString download_file_name;
    uint8_t download_file_type;
    uint8_t download_retry;
    QString download_status;
    QByteArray download_buffer;


    static strTCPMessageMap static_maps[];

signals:
    void downloadEvent(QString EventName, QByteArray Datas);
};

#endif // TCPCONTROLER_H
