#include "XhGcodeFileParser.h"

#include <QFile>
#include <QByteArray>
#include <QChar>
#include <QMutexLocker>
#include <QDebug>
#include <QTextStream>

XhGcodeFileParser::XhGcodeFileParser(QObject *parent) : QThread(parent)
{
    m_headerInfo.insert("result", false);
    m_headerInfo.insert("mode", "Unknown");
    m_headerInfo.insert("offset", "0");
    m_headerInfo.insert("left_temp", "0");
    m_headerInfo.insert("right_temp", "0");
    m_headerInfo.insert("bed_temp", "0");
}

XhGcodeFileParser::~XhGcodeFileParser()
{
    delete m_sourceGcodeLines;
    delete m_mutex;
}

void XhGcodeFileParser::parseByDirect(const QString &inputFileName, const QString &outputFileName, QByteArray FileFrom)
{
    qDebug()<<"Input: " << inputFileName;
    qDebug()<<QFileInfo(inputFileName).path();
    qDebug()<<UDiskPath;
    if(QFileInfo(inputFileName).path() == UDiskPath)
        file_from = "UDisk";
    process_percent = 0;
    m_mutex->lock();
    m_inputFileName = inputFileName;
    m_outputFileName = outputFileName;
    m_mutex->unlock();
    m_parseType.store((int)ParseType::Direct);
    start();
}

void XhGcodeFileParser::parseByDeep(const QString &inputFileName, const QString &outputFileName, QByteArray FileFrom)
{
    qDebug()<<"Input: " << inputFileName;
    qDebug()<<QFileInfo(inputFileName).path();
    qDebug()<<UDiskPath;
    if(QFileInfo(inputFileName).path() == UDiskPath)
        file_from = "UDisk";
    process_percent = 0;
    m_mutex->lock();
    m_inputFileName = inputFileName;
    m_outputFileName = outputFileName;
    m_mutex->unlock();
    m_parseType.store((int)ParseType::Deep);
    start();

}

void XhGcodeFileParser::parseByDirect(const QString &inputFileName, const QString &outputFileName)
{
    parseByDirect(inputFileName, outputFileName, QByteArray(""));
}

void XhGcodeFileParser::parseByDeep(const QString &inputFileName, const QString &outputFileName)
{
    parseByDeep(inputFileName, outputFileName, QByteArray(""));
}

int XhGcodeFileParser::GetParsedLine()
{
    if(line_parsed >= (m_sourceGcodeLines->size() - 1))
    {
        return 1000;
    }
    else
    {
        return (int)(line_parsed * 1000 / m_sourceGcodeLines->size());
    }
}

void XhGcodeFileParser::run()
{
    ParseType parseType = (ParseType)m_parseType.load();

    switch (parseType) {
    case ParseType::Direct:
        doParseByDirect();
        break;
    case ParseType::Deep:
        doParseByDeep();
        break;
    default:
        break;
    }
    qDebug()<<file_from;
    if(file_from == "UDisk")
        writeNewFile();
    else
        rewriteLocalFile();

    m_mutex->lock();
    QString outputFileName = m_outputFileName;
    m_mutex->unlock();
    process_status = QByteArray("Complete");
    m_sourceGcodeLines->clear();
    emit parseSucceded(outputFileName);
}

void XhGcodeFileParser::doParseByDirect()
{
    variableInit();
    loadFile();
    getJlHeader();

    if (m_headerInfo["result"] == false)
    {
        parseTop100Lines();
        int l  = m_headerInfo["left_temp"].toString().toInt();
        if((m_headerInfo["mode"].toString() == "Origin-Mirror") || (m_headerInfo["mode"].toString() == "Origin-Duplicate"))
            m_headerInfo["right_temp"] = QString::number(l+m_tempOffset);
#ifdef DEBUG
        qDebug()<<"left_temp"<<l<<m_headerInfo.value("left_temp").toString();
        qDebug()<<"mtempOffset"<<m_tempOffset;
        qDebug()<<"right_temp"<<m_headerInfo.value("right_temp").toString();
#endif
    }
}

void XhGcodeFileParser::doParseByDeep()
{
    process_status = QByteArray("Parsing");
    // qDebug()<<"deep1";
    doParseByDirect();
    // qDebug()<<"deep2";
    parseWholeFile();
}

void XhGcodeFileParser::variableInit()
{
    m_lineParsed = 0;
    m_sourceGcodeLines->clear();
    m_lastToolHead = 0;
    m_tempOffset = 0;
    m_startLineIndex = 0;

    m_headerInfo["result"] = false;
    m_headerInfo["mode"] = "Unknown";
    m_headerInfo["offset"] = "0";
    m_headerInfo["left_temp"] = "0";
    m_headerInfo["right_temp"] = "0";
    m_headerInfo["bed_temp"] = "0";
}

