#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::state(QString a, QString b, QString c, QString d, QString e, QString f, QString g)
{
    if(m_setdlog != NULL)
    {
        m_setdlog->initnum(a,b,c,d,e,f,g);
    }
    if(m_parsetdlog != NULL)
    {
        m_parsetdlog->initnum(a,b,c,d,e,f,g);
    }
}

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
