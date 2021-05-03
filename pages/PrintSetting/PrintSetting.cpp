#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::onSettingDialogHide()
{
    qDebug()<<"Setting dialog hide";
    QList<QByteArray> ret = m_setdlog->get_return_value();
    qDebug()<<ret[0];
    if(ret[0] == "Enable Backup")
        m_port->setBackupEnableStatus(true);
    else if(ret[0] == "Disable Backup")
        m_port->setBackupEnableStatus(false);
}
