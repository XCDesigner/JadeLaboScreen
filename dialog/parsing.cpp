#include "parsing.h"
#include "ui_parsing.h"

parsing::parsing(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::parsing)
{
    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl("qrc:/qml/CircleProgressBar.qml"));
    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget->setClearColor(QColor("#2d2c2b"));

    m_file_parser = new XhGcodeFileParser(this);
    QObject::connect(m_file_parser, SIGNAL(parseSucceded(QString)), this, SLOT(onParseComplete(QString)));
}

parsing::~parsing()
{
    delete ui;
}

void parsing::init(QByteArray InitData, QString ReqMode, QString InputFile, QString OutputFileName)
{
    req_mode = ReqMode;
    is_parsing = true;
    if(ReqMode == "Direct")
        m_file_parser->parseByDirect(InputFile, OutputFileName);
    else
        m_file_parser->parseByDeep(InputFile, OutputFileName);
}

void parsing::show()
{
    QWidget::show();

    QTimer::singleShot(50, this, SLOT(updateParsingStatus()));
}

void parsing::updateParsingStatus()
{
    if(is_parsing == true)
    {
        QByteArray status = m_file_parser->getParseStatus();
        int percent = m_file_parser->getPercent();
        ui->quickWidget->rootObject()->setProperty("currentPercent", percent);
        QTimer::singleShot(50, this, SLOT(updateParsingStatus()));
    }
}

void parsing::onParseComplete(QString FileName)
{
    output_file_name = FileName;
    qDebug()<<FileName;
    is_parsing = false;
    ui->quickWidget->rootObject()->setProperty("currentPercent", 1000);
    QTimer::singleShot(500, this, SLOT(onDelayReturn()));
}

void parsing::onDelayReturn()
{
    QVariantMap parsed_result = m_file_parser->parseQuickly(localPath + output_file_name);
    qDebug()<<req_mode;
    if((req_mode != "Direct") && (parsed_result["mode"].toString() != req_mode))
    {
        ret_value.append("Fail");
        ret_value.append(QByteArray(output_file_name.toUtf8()));
    }
    else
    {
        ret_value.append("Success");
        ret_value.append(QByteArray(output_file_name.toUtf8()));
        ret_value.append(QByteArray(req_mode.toUtf8()));
    }
    emit hideWidget();
    hide();
}

void parsing::on_pushButton_clicked()
{
    emit cancel();
}
