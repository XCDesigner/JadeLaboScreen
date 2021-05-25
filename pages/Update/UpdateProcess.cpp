#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CMOD/XhUpdater.h"
#include <QThread>

void MainWindow::updateFileAnalize(QString SourceFile)
{
    if(QFile::exists(SourceFile) == false)
        return;
    if(QFile::exists(UpdateFile) == true)
        QFile::remove(UpdateFile);
    QFile::copy(SourceFile, UpdateFile);
    QList<uint32_t> printer_update_info;
    printer_update_info = getUpdateItem(1);
    qDebug()<<printer_update_info;
    if(printer_update_info.count() > 0) {
        printerUpdateFileBuffer = getUpdateContent(printer_update_info);
        QByteArray update_info = getUpdateInfo(printer_update_info);
        printerUpdatePacks = printerUpdateFileBuffer.size() / 512;
        if(printerUpdateFileBuffer.size() % 512 != 0)
            printerUpdatePacks++;
        qDebug()<<printerUpdatePacks;
        startUpdatePrinter();
    }
    else {
        startUpdateScreen();
    }
}

QByteArray MainWindow::getUpdateInfo(QList<uint32_t> Info)
{
    QFile *file = new QFile(UpdateFile);
    QByteArray ret;
    if(file->open(QIODevice::ReadOnly) == true)
    {
        file->seek(Info.at(1));
        ret = file->read(512);
        file->close();
    }
    return ret;
}

QByteArray MainWindow::getUpdateContent(QList<uint32_t> Info)
{
    QFile *file = new QFile(UpdateFile);
    QByteArray ret;
    if(file->open(QIODevice::ReadOnly) == true)
    {
        file->seek(Info.at(1) + 512);
        ret = file->read(Info.at(2) - 512);
        file->close();
    }
    return ret;
}

QList<uint32_t> MainWindow::getUpdateItem(uint32_t SearchType)
{
    QFile *file = new QFile(UpdateFile);
    QList<uint32_t> ret;
    if(file->open(QIODevice::ReadOnly) == true)
    {
        file->seek(0);
        char header[512];
        file->read(header, 512);

        uint32_t items;
        uint32_t type, offset, size;
        items = (uint8_t)header[0];
        if(items > 42)
            return ret;
        for(uint32_t i=0;i<items;i++)
        {
            int j = i * 12;
            type = (uint8_t)header[7 + j] << 24 | (uint8_t)header[6 + j] << 16 | (uint8_t)header[5 + j] << 8 | (uint8_t)header[4 + j];
            offset = (uint8_t)header[11 + j] << 24 | (uint8_t)header[10 + j] << 16 | (uint8_t)header[9 + j] << 8 | (uint8_t)header[8 + j];
            size = (uint8_t)header[15 + j] << 24 | (uint8_t)header[14 + j] << 16 | (uint8_t)header[13 + j] << 8 | (uint8_t)header[12 + j];
            if(type == SearchType) {
                ret.append(type);
                ret.append(offset);
                ret.append(size);
                break;
            }
        }
        file->close();
    }
    return ret;
}

void MainWindow::startUpdatePrinter()
{
    QObject::connect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(updateCommandProcess(uint8_t, uint8_t, QByteArray)));
    m_update = new updateProgreBar();
    m_update->show();
    m_port->startUpdate();
    printTimer->stop();
}

void MainWindow::sendPrinterUpdatePack(uint16_t PackIndex)
{
    QByteArray s;
    uint16_t read_len;
    s.append(1, PackIndex);
    s.append(1, (PackIndex >> 8));
    if(PackIndex == (printerUpdatePacks - 1))
        read_len = printerUpdateFileBuffer.size() - 512 * PackIndex;
    else
        read_len = 512;
    qDebug()<<QString("UpdatePackReq:%1 / %2").arg(PackIndex).arg(printerUpdatePacks);
    s.append(printerUpdateFileBuffer.mid(PackIndex * 512), read_len);
    m_port->sendUpdateData(s);
}

void MainWindow::sendEndUpdatePrinter()
{
    qDebug()<<"Send End update";
    m_port->sendEndUpdate();
}

void MainWindow::sendPrinterUpdateInfo()
{
    QList<uint32_t> update_item = getUpdateItem(1);
    qDebug()<<"Write Printer Update Info";
    QByteArray update_info = getUpdateInfo(update_item);
    m_port->sendUpdateInfo(update_info);
}

void MainWindow::rebootSystem()
{
    qDebug()<<"Send Reboot system";
    m_port->sendRebootSystem();
}

void MainWindow::startUpdateScreen()
{
    QList<uint32_t> info = getUpdateItem(0);

    if(info.size() > 0)
    {
        #if defined(XH_LINUX)
        QFile upDateGz(UPDATE_FILE_TMP);
        QByteArray file_data = getUpdateContent(info);
        if(upDateGz.open(QIODevice::ReadWrite))
        {
            upDateGz.write(file_data);
            upDateGz.flush();
            upDateGz.close();
        }
        else
        {
            qDebug()<<"file info false";
        }
        m_upDater = new XhUpdater(this);
        m_upDater->startUpdate(UPDATE_FILE_TMP);
        QObject::connect(m_upDater, SIGNAL(completed()), this, SLOT(rebootSystem()));
        #elif defined(XH_WIN)
        qDebug()<<"Screen update";
        rebootSystem();
        #endif

    }
    else
    {
        rebootSystem();
    }
}

void MainWindow::updateCommandProcess(uint8_t Command, uint8_t SubCode, QByteArray Datas)
{
    if(Command == 0x05)
    {
        if(SubCode == 0x00)
        {
            if(Datas.at(2) != 0)
            {
                qDebug()<<"Start update fail!";
            }
        }
        else if(SubCode == 0x01)
        {
            uint16_t req_pack;
            req_pack = ((uint8_t)Datas.at(3) << 8) | (uint8_t)Datas.at(2);
            if(req_pack < printerUpdatePacks)
            {
                sendPrinterUpdatePack(req_pack);
                m_update->change(req_pack * 1000 / printerUpdatePacks);
            }
            else
            {
                sendEndUpdatePrinter();
                m_update->hide();
                m_update = NULL;
            }
        }
        else if(SubCode == 0x02)
        {
            QThread::sleep(2);
            sendPrinterUpdateInfo();

        }
        else if(SubCode == 0x0b)
        {
            startUpdateScreen();
            // QObject::connect(this, SIGNAL(printUpdateCompleted()), this, SLOT(startUpdateScreen()), Qt::QueuedConnection);
        }
    }
}
