#ifndef DLMSTYPES_H
#define DLMSTYPES_H

#include <QList>
#include <QByteArray>
#include <QString>

typedef QList<quint64> ObisList;
typedef QList<quint16> AttributeList;
typedef QList<QByteArray> ArrayHexList;

struct LastErrStruct{
    QString lastErrorStr;
    QString lastWarning;
};

struct DLMSExchangeState
{
    LastErrStruct lastErrS;
    QByteArray lastHiLoHex;
//    QString lastErrorStr, lastWarning;

    QByteArray lastMeterH;
    int lastDataTypeLen;
    int lastObisCounter;

    quint8 messageCounterRRR, messageCounterSSS;

    ObisList lastObisList;

    quint8 relayAtttr;

    bool lastMeterIsShortDlms;


    QByteArray sourceAddressH;//dlsm source address, must be shifted

 //When obis code is added for some reason in answers , Old G3B.144 2018
    QByteArray dlmsFuckingChecksRemoveTypePrefixH;
    int dlmsFuckingChecksRemoveLen; //remove from one frame
    int dlmsFuckingChecksObisCounterPos; //byte_number x 2
    int dlmsFuckingChecksForceDataLen; //use this dataLen instead
    bool dlmsFuckingIgnoreEndOfRRframes; //to receive data stream using fukcing method
    QByteArray dlmsFuckingLastReceivedArr; //last received arr in fukcing mode
    bool dlmsFuckingHasMoreData; //when fukcing mode has more data (fucking stream mode)
    QByteArray dlmsFukcingForcedDataPrefixH; //when to decode fucking data in a normal mode a prefix is requred, when stream mode - it is added only once


    DLMSExchangeState() : lastDataTypeLen(0), lastObisCounter(0), messageCounterRRR(0), messageCounterSSS(0),
        relayAtttr(0), sourceAddressH("03"),
        dlmsFuckingChecksRemoveLen(0), dlmsFuckingChecksObisCounterPos(0), dlmsFuckingChecksForceDataLen(0),
        dlmsFuckingIgnoreEndOfRRframes(false), dlmsFuckingHasMoreData(false) {}
};

#endif // DLMSTYPES_H