void XhGcodeFileParser::loadFile()
{
    m_mutex->lock();
    QString inputFileName = m_inputFileName;
    m_mutex->unlock();

    QFile in(inputFileName);
    if (!in.open(QIODevice::ReadOnly))
        return;

    QTextStream textStream(&in);
    textStream.setCodec("UTF-8");
    while (true) {
        if (textStream.atEnd())
            break;
        m_sourceGcodeLines->append(textStream.readLine());
    }
    in.close();
}

void XhGcodeFileParser::loadFile(int LinesToLoad)
{
    m_mutex->lock();
    QString inputFileName = m_inputFileName;
    m_mutex->unlock();

    QFile in(inputFileName);
    if (!in.open(QIODevice::ReadOnly))
        return;

    QTextStream textStream(&in);
    textStream.setCodec("UTF-8");
    while (LinesToLoad--) {
        if (textStream.atEnd())
            break;
        m_sourceGcodeLines->append(textStream.readLine());
    }
    in.close();
}

void XhGcodeFileParser::getJlHeader()
{
    if(!m_sourceGcodeLines->at(0).startsWith(";JL-ParsedResult"))
        return;
    m_headerInfo["result"] = true;
    QString firstLine = m_sourceGcodeLines->at(0);
    QStringList options = firstLine.split(" ", QString::SkipEmptyParts);
    options.removeFirst();
    m_headerInfo["mode"] = options[0].split(":")[1];
    m_headerInfo["offset"] = options[1].split(":")[1];
    m_headerInfo["left_temp"] = options[2].split(":")[1];
    m_headerInfo["right_temp"] = options[3].split(":")[1];
    m_headerInfo["bed_temp"] = options[4].split(":")[1];
    m_startLineIndex = 1;

}

void XhGcodeFileParser::parseTop100Lines()
{
    int lineIndex = 0;
    while (lineIndex < 100) {
        QString tmpLine = m_sourceGcodeLines->at(m_lineParsed).trimmed();
        // qDebug()<<tmpLine;
        int curLineNumber = m_lineParsed;
        m_lineParsed++;
        if (tmpLine.startsWith(";"))
            continue;
        QString line_cut_comment = cutComment(tmpLine);
        parseStartLine(line_cut_comment, curLineNumber);
        parseTemp(line_cut_comment);
        parseToolHead(line_cut_comment);
        parseMode(line_cut_comment);
        lineIndex++;
    }
}

QString XhGcodeFileParser::cutComment(QString gcode)
{
    int commnent_start_index = 0;
    QString new_string;
    gcode = gcode.trimmed();
    commnent_start_index = gcode.indexOf(";",0) ;
    if(commnent_start_index == -1)
        new_string = gcode;
    else
        new_string = gcode.left(commnent_start_index);
    return new_string;
}

void XhGcodeFileParser::parseStartLine(QString &gcode, int lineNumber)
{
    if (m_startLineIndex == 0) {
        if (gcode.contains("Z") && (gcode.contains("G0") || gcode.contains("G1"))) {
            float zHeight = getSymbolValue("Z", gcode).toFloat();
            if (zHeight <= 0.3f)
                m_startLineIndex = lineNumber;
        }
    }
}

QString XhGcodeFileParser::getSymbolValue(QString symbol, QString string)
{
    bool charFound = false;
    QString strvalue = "";
    if (string.contains(symbol) == false)
        return strvalue;
    foreach(QChar tmpC, string) {
        if (charFound == true) {
            if(((tmpC >= '0') && (tmpC <= '9')) || (tmpC == '.') || (tmpC == '-') || (tmpC == '+'))
                strvalue.append(tmpC);
            else
                break;
            // if ((tmpC != ".") && (tmpC != "-") && (tmpC != "+")) {
            //     if (!tmpC.isNumber())
            //         break;
            //     strvalue.append(tmpC);
            // } else {
            //     strvalue.append(tmpC);
            // }
        } else if (tmpC == symbol){
            charFound = true;
        }
    }

    return strvalue;
}

