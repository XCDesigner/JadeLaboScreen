#include "mainwindow.h"
#include "ui_mainwindow.h"


#ifdef XH_LINUX
void tWifi_event_callback(struct Manager *wmg,int event_lavel)
{
    qDebug()<<"tWifi_event_callback";
}
#endif

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    /*初始化*/
    m_WinFile = NULL;
    pdlg_parsing = NULL;
    skpWin = new askPause(this);
    skpWin->hide();

    changeFilamentDialog = new changeFilamentDlg(this);
    changeFilamentDialog->hide();

    pdlg_warning = new WarningDialog(this);
    pdlg_warning->hide();

    QObject::connect(skpWin, SIGNAL(hideWidget()), this, SLOT(onPauseDialogHide()));
    m_delete = NULL;

    m_wizard = NULL;

    m_port = NULL;
    m_event = NULL;

    m_filamentfault = NULL;
    m_printfilament = NULL;
    m_parsetdlog = NULL;
    chooseit = NULL;

    m_power = NULL;
    m_setdlog = new PrintSetDlog();
    m_setdlog->hide();
    QObject::connect(m_setdlog, SIGNAL(hideWidget()), this, SLOT(onSettingDialogHide()));

#ifdef XH_LINUX
    aw_wifi =NULL;
    udpControl = NULL;
#endif
    m_update = NULL;
    m_fileParser = NULL;

    /*开启串口*/
    m_port = new XhPort(this);
    m_event = new JLEvent(this);

#ifdef XH_WIN
    QList<QString> port_names = JLSerialPort::getPortNames();
    ui->comboBox_15->addItems(QStringList(port_names));
#endif

    /*绑定串口信号*/
    print = new QTimer(this);
    QObject::connect(print,&QTimer::timeout,this,&MainWindow::printTime);
    /*设置透明度淡入淡出*/

    /*设置状态栏*/
    ui->m_StatusBar->setVisible(false);
    /*设置列表*/
    ui->listWidget->setViewMode(QListView::ListMode);
    ui->listWidget->setFlow(QListView::TopToBottom);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setHorizontalScrollMode(QListWidget::ScrollPerPixel);
    ui->listWidget->setVerticalScrollMode(QListWidget::ScrollPerPixel);
    QScroller::grabGesture(ui->listWidget->viewport(),QScroller::LeftMouseButtonGesture);
    QScroller *scroller = QScroller::scroller(ui->listWidget->viewport());
    QScrollerProperties scroller_properties = scroller->scrollerProperties();
    scroller_properties.setScrollMetric(QScrollerProperties::DragVelocitySmoothingFactor,0.3);
    scroller_properties.setScrollMetric(QScrollerProperties::FrameRate,QScrollerProperties::Fps60);
    scroller->setScrollerProperties(scroller_properties);

    ui->listWidget_2->setViewMode(QListView::ListMode);
    ui->listWidget_2->setFlow(QListView::TopToBottom);
    ui->listWidget_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_2->setHorizontalScrollMode(QListWidget::ScrollPerPixel);
    ui->listWidget_2->setVerticalScrollMode(QListWidget::ScrollPerPixel);
    QScroller::grabGesture(ui->listWidget_2->viewport(),QScroller::LeftMouseButtonGesture);
    scroller = QScroller::scroller(ui->listWidget_2->viewport());
    scroller_properties = scroller->scrollerProperties();
    scroller_properties.setScrollMetric(QScrollerProperties::DragVelocitySmoothingFactor,0.3);
    scroller_properties.setScrollMetric(QScrollerProperties::FrameRate,QScrollerProperties::Fps60);
    scroller->setScrollerProperties(scroller_properties);

    ui->listWidget_3->setViewMode(QListView::ListMode);
    ui->listWidget_3->setFlow(QListView::TopToBottom);
    ui->listWidget_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_3->setHorizontalScrollMode(QListWidget::ScrollPerPixel);
    ui->listWidget_3->setVerticalScrollMode(QListWidget::ScrollPerPixel);
    QScroller::grabGesture(ui->listWidget_3, QScroller::LeftMouseButtonGesture);
    scroller = QScroller::scroller(ui->listWidget_3->viewport());
    scroller_properties = scroller->scrollerProperties();
    scroller_properties.setScrollMetric(QScrollerProperties::DragVelocitySmoothingFactor,0.3);
    scroller_properties.setScrollMetric(QScrollerProperties::FrameRate,QScrollerProperties::Fps60);
    scroller->setScrollerProperties(scroller_properties);

    /*检测U盘*/
    QTimer::singleShot(500, this, SLOT(fileList()));

    ui->listWidget->clear();

    printTimer = new QTimer(this);
    m_opaCity=0.0;
    m_effect=new QGraphicsOpacityEffect();
    m_effect->setOpacity(m_opaCity);

    ui->quickWidget_3->setSource(QUrl("qrc:/qml/CircleProgressBar.qml"));
    ui->quickWidget_3->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget_3->setClearColor(QColor(qmlColor));

    ui->qw_PreHeating->setSource(QUrl("qrc:/qml/HeatingCircle.qml"));
    ui->qw_PreHeating->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->qw_PreHeating->setClearColor(QColor(qmlColor));

    ui->qw_Distance->setSource(QUrl("qrc:/qml/DistanceButton.qml"));
    ui->qw_Distance->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->qw_Distance->setClearColor(QColor(qmlColor));

    ui->qw_StatusNotice->setSource(QUrl("qrc:/qml/StatusBarNotice.qml"));
    ui->qw_StatusNotice->setClearColor(QColor(qmlColor));
    ui->qw_StatusNotice->rootObject()->setProperty("udiskVisible", false);
    ui->qw_StatusNotice->rootObject()->setProperty("wifiVisible", false);
    ui->qw_StatusNotice->rootObject()->setProperty("lightChecked", false);

    QObject::connect(ui->quickWidget_3->rootObject(),SIGNAL(finishClicked()), this, SLOT(onFinishPrintClicked()));

    QObject::connect(ui->qw_StatusNotice->rootObject(), SIGNAL(lightClicked()), this, SLOT(StatusNotice_Light_clicked()));
    QObject::connect(ui->qw_StatusNotice->rootObject(), SIGNAL(stepperClicked()), this, SLOT(StatusNotice_Stepper_clicked()));

    QObject::connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(WidgetChanged(int)));

    QTimer::singleShot(1500, this, SLOT(updateStatusBar()));

    m_printsec = new QTimer(this);
    QObject::connect(m_printsec,&QTimer::timeout,this,&MainWindow::timeAdd);

    ListenerInit();

