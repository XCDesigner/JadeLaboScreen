#ifndef XHGCODEFILEPARSER_H
#define XHGCODEFILEPARSER_H

#include <QThread>
#include <QMutex>
#include <QStringList>
#include <QVariantMap>
#include <QAtomicInt>
#include "define/imagePath.h"

class XhGcodeFileParser : public QThread
{
    Q_OBJECT

public:
    enum class Status {
        Normal,
        Parseing
    };

    enum class ParseType : int {
        None,
        Direct,
        Deep
    };

public:
    explicit XhGcodeFileParser(QObject *parent = nullptr);
    virtual ~XhGcodeFileParser();

    void    parseByDirect(const QString &inputFileName, const QString &outputFileName, QByteArray);
    void    parseByDeep(const QString &inputFileName, const QString &outputFileName, QByteArray);

    void    parseByDirect(const QString &inputFileName, const QString &outputFileName);
    void    parseByDeep(const QString &inputFileName, const QString &outputFileName);

    QVariantMap parseQuickly(const QString inputFileName);
    void    clearRam();
    QByteArray getParseStatus();
    int     getPercent();

    int     GetParsedLine();

    /* 2021/3/8/ by paladin  over */
signals:
    void    parseSucceded(QString outputFileName);

protected:
    virtual void run() override;

private:
    QMutex          *m_mutex{ new QMutex };
    QString         m_inputFileName;
    QString         m_outputFileName;
    QAtomicInt      m_parseType{ (int)ParseType::None };

private:
    int             m_lineParsed{ 0 };
    QStringList     *m_sourceGcodeLines{ new QStringList };
    int             m_lastToolHead{ 0 };
    int             m_tempOffset{ 0 };
    int             m_startLineIndex{ 0 };
    QVariantMap     m_headerInfo;
    bool            m_relativeMotion{ false };
    int             line_parsed;
    bool            m_origin_duplucate_found{ false };
    QByteArray      process_status;
    int             process_percent;
    QByteArray      file_from;

private:
    void            doParseByDirect();
    void            doParseByDeep();
    void            variableInit();
    void            loadFile();
    void            loadFile(int);
    void            getJlHeader();
    void            parseTop100Lines();
    void            parseStartLine(QString &gcode, int lineNumber);
    QString         getSymbolValue(QString symbol, QString string);
    void            parseTemp(QString &gcode);
    void            parseToolHead(QString &gcode);
    void            parseMode(QString &gcode);
    void            parseWholeFile();
    bool            parseMotionMode(QString &gcode);
    float           parseXValue(QString &gcode);
    void            writeNewFile();
    QString         header2StringLine();
    QString         cutComment(QString gcode);
    void            rewriteLocalFile();
};

#endif // XHGCODEFILEPARSER_H
