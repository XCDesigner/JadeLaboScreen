#include "jlprotocal.h"

JLProtocal::JLProtocal() {
    JLProtocal(0x30);
}

JLProtocal::JLProtocal(uint8_t Version) {
    header[0] = 'J';
    header[1] = 'F';
    version = Version;
    attribute = 0xe0;
}

QByteArray JLProtocal::setupPackage(QByteArray Datas) {
    QByteArray ret;
    ret.append(1, header[0]);
    ret.append(1, header[1]);
    ret.append(1, version);
    ret.append(1, (uint8_t)Datas.size());
    ret.append(1, (uint8_t)(Datas.size() >> 8));
    if(version == 0x31) {
        ret.append(1, (uint8_t)(Datas.size() >> 16));
        ret.append(1, (uint8_t)(Datas.size() >> 24));
    }
    if(version == 0x30)
        ret.append(1, (uint8_t)(ret.at(3) ^ ret.at(4)));
    else
        ret.append(1, (uint8_t)(ret.at(3) ^ ret.at(4) ^ ret.at(5) ^ ret.at(6)));
    ret.append(1, (uint8_t)(0));
    uint32_t checksum;
    checksum = 0;
    for(int i=0;i<Datas.size();i++)
        checksum += (uint8_t)Datas.at(i);
    ret.append(1, (uint8_t)checksum);
    ret.append(1, (uint8_t)(checksum >> 8));
    ret.append(Datas);
    return ret;
}

QByteArray JLProtocal::parseDataV30(QByteArray SourceData, uint32_t *DataRead)
{
    uint32_t data_read = 0;
    QByteArray ret_datas;

    while(SourceData.size() > 0) {
        if(SourceData.at(0) != header[0])
        {
            SourceData.remove(0, 1);
            data_read = data_read + 1;
            qDebug()<<"P0";
            continue;
        }
        if(SourceData.size() > 1)
        {
            if(SourceData.at(1) == header[1])
            {
                break;
            }
            else
            {
                qDebug()<<"P1";
                SourceData.remove(0, 2);
                data_read = data_read + 2;
            }
        }
        else
        {
            break;
        }
    }

    while(SourceData.size() > 10) {
        if(SourceData.at(0) != header[0])
        {
            data_read++;
            SourceData.remove(0, 1);
            qDebug()<<"P2";
            continue;
        }
        if(SourceData.at(1) != header[1])
        {
            data_read = data_read + 2;
            SourceData.remove(0, 2);
            qDebug()<<"P3";
            continue;
        }
        uint32_t command_len = 0;
        uint8_t len_checksum;

        command_len = ((uint8_t)SourceData.at(4) << 8) | (uint8_t)SourceData.at(3);
        len_checksum = SourceData.at(4) ^ SourceData.at(3);

        if(len_checksum != (uint8_t)SourceData.at(5))
        {
            data_read = data_read + 2;
            SourceData.remove(0, 2);
            qDebug()<<"P4";
            continue;
        }

        // Data len exceed 1K bytes. Error package
        if(command_len >1024) {
            data_read = data_read + 2;
            SourceData.remove(0, 2);
            qDebug()<<"P5";
            continue;
        }

        // No enough data
        if((int)(command_len + 9) > SourceData.size()) {
            break;
        }

        // Attribute pass

        // Data checksum
        uint32_t checksum, cal_checksum;
        checksum = ((uint8_t)SourceData.at(8) << 8) | (uint8_t)SourceData.at(7);
        ret_datas = SourceData.mid(0, command_len + 9);
        cal_checksum = 0;
        for(int i=9;i<ret_datas.size(); i++)
            cal_checksum += (uint8_t)ret_datas.at(i);
        cal_checksum = cal_checksum & 0xffff;
        if(cal_checksum != checksum) {
            data_read = data_read + 2;
            SourceData.remove(0, 2);
            ret_datas.clear();
            qDebug()<<cal_checksum << checksum << "P6";
            continue;
        }

        data_read += command_len + 9;
        break;
    }

    *DataRead = data_read;
    return ret_datas;
}

QByteArray JLProtocal::parseDataV31(QByteArray SourceData, uint32_t *DataRead)
{
    uint32_t data_read = 0;
    QByteArray ret_datas;

    while(SourceData.size() > 0) {
        if(SourceData.at(0) != header[0])
        {
            SourceData.remove(0, 1);
            data_read = data_read + 1;
            continue;
        }
        if(SourceData.size() > 1)
        {
            if(SourceData.at(1) == header[1])
            {
                break;
            }
            else
            {
                SourceData.remove(0, 2);
                data_read = data_read + 2;
            }
        }
        else
        {
            break;
        }
    }

    while(SourceData.size() > 12) {
        if(SourceData.at(0) != header[0])
        {
            data_read++;
            SourceData.remove(0, 1);
            continue;
        }
        if(SourceData.at(1) != header[1])
        {
            data_read = data_read + 2;
            SourceData.remove(0, 2);
            continue;
        }
        uint32_t command_len = 0;
        uint8_t len_checksum;

        command_len = ((uint8_t)SourceData.at(6) << 24) | ((uint8_t)SourceData.at(5) << 16) | ((uint8_t)SourceData.at(4) << 8) | (uint8_t)SourceData.at(3);
        len_checksum = SourceData.at(6) ^ SourceData.at(5) ^ SourceData.at(4) ^ SourceData.at(3);

        if(len_checksum != (uint8_t)SourceData.at(7))
        {
            data_read = data_read + 2;
            SourceData.remove(0, 2);
            continue;
        }

        // No enough data
        if((int)(command_len + 11) > SourceData.size()) {
            break;
        }

        // Attribute pass

        // Data checksum
        uint32_t checksum, cal_checksum;
        checksum = ((uint8_t)SourceData.at(10) << 8) | (uint8_t)SourceData.at(9);
        ret_datas = SourceData.mid(0, command_len + 11);
        cal_checksum = 0;
        for(int i=11;i<ret_datas.size(); i++)
            cal_checksum += (uint8_t)ret_datas.at(i);
        cal_checksum = cal_checksum & 0xffff;
        if(cal_checksum != checksum) {
            data_read = data_read + 2;
            SourceData.remove(0, 2);
            ret_datas.clear();
            continue;
        }

        data_read += command_len + 11;
        break;
    }

    *DataRead = data_read;
    return ret_datas;
}

QByteArray JLProtocal::parseData(QByteArray SourceData, uint32_t *DataRead) {
    if(version == 0x30)
        return parseDataV30(SourceData, DataRead);
    else if(version == 0x31)
        return parseDataV31(SourceData, DataRead);
    else
        return QByteArray();
}