#ifdef  XH_LINUX
    m_port->portInit(serialNum);
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);

    ui->m_StatusBar->setVisible(true);
    QObject::connect(printTimer,&QTimer::timeout,this,&MainWindow::getMachineStatus);
    printTimer->start(1000);
    skpWin->setXHPort(m_port);
    skpWin->setScreenStausContext(&screen_status);
    changeFilamentDialog->setXHPort(m_port);
    changeFilamentDialog->setScreenStausContext(&screen_status);
    m_setdlog->setScreenStausContext(&screen_status);
    m_setdlog->setXHPort(m_port);
    PowerLostInit();
    FaultDetectInit();
#endif

#ifdef XH_WIN
    ui->stackedWidget->setCurrentWidget(ui->page_WinStartup);
#endif

    setWinPic(false);

    m_event->setup(m_port);
    QObject::connect(this->m_event, SIGNAL(changePageAccept(&QByteArray)), this, SLOT(changePageCallback(&QByteArray)));
    QObject::connect(this->m_event, SIGNAL(changeDialogAccept(&QByteArray)), this, SLOT(changeDialogCallback(&QByteArray)));

    QObject::connect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray &)), this, SLOT(printMessageProcess(uint8_t, uint8_t, QByteArray &)));
//    QObject::connect(m_port->getXhPage(), SIGNAL(command_received(uint8_t, uint8_t, QByteArray)), this, SLOT(onMessageTest(uint8_t, uint8_t, QByteArray)));

    AboutPageInit();

    // #if defined(XH_WIN)
    wifiPageInit();
    // #endif

    TempControlInit();
    ExtrudeControlInit();
    platformCalibratePageinit();
    xyCalibratePageinit();
    nozzleCalibratePageinit();
    changeHotendPageInit();
    lightSettingPageInit();
    jodMovePageInit();
    changeFilamentPageInit();
    printingPageInit();
    preparePrintingPageInit();

    // pMovie = new QMovie(this);
    // pMovie->setFileName("/usr/share/3d_printer/test.gif");
    fileListPageInit();
}


