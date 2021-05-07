#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_101_clicked()
{
    ui->pushButton_134->setStyleSheet("QPushButton{border-top-left-radius: 20px;\
                                      border-bottom-left-radius: 20px;\
                                      border-left: 2px solid rgb(81, 83, 86);\
                                      border-top: 2px solid rgb(81, 83, 86);\
                                      border-bottom: 2px solid rgb(81, 83, 86);\
                                      background-color: rgb(32, 32, 32);\
                                      font-weight: bold;\
                                      font-family:Barlow;outline:none;\
                                      color: rgb(255, 255, 255);\
                                      font-size: 32px;\
};");
    ui->pushButton_101->setStyleSheet("QPushButton{\
                                      background-color: rgba(45, 44, 43, 255);\
                                      font-weight: bold;\
                                      font-family:Barlow;outline:none;\
                                      color: rgb(255, 255, 255);\
                                      font-size: 32px;\
                                      border-top-right-radius: 20px;\
                                      border-bottom-right-radius: 20px;\
                                      border-right: 2px solid rgb(81, 83, 86);\
                                      border-top: 2px solid rgb(81, 83, 86);\
                                      border-bottom: 2px solid rgb(81, 83, 86);\
};");

        ui->listWidget->setVisible(false);
        ui->listWidget_2->setVisible(true);

        ui->listWidget_2->clear();
        QDir *m_dir=new QDir(UDiskPath);
        QStringList filter;
        QFileInfoList m_fileinfo = m_dir->entryInfoList();
        for(int i = 0;i< m_fileinfo.count();i++)
            m_addItemToList(m_fileinfo.at(i).fileName(),m_fileinfo.at(i).filePath(),"UDisk");
}

void MainWindow::on_pushButton_134_clicked()
{
    ui->pushButton_134->setStyleSheet("QPushButton{border-top-left-radius: 20px;\
                                      border-bottom-left-radius: 20px;\
                                      border-left: 2px solid rgb(81, 83, 86);\
                                      border-top: 2px solid rgb(81, 83, 86);\
                                      border-bottom: 2px solid rgb(81, 83, 86);\
                                      background-color: rgba(45, 44, 43, 255);\
                                      font-weight: bold;\
                                      font-family:Barlow;outline:none;\
                                      color: rgb(255, 255, 255);\
                                      font-size: 32px;\
};");
    ui->pushButton_101->setStyleSheet("QPushButton{\
                                      background-color: rgb(32, 32, 32);\
                                      font-weight: bold;\
                                      font-family:Barlow;outline:none;\
                                      color: rgb(255, 255, 255);\
                                      font-size: 32px;\
                                      border-top-right-radius: 20px;\
                                      border-bottom-right-radius: 20px;\
                                      border-right: 2px solid rgb(81, 83, 86);\
                                      border-top: 2px solid rgb(81, 83, 86);\
                                      border-bottom: 2px solid rgb(81, 83, 86);\
};");
    ui->listWidget->setVisible(true);
    ui->listWidget_2->setVisible(false);

    ui->listWidget->clear();
    QDir *m_dir=new QDir(localPath);
    QStringList filter;
    QFileInfoList m_fileinfo = m_dir->entryInfoList();
    for(int i = 0;i< m_fileinfo.count();i++)
        m_addItemToList(m_fileinfo.at(i).fileName(),m_fileinfo.at(i).filePath(), "Local");
}

void MainWindow::m_addItemToList(const QString &fileName, QString filePath, QByteArray FileFrom)
{
    if(fileName == "."||fileName == "..")
        return;
    QListWidgetItem* pItem;
    myListWidgetItem *pWidgetItem = new myListWidgetItem(this);
    pWidgetItem->m_addItem(fileName,filePath);
    pWidgetItem->isUDisk = FileFrom;
    if(FileFrom == "UDisk")
    {
        pItem = new QListWidgetItem(ui->listWidget_2);
        ui->listWidget_2->setItemWidget(pItem,pWidgetItem);
    }
    else
    {
        pItem = new QListWidgetItem(ui->listWidget);
        ui->listWidget->setItemWidget(pItem,pWidgetItem);

    }
    pItem->setSizeHint(QSize(930,127));

    m_map.insert(pWidgetItem,pItem);

    QObject::connect(pWidgetItem,SIGNAL(deleteItem(myListWidgetItem * )),this,SLOT(m_deleteItem(myListWidgetItem * )));
    QObject::connect(pWidgetItem,SIGNAL(chooseFile(myListWidgetItem * )),this,SLOT(m_chooseItem(myListWidgetItem * )));
}

