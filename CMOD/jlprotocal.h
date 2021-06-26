#ifndef JLPROTOCAL_H
#define JLPROTOCAL_H

#include <QByteArray>
#include <QDebug>
class JLProtocal
{
public:
    JLProtocal();
    JLProtocal(uint8_t);
    QByteArray setupPackage(QByteArray &);
    QByteArray parseData(QByteArray, uint32_t *);

private:
    QByteArray parseDataV30(QByteArray &SourceData, uint32_t *DataRead);
    QByteArray parseDataV31(QByteArray &SourceData, uint32_t *DataRead);

private:
    uint8_t header[2];
    uint8_t version;
    uint8_t attribute;
};

#endif // PROTOCAL_H