MainWindow::~MainWindow()
{
    delete ui;
    if(m_thread->isRunning())
    {
        m_thread->exit(0);
        delete  m_thread;
    }
}

void MainWindow::WidgetChanged(int index)
{
    char buff[20];
    sprintf(buff, "Cur Widget:%d", index);
    qDebug()<<buff;
    if(ui->stackedWidget->currentWidget() == ui->page_ChangeFilament)
    {
        changeFilamentPageLoad();
    }
    else if(ui->stackedWidget->currentWidget() == ui->page_PreparePrint)
    {
        preparePrintPageLoad();
    }
}

void MainWindow::m_adTtemtowifi(const QString &wifiname, QString wifilevel)
{
    myWifiItem *pWidgetItem = new myWifiItem(this);
    pWidgetItem->addwifi(wifiname,wifilevel);
    QListWidgetItem* pItem = new QListWidgetItem(ui->listWidget_3);
    m_wmap.insert(pWidgetItem,pItem);
    ui->listWidget_3->setItemWidget(pItem,pWidgetItem);

    QObject::connect(pWidgetItem,&myWifiItem::conncetwifi,this,&MainWindow::connctwifi);
//    QObject::connect(pWidgetItem,SIGNAL(chooseFile(myListWidgetItem * )),this,SLOT(m_chooseItem(myListWidgetItem * )));
}

void MainWindow::firstStart()
{
    if(m_opaCity >= 1.0)
    {
        m_timer.stop();
        QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(firstStart()));
        QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpOne()));
        m_timer.start(2000);
    }
    else
    {
        m_effect->setOpacity(m_opaCity);
    }
    m_opaCity+=0.1;
}

void MainWindow::jumpOne()
{
    /*跳到welcome页，并初始化G1页参数*/
    ui->stackedWidget->setCurrentIndex(1);
    m_timer.stop();
    m_opaCity=0.0;
    m_effect->setOpacity(m_opaCity);
    QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpOne()));
    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpTwo()));
    m_timer.start(2000);
}

void MainWindow::jumpTwo()
{
    m_timer.stop();
    /*跳转到G1页*/
    ui->stackedWidget->setCurrentIndex(2);
    QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpTwo()));
    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(winGone()));
    m_timer.start(250);
}

void MainWindow::winGone()
{
    if(m_opaCity >= 1.0)
    {
        m_timer.stop();
        QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(winGone()));
        QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(winGtwo()));
        m_timer.start(1000);
    }
    else
    {
        m_effect->setOpacity(m_opaCity);
    }
    m_opaCity+=0.1;
}

void MainWindow::winGtwo()
{
    /*跳页至G2页*/
    ui->stackedWidget->setCurrentIndex(3);
    m_timer.stop();
    m_opaCity=0.0;
    m_effect->setOpacity(m_opaCity);
    QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(winGtwo()));
    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpThree()));
    m_timer.start(2000);
}

void MainWindow::jumpThree()
{
    /*跳页至G3页自检*/
    ui->stackedWidget->setCurrentIndex(4);
    m_timer.stop();
    QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpThree()));

    m_port->askStatus();
}

/*正常启动后进入*/
void MainWindow::jumpFour()
{
    /*当前界面为G5*/
    ui->stackedWidget->setCurrentIndex(6/*7*/);
    m_timer.stop();
    QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpFour()));
}

void MainWindow::jumpFive()
{
    /*G4-1-1*/
    m_timer.stop();
    ui->stackedWidget->setCurrentIndex(9);
    QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpFive()));
    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpSix()));
    m_timer.start(2000);
}

void MainWindow::jumpSix()
{
    /*G4-1-2*/
    m_timer.stop();
    ui->stackedWidget->setCurrentIndex(10);
    QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpSix()));
    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpSeven()));
    m_timer.start(2000);
}

void MainWindow::jumpSeven()
{
    /*G4-1-3*/
    m_timer.stop();
    ui->stackedWidget->setCurrentIndex(11);
    QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpSeven()));
}

void MainWindow::jumpEight()
{
    m_timer.stop();
    ui->stackedWidget->setCurrentIndex(13);
    QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpEight()));
    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpNine()));
    m_timer.start(2000);

}

