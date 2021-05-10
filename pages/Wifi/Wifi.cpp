#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CMOD/XhUpdater.h"
#include <QThread>

void MainWindow::wifiPageInit()
{
    m_udp_listener = new UdpListener();
    m_udp_listener->startListen(9999);
    m_tcp_controler = new TcpControler();
    QObject::connect(m_udp_listener, SIGNAL(sigManageEvent(QByteArray)), this, SLOT(wifiConnectEvent(QByteArray)));
    QObject::connect(m_tcp_controler, SIGNAL(downloadEvent(QString, QByteArray)), this, SLOT(wifiDownloadEvent(QString, QByteArray)));
}

void MainWindow::wifiConnectEvent(QByteArray Data)
{
    qDebug()<<Data;
    if(Data == "Connect Request")
    {
        m_tcp_controler->connectServer("192.168.1.6", 8888);
    }
    else if(Data == "Disconnect Request")
    {
        m_tcp_controler->disconnectServer();
    }
}

void MainWindow::wifiDownloadEvent(QString EventName, QByteArray Data)
{
    if(EventName == "Start")
    {
        pdlg_Download = new updateProgreBar(this);
        pdlg_Download->show();
        pdlg_Download->change(0);
        last_download_type = (uint8_t)Data.at(0);
        last_download_filename = Data.mid(1,-1);
    }
    else if(EventName == "PackReceived")
    {
        int percent = (uint8_t)Data.at(1) << 8 | (uint8_t)Data.at(0);
        pdlg_Download->change(percent);
    }
    else if(EventName == "End")
    {
        pdlg_Download->hide();
        delete pdlg_Download;
        if(last_download_type == 1)
        {
            if(QFile::exists(downloadUpdateFile) == true)
                QFile::remove(downloadUpdateFile);
            QFile::rename(downloadFile, downloadUpdateFile);
            updateFileAnalize(downloadUpdateFile);
        }
        else if(last_download_type == 2)
        {
            if(QFile::exists(downloadGcodeFile) == true)
                QFile::remove(downloadGcodeFile);
            QFile::rename(downloadFile, downloadGcodeFile);
            qDebug()<<"Output:" << last_download_filename;
            wifiPrint("Direct", downloadGcodeFile, last_download_filename);
        }
    }
}

void MainWindow::wifiPrint(QString Mode, QString SourceFile, QString OutputFileName)
{
    pdlg_parsing = new parsing(this);
    pdlg_parsing->init(QByteArray(), Mode, SourceFile, OutputFileName);
    pdlg_parsing->show();
    QObject::connect(pdlg_parsing, SIGNAL(hideWidget()), this, SLOT(wifiParseComplete()), Qt::QueuedConnection);
}

void MainWindow::wifiParseComplete()
{
    QList<QByteArray> ret = pdlg_parsing->get_return_value();
    if(ret[0] == "Success")
    {
        qDebug()<<ret[1];
        qDebug()<<ret[2];
        QVariantMap parse_result = m_fileParser->parseQuickly(localPath + ret[1]);
        print_desc.Mode = ret[2];
        print_desc.LeftTemp = parse_result["left_temp"].toString();
        print_desc.RightTemp = parse_result["right_temp"].toString();
        print_desc.BedTemp = parse_result["bed_temp"].toString();
        print_desc.XOffset = parse_result["offset"].toFloat();
        print_desc.FileName = localPath + ret[1];
        ui->label_36->setText(ret[2]);
        ui->label_69->setText(ret[2]);
        if(print_desc.Mode == "Direct")
            print_desc.RightTemp = QString("0");
        else if((print_desc.Mode == "Duplicate") || (print_desc.Mode == "Mirror"))
            print_desc.RightTemp =print_desc.LeftTemp;
        screen_status.setPerformance(PREPARE_PRINT);
        qDebug()<<"Temp:" << print_desc.LeftTemp << " " << print_desc.RightTemp;
        m_port->setHeattingUnit(print_desc.LeftTemp, print_desc.RightTemp, print_desc.BedTemp);
        // Need add check for file is opened successfully
        ui->stackedWidget->setCurrentWidget(ui->page_PreparePrint);
    }
    else
    {
        qDebug()<<"Mode unsupported!";
    }
    delete pdlg_parsing;
}
