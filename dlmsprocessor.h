#ifndef DLMSPROCESSOR_H
#define DLMSPROCESSOR_H

#include <QObject>
#include <QDebug>

///[!] meter-plugin-shared
#include "shared/meterpluginhelper.h"

///[!] type-converter
#include "src/base/prettyvalues.h"
#include "src/base/convertatype.h"


#include "dlmstypes.h"
#include "global_dlms_defines.h"

class DlmsProcessor : public QObject
{
    Q_OBJECT
public:
    explicit DlmsProcessor(QObject *parent = nullptr);

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


        DLMSExchangeState() : lastDataTypeLen(0), lastObisCounter(0), messageCounterRRR(0), messageCounterSSS(0), relayAtttr(0) {}
    } lastExchangeState;

    bool verboseMode;


    void addDefaultReadingParams(QVariantHash &hashMessage);


    void resetHDLCglobalVariables();

    bool messageIsValid(const QByteArray &readArr, QVariantList &listMeterMesageVar, QList<QByteArray> &commandCodeH, const QByteArray &lastAddrH, quint8 &frameType, quint8 &errCode, const QByteArray lastSrcAddr = "");

    QByteArray getArrayHex(const QByteArray &readArr, const QByteArray &lastSrcAddr, const QByteArray &lastAddrH, bool &endOfRRframes, bool &need2useBuffer, quint8 &frameType);

    bool isCrcValid(const QByteArray &meterMessH, const QByteArray &arrHex, quint8 &errCode);

    bool isItShortDLMSBreak(const quint8 &frameType, const QByteArray &lastSrcAddr, const QByteArray &meterMessH);

    bool checkPreparyCache(QByteArray &meterMessH, quint8 &errCode, int &obisCounter, int &payloadLen, int &dataTypeLen, const bool &lastMeterIsShortDlms);

    QVariantList processCachedData(int &obisCounter, QByteArray &meterMessH, int &dataTypeLen, QList<QByteArray> &commandCodeH, bool &need2useBuffer, int &ob, QByteArray &topType);

    void topArrayChecks(const bool &hasByteA8, QByteArray &meterMessH, QByteArray &topType, QVariantList &listMeterMesageVar, bool &endOfRRframes, bool &need2useBuffer, int &obisCounter, int &ob);



    QByteArray crcCalc(const QByteArray &destSN, const quint8 &frameType, const quint8 &messCounterRRR, const quint8 &messCounterSSS, const QByteArray &arrMess) ;
    QByteArray crcCalc(const QVariantHash &hashConstData, const quint8 &frameType, const quint8 &messCounterRRR, const quint8 &messCounterSSS, const QByteArray &arrMess) ;

    QByteArray crcCalcFrameI(const QVariantHash &hashConstData, const ObisList &obisList, const AttributeList &attributeList) ;

    QByteArray crcCalcFrameIarr(const QVariantHash &hashConstData, const QByteArray &arrMessXtend) ;

    QByteArray crcCalcFrameRR(const QVariantHash &hashConstData) ;


    bool exitCozNAuth(const int &errCode, QVariantHash &hashTmpData);

    QVariantHash fullPowerEmptyValsExt(const QVariantHash &hashConstData, const QVariantHash &hashTmpData, const quint32 &pwrIntrvl, const QStringList &list4meterEnrg);




signals:

};

#endif // DLMSPROCESSOR_H
