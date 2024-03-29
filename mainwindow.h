#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customTypes.h"

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QQuickWidget>
#include <QDialog>
#include <QString>
#include <QByteArray>
#include <QMap>
#include <QDebug>
#include <QListWidgetItem>
#include <QQuickItem>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QDataStream>
#include <QMessageBox>
#include <QMutex>
#include <QStorageInfo>
#include "CMOD/xhpage.h"
#include "CMOD/xhEvent.h"
#include "CMOD/xhport.h"
#include "dialog/choosefile.h"
#include "dialog/parsing.h"
#include "dialog/askpause.h"
#include "dialog/changefilamentdlg.h"
#include "dialog/selectmode.h"
#include "dialog/xhwizard.h"
#include "dialog/delete.h"
#include "oldplan/filecheckthread.h"
#include "dialog/choosetemp.h"
#include "dialog/unnoknfile.h"
#include "dialog/filamentfault.h"
#include "dialog/printflament.h"
#include "dialog/powerlost.h"
#include "dialog/printsetdlog.h"
#include "dialog/parsetdlog.h"
#include "dialog/dupandmirror.h"
#include "dialog/duponly.h"
#include "dialog/jlwidget.h"
#include "dialog/printmodeselect.h"
#include "listwidgetitem/mywifiitem.h"
#include "dialog/updateprogrebar.h"
#include "dialog/warningdialog.h"
#include "CMOD/XhGcodeFileParser.h"
#include "CMOD/screenstatus.h"
#include "listwidgetitem/mylistwidgetitem.h"
#ifdef XH_LINUX
#include "wifi_intf.h"
#include "wifi_udhcpc.h"
#include "CMOD/xhcontrolr818.h"
#include <stdlib.h>
#endif
#include <QPixmap>
#include <QString>
#include <QStringList>
#include <QGuiApplication>
#include <QProcess>
#include <QSet>
#include <binders.h>
#include <QScroller>

#include "define/imagePath.h"

#include "CMOD/jlserialport.h"
#include <QThread>
#include <CMOD/jlprotocal.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setUSBpic(bool isVisible);
    void setLightPic(bool isVisible);
    void setWinPic(bool isVisible);

    void m_addItemToList(const QString &, QString, QByteArray);
    void m_adTtemtowifi(const QString& wifiname,QString wifilevel);

    //void blockingChangePage(QByteArray Command, QWidget *pPage);
    void blockingChangePage(QByteArray Command, QWidget *pPage, bool NeedProcessingPage = true);
    void blockingChangeDialog(QByteArray Command, JLWidget *pDialog);
    void changeDialog(JLWidget *pDialog);
    void changePageOnStatus(QByteArray Status, QWidget *pPage);

    void changeFilamentPageInit();
    void AboutPageInit();

    void ListenerInit();
    void AddListen(QByteArray MatchData, pFunction, bool);
    void TestListener(QByteArray);

private:
    Ui::MainWindow *ui;

    int changeFilamentSelectExtruder;

    float m_opaCity;
    bool flicker;

    int printMode;
    int itemMode;
    int timeLonger;
    int m_x;
    int m_y;
    int m_w;
    int m_h;
    int printtime;
    QString lt;
    QString rt;
    QString bt;

    strPrintDesc print_desc;

    QString loaclPATH;
    QString udiskPATH;
    bool openMode;

    QByteArray offset;

    QGraphicsOpacityEffect *m_effect;
    QTimer m_timer;
    QTimer *fileListTimer;
    QTimer *printTimer;
    QTimer *print;

    QMap<myListWidgetItem *,QListWidgetItem* > m_map;
    QMap<myWifiItem *,QListWidgetItem* >m_wmap;

    chooseFile * m_WinFile;
    parsing *pdlg_parsing;
    askPause * skpWin;
    selectMode * m_mode;
    Delete * m_delete;
    changeFilamentDlg *changeFilamentDialog;

    XhWizard *m_wizard;

    XhPort *m_port;
    JLEvent *m_event;
    fileCheckThread *m_thread;
    chooseTemp *mchoose;

    PrintModeSelect *pdlg_select_mode;
    WarningDialog *pdlg_warning;

    UnNoknfile *m_modeone;
    DupandMirorr *m_dam;
    duponly *m_dup;


    QQuickItem *item;
    QQuickItem *item3;
    QQuickItem *item4;
    QQuickItem *qw_DistanceItem;
    QQuickItem *qw_LightItem;

    filamentFault *m_filamentfault;
    printFlament *m_printfilament;

    powerLost *m_power;

    PrintSetDlog *m_setdlog;
    parsetdlog *m_parsetdlog;
    int32_t  offsetnum;

    myWifiItem * chooseit;