void XhGcodeFileParser::parseTemp(QString &gcode)
{
    if ((gcode.contains("M104") || gcode.contains("M109")) && gcode.contains("S")) {
        QString tempValue = getSymbolValue("S", gcode);
        if (gcode.contains("T")) {
            int tIndex = gcode.indexOf("T") + 1;
            int nozzleIndex = QString("%1").arg(gcode.at(tIndex)).toInt();
            if (nozzleIndex == 0) {
                m_headerInfo["left_temp"] = tempValue;
            } else if (nozzleIndex == 1) {
                m_headerInfo["right_temp"] = tempValue;
            }
        } else {
            if (m_lastToolHead == 0) {
                m_headerInfo["left_temp"] = tempValue;
            }
            else if (m_lastToolHead == 1) {
                m_headerInfo["right_temp"] = tempValue;
            }
        }
    } else if ((gcode.contains("M140") || gcode.contains("M190")) && gcode.contains("S")) {
        QString tempValue = getSymbolValue("S", gcode);
        m_headerInfo["bed_temp"] = tempValue;
    }
}

void XhGcodeFileParser::parseToolHead(QString &gcode)
{
    if (gcode.startsWith("T"))
        m_lastToolHead = getSymbolValue("T",gcode).toInt();
}

void XhGcodeFileParser::parseMode(QString &gcode)
{
    if (gcode.contains("M605") && gcode.contains("S")) {
        auto mode = getSymbolValue("S", gcode);
        if (mode == "2") {
            m_headerInfo["mode"] = "Origin-Duplicate";
            m_tempOffset = getSymbolValue("R", gcode).toInt();
            m_headerInfo["offset"] = getSymbolValue("X", gcode).toFloat();
            m_origin_duplucate_found = true;
        } else if (mode == "3") {
            m_headerInfo["mode"] = "Origin-Mirror";
        } else if (mode == "1") {
            m_headerInfo["mode"] = "Mix";
        }
    }
}

void XhGcodeFileParser::parseWholeFile()
{
    if(m_headerInfo.value("mode") != "Unknown") {
        return;
    }
    float maxX = -999.0;
    float minX = 999.0;
    float lastX = 0.0;

    line_parsed = 0;
    for (int var=m_startLineIndex; var<m_sourceGcodeLines->size(); var++)
    {
        QString tmpLine = m_sourceGcodeLines->at(var);
        line_parsed = var;
        process_percent = (uint32_t)var * 1000 / (uint32_t)m_sourceGcodeLines->size();
        if (tmpLine.startsWith(";"))
            continue;
        if (parseMotionMode(tmpLine) == true)
            continue;
        float x = parseXValue(tmpLine);

        if (x != -999) {
            if (m_relativeMotion == false) {
                lastX = x;
            } else {
                lastX += x;
            }
            if (lastX > maxX) {
                maxX = lastX;
            } else if (lastX < minX) {
                minX = lastX;
            }
        }
    }
    process_percent = 1000;

    float xCenter, xSize;
    xSize = 300;
    if ((minX != 999) && (maxX != -999)) {
        xCenter = (maxX + minX) / 2.0f;
        xSize = maxX - minX;
        qDebug("Min:%0.2f Max:%0.2f", minX, maxX);
        qDebug("Size:%0.2f Center:%0.2f", xSize, xCenter);
    }

    if (xSize < 140.0f) {
        m_headerInfo["mode"] = "Mirror";
        m_headerInfo["offset"] = QString::number(75.0f - xCenter, 'f', 2);
    } else if (xSize < 145.0f) {
        m_headerInfo["mode"] = "Duplicate";
        m_headerInfo["offset"] = QString::number(75.0f - xCenter, 'f', 2);
    } else {
        m_headerInfo["mode"] = "Unsupport";
    }
}

bool XhGcodeFileParser::parseMotionMode(QString &gcode)
{
    if (gcode.contains("G91")) {
        m_relativeMotion = true;
    } else if (gcode.contains("G90")) {
        m_relativeMotion = false;
    } else {
        return false;
    }
    return true;
}

float XhGcodeFileParser::parseXValue(QString &gcode)
{
    float x = -999.0;
    if (gcode.contains("X") && (gcode.contains("G0") || gcode.contains("G1"))) {
        x = getSymbolValue("X", gcode).toFloat();
    }

    return x;
}

