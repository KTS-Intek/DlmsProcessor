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

    DLMSExchangeState lastExchangeState;

    bool verboseMode;


    //I need these to store DLSM short names to supported OBIS codes,
    //Gama meters do not use it
    //Landis+Gyr meters use it
    struct DLMSShortNames
    {
        QString enrgKey;
        quint16 shortname;
        DLMSShortNames() : shortname(0) {}
    };

    struct DLMSShortNamesParams
    {
        QMap<quint64, DLMSShortNames> obis2shortNames;
        QHash<QString,quint64> enrgKey2obis;
        DLMSShortNamesParams() {}
    };

    QHash<QString, DLMSShortNamesParams > hNi2obis2ShortNamesTotal;
    QHash<QString, DLMSShortNamesParams > hNi2obis2ShortNamesVoltage;
    QHash<QString, DLMSShortNamesParams > hNi2obis2ShortNamesLoadProfile;


    struct LastShortNamesParams
    {
        QString ni;
        DLMSShortNamesParams lastObis2shortNames;//it stores last NI short names, try to use it everywhere
        QList<quint16> lastShortNames2get;//do I really need it?
        LastShortNamesParams() {}
    } lastShortNames;

    bool isItTime2getShortNames2obisTotalFromVHsmart(const QVariantHash &hashConstData, QVariantHash &hashTmpData);//it updates the lastObis2shortNames, profile 140

    bool isItTime2getShortNames2obisVoltageFromVHsmart(const QVariantHash &hashConstData, QVariantHash &hashTmpData);//it updates the lastObis2shortNames, profile 140

    bool isItTime2getShortNames2obisLoadProfileFromVHsmart(const QVariantHash &hashConstData, QVariantHash &hashTmpData);//it updates the lastObis2shortNames, profile 140


    bool isItMarkedAsDoneSn2obis(const QVariantHash &hashTmpData);

    void markThisMeterAsDoneSn2obis(QVariantHash &hashTmpData);


    bool isItTime2getShortNames2obisTotalFromVH(const QVariantHash &hashConstData);//it updates the lastObis2shortNames, profile 140

    bool isItTime2getShortNames2obisTotal(const QString &ni);//it updates the lastObis2shortNames, profile 140


    bool isItTime2getShortNames2obisVoltageFromVH(const QVariantHash &hashConstData);//it updates the lastObis2shortNames, profile 140

    bool isItTime2getShortNames2obisVoltage(const QString &ni);//it updates the lastObis2shortNames, profile 140


    bool isItTime2getShortNames2obisLoadProfileFromVH(const QVariantHash &hashConstData);//it updates the lastObis2shortNames, profile 140

    bool isItTime2getShortNames2obisLoadProfile(const QString &ni);//it updates the lastObis2shortNames, profile 140


    bool isItTime2getShortNames2obisExt(const QString &ni, const QHash<QString, DLMSShortNamesParams > &h);//it updates the lastObis2shortNames, profile 140


    bool addShortName2obisCode(const quint16 &shortname, const quint64 &obiscode);//it uses ni from lastShortNames, and updates map and hash


    void swapParams(DLMSShortNamesParams &inOut, const DLMSShortNamesParams &in);

    void updateLastNiShortNamesTotal();

    void updateLastNiShortNamesVoltage();

    void updateLastNiShortNamesLoadProfile();

    void addDefaultReadingParams(QVariantHash &hashMessage);



    void resetHDLCglobalVariables();

    void setDlmsFuckingChecks(const QVariantHash &h);

    bool messageIsValid(const QByteArray &readArr, QVariantList &listMeterMesageVar, QList<QByteArray> &commandCodeH, const QByteArray &lastAddrH, quint8 &frameType, quint8 &errCode, const QByteArray lastSrcAddr = "");

    bool messageIsValidExt(DLMSExchangeState &lastExchangeState, const QByteArray &readArr, QVariantList &listMeterMesageVar, QList<QByteArray> &commandCodeH, const QByteArray &lastAddrH, quint8 &frameType, quint8 &errCode, const QByteArray lastSrcAddr = "");


    QByteArray getArrayHex(const QByteArray &readArr, const QByteArray &lastSrcAddr, const QByteArray &lastAddrH, bool &endOfRRframes, bool &need2useBuffer, quint8 &frameType);

    bool isCrcValid(const QByteArray &meterMessH, const QByteArray &arrHex, quint8 &errCode);

    bool isItShortDLMSBreak(const quint8 &frameType, const QByteArray &lastSrcAddr, const QByteArray &meterMessH);

    bool checkPreparyCache(QByteArray &meterMessH, quint8 &errCode, int &obisCounter, int &payloadLen, int &dataTypeLen, DLMSExchangeState &lastExchangeState, int &forcedDataTypeLen);

    QVariantList processCachedData(int &obisCounter, QByteArray &meterMessH, int &dataTypeLen, QList<QByteArray> &commandCodeH, bool &need2useBuffer, int &ob, QByteArray &topType, const int &forcedDataTypeLen);

    void topArrayChecks(const bool &hasByteA8, QByteArray &meterMessH, QByteArray &topType, QVariantList &listMeterMesageVar, bool &endOfRRframes, bool &need2useBuffer, int &obisCounter, int &ob);




    QByteArray crcCalcExt(const QByteArray &arrAddrHex, const quint8 &frameType, const quint8 &messageCounterRRR, const quint8 &messageCounterSSS, const QByteArray &arrMessage) ;

    QByteArray crcCalc(const QByteArray &destSN, const quint8 &frameType, const quint8 &messageCounterRRR, const quint8 &messageCounterSSS, const QByteArray &arrMessage) ;
    QByteArray crcCalc(const QVariantHash &hashConstData, const quint8 &frameType, const quint8 &messageCounterRRR, const quint8 &messageCounterSSS, const QByteArray &arrMessage) ;

    QByteArray crcCalcFrameI(const QVariantHash &hashConstData, const ObisList &obisList, const AttributeList &attributeList) ;

    QByteArray crcCalcFrameIarr(const QVariantHash &hashConstData, const QByteArray &arrMessageXtend) ;

    QByteArray crcCalcFrameRR(const QVariantHash &hashConstData) ;


    bool exitCozNAuth(const int &errCode, QVariantHash &hashTmpData);

    QVariantHash fullLoadProfileEmptyValsExt(const QVariantHash &hashConstData, const QVariantHash &hashTmpData, const quint32 &pwrIntrvl, const QStringList &list4meterEnrg);

    void preparyLoginedHashTmpData(QVariantHash &hashTmpData);

    void fullLogined(const QVariantList &meterMessVar, const quint8 &frameType, QVariantHash &hashTmpData);


signals:

};

#endif // DLMSPROCESSOR_H