void MainWindow::jumpNine()
{
    m_timer.stop();
    ui->stackedWidget->setCurrentIndex(14);
    QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpNine()));
    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpTen()));
    m_timer.start(2000);
}

void MainWindow::jumpTen()
{
    m_timer.stop();
    ui->stackedWidget->setCurrentIndex(15);
    QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpTen()));
    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpFour()));
    m_timer.start(2000);
}

void MainWindow::jumpEleven()
{
    /*第一个pageview页面*/
    m_timer.stop();
    QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(jumpEleven()));
    ui->stackedWidget->setCurrentIndex(17);

}

void MainWindow::shineone()
{
#ifdef OLD
    if(flicker)
    {
        if(m_opaCity >= 1.0)
        {
           flicker =false;
        }
        else
        {
            m_effect->setOpacity(m_opaCity);
            ui->pushButton_24->setGraphicsEffect(m_effect);
        }
        m_opaCity += 0.1;
    }
    else
    {
        if(m_opaCity <= 0.0)
        {
            flicker =true;
        }
        else
        {
            m_effect ->setOpacity(m_opaCity);
            ui->pushButton_24->setGraphicsEffect(m_effect);
        }
        m_opaCity -= 0.1;
    }
    timeLonger += 1;
    if(timeLonger == 160)
    {
        m_timer.stop();
        QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(shineone()));
        m_opaCity = 1.0;
        m_effect ->setOpacity(m_opaCity);
        ui->pushButton_24->setGraphicsEffect(m_effect);
    }
#endif
}

void MainWindow::shinetwo()
{
#ifdef OLD
    if(flicker)
    {
        if(m_opaCity >= 1.0)
        {
           flicker =false;
        }
        else
        {
            m_effect->setOpacity(m_opaCity);
            ui->pushButton_41->setGraphicsEffect(m_effect);
        }
        m_opaCity += 0.1;
    }
    else
    {
        if(m_opaCity <= 0.0)
        {
            flicker =true;
        }
        else
        {
            m_effect ->setOpacity(m_opaCity);
            ui->pushButton_41->setGraphicsEffect(m_effect);
        }
        m_opaCity -= 0.1;
    }
    timeLonger += 1;
    if(timeLonger == 1600)
    {
        m_timer.stop();
        QObject::disconnect(&m_timer,SIGNAL(timeout()),this,SLOT(shinetwo()));
        m_opaCity = 1.0;
        m_effect ->setOpacity(m_opaCity);
        ui->pushButton_41->setGraphicsEffect(m_effect);
    }
#endif
}

void MainWindow::jumpnineteen()
{
    /*print3动图槽函数*/

}


void MainWindow::printTime()
{
    printtime++;
}

void MainWindow::getCondition()
{
#ifdef XH_LINUX
    emit sendCondition(currentState);
#endif
}

void MainWindow::downloadOver(QString fileName)
{
    m_fileParser = new XhGcodeFileParser(this);
    m_fileParser->parseByDeep("/usr/share/3d_printer/tmp/"+fileName,localPath+fileName);
    delete m_fileParser;
#ifdef XH_LINUX
    system(QString::asprintf("rm /usr/share/3d_printer/tmp/%s",fileName.toStdString().c_str()).toStdString().c_str());
#endif
}

void MainWindow::connctwifi(myWifiItem *itm)
{
    ui->label_319->setText(itm->wifiname);
    ui->stackedWidget->setCurrentWidget(ui->page_KeyBoard);
    ui->stackedWidget_2->setCurrentIndex(0);
    chooseit = NULL;
    chooseit = itm;
}

void MainWindow::fileList()
{
#ifdef XH_WIN
    QFileInfo usbfile(UDiskfind);
    if(usbfile.isDir())
    {
       ui->qw_StatusNotice->rootObject()->setProperty("udiskVisible", true);
       ui->pushButton_101->setEnabled(true);
    }
    else
    {
        ui->qw_StatusNotice->rootObject()->setProperty("udiskVisible", false);
        ui->pushButton_101->setEnabled(false);
        ui->listWidget_2->setVisible(false);
        ui->listWidget->setVisible(true);
    }
#endif
#ifdef XH_LINUX
    system("mount > /usr/share/3d_printer/tmp/udisk.txt");
    QFile udisk("/usr/share/3d_printer/tmp/udisk.txt");
    if(!udisk.open(QIODevice::ReadOnly|QIODevice::Text))
        return;
    QString mountEcho =  udisk.readAll();
    udisk.close();
    if(mountEcho.contains("/mnt/exUDISK"))
    {
        // qDebug()<<"mount";
        ui->qw_StatusNotice->rootObject()->setProperty("udiskVisible", true);
        ui->pushButton_101->setEnabled(true);
    }
    else
    {
        // qDebug()<<"no mount";
        ui->qw_StatusNotice->rootObject()->setProperty("udiskVisible", false);
        ui->pushButton_101->setEnabled(false);
        ui->listWidget_2->setVisible(false);
        ui->listWidget->setVisible(true);
    }
#endif

    QTimer::singleShot(500, this, SLOT(fileList()));
}