void MainWindow::m_chooseItem(myListWidgetItem *itm)
{
    m_WinFile = new chooseFile(this);
    m_WinFile->init(itm);
    QObject::connect(m_WinFile, SIGNAL(hideWidget()), this, SLOT(onFileChooseReturn()), Qt::QueuedConnection);
    m_WinFile->show();

    ui->label_72->setText(itm->m_fileName);
    ui->label_73->setText(itm->m_fileName);
}

void MainWindow::onFileChooseReturn()
{
    QList<QByteArray> ret = m_WinFile->get_return_value();
    myListWidgetItem *p_item = m_WinFile->getSelectItem();
    delete m_WinFile;
    if(ret[0] == "Confirm")
    {
        QVariantMap parse_result = m_fileParser->parseQuickly(p_item->m_filePath);
        pdlg_select_mode = new PrintModeSelect();;
        pdlg_select_mode->init(QByteArray(parse_result["mode"].toByteArray()), p_item);
        pdlg_select_mode->show();
        QObject::connect(pdlg_select_mode, SIGNAL(hideWidget()), this, SLOT(onModeSelectReturn()), Qt::QueuedConnection);
    }
}

void MainWindow::onModeSelectReturn()
{
    QList<QByteArray> ret = pdlg_select_mode->get_return_value();
    if(ret[0] == "Cancel")
    {
        delete pdlg_select_mode;
    }
    else
    {
        QString input_file = pdlg_select_mode->getInputFileName();
        QString output_file_name = pdlg_select_mode->getOutputFileName();
        delete pdlg_select_mode;

        pdlg_parsing = new parsing(this);
        pdlg_parsing->init(QByteArray(), ret[0], input_file, output_file_name);
        pdlg_parsing->show();
        QObject::connect(pdlg_parsing, SIGNAL(hideWidget()), this, SLOT(onParseComplete()), Qt::QueuedConnection);
    }
}

void MainWindow::onParseComplete()
{
    QList<QByteArray> ret = pdlg_parsing->get_return_value();
    if(ret[0] == "Success")
    {
        qDebug()<<ret[1];
        qDebug()<<ret[2];
        QVariantMap parse_result = m_fileParser->parseQuickly(localPath + ret[1]);
        print_desc.Mode = parse_result["mode"].toString();
        print_desc.LeftTemp = parse_result["left_temp"].toString();
        print_desc.RightTemp = parse_result["right_temp"].toString();
        print_desc.BedTemp = parse_result["bed_temp"].toString();
        print_desc.XOffset = parse_result["offset"].toFloat();
        print_desc.FileName = localPath + ret[1];
        if(print_desc.Mode == "Direct")
            print_desc.RightTemp = QString("0");
        else if((print_desc.Mode == "Duplicate") || (print_desc.Mode == "Mirror"))
            print_desc.RightTemp =print_desc.LeftTemp;
        screen_status.setPerformance(PREPARE_PRINT);
        m_port->setHeattingUnit(print_desc.LeftTemp, print_desc.RightTemp, print_desc.BedTemp);
        // Need add check for file is opened successfully
        ui->stackedWidget->setCurrentWidget(ui->page_PreparePrint);
    }
    else
    {
        QVariantMap parse_result = m_fileParser->parseQuickly(localPath + ret[1]);
        pdlg_select_mode = new PrintModeSelect(this);
        qDebug()<<parse_result["mode"].toByteArray();
        pdlg_select_mode->init(QByteArray(parse_result["mode"].toByteArray()), localPath+ret[1], ret[1]);
        pdlg_select_mode->show();
        QObject::connect(pdlg_select_mode, SIGNAL(hideWidget()), this, SLOT(onModeSelectReturn()), Qt::QueuedConnection);
    }
    delete pdlg_parsing;
}