#ifdef XH_LINUX
    const aw_wifi_interface_t *aw_wifi;
    XhControlR818 *udpControl;
    QByteArray currentState;
#endif
    updateProgreBar *m_update;
    XhGcodeFileParser *m_fileParser;
    /*打印计时*/
    QTimer *m_printsec;
    QTime *m_time;

    QTimer *timer_light_slider;

    QWidget *pNextShowPage;
    JLWidget *pDialogToShow;
    QByteArray statusWaiting;

    ScreenStatus screen_status;
    JLSerialPort *serial_port;

    int test_inc;

    QByteArray printerUpdateFileBuffer;
    uint16_t printerUpdatePacks;
    XhUpdater *m_upDater;

    // Message Listen List
    QList<ListenerItem> lst_listen_item;

private slots:
    void printMessageProcess(uint8_t, uint8_t, QByteArray Datas);
    void nozzleCalibrationMessageProcess(uint8_t Command, uint8_t SubCode, QByteArray Datas);
    void platformCalibrationMessageProcess(uint8_t Command, uint8_t SubCode, QByteArray Datas);
    void xyCalibrationMessageProcess(uint8_t Command, uint8_t SubCode, QByteArray Datas);

    void onFinishPrintClicked();
    void preparePrinTempChecking();
    void preparePrintPageInit();

    void PowerLostDialogReturn();
    void RecoveryStop();
    void RecoverySettingShow();

    void onFilamentFaultDialogReturn();

    void onFileChooseReturn();
    void onDeleteFileReturn();
    void onModeSelectReturn();
    void onParseComplete();

    // Fault detection
    void onMessageListen(uint8_t, uint8_t, QByteArray);

    //Test
    void onMessageTest(uint8_t Command, uint8_t SubCode, QByteArray Datas);

    // Update page
    void updateFileAnalize();
    QList<uint32_t> getUpdateItem(uint32_t SearchType);
    QByteArray getUpdateInfo(QList<uint32_t>);
    QByteArray getUpdateContent(QList<uint32_t>);
    void startUpdatePrinter();
    void startUpdateScreen();
    void sendPrinterUpdatePack(uint16_t PackIndex);
    void sendEndUpdatePrinter();
    void sendPrinterUpdateInfo();
    void updateCommandProcess(uint8_t Command, uint8_t SubCode, QByteArray Datas);
    void rebootSystem();

    void updateStatusBar();
    void waitforIdleStatus();
    void changePageCallback(QByteArray ReplyData);
    void changeDialogCallback(QByteArray ReplyData);
    void onPauseDialogHide();
    void onSettingDialogHide();
    void firstStart();
    void jumpOne();
    void jumpTwo();
    void winGone();

    void winGtwo();
    void jumpThree();