void MainWindow::on_pushButton_129_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_FileList);
    on_pushButton_134_clicked();
}

void MainWindow::on_pushButton_174_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Calibration);
}

void MainWindow::on_pushButton_175_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_ManualControl);
}

void MainWindow::on_pushButton_177_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_MachineSetting);
}

void MainWindow::on_pushButton_230_clicked()
{
    ui->stackedWidget->setCurrentIndex(42);
}

void MainWindow::on_pushButton_235_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_PlatformCali_0);
}

void MainWindow::on_pushButton_236_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_NozzleCali_0);
}

void MainWindow::on_pushButton_237_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_XYCali_0);
}

void MainWindow::on_pushButton_233_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::on_pushButton_170_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_172_clicked()
{
    m_port->prepareChangeFilament();
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeFilament);
}

void MainWindow::on_pushButton_341_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_FILSensorsetting);
}

void MainWindow::on_pushButton_670_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_668_clicked()
{
    m_port->prepareChangeFilament();
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeFilament);
}

void MainWindow::on_pushButton_669_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::on_pushButton_667_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::on_pushButton_231_clicked()
{
    m_port->prepareChangeFilament();
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeFilament);
}

void MainWindow::on_pushButton_232_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_240_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_238_clicked()
{
    m_port->prepareChangeFilament();
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeFilament);
}

void MainWindow::on_pushButton_239_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::on_pushButton_256_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_257_clicked()
{
    m_port->prepareChangeFilament();
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeFilament);
}

void MainWindow::on_pushButton_254_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::on_pushButton_284_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_285_clicked()
{
    m_port->prepareChangeFilament();
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeFilament);
}

void MainWindow::on_pushButton_282_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::on_pushButton_298_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_301_clicked()
{
    m_port->prepareChangeFilament();
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeFilament);
}

void MainWindow::on_pushButton_300_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::on_pushButton_627_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::on_pushButton_646_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::on_pushButton_349_clicked()
{
#ifdef XH_LINUX
    ui->listWidget_3->clear();
    char buff[2048]="";
    int i = sizeof(buff);
    if(aw_wifi->get_scan_results(buff,&i) == 0)
    {
        qDebug()<<buff;
        QString A = QString(buff);
        QStringList C;
        QStringList a = A.split("\n");
        for (int i = 0;i<a.size() ;i++) {
            QStringList b = a[i].split("\t");
            C<<b.at(b.size()-1);
        }
        for (int j =1;j<C.size();j++)
        {
            m_adTtemtowifi(C[j],"1");
        }
    }
    else
    {
        qDebug()<<"scan bad";
    }
#endif
}

