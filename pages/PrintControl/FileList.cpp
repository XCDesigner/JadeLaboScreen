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
        int i = 0;
        qDebug()<<m_fileinfo.count();
        for(i = 0;i< m_fileinfo.count();i++)
        {
            m_addItemToList(m_fileinfo.at(i).fileName(),m_fileinfo.at(i).filePath(),"udisk");
                    qDebug()<<m_fileinfo.at(i).filePath();
                    qDebug()<<m_fileinfo.at(i).fileName();
        }
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

    int i = 0;
    for(i = 0;i< m_fileinfo.count();i++)
    {
        m_addItemToList(m_fileinfo.at(i).fileName(),m_fileinfo.at(i).filePath());
    }

}