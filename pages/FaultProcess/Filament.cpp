#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CMOD/XhUpdater.h"
#include <QThread>

void MainWindow::FilamentFaultDetected()
{
    QByteArray s0 = "Filament";
    pdlg_warning->init(s0);
    pdlg_warning->show();

    m_filamentfault = new filamentFault(this);
    QByteArray s1;
    m_filamentfault->init(s1);
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
        m_port->continuePrint();
    }
    else if(ret[0] == "Cancel")
    {

    }
    delete m_filamentfault;
}