void XhGcodeFileParser::rewriteLocalFile()
{
    bool need_rewrite = false;
    QFile old_file(localPath + m_outputFileName);
    if(old_file.open(QIODevice::ReadOnly) == false)
    {
        need_rewrite = true;
    }
    else
    {
        QTextStream text_reader(&old_file);
        QString header_line = text_reader.readLine(0);
        old_file.close();
        if(header_line != header2StringLine())
        {
            qDebug()<<"Old" + header_line;
            qDebug()<<"New" + header2StringLine();
            need_rewrite = true;
        }
    }
    if(need_rewrite == true)
    {
        qDebug()<<"Rewrite new file";
        QFile new_file(localPath + "tmpfile.gcode");
        int retry = 2;
        do
        {
            if(new_file.open(QIODevice::WriteOnly | QIODevice::Truncate) == false)
                QFile::remove(localPath + "tmpfile.gcode");
            else
                break;
        }while(retry--);
        if(new_file.isOpen() == true)
        {
            process_status = QByteArray("Writing to local");
            QTextStream text_writer(&new_file);
            text_writer.setCodec("UTF-8");
            text_writer<<header2StringLine() << "\r\n";
            int total_line = m_sourceGcodeLines->size();
            for (int var=m_startLineIndex; var<total_line; var++)
            {
                text_writer << m_sourceGcodeLines->at(var) << "\r\n";
                process_percent = (uint32_t)var * 1000 / (uint32_t)total_line;
            }
            process_percent = 1000;
            new_file.close();
            QFile::remove(localPath + m_outputFileName);
            QFile::rename(localPath + "tmpfile.gcode", localPath + m_outputFileName);
        }
        else
        {
            qDebug()<<"Temp file create fail!";
        }
    }
}

void XhGcodeFileParser::writeNewFile()
{
    qDebug()<<"Write new file";
    QFile new_file(localPath + "tmpfile.gcode");
    int retry = 2;
    do
    {
        if(new_file.open(QIODevice::WriteOnly | QIODevice::Truncate) == false)
            QFile::remove(localPath + "tmpfile.gcode");
        else
            break;
    }while(retry--);
    if(new_file.isOpen() == true)
    {
        qDebug()<<"File Open Success";
        process_status = QByteArray("Writing to local");
        QTextStream text_writer(&new_file);
        text_writer.setCodec("UTF-8");
        text_writer<<header2StringLine() << "\r\n";
        int total_line = m_sourceGcodeLines->size();
        for (int var=m_startLineIndex; var<total_line; var++)
        {
            text_writer << m_sourceGcodeLines->at(var) << "\r\n";
            process_percent = var * 1000 / total_line;
        }
        process_percent = 1000;
        new_file.close();
        insertFileListRecord(m_outputFileName);
        QFile::remove(localPath + m_outputFileName);
        QFile::rename(localPath + "tmpfile.gcode", localPath + m_outputFileName);
    }
    else
    {
        qDebug()<<"Temp file create fail!";
    }
}

#if(0)
void XhGcodeFileParser::writeFile()
{
    process_percent = 0;
    process_status = QByteArray("Writing File");
    m_mutex->lock();
    QString outputFileName = m_outputFileName;
    m_mutex->unlock();

    QFile f(outputFileName);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    QTextStream out(&f);
    out.setCodec("UTF-8");
    out << header2StringLine() << "\r\n";
    int total_line = m_sourceGcodeLines->size();
    for (int var=m_startLineIndex; var<total_line; var++)
    {
        out << m_sourceGcodeLines->at(var) << "\r\n";
        process_percent = var * 1000 / total_line;
    }
    process_percent = 1000;
    f.close();
}
#endif

QString XhGcodeFileParser::header2StringLine()
{
    QString retval = ";JL-ParsedResult";
    retval = retval + " MoreOption:" + m_headerInfo["mode"].toString();
    retval = retval + " Offset:" + m_headerInfo["offset"].toString();
    retval = retval + " Left_temp:" + m_headerInfo["left_temp"].toString();
    retval = retval + " Right_temp:" + m_headerInfo["right_temp"].toString();
    retval = retval + " Bed_temp:" + m_headerInfo["bed_temp"].toString();

    return retval;
}

QVariantMap XhGcodeFileParser::parseQuickly(const QString inputFileName)
{
    m_inputFileName = inputFileName;
    variableInit();
    loadFile(2000);
    getJlHeader();
    if (m_headerInfo["result"] == false)
    {
        parseTop100Lines();
        int l  = m_headerInfo["left_temp"].toString().toInt();
        m_headerInfo["right_temp"] = QString::number(l+m_tempOffset);
    }
    // qDebug()<<m_headerInfo["mode"].toString();
    // qDebug()<<m_headerInfo["offset"].toInt();
    // qDebug()<<m_headerInfo["left_temp"].toString();
    // qDebug()<<m_headerInfo["right_temp"].toString();
    // qDebug()<<m_headerInfo["bed_temp"].toString();
    m_sourceGcodeLines->clear();
    return m_headerInfo;
}

void XhGcodeFileParser::clearRam()
{
    m_sourceGcodeLines->clear();
}

QByteArray XhGcodeFileParser::getParseStatus()
{
    return process_status;
}

int XhGcodeFileParser::getPercent()
{
    return process_percent;
}