void MainWindow::on_pushButton_340_clicked()
{
#ifdef XH_LINUX
    /*wifi初始化进入*/
    if(aw_wifi == NULL)
    {
        ui->listWidget_3->clear();
        ui->stackedWidget->setCurrentWidget(ui->page_WifiConnect_0);
        aw_wifi = aw_wifi_on(tWifi_event_callback,0);
        if(aw_wifi == NULL)
        {
            qDebug()<<"wifi open failed";
            return;
        }
        char buff[2048]="";
        int i = sizeof(buff);
        if(aw_wifi->get_scan_results(buff,&i) == 0)
        {
            qDebug()<<buff;
            QString A = QString(buff);
            QStringList C;
            QStringList a = A.split("\n");
            for (int i = 0;i<a.size() ;i++) {
                QStringList b = a[i].split("\t");
                C<<b.at(b.size()-1);
            }
            for (int j =1;j<C.size();j++)
            {
                m_adTtemtowifi(C[j],"1");
            }

            /*自动连接*/
            QFileInfo wifiConncetinfo(localWIFI);
            if(wifiConncetinfo.isFile())
            {
                QFile wifiConncet(localWIFI);
                QTextStream textStream(&wifiConncet);
                QStringList list;
                if(wifiConncet.open(QIODevice::ReadOnly|QIODevice::Text))
                {
                    /*读文件到list*/
                    while(true)
                    {
                        QString line = textStream.readLine();
                        if(line.isNull())
                            break;
                        else
                            list.append(line.toLatin1());
                    }
                    wifiConncet.close();
                    if(C.size()!=0&&list.size()!=0)
                    {
                        for (int i= 1; i<C.size();i++) {
                            for (int j = 0; j<list.size();j+2) {
                                if(C.at(i) == list.at(j))
                                {
                                    /*如果有存档*/
                                    std::string str = list.at(j).toStdString();
                                    const char * a= str.c_str();
                                    std::string str1 = list.at(j+1).toStdString();
                                    const char * b= str1.c_str();
                                    if(aw_wifi->connect_ap(a,b,1)>=0)
                                    {
                                        /*如果连接成功*/
                                        qDebug()<<"connect success!";
                                        start_udhcpc();
                                        ui->stackedWidget->setCurrentWidget(ui->page_WifiConnect_2);
                                        setWinPic(true);
                                        // wifiControlerInit();
                                        udpControl = new XhControlR818(this);
                                        QObject::connect(udpControl,&XhControlR818::signalsAskCondition,this,&MainWindow::getCondition);
                                        QObject::connect(this,&MainWindow::sendCondition,udpControl,&XhControlR818::slotAskCondition);
                                        QObject::connect(udpControl,&XhControlR818::signalsDownloadOver,this,&MainWindow::downloadOver);
                                        ui->label_316->setText(list.at(j));
                                    }
                                    else
                                    {
                                        qDebug()<<"connect bad";
                                        ui->stackedWidget->setCurrentWidget(ui->page_WifiConnect_1);
                                        setWinPic(false);
                                    }
                                    return;
                                }
                            }

                        }
                    }

                }
            }
        }



    }
    else
    {
        qDebug()<<"scan bad";
    }
#endif

}

void MainWindow::on_pushButton_128_clicked()
{
    m_port->prepareChangeFilament();
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeFilament);
}

void MainWindow::on_pushButton_125_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::on_pushButton_130_clicked()
{
    m_port->prepareChangeFilament();
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeFilament);
}

void MainWindow::on_pushButton_133_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_132_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Tools);
}

void MainWindow::on_pushButton_354_clicked()
{
    m_port->portInit(ui->comboBox_15->currentText());
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
    skpWin->setXHPort(m_port);
    skpWin->setScreenStausContext(&screen_status);
    changeFilamentDialog->setXHPort(m_port);
    changeFilamentDialog->setScreenStausContext(&screen_status);
    m_setdlog->setXHPort(m_port);
    m_setdlog->setScreenStausContext(&screen_status);
    ui->m_StatusBar->setVisible(true);
    QObject::connect(printTimer,&QTimer::timeout,this,&MainWindow::getMachineStatus);
    printTimer->start(1000);
    PowerLostInit();
    FaultDetectInit();
    //while(1) {

    //}
}

void MainWindow::on_pushButton_356_clicked()
{
    m_filamentfault = new  filamentFault(this);
    m_filamentfault->show();
    ui->stackedWidget->setCurrentWidget(ui->page_Printing);
}

