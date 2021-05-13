#ifndef DLMSHELPER_H
#define DLMSHELPER_H


///[!] type-converter
#include "src/base/convertatype.h"

#include <QDebug>



#include "dlmstypes.h"
#include "global_dlms_defines.h"
#include "ucmetereventcodes.h"
#include "definedpollcodes.h"

class DlmsHelper
{
public:
    static int datatype2len(const quint16 &dataType);

    static QVariant datatype2normal(const quint16 &dataType, const QByteArray &arrh, const bool &verboseMode);

    static QDateTime dtFromArr(const QByteArray &arrh, const bool &asLocalTime);

    static QDateTime dtWhen25hour(const QDateTime &indt, const QDateTime &dtpwrCorr25hour, const bool &isDstNow);


    static QDateTime arrh2dataTime(const QByteArray &arrh);

    static QDateTime arrh2dataTimeExt(const QByteArray &arrh, const bool &asLocalTime, const QDateTime &dtpwrCorr25hour, const bool &ignoredst, const bool &isPwr4snDlms);

    static QString arrh2dataTimeDstSett(const QByteArray &arrh, const int &deviation, const bool &deviationSettIsValid);


    static QVariantMap arr2map(QByteArray arrh, int addLen, bool &isNotAll, quint32 &arrlen, const bool &verboseMode);

    static QVariantMap strct2map(QByteArray arrh, int addLen, bool &isNotAll, quint32 &arrlen, const bool &verboseMode);


    static void moveCache2hash(const QVariantHash &h, const QList<QByteArray> &commandCodeH, QVariantHash &hashTmpData, quint16 &step, int &error_counter, const bool &verboseMode, LastErrStruct &lastErrS);


    static QByteArray arrMessWriteSN(ObisList &lastObisList, const quint64 &obis, const quint16 &attr, const QByteArray &arrh);

    static QByteArray arrMessWrite(ObisList &lastObisList, const quint64 &obis, const quint16 &attr, const QByteArray &arrh);

    static QByteArray arrMessXtend(ObisList &lastObisList, const ObisList &obisList, const AttributeList &attributeList, const bool &lastIsShortDlms);//Get.request

    static QByteArray arrMessXtendSN(ObisList &lastObisList, const ObisList &obisList, const AttributeList &attributeList);//Get.request


    static QByteArray obis2classId(const quint64 &obis);
    static quint16 obis2classIdsubObis(quint64 obis);



    static QByteArray dt2arr(const QDateTime &currDateTime, const QByteArray rightarr = "FF FF FF FF");

    static QVariantMap arrStructure2map(const QByteArray &arr);


    static QString calcMeterAddr(const quint64 &meterSn, const int &addVal);

    static void addEmptyIval2listDate(const QVariantHash &hashConstData, const QVariantHash &hashTmpData, const QVariantMap &mapPos2obis, const QStringList &list4pllEnrg, QVariantHash &hash, QStringList &listDate);


    static QDateTime fixDstShift(const QDateTime &indt, const bool &isDstNow);
    static QDateTime fixDstShiftSmart25hour(const QDateTime &indt);




};

#endif // DLMSHELPER_H