//    void winGfour();
    void winGfour(bool a,bool b,bool c,bool d,bool e);
    void jumpFour();

    void jumpFive();
    void jumpSix();
    void jumpSeven();

    void jumpEight();
    void jumpNine();
    void jumpTen();

    void jumpEleven();
    void shineone();
    void shinetwo();

    void askPrint();
    void jumpSeventeen();
    void jumpnineteen();

    void printStop();
    void printPause();
    void printContinue();
    void printChangeFilament();
    void printTime();

    /******udp**************/
    void getCondition();
    void downloadOver(QString );
    /***/


    void m_deleteItem(myListWidgetItem * itm);
    void m_chooseItem(myListWidgetItem * itm);

    void connctwifi(myWifiItem* itm);
    void m_canPrintFile();
    void m_parcancel();

    void m_backPrint();
    void m_whatThis();

    void wizardCancel();
    void wizardConfirm();

    void fileList();

    void nozzleCalibrationHeating();
    void platformCalibrationHeating();
    void xyCalibrationHeating();

    void changeFilamentTempChecking();

    void plt(QString a);
    void prt(QString a);

    void selftest1();
    void selftest2();
    void selftest3();
    void selftest4();
    void selftest5();
    void selftest6();

    void paracktiv(bool );
    void findhotend();
    void cannext(bool );

    void up();
    void down();

    void updatebegin();
    void updateNumx(int );

    void timeAdd();

    void on_pushButton_129_clicked();

    void on_pushButton_134_clicked();

    void on_pushButton_169_clicked();

    void on_pushButton_174_clicked();

    void on_pushButton_175_clicked();

    void on_pushButton_176_clicked();

    void on_pushButton_177_clicked();

    void on_pushButton_182_clicked();

    void on_pushButton_183_clicked();

    void on_pushButton_194_clicked();

    void on_pushButton_195_clicked();

    void on_pushButton_206_clicked();

    void on_pushButton_207_clicked();

    void on_pushButton_212_clicked();

    void on_pushButton_213_clicked();

    void on_pushButton_218_clicked();

    void on_pushButton_219_clicked();

    void on_pushButton_224_clicked();

    void on_pushButton_225_clicked();

    void on_pushButton_230_clicked();

    void on_pushButton_235_clicked();

    void on_pushButton_236_clicked();

    void on_pushButton_237_clicked();

    void on_pushButton_242_clicked();

    void on_pushButton_259_clicked();

    void on_pushButton_286_clicked();

    void on_pushButton_287_clicked();

    void on_pushButton_302_clicked();

    void on_pushButton_303_clicked();

    void on_pushButton_631_clicked();

    void on_pushButton_632_clicked();

    void on_pushButton_647_clicked();

    void on_pushButton_233_clicked();

    void on_pushButton_180_clicked();

    void on_pushButton_170_clicked();

    void on_pushButton_172_clicked();

    void on_pushButton_173_clicked();

    void on_pushButton_341_clicked();

    void on_pushButton_670_clicked();

    void on_pushButton_668_clicked();

    void on_pushButton_669_clicked();

    void on_pushButton_671_clicked();

    void on_pushButton_667_clicked();

    void on_pushButton_179_clicked();

    void on_pushButton_181_clicked();

    void on_pushButton_178_clicked();

    void on_pushButton_193_clicked();

    void on_pushButton_190_clicked();

    void on_pushButton_191_clicked();

    void on_pushButton_202_clicked();

    void on_pushButton_203_clicked();

    void on_pushButton_205_clicked();

    void on_pushButton_210_clicked();

    void on_pushButton_209_clicked();

    void on_pushButton_211_clicked();

    void on_pushButton_216_clicked();

    void on_pushButton_214_clicked();

    void on_pushButton_215_clicked();

    void on_pushButton_220_clicked();

    void on_pushButton_223_clicked();

    void on_pushButton_221_clicked();

    void on_pushButton_227_clicked();

    void on_pushButton_226_clicked();

    void on_pushButton_228_clicked();

    void on_pushButton_243_clicked();

    void on_pushButton_231_clicked();

    void on_pushButton_232_clicked();

    void on_pushButton_234_clicked();

    void on_pushButton_240_clicked();

    void on_pushButton_238_clicked();

    void on_pushButton_239_clicked();

    void on_pushButton_241_clicked();

    void on_pushButton_248_clicked();

    void on_pushButton_256_clicked();

    void on_pushButton_257_clicked();

    void on_pushButton_254_clicked();

    void on_pushButton_255_clicked();

    void on_pushButton_284_clicked();

    void on_pushButton_285_clicked();

    void on_pushButton_282_clicked();

    void on_pushButton_283_clicked();

    void on_pushButton_298_clicked();

    void on_pushButton_301_clicked();

    void on_pushButton_300_clicked();

    void on_pushButton_299_clicked();

    void on_pushButton_628_clicked();

    void on_pushButton_629_clicked();

    void on_pushButton_627_clicked();

    void on_pushButton_630_clicked();

    void on_pushButton_637_clicked();

    void on_pushButton_643_clicked();

    void on_pushButton_644_clicked();

    void on_pushButton_646_clicked();

    void on_pushButton_645_clicked();

    void on_pushButton_347_clicked();

    void on_pushButton_342_clicked();

    void on_pushButton_348_clicked();

    void on_pushButton_349_clicked();

    void on_pushButton_340_clicked();

    void on_pushButton_679_clicked();

    void on_pushButton_676_clicked();

    void on_pushButton_678_clicked();

    void on_pushButton_677_clicked();

    void on_pushButton_128_clicked();

    void on_pushButton_125_clicked();

    void on_pushButton_126_clicked();

    void on_pushButton_130_clicked();

    void on_pushButton_133_clicked();

    void on_pushButton_132_clicked();

    void on_pushButton_131_clicked();

    void on_pushButton_149_clicked();

    void on_pushButton_151_clicked();

    void on_pushButton_148_clicked();

    void on_pushButton_346_clicked();

    void on_pushButton_354_clicked();

    void on_pushButton_253_clicked();

    void on_pushButton_365_clicked();

    void on_pushButton_367_clicked();

    void on_pushButton_375_clicked();

    void on_pushButton_308_clicked();

    void on_pushButton_356_clicked();

    void on_pushButton_263_clicked();

    void on_pushButton_262_clicked();

    void on_pushButton_100_clicked();

    void on_pushButton_101_clicked();

    void on_pushButton_371_clicked();

    void on_pushButton_373_clicked();

    void on_pushButton_164_clicked();

    void on_pushButton_393_clicked();

    void on_pushButton_313_clicked();

    void on_pushButton_387_clicked();

    void on_pushButton_418_clicked();

    void on_pushButton_138_clicked();

    void on_pushButton_139_clicked();

    void on_pushButton_142_clicked();

    void on_pushButton_143_clicked();

    void on_pushButton_144_clicked();

    void on_pushButton_145_clicked();

    void on_pushButton_150_clicked();

    void on_pushButton_152_clicked();

    void on_pushButton_153_clicked();

    void on_pushButton_154_clicked();

    void on_pushButton_155_clicked();

    void on_pushButton_156_clicked();

    void on_pushButton_157_clicked();

    void on_pushButton_158_clicked();

    void on_pushButton_159_clicked();

    void on_pushButton_163_clicked();

    void on_pushButton_165_clicked();

    void on_pushButton_166_clicked();

    void on_pushButton_258_clicked();

    void on_pushButton_265_clicked();

    void on_pushButton_267_clicked();

    void on_pushButton_297_clicked();

    void on_pushButton_311_clicked();

    void on_pushButton_385_clicked();

    void on_pushButton_382_clicked();

    void on_pushButton_398_clicked();

    void on_pushButton_381_clicked();

    void on_pushButton_397_clicked();

    void on_pushButton_389_clicked();

    void on_pushButton_392_clicked();

    void on_pushButton_407_clicked();

    void on_pushButton_399_clicked();

    void on_pushButton_384_clicked();

    void on_pushButton_383_clicked();

    void on_pushButton_404_clicked();

    void on_pushButton_388_clicked();

    void on_pushButton_390_clicked();

    void on_pushButton_395_clicked();

    void on_pushButton_406_clicked();

    void on_pushButton_403_clicked();

    void on_pushButton_386_clicked();

    void on_pushButton_394_clicked();

    void on_pushButton_405_clicked();

    void on_pushButton_360_clicked();

    void on_pushButton_400_clicked();

    void on_pushButton_396_clicked();

    void on_pushButton_379_clicked();

    void on_pushButton_345_clicked();

    void on_pushButton_380_clicked();

    void on_pushButton_416_clicked();

    void on_pushButton_413_clicked();

    void on_pushButton_429_clicked();

    void on_pushButton_412_clicked();

    void on_pushButton_428_clicked();

    void on_pushButton_420_clicked();

    void on_pushButton_423_clicked();

    void on_pushButton_438_clicked();

    void on_pushButton_430_clicked();

    void on_pushButton_415_clicked();

    void on_pushButton_414_clicked();

    void on_pushButton_435_clicked();

    void on_pushButton_419_clicked();

    void on_pushButton_421_clicked();

    void on_pushButton_426_clicked();

    void on_pushButton_437_clicked();

    void on_pushButton_434_clicked();

    void on_pushButton_417_clicked();

    void on_pushButton_425_clicked();

    void on_pushButton_424_clicked();

    void on_pushButton_436_clicked();

    void on_pushButton_409_clicked();

    void on_pushButton_431_clicked();

    void on_pushButton_427_clicked();

    void on_pushButton_410_clicked();

    void on_pushButton_408_clicked();

    void on_pushButton_411_clicked();

    void on_pushButton_689_clicked();

    void on_pushButton_691_clicked();

    void on_pushButton_690_clicked();

    void on_pushButton_642_clicked();

    void on_pushButton_312_clicked();

    void on_pushButton_401_clicked();

    void on_pushButton_432_clicked();

    void on_pushButton_433_clicked();

    void on_pushButton_402_clicked();

    void on_pushButton_688_clicked();

    void on_pushButton_447_clicked();

    void on_pushButton_692_clicked();

    void on_pushButton_453_clicked(bool checked);

    void on_pushButton_454_clicked(bool checked);

    void on_pushButton_455_clicked();

    void on_pushButton_693_clicked();

    void on_pushButton_694_clicked();

    void on_pushButton_695_clicked();

    void on_pushButton_698_clicked();

    void on_pushButton_697_clicked();

    void on_pushButton_696_clicked();

    void on_pushButton_699_clicked();

    void on_pushButton_701_clicked();

    void on_pushButton_700_clicked();

    void on_pushButton_350_clicked();

    void LightSliderPressed();
    void LightSliderReleased();
    void LightSettingTimer();

    void leftSetTemp();
    void leftExtrude();
    void leftRetract();
    void rightSetTemp();
    void rightExtrude();
    void rightRetract();
    void onSetTemp();

    void StopPreHeatting();

    void on_pushButton_702_clicked();

    void ExtruderChange();

    void StatusNotice_Light_clicked();

    void ShowPauseDialogClicked();
    void ShowParameterDialogClicked();
    void StopPrintClicked();
    void WidgetChanged(int index);

    void on_pushButton_648_clicked();

    void on_pushButton_359_clicked();

    void on_pushButton_113_clicked();

    void on_pushButton_117_clicked();

    void on_AboutReturn(int);

signals:
    void detection(bool);
    void updateNum(int );
    void sendCondition(QByteArray);
    void sendSignalToQml(int );
    void sendSignalHeating(int , int );

    void printUpdateCompleted();
private:
    void romClean(int fileSize);

    void PowerLostInit();
    void PowerTestResult(QByteArray);
    void AcceptRecoveryInfo(QByteArray);
    QString GetRecoveryFile();

    void FaultDetectInit();
    void onPauseRequest(QByteArray);
    void onFaultFlag(QByteArray);

    void FilamentFaultDetected();
    void MovementFaultDetected();

    void platformCalibrateFail();
    void xyCalibrateFail();

    void onPreparePirntComplete(QByteArray);

};

#endif // MAINWINDOW_H