void MainWindow::on_pushButton_689_clicked()
{
#ifdef XH_LINUX
    std::string str = chooseit->wifiname.toStdString();
    const char * a= str.c_str();

    std::string str1 = ui->lineEdit->text().toStdString();
    const char * b= str1.c_str();

    qDebug()<<"a"<<a;
    qDebug()<<"b"<<b;
    if(aw_wifi->connect_ap(a,b,1)>=0)
    {
        qDebug()<<"connect success!";
        start_udhcpc();
        ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
        setWinPic(true);
        // wifiControlerInit();

        QFile wifiConnect(localWIFI);
        QTextStream textStream(&wifiConnect);
        QStringList list;
        if(wifiConnect.open(QIODevice::ReadWrite|QIODevice::Text))
        {
            list.clear();
            /*读文件到list*/
            while(true)
            {
                QString line = textStream.readLine();
                if(line.isNull())
                    break;
                else
                   list.append(line.toLatin1());
            }
            /*保存最新k-v*/
            if(list.contains(chooseit->wifiname))
            {
                int index = list.indexOf(chooseit->wifiname);
                list.replace(index+1,ui->lineEdit->text());
            }
            else
            {
                list.append(chooseit->wifiname);
                list.append(ui->lineEdit->text());
            }
            /*判断是否超标*/
            while(list.size()>40)
            {
                list.removeAt(0);
                list.removeAt(0);
            }
            wifiConnect.resize(0);
            for (int i = 0 ;i<list.size();i++) {
                wifiConnect.write(list.at(i).toLatin1()+"\n");
            }
            wifiConnect.close();
#ifdef OLD
            wifiConnect.resize(0);
            wifiConnect.write(chooseit->wifiname.toLatin1());
            wifiConnect.write(" ");
            wifiConnect.write(ui->lineEdit->text().toLatin1());
            wifiConnect.close();
#endif
        }
        if(udpControl == NULL)
        {
            udpControl = new XhControlR818(this);
            QObject::connect(udpControl,&XhControlR818::signalsAskCondition,this,&MainWindow::getCondition);
            QObject::connect(this,&MainWindow::sendCondition,udpControl,&XhControlR818::slotAskCondition);
            QObject::connect(udpControl,&XhControlR818::signalsDownloadOver,this,&MainWindow::downloadOver);
        }

    }
    else
    {
        qDebug()<<"connect bad";
        ui->stackedWidget->setCurrentWidget(ui->page_WifiConnect_1);
        setWinPic(false);
    }
#endif
}

void MainWindow::on_pushButton_691_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_MachineSetting);
    if(chooseit)
        ui->label_316->setText(chooseit->wifiname);
    ui->label_316->setStyleSheet("QLabel{font-weight: bold;\
            font-family:Barlow;border-radius: 20px;\
            background-color: rgb(255, 99, 11);\
            color: rgba(255, 255, 255, 255);\
            font-size: 36px;font-weight:bold;\
            border: 2px solid rgba(255, 99, 11, 255);\
};");
}

void MainWindow::on_pushButton_690_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_MachineSetting);
    ui->label_316->setText("none");
    ui->label_316->setStyleSheet("QLabel{background-color: rgba(255, 255, 255, 0);\
                                 color: rgb(255, 255, 255);\
                                 font-family:Barlow;\
                                 font-weight:bold;\
                                 font-size:36px;\
};");
}

void MainWindow::on_pushButton_688_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_MachineSetting);
}

void MainWindow::on_pushButton_447_clicked()
{
    updateFileAnalize(UpdateSourceFile);
    // m_port->updateBegin(UpdateFile);
}

//void MainWindow::on_pushButton_453_clicked(bool checked)
//{
//    if(!checked)
//    {
//        if(!ui->pushButton_454->isChecked())
//        {
//            ui->pushButton_454->setChecked(true);
//        }
//    }
//}

//void MainWindow::on_pushButton_454_clicked(bool checked)
//{
//    if(!checked)
//    {
//        if(!ui->pushButton_453->isChecked())
//        {
//            ui->pushButton_453->setChecked(true);
//        }
//    }
//}

void MainWindow::onMessageTest(uint8_t Command, uint8_t SubCode, QByteArray &Datas)
{
    if(Command == 0x09) {
        if(SubCode == 0x01)
        {
            test_inc++;
            char tmpBuff[20];
            sprintf(tmpBuff, "test:%d", test_inc);
            qDebug()<<tmpBuff;
        }
        else if(SubCode == 0x02)
        {
            qDebug()<<test_inc;
            test_inc = 0;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_272_clicked()
{
    QByteArray prepare_manual_move = QByteArray::fromHex("0209");
    blockingChangePage(prepare_manual_move, ui->page_JodMove);
}

void MainWindow::on_pushButton_269_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_273_clicked()
{
    m_port->prepareChangeFilament();
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeFilament);
}

void MainWindow::on_pushButton_268_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_TempControl);
}

void MainWindow::on_pushButton_119_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GetStart);
}

void MainWindow::on_pushButton_146_clicked()
{
    m_port->prepareChangeFilament();
    ui->stackedWidget->setCurrentWidget(ui->page_ChangeFilament);
}