void XhGcodeFileParser::syncFiles(QList<QString> FileList)
{
    QFileInfoList file_info_list;
    bool found;
    QDir *p_dir = new QDir(localPath);
    file_info_list = p_dir->entryInfoList();
    qDebug()<<"Start Sync";
    foreach(QFileInfo info, file_info_list)
    {
        found = false;
        foreach(QString file_name, FileList)
        {
            if(file_name == info.fileName())
            {
                found = true;
                break;
            }
        }
        if(found == false)
        {
            qDebug()<<"Remove: " << info.filePath();
            QFile::remove(info.filePath());
        }
    }
    delete p_dir;
    file_info_list.clear();
}

void XhGcodeFileParser::fileListRecordInit()
{
    qDebug()<<FileListRecordPath;

    QDir *pDir = new QDir(FileListRecordPath);
    if(pDir->exists() == false)
    {
        qDebug()<<"Create file record directory";
        pDir->mkdir(FileListRecordPath);
    }
    QList<QString> file_list = loadFileListRecord();
    syncFiles(file_list);
    file_list.clear();
    delete pDir;
}

void XhGcodeFileParser::writeFileList(QString FileName, QList<QString> List)
{
    QFile *pFile = new QFile(FileName);
    pFile->open(QIODevice::Truncate | QIODevice::WriteOnly);
    QTextStream in(pFile);
    in << "Start\n";
    foreach(QString line, List)
        in<<line+"\n";
    in << "End";
    pFile->close();
    delete pFile;
}

void XhGcodeFileParser::writeFileListRecord(QList<QString> FileList)
{
    writeFileList(FileListRecord, FileList);
    writeFileList(FileListRecord_BAK, FileList);
}

void XhGcodeFileParser::insertFileListRecord(QString Item)
{
    QList<QString> file_list = loadFileListRecord();
    file_list.insert(0, Item);
    writeFileListRecord(file_list);
    file_list.clear();
}

QList<QString> XhGcodeFileParser::loadFileListRecordContent(QString FileName)
{
    QList<QString> ret;
    QFile *pFile = new QFile(FileName);
    pFile->open(QIODevice::ReadOnly);
    QTextStream stream(pFile);
    QString new_line;
    do
    {
        new_line = stream.readLine(255);
        if(new_line != nullptr)
            ret.append(new_line);
    }while(new_line != nullptr);
    pFile->close();
    delete pFile;
    return ret;
}

void XhGcodeFileParser::checkFileList(QString FileName)
{
    QFile *pFile;
    // The file is unexisted
    if(QFile::exists(FileName) == false)
    {
        qDebug()<<"Create file: " << FileName;
        pFile = new QFile(FileName);
        pFile->open(QIODevice::ReadWrite);
        QTextStream out(pFile);
        out<<"Start\n";
        out<<"End";
        pFile->close();
        delete pFile;
    }
}

QList<QString> XhGcodeFileParser::loadFileListRecord()
{
    QList<QString> ret;
    checkFileList(FileListRecord);
    checkFileList(FileListRecord_BAK);

    // Load file list
    QList<QString> file_list = loadFileListRecordContent(FileListRecord);
    // Load file list backup
    QList<QString> file_list_backup = loadFileListRecordContent(FileListRecord_BAK);
    bool complete_0, complete_1;
    complete_0 = (file_list.at(0) == "Start") && (file_list.at(file_list.count() - 1) == "End");
    complete_1 = (file_list_backup.at(0) == "Start") && (file_list_backup.at(file_list.count() - 1) == "End");
    // The 2 files are complete
    if((complete_0 == true) && (complete_1 == true))
    {
        // These 2 files are different. So we recover the backup file.
        if(file_list != file_list_backup)
        {
            qDebug()<<"Recover file list backup file";
            QFile::remove(FileListRecord_BAK);
            QFile::copy(FileListRecord, FileListRecord_BAK);
        }
        ret = file_list;
    }
    // One of the file is incomplete
    else
    {
        // The file list is complete.This means the backup is incomplete.The situation is happened while writing the backup file.
        // So we need to recover the backup file
        if(complete_0 == true)
        {
            qDebug()<<"Recover file list backup file";
            QFile::exists(FileListRecord_BAK);
            QFile::remove(FileListRecord_BAK);
            QFile::copy(FileListRecord, FileListRecord_BAK);
            ret = file_list;
        }
        else
        {
            qDebug()<<"Recover file list file";
            QFile::exists(FileListRecord);
            QFile::remove(FileListRecord);
            QFile::copy(FileListRecord_BAK, FileListRecord);
            ret = file_list_backup;
        }
    }
    ret.removeAt(0);
    ret.removeAt(ret.count() - 1);

    return ret;
}
