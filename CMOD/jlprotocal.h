#ifndef JLPROTOCAL_H
#define JLPROTOCAL_H

#include <QByteArray>

class JLProtocal
{
public:
    JLProtocal();
    JLProtocal(uint8_t);
    QByteArray setupPackage(QByteArray);
    QByteArray parseData(QByteArray, uint32_t *);

private:
    uint8_t header[2];
    uint8_t version;
    uint8_t attribute;
    uint8_t command_len;
};

#endif // PROTOCAL_H