//void MainWindow::PreparePrint(QString FileName)
//{

//}

void MainWindow::m_deleteItem(myListWidgetItem *itm)
{
    m_delete = new Delete(this);
    m_delete->init(itm->m_fileName, itm);
    m_delete->show();
    QObject::connect(m_delete, SIGNAL(hideWidget()), this, SLOT(onDeleteFileReturn()), Qt::QueuedConnection);
}

void MainWindow::onDeleteFileReturn()
{
    QList<QByteArray> ret = m_delete->get_return_value();

    if(ret[0] == "Confirm")
    {
        myListWidgetItem *pItem = m_delete->getDeleteItem();
        QFile fileTemp(pItem->m_filePath);
        fileTemp.remove();
        if(pItem->isUDisk == "UDisk")
        {
            QListWidgetItem *v=m_map.take(pItem);
            ui->listWidget->takeItem(ui->listWidget->row(v));
            delete v;
        }else
        {
            QListWidgetItem *v=m_map.take(pItem);
            ui->listWidget_2->takeItem(ui->listWidget_2->row(v));
            delete v;
        }
    }
    delete m_delete;
}

void MainWindow::m_chooseEN()
{
    loaclPATH.clear();
    loaclPATH = localPath+m_WinFile->m_fileName;
    /* 2021/3/2 cbw */
    QString a= QDir::currentPath()+"/UD";
    if(m_WinFile->m_filePath.left(4) == "/mnt"||m_WinFile->m_filePath.left(a.size()) == UDiskPath)
    {
        QFileInfo directFile(m_WinFile->m_filePath);
        romClean(directFile.size());
        m_fileParser->parseByDirect(m_WinFile->m_filePath,localPath+m_WinFile->m_fileName);
        udiskPATH = m_WinFile->m_filePath;
        openMode = false;
    }
    else
    {
        //解析文件
        int mode = 0;
        QFile m_sendFile(m_WinFile->m_filePath);
        if(m_sendFile.open(QIODevice::ReadOnly))
        {
            QByteArray m_filedata = m_sendFile.readLine();
            QList<QByteArray> params = m_filedata.split(' ');
            qDebug()<<params;
            QByteArray print_mode = params[1].split(':')[1];
            QString offset = params[2].split(':')[1];
            lt = params[3].split(':')[1];
            rt = params[4].split(':')[1];
            bt = params[5].split(':')[1];

            QString data = m_filedata;
            if((print_mode == "unknown")|| (print_mode =="Unknown"))
            {
                mode = 1;
                this->printMode = 0;
            }
            if(print_mode == "Mirror")
            {
                mode = 2;
            }
            if(print_mode == "Duplicate")
            {
                mode = 3;
            }
            if(print_mode == "Unsupport")
            {
                mode = 4;
                this->printMode = 0;
            }
            if(print_mode == "Mix")
            {
                mode = 5;
                this->printMode = 6;
            }
            if(print_mode == "Orgin-Mirror")
            {
                mode = 6;
                this->printMode = 5;
            }
            if(print_mode == "Orgin-Duplicate")
            {
                mode = 7;
                this->printMode = 4;
            }

            qDebug()<<"offset qstring read"<<offset;

            if(offset.contains("-"))
            {
                offset = offset.mid(1,offset.size()-1);
                qDebug()<<"offset"<<offset;
                float a = offset.toFloat();
                offsetnum = 0 - (a*1000);
                qDebug()<<"numoffset"<<offsetnum;
            }
            else {
                float a = offset.toFloat();
                offsetnum = a*1000;
                qDebug()<<"numoffset"<<offsetnum;
            }
        }

        m_dam = new DupandMirorr(this);
        QObject::connect(m_dam,&DupandMirorr::print,this,&MainWindow::tprint);
        QObject::connect(m_dam,&DupandMirorr::mirro,this,&MainWindow::tmirro);
        QObject::connect(m_dam,&DupandMirorr::dup,this,&MainWindow::tdup);
        QObject::connect(m_dam,&DupandMirorr::cancle,this,&MainWindow::tcanle);

        switch (mode) {
        case 1:
            m_dam->changeMode(0);
            break;
        case 2:
            m_dam->changeMode(2);
            break;
        case 3:
            m_dam->changeMode(3);
            break;
        case 4:
            m_dam->changeMode(1);
            break;
        case 5:
            m_dam->changeMode(1);
            break;
        case 6:
            m_dam->changeMode(1);
            break;
        case 7:
            m_dam->changeMode(1);
            break;
        default:
            break;
        }
        openMode =true;
        m_dam->show();
        m_WinFile->hide();
        m_WinFile->close();

        m_sendFile.close();
    }
    /* over */

//    QStorageInfo storage = QStorageInfo::root();
//    storage.refresh();
//    qDebug()<<storage.rootPath();
//    if(storage.isReadOnly())
//        qDebug()<<"isReadOnly:"<<storage.isReadOnly();
//    qDebug()<<"name:"<<storage.name();
//    qDebug()<<"fileSystemType:"<<storage.fileSystemType();
//    qDebug()<<"size:"<<storage.bytesTotal()/1000/1000<<"MB";
//    qDebug()<<"availableSize:"<<storage.bytesAvailable()/1000/1000<<"MB";
}

