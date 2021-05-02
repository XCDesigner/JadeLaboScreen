#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CMOD/XhUpdater.h"
#include <QThread>

void MainWindow::FilamentFaultDetected()
{
    m_filamentfault = new filamentFault(this);
    m_filamentfault->init(QByteArray());
    m_filamentfault->show();
    QObject::connect(m_filamentfault, SIGNAL(hideWidget()), this, SLOT(onFilamentFaultDialogReturn()));
}

void MainWindow::onFilamentFaultDialogReturn()
{
    QList<QByteArray> ret = m_filamentfault->get_return_value();
    if(ret[0] == "ChangeFilament")
    {
        changeDialog((JLWidget*)changeFilamentDialog);
    }
    else if(ret[0] == "Resume")
    {
        m_port->resume();
    }
    else if(ret[0] == "Cancel")
    {

    }

    delete m_filamentfault;
}