void MainWindow::romClean(int fileSize)
{
    /*判断存储空间*/
    QStorageInfo storage = QStorageInfo::root();
    storage.refresh();
#ifdef DEBUG
    qDebug()<<storage.rootPath();
    if(storage.isReadOnly())
        qDebug()<<"isReadOnly:"<<storage.isReadOnly();
    qDebug()<<"name:"<<storage.name();
    qDebug()<<"fileSystemType:"<<storage.fileSystemType();
    qDebug()<<"size:"<<storage.bytesTotal()/1000/1000<<"MB";
    qDebug()<<"availableSize:"<<storage.bytesAvailable()/1000/1000<<"MB";
#endif
    int i,j;
    QDir *dir=new QDir(localPath);
    QList<QFileInfo> fileInfo = QList<QFileInfo>(dir->entryInfoList());
    if(fileInfo.size() > 0 )
    {
        /*判断文件输入后剩余容量是否小于512MB*/
        if((storage.bytesAvailable()/1000/1000 - fileSize) < 512)
        {
            /*文件最后修改日期排序*/
            QList<QDateTime> fileTime;
            for(i = 0; i < fileInfo.size(); i++)
            {
                fileTime.append(fileInfo.at(i).lastModified());
            }
            qSort(fileTime.begin(), fileTime.end());//容器元素的递增排序
            /*腾出空间，直到可以容纳输入文件*/
            while(1)
            {
                if((storage.bytesAvailable()/1000/1000 - fileSize) >= 512)
                {
                    break;
                }
                qDebug()<<"while run";
                qDebug()<<fileInfo.size();
                if(fileInfo.size()<= 0 )
                    break;
                for (j = 0;j<fileInfo.size();j++)
                {
                    qDebug()<<"list"<<j;
                    if(fileInfo.at(j).lastModified() == fileTime.at(0))
                    {
                        qDebug()<<fileInfo.at(j).fileName();
                        dir->remove(fileInfo.at(j).fileName());
                        fileInfo.removeAt(j);
                        fileTime.removeAt(0);
                    }
                }
                storage.refresh();
                qDebug()<<storage.bytesAvailable()/1000/1000<<"MB";
            }
            qDebug()<<fileTime;
        }
    }
}

void MainWindow::m_chooseUEN()
{
    m_WinFile->hide();
    m_WinFile->close();
}
