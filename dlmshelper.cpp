#include "dlmshelper.h"

///[!] meter-plugin-shared
#include "shared/meterpluginhelper.h"

//-----------------------------------------------------------------------------------------

int DlmsHelper::datatype2len(const quint16 &dataType)
{
    int r = 0;
    switch(dataType){
    case DLMS_DATA_TYPE_NULL_DATA       : r = 0; break;
    case DLMS_DATA_TYPE_BOOLEAN         : r = 1; break;
//    case DLMS_DATA_TYPE_BIT_STRING      : break;
    case DLMS_DATA_TYPE_DOUBLE_LONG     :
    case DLMS_DATA_TYPE_DOUBLE_LONG_UNS : r = 4; break;
    case DLMS_DATA_TYPE_INTEGER         : r = 1; break;
    case DLMS_DATA_TYPE_LONG            : r = 2; break;
    case DLMS_DATA_TYPE_UNSIGNED        : r = 1; break;
    case DLMS_DATA_TYPE_LONG_UNSIGNED   : r = 2; break;
    case DLMS_DATA_TYPE_LONG64          : r = 8; break;
    case DLMS_DATA_TYPE_LONG64_UNSIGNED : r = 8; break;
    case DLMS_DATA_TYPE_FLOAT32         : r = 4; break;
    case DLMS_DATA_TYPE_FLOAT64         : r = 8; break;
    case DLMS_DATA_TYPE_ENUM            : r = 1; break;

    case DLMS_DATA_TYPE_EMPTY_LGZ_SN   : r = 0; break;

    case DLMS_DATA_FUCKING_UNKDATA      : r = 0; break;
    case DLMS_DATA_FUCKING_UNKDATA_2    : r = 0; break;

    case DLMS_DATA_RELAY_FCKN_OK        : r = 0; break;
//    case DLMS_DATA_TYPE_STRUCTURE       : r = 5; break;

    default:{
//        qDebug() << "datatype2len=" << dataType ;
//        if(verboseMode)
//            qDebug() << "unknown type ";
        r = -1;
        break;}
    }

    return r;
}

//-----------------------------------------------------------------------------------------

QVariant DlmsHelper::datatype2normal(const quint16 &dataType, const QByteArray &arrh, const bool &verboseMode)
{


        //#define DLMS_DATA_TYPE_NULL_DATA        0x0
        //#define DLMS_DATA_TYPE_BOOLEAN          0x3 //TRUE OR FALSE
        //#define DLMS_DATA_TYPE_BIT_STRING       0x4 //An ordered sequence of boolean values
        //#define DLMS_DATA_TYPE_DOUBLE_LONG      0x5 //int32 -2 147 483 648...2 147 483 647
        //#define DLMS_DATA_TYPE_DOUBLE_LONG_UNS  0x6 //uint32 0...4 294 967 295
        //#define DLMS_DATA_TYPE_OCTET_STRING     0x9 //An ordered sequence of octets (8 bit bytes)
        //#define DLMS_DATA_TYPE_VISIBLE_STRING   0x0A //An ordered sequence of ASCII characters
        //#define DLMS_DATA_TYPE_UTF_STRING       0x0C //An ordered sequence of characters encoded as UTF-8
        //#define DLMS_DATA_TYPE_BCD              0x0D //binary coded decimal
        //#define DLMS_DATA_TYPE_INTEGER          0x0F //int8
        //#define DLMS_DATA_TYPE_LONG             0x10 //int16
        //#define DLMS_DATA_TYPE_UNSIGNED         0x11 //uint8
        //#define DLMS_DATA_TYPE_LONG_UNSIGNED    0x12 //uint16
        //#define DLMS_DATA_TYPE_LONG64           0x14 //int64
        //#define DLMS_DATA_TYPE_LONG64_UNSIGNED  0x15 //uint64
        //#define DLMS_DATA_TYPE_ENUM             0x16 //enum 0...255
        //#define DLMS_DATA_TYPE_FLOAT32          0x17 //OCTET STRING (SIZE(4))
        //#define DLMS_DATA_TYPE_FLOAT64          0x18 //OCTET STRING (SIZE(8))
        //#define DLMS_DATA_TYPE_DATE_TIME        0x19 //OCTET STRING (SIZE(12))
        //#define DLMS_DATA_TYPE_DATE             0x1A //OCTET STRING (SIZE(5))
        //#define DLMS_DATA_TYPE_TIME             0x1B //OCTET STRING (SIZE(4))
        //#define DLMS_DATA_TYPE_ARRAY            0x01 //???
        //#define DLMS_DATA_TYPE_STRUCTURE        0x02
        //#define DLMS_DATA_TYPE_COMPACT_ARRAY    0x13

            QVariant r;
            bool ok = true;
            QByteArray arr = QByteArray::fromHex(arrh);

            switch(dataType){ //toUInt перевожу і знакові бо інакше з 16-кової системи не конвертується, мінус отримую шляхом (qint32)
            case DLMS_DATA_TYPE_NULL_DATA       : r = arr                       ; break;
            case DLMS_DATA_TYPE_BOOLEAN         : r = (arrh.toUInt(0,16) != 0)        ; break;
        //    case DLMS_DATA_TYPE_BIT_STRING      : break;
            case DLMS_DATA_TYPE_DOUBLE_LONG     : r = (qint32)arrh.toUInt(&ok, 16)    ; break;
            case DLMS_DATA_TYPE_DOUBLE_LONG_UNS : r = (quint32)arrh.toUInt(&ok, 16)  ; break;
            case DLMS_DATA_TYPE_OCTET_STRING    : r = arr                       ; break;
            case DLMS_DATA_TYPE_VISIBLE_STRING  : r = QString(arr)              ; break;
            case DLMS_DATA_TYPE_UTF_STRING      : r = arr                       ; break;
            case DLMS_DATA_TYPE_BCD             : r = arrh.toULongLong(&ok, 16)     ; break;
            case DLMS_DATA_TYPE_INTEGER         : r = (qint8)arrh.toUShort(&ok, 16)   ; break;
            case DLMS_DATA_TYPE_LONG            : r = (qint16)arrh.toUShort(&ok, 16)  ; break;
            case DLMS_DATA_TYPE_UNSIGNED        : r = (quint8)arrh.toUShort(&ok, 16) ; break;
            case DLMS_DATA_TYPE_LONG_UNSIGNED   : r = (quint16)arrh.toUShort(&ok, 16); break;
            case DLMS_DATA_TYPE_LONG64          : r = (qint64)arrh.toULongLong(&ok, 16); break;
            case DLMS_DATA_TYPE_LONG64_UNSIGNED : r = (quint64)arrh.toULongLong(&ok, 16); break;
        //    case DLMS_DATA_TYPE_ENUM            : r = arrEnum2map(arr)          ; break; //????
            case DLMS_DATA_TYPE_FLOAT32         : r = ConvertAtype::hexstr2float(arrh, ok); break;
            case DLMS_DATA_TYPE_FLOAT64         : r = ConvertAtype::hexstr2double(arrh, ok); break;
            case DLMS_DATA_TYPE_DATE_TIME       : r = arrh2dataTime(arrh)       ; break;
            case DLMS_DATA_TYPE_DATE            : r = QDate(arrh.left(4  ).toUInt(0,16), arrh.mid( 4,2).toUInt(0,16), arrh.mid( 6,2).toUInt(0,16)); break;
            case DLMS_DATA_TYPE_TIME            : r = QTime(arrh.mid( 0,2).toUInt(0,16), arrh.mid( 2,2).toUInt(0,16), arrh.mid( 4,2).toUInt(0,16)); break;
        //    case DLMS_DATA_TYPE_ARRAY           : r = arrh.toUpper()            ; break;
        //    case DLMS_DATA_TYPE_STRUCTURE       : r = arrStructure2map(arr)     ; break; //02 0F FF 16 1E
        //    case DLMS_DATA_TYPE_COMPACT_ARRAY   : break;

            case DLMS_DATA_FUCKING_UNKDATA_2:
            case DLMS_DATA_FUCKING_UNKDATA:
            case DLMS_DATA_TYPE_EMPTY_LGZ_SN:
                r = dataType;
                break;




            default:{
                if(verboseMode)
                    qDebug() << "datatype2normal=" << dataType << arrh;
                r = arr;
                if(verboseMode)
                    qDebug() << "unknown type " << arrh << dataType << r;
                break;}
            }
            if(!ok){
                if(verboseMode)
                qDebug() << "datatype2normal bad conversion " << r << arrh << ok << dataType;
                r = QVariant();
            }
            return r;


}

//-----------------------------------------------------------------------------------------

QDateTime DlmsHelper::dtFromArr(const QByteArray &arrh, const bool &asLocalTime)
{
    //07 E1 06 0F 04 12 09 1C 00 00 00  dt
    const QDateTime dt = QDateTime(QDate(arrh.left(4  ).toUInt(0,16), arrh.mid( 4,2).toUInt(0,16), arrh.mid( 6,2).toUInt(0,16)),
                     QTime(arrh.mid(10,2).toUInt(0,16), arrh.mid(12,2).toUInt(0,16), arrh.mid(14,2).toUInt(0,16)),
                     asLocalTime ? Qt::LocalTime : Qt::UTC);

    return dt;
}

//-----------------------------------------------------------------------------------------

QDateTime DlmsHelper::dtWhen25hour(const QDateTime &indt, const QDateTime &dtpwrCorr25hour, const bool &isDstNow)
{
    QDateTime dt = indt.toLocalTime();
    const int offset = dt.offsetFromUtc() - dtpwrCorr25hour.toLocalTime().offsetFromUtc();


    if(!dt.isDaylightTime() && dt.addSecs(offset - 10).isDaylightTime() && dtpwrCorr25hour.toLocalTime().isDaylightTime()){

        dt = dt.addSecs(offset);
    }else{
        if(dt.isDaylightTime() != isDstNow){

            QDateTime d = dt;
            d.setDate(QDate(d.date().year(), isDstNow ? 7 : 1, 1));

            const int utcOffset = d.offsetFromUtc();

            if(dt.offsetFromUtc() != utcOffset){
                dt.setOffsetFromUtc(utcOffset);
            }


        }
    }

    return dt;
}

//-----------------------------------------------------------------------------------------

QDateTime DlmsHelper::arrh2dataTime(const QByteArray &arrh)
{
    // const QByteArray &arrh, const bool &verboseMode, const bool asLocalTime = true, const QDateTime dtpwrCorr25hour = QDateTime(), const bool ignoredst = false);
    //, const QDateTime dtpwrCorr25hour = QDateTime(), const bool ignoredst = false
    return arrh2dataTimeExt(arrh, true, QDateTime(), false, false);
}

//-----------------------------------------------------------------------------------------

QDateTime DlmsHelper::arrh2dataTimeExt(const QByteArray &arrh, const bool &asLocalTime, const QDateTime &dtpwrCorr25hour, const bool &ignoredst, const bool &isPwr4snDlms)
{
    QDateTime dt = dtFromArr(arrh, asLocalTime);

//    07e4 09 09  2020 Sep 9
//    03 Wed
//    0b 00 00 11:00:00
//    ff - hundredths (for time)
//    80 - deviation highbyte
//    00 - deviation lowbyte
//    00 - clock status, 0xFF not specified,

//     deviation range -720...+720 in minutes of local time to UTC, 0x8000 = not specified

    const QBitArray bitArr = ConvertAtype::byteArrayToBitArray(QByteArray::fromHex(arrh.mid(22,2)));



    const bool ignoreClockStatuses = (arrh.mid(22,2).toUpper() == "FF" || isPwr4snDlms);// || arrh.mid(18, 4) == "8000");

    //isPwr4snDlms - dt is processed in the fullPower method

//    QBitArray bitArr = ConvertAtype::byteArrayToBitArray(QByteArray::fromHex(arrh.mid(22,2)));
//    if(asLocalTime && arrh.mid(22,2).toUpper() != "FF" && bitArr.size() == 8){

    if(asLocalTime && !ignoreClockStatuses && bitArr.size() == 8){//arrh.mid(22,2).toUpper() = "FF" not specified
        bool isDstNow = bitArr.at(7);
        //I've got problems with short dlms because of this bit,
        //those fucking meters tell that time is not in DST, but time must be in DST

        if(!dt.isValid()){
            QDateTime dtutc = dtFromArr(arrh, false);

            if(dtutc.isValid()){


                //23 hour  2:59:59 -> 4:00:00 , meter 3:00:00 -> 4:00:01
                //25 hour  3:59:59 -> 3:00:00 , meter 4:00:00 -> 3:00:01
 //               QString strtime = dtutc.addSecs(-7200).toString();// oLocalTime().addSecs(10);
                dtutc = dtutc.addSecs(-10);

                dt = QDateTime(dtutc.date(), dtutc.time()).addSecs(10);

 //               dt = dt.addSecs(10);
 //               qDebug() << "arrh2dataTime= dtutc " << dt.toString("yyyy-MM-dd hh:mm:ss") << dt.offsetFromUtc() << dtutc.toString("yyyy-MM-dd hh:mm:ss") << dtutc.offsetFromUtc();

                if(dt.isValid() && MeterPluginHelper::has23hoursInDay(dt) )
                    return dt;
            }
        }

        //4:00:00 = 3:00:00 - при переході з ЛЧ елгама переходить після 4:00:00 на 3:00:01
        if(MeterPluginHelper::has25hoursInDay(dt)){

            return dtWhen25hour(dt, dtpwrCorr25hour, isDstNow);


 //           if(dt.toString("mmss") == "0000" && !dt.isDaylightTime() && !isDstNow && dt.addSecs((-1) * 3600).isDaylightTime()) {//у мене четверта година вважається нормальним часом
 //               dt = dt.addSecs((-1) * 3600);
 //           }
        }
        if(dt.isDaylightTime() != isDstNow && !ignoredst){

            //Gama G3B Sn meters need it

            dt = fixDstShift(dt, isDstNow);




        }
    }
    return dt;
}

//-----------------------------------------------------------------------------------------

QString DlmsHelper::arrh2dataTimeDstSett(const QByteArray &arrh, const int &deviation, const bool &deviationSettIsValid)
{
    //    FF FF - year
    //    03 - month
    //    FE - day of month
    //    07 - DoW
    //    03 - hour
    //    00 - second
    //    00 00 80 00 00
        int year = arrh.left(4).toInt(0,16);
        if(year == 0xFFFF)
            year = QDate::currentDate().year();

        int offset ;
        if(deviationSettIsValid){
            offset = deviation/60;//deviation in minutes
            if(deviation > 0 && offset < 1)
                offset = 1;
        }else{
            offset = qAbs( QDateTime(QDate(year, 1, 1), QTime(0,0,0,0) ).offsetFromUtc() -  QDateTime(QDate(year, 7, 1), QTime(0,0,0,0) ).offsetFromUtc());
        }

        QString s = QString("%1,%2,%3,%4")
                    .arg(arrh.mid( 4,2).toInt(0,16))
                    .arg(arrh.mid( 8,2).toInt(0,16))
                    .arg(arrh.mid(10,2).toInt(0,16))
                    .arg(offset);

        return s;
}

//-----------------------------------------------------------------------------------------

QVariantMap DlmsHelper::arr2map(QByteArray arrh, int addLen, bool &isNotAll, quint32 &arrlen, const bool &verboseMode, const int &forcedDataTypeLen)
{
    //array 2 map

    //len data
    arrlen = 0;
    const int arrsize = arrh.mid(0,2 + addLen).toUInt(0, 16);
    arrh = arrh.mid(2 + addLen);
    QVariantMap m;

    int dataTypeLen = 2;
    if(forcedDataTypeLen > 0)
        dataTypeLen = forcedDataTypeLen;

    for(int i = 0; i < arrsize; i++){

        const quint16 datatype = arrh.left(dataTypeLen).toUInt(0, 16);
        quint32 len = arrh.mid(dataTypeLen,2 ).toUInt(0, 16);

        addLen = 0;
        if(len > 0x80 && len < 0x84){
            addLen = ((int)len - 0x80) * 2;
            len = arrh.mid(dataTypeLen + 2, addLen).toUInt(0, 16);
        }


        QVariant readyval;
        bool useReadyVal = false;

        int lenFromLine = 2;
        int altLen = datatype2len(datatype);
        if(altLen >= 0){
            len = (quint8)altLen;
            lenFromLine = 0;
        }else{
            if(datatype == DLMS_DATA_TYPE_ARRAY){
//                need2useBuffer = true;
                useReadyVal = true;
                readyval = arr2map(arrh.mid(dataTypeLen), addLen, isNotAll, len, verboseMode, forcedDataTypeLen);
            }else{
                if(datatype == DLMS_DATA_TYPE_STRUCTURE){//toVariantList
                    useReadyVal = true;
                    readyval = strct2map(arrh.mid(dataTypeLen), addLen, isNotAll, len, verboseMode, forcedDataTypeLen);
                }
            }
        }
        if(isNotAll)
            break;

        if(useReadyVal){
            m.insert(QString::number(i), readyval);

        }else{
            const QByteArray a = arrh.mid(dataTypeLen + lenFromLine, len * 2);
            if((quint32)a.length() != (len * 2)){
                if(verboseMode) qDebug() << "err parse data data.len() " << (int)datatype << (int)len << dataTypeLen << arrh.left(10) << a;

                break;
            }
            //        commandCodeH.append(meterMessH.left(dataTypeLen + lenFromLine + len * 2));

            m.insert(QString::number(i), datatype2normal(datatype, a, verboseMode));
        }

        arrh = arrh.mid(dataTypeLen + addLen + lenFromLine + len * 2);
        arrlen += ((dataTypeLen + lenFromLine + len * 2)/2);
        if(arrh.isEmpty())
            break;

    }
    if(m.size() != arrsize)
        isNotAll = true;
    return m;
}

//-----------------------------------------------------------------------------------------

QVariantMap DlmsHelper::strct2map(QByteArray arrh, int addLen, bool &isNotAll, quint32 &arrlen, const bool &verboseMode, const int &forcedDataTypeLen)
{
    arrlen = 0;
    //len data

    const int strctlen = arrh.left(2 + addLen).toUInt(0, 16);
    arrh = arrh.mid(2 + addLen);

    QVariantMap m;
    int dataTypeLen = 2;
    if(forcedDataTypeLen > 0)
        dataTypeLen = forcedDataTypeLen;

    for(int i = 0; i < strctlen; i++){
        const quint16 datatype = arrh.left(dataTypeLen).toUInt(0, 16);
        quint32 len = arrh.mid(dataTypeLen,2).toUInt(0, 16);
        addLen = 0;
        if(len > 0x80 && len < 0x84){
            addLen = ((int)len - 0x80) * 2;
            len = arrh.mid(dataTypeLen + 2, addLen).toUInt(0, 16);
        }

        QVariant readyval;
        bool useReadyVal = false;

        int lenFromLine = 2;
        const int altLen = datatype2len(datatype);
        if(altLen >= 0){
            len = (quint8)altLen;
            lenFromLine = 0;
        }else{
            if(datatype == DLMS_DATA_TYPE_ARRAY){
//                need2useBuffer = true;
                useReadyVal = true;
                readyval = arr2map(arrh.mid(dataTypeLen), addLen, isNotAll, len, verboseMode, forcedDataTypeLen);
            }else{
                if(datatype == DLMS_DATA_TYPE_STRUCTURE){//toVariantList
                    useReadyVal = true;
                    readyval = strct2map(arrh.mid(dataTypeLen), addLen, isNotAll, len, verboseMode, forcedDataTypeLen);
                }
            }
        }
        if(isNotAll)
            break;
        if(useReadyVal){
            m.insert(QString::number(i), readyval);
        }else{
            const QByteArray a = arrh.mid(dataTypeLen + lenFromLine, len * 2);
            if((quint32)a.length() != (len * 2)){
                if(verboseMode) qDebug() << "err parse data data.len() " << (int)datatype << (int)len << dataTypeLen << arrh.left(10) << a;

                break;
            }
            //        commandCodeH.append(meterMessH.left(dataTypeLen + lenFromLine + len * 2));

            m.insert(QString::number(i), datatype2normal(datatype, a, verboseMode));
        }

        arrh = arrh.mid(dataTypeLen + addLen + lenFromLine + len * 2);
        arrlen += ((dataTypeLen + lenFromLine + len * 2) / 2);

        if( arrh.isEmpty())
            break;

    }
    if(m.size() != strctlen)
        isNotAll = true;
    return m;
}

//-----------------------------------------------------------------------------------------

void DlmsHelper::moveCache2hash(const QVariantHash &h, const QList<QByteArray> &commandCodeH, QVariantHash &hashTmpData, quint16 &step, int &error_counter, const bool &verboseMode, LastErrStruct &lastErrS)
{
    if(h.isEmpty()){
        if(verboseMode) qDebug() << "hash is empty, exiting .................................. ";
        hashTmpData.insert(MeterPluginHelper::errWarnKey(error_counter, true), MeterPluginHelper::prettyMess(QString("empty hash"), commandCodeH.join("\n"), lastErrS.lastErrorStr, lastErrS.lastWarning, true));
        step = 0xFFFF;
    }else{
        if(!h.value("messFail", true).toBool()){
            const QList<QString> lKey = h.keys();
            for(int i = 0, iMax = lKey.size(); i < iMax; i++)
                hashTmpData.insert(lKey.at(i), h.value(lKey.at(i)));

        }else{
            const QList<QString> lKey = h.keys();
            for(int i = 0, iMax = lKey.size(); i < iMax; i++){
                if(lKey.at(i).left(6) == "Error_" || lKey.at(i).left(8) == "Warning_")
                    hashTmpData.insert(lKey.at(i), h.value(lKey.at(i)));
            }
        }
    }
}

//-----------------------------------------------------------------------------------------

QByteArray DlmsHelper::arrMessageWriteSN(ObisList &lastObisList, const quint64 &obis, const quint16 &attr, const QByteArray &arrh)
{
    //obis must be from regular DLMS
    //attr - is short name dlms OBIS
    lastObisList.clear();
    lastObisList.append(obis);
    QByteArray payLoad = "E6 E6 00 06 01 02 "; //perhaps only for one obis code

    payLoad.append( QByteArray::number(attr, 16).rightJustified(4, '0'));//it can't be longer that 2 bytes
    payLoad.append("01");//I don't know why, but it is always sent here
    payLoad.append(arrh);
    return payLoad;
}

//-----------------------------------------------------------------------------------------

QByteArray DlmsHelper::arrMessageWrite(ObisList &lastObisList, const quint64 &obis, const quint16 &attr, const QByteArray &arrh)
{
    lastObisList.clear();
    lastObisList.append(obis);

    QByteArray payLoad = (obis == CMD_GSET_RELAY) ? "C3 01 81 " : "C1 01 81 ";
    QByteArray a = obis2classIdExt(obis) + QByteArray::number(obis, 16).rightJustified(12, '0');
    a.append( QByteArray::number(attr, 16).rightJustified(2, '0') + "00");
    a.append(arrh);
    payLoad.append(a);


//    qDebug() << "write mess=" << payLoad;
    return payLoad;
}

//-----------------------------------------------------------------------------------------

QByteArray DlmsHelper::arrMessageXtend(ObisList &lastObisList, const ObisList &obisList, const AttributeList &attributeList, const bool &lastIsShortDlms)
{
    lastObisList.clear();

    if(lastIsShortDlms)
        return arrMessageXtendSN(lastObisList, obisList, attributeList);





    QList<QByteArray> cidl;
    for(int i = 0, iMax = obisList.size(); i < iMax; i++){
        //<2byte class_id> <6byte obis code> <2 byte attribute>
//        QByteArray a = ;// + QByteArray::number(obisList.at(i), 16).rightJustified(12, '0');
//        a.append( QByteArray::number( (i < iMax2) ? attributeList.at(i) : 1 ).rightJustified(2, '0') + "00");

        cidl.append(obis2classIdExt(obisList.at(i)));
//        qDebug() << "xTend a=" << cidl.last();

    }


    return arrMessageXtendExt(lastObisList, obisList, cidl, attributeList);

}

QByteArray DlmsHelper::arrMessageXtendExt(ObisList &lastObisList, const ObisList &obisList, const QList<QByteArray> &cidl, const AttributeList &attributeList)
{

    const int obisCounter = obisList.size();
    if(obisCounter < 1)
        return "";

    QByteArray payLoad = QByteArray::number(obisCounter, 16).rightJustified(2, '0');
    if(true){
        QByteArray a = "E6 E6 00";//LLC bytes
        a.append("C0");//GET.request.
        if(obisCounter == 1){
            a.append("01");//only one obis code
            a.append("81");//invoke-id and priority
            payLoad.clear();//no need obis counter
        }else{
            a.append("03");//xxx?? has obis counter
            a.append("81");//invoke-id and priority
        }
        payLoad.prepend(a);// a.append(payLoad);
    }

    for(int i = 0, iMax = obisCounter, iMax2 = attributeList.size(), imax3 = cidl.size(); i < iMax; i++){
        //<2byte class_id> <6byte obis code> <2 byte attribute>

        payLoad.append((i < imax3) ? cidl.at(i) : "0000");//class id
        payLoad.append(QByteArray::number(obisList.at(i), 16).rightJustified(12, '0'));//obis code
        payLoad.append(QByteArray::number( (i < iMax2) ? attributeList.at(i) : 1 ).rightJustified(2, '0') + "00");//attribute

//        QByteArray a = (i < imax3) ? cidl.at(i) : "0000";// obis2classIdExt(obisList.at(i)) + QByteArray::number(obisList.at(i), 16).rightJustified(12, '0');
//        a.append( QByteArray::number( (i < iMax2) ? attributeList.at(i) : 1 ).rightJustified(2, '0') + "00");
//        payLoad.append(a);
//        qDebug() << "xTend a=" << a;

    }
//    qDebug() << "xTend mess=" << payLoad;
    lastObisList = obisList;
    return payLoad;
}

//-----------------------------------------------------------------------------------------

QByteArray DlmsHelper::arrMessageXtendSN(ObisList &lastObisList, const ObisList &obisList, const AttributeList &attributeList)
{
    const int obisCounter = obisList.size();
    if(obisCounter < 1)
        return "";


    QByteArray message = "E6 E6 00 05 " + QByteArray::number(obisCounter, 16).rightJustified(2, '0');//LLC bytes + request + size

    for(int i = 0, iMax = obisCounter, iMax2 = attributeList.size(); i < iMax && i < iMax2; i++){
        //<size 1b> <attribute 2b>
        const QByteArray a = "02" + QByteArray::number(attributeList.at(i), 16).rightJustified(4, '0');
        message.append(a);
    }

    lastObisList = obisList;
    return message;
}

//-----------------------------------------------------------------------------------------

QByteArray DlmsHelper::obis2classIdExt(const quint64 &obis)
{
    quint16 cid = 0x0;


//#define DLMS_CLASS_ID_DATA                      0x1//v0 4.3.1       class_id = 1
//#define DLMS_CLASS_ID_REGISTER                  0x3//v0 4.3.2       class_id = 3
//#define DLMS_CLASS_ID_EXTENDED_REGISTER         0x4//v0 4.3.3       class_id = 4
//#define DLMS_CLASS_ID_DEMAND_REGISTER           0x5//v0 4.3.4       class_id = 5
//#define DLMS_CLASS_ID_REGISTER_ACTIVATION       0x6//v0 4.3.5       class_id = 6
//#define DLMS_CLASS_ID_PROFILE_GENERIC           0x7//v1 4.3.6       class_id = 6
//#define DLMS_CLASS_ID_UTILITY_TABLES            0x1A//v0 4.3.7      class_id = 26
//#define DLMS_CLASS_ID_REGISTER_TABLE            0x3D//v0 4.3.8      class_id = 61
//#define DLMS_CLASS_ID_STATUS_MAPPING            0x3F//v0 4.3.9      class_id = 63
//#define DLMS_CLASS_ID_COMPACT_DATA              0x3E//v0 4.3.10.1   class_id = 62
//#define DLMS_CLASS_ID_ASSOCIATION_SN            0x0C//v4 4.4.3      class_id = 12
//#define DLMS_CLASS_ID_ASSOCIATION_LN            0x0F//v3 4.4.4      class_id = 15
//#define DLMS_CLASS_ID_SAP_ASSIGNMENT            0x11//v0 4.4.5      class_id = 17
//#define DLMS_CLASS_ID_IMAGE_TRANSFER            0x12//v0 4.4.6.3    class_id = 18

//#define DLMS_CLASS_ID_SECURITY_SETUP            0x40//v1 4.4.7      class_id = 64
//#define DLMS_CLASS_ID_PUSH_SETUP                0x28//v0 4.4.8.2    class_id = 40
//#define DLMS_CLASS_ID_DATA_PROTECTION           0x1E//v0 4.4.9.2    class_id = 30

//#define DLMS_CLASS_ID_CLOCK                     0x08//v0 4.5.1      class_id = 8
//#define DLMS_CLASS_ID_SCRIPT_TABLE              0x09//v0 4.5.2      class_id = 9
//#define DLMS_CLASS_ID_SCHEDULE                  0x0A//v0 4.5.3      class_id = 10
//#define DLMS_CLASS_ID_SPECIAL_DAYS_TABLE        0x0B//v0 4.5.4      class_id = 11
//#define DLMS_CLASS_ID_ACTIVITY_CALENDAR         0x14//v0 4.5.5      class_id = 20
//#define DLMS_CLASS_ID_REGISTER_MONITOR          0x15//v0 4.5.6      class_id = 21
//#define DLMS_CLASS_ID_SINGLE_ACTION_SCHEDULE    0x16//v0 4.5.7      class_id = 22

//#define DLMS_CLASS_ID_DISCONNECT_CONTROL        0x46//v0 4.5.8      class_id = 70
//#define DLMS_CLASS_ID_LIMITER                   0x47//v0 4.5.9      class_id = 71
//#define DLMS_CLASS_ID_PARAMETER_MONITOR         0x41//v0 4.5.10     class_id = 65

//#define DLMS_CLASS_ID_SENSOR_MANAGER            0x43//v0 4.5.11.2   class_id = 67
//#define DLMS_CLASS_ID_ARBITRATOR                0x44//v0 4.5.12.2   class_id = 68
//#define DLMS_CLASS_ID_ACCOUNT                   0x6F//v0 4.6.2      class_id = 111
//#define DLMS_CLASS_ID_IEC_LOCAL_PORT_SETUP      0x13//v1 4.7.1      class_id = 19
//#define DLMS_CLASS_ID_IEC_HDLC_SETUP            0x15//v1 4.7.2      class_id = 23
//#define DLMS_CLASS_ID_IEC_TWISTED_PAIR          0x16//v1 4.7.3      class_id = 24
//#define DLMS_CLASS_ID_MODEM_CONFIGURATION       0x1B//v1 4.7.4      class_id = 27
//#define DLMS_CLASS_ID_AUTO_ANSWER               0x1C//v2 4.7.5      class_id = 28
//#define DLMS_CLASS_ID_AUTO_CONNECT              0x1D//v2 4.7.6      class_id = 29
//#define DLMS_CLASS_ID_GPRS_MODEM_SETUP          0x2D//v1 4.7.7      class_id = 45
//#define DLMS_CLASS_ID_GSM_DIAGNOSTIC            0x2F//v0 4.7.8      class_id = 47

    switch(obis){

    case CMD_GET_MODIFICATION           :
    case CMD_GET_FIRMWARE_VERSION       :
    case CMD_GSET_METER_NUMBER          : cid = DLMS_CLASS_ID_DATA         ; break;



    case CMD_GET_PWR_ACTIVE_SUMM                 :

        //A+
    case CMD_GET_PWR_ACTIVE_IMPORT_SUMM          :
        //A-
    case CMD_GET_PWR_ACTIVE_EXPORT_SUMM          :


        //R+Ax
    case CMD_GET_PWR_REACTIVE_AXIMPORT_SUMM      :
        //R+Ay
    case CMD_GET_PWR_REACTIVE_AYIMPORT_SUMM      :
        //R-Rx
    case CMD_GET_PWR_REACTIVE_AXEXPORT_SUMM      :
        //R-Ry
    case CMD_GET_PWR_REACTIVE_AYEXPORT_SUMM      : cid = DLMS_CLASS_ID_DEMAND_REGISTER; break;//scaler_unit = 4


    case CMD_GET_EOD_ACTIVE_IMPORT_SUMM     :
    case CMD_GET_EOD_ACTIVE_IMPORT_T1       :
    case CMD_GET_EOD_ACTIVE_IMPORT_T2       :
    case CMD_GET_EOD_ACTIVE_IMPORT_T3       :
    case CMD_GET_EOD_ACTIVE_IMPORT_T4       :


    case CMD_GET_INSTANT_SUMM_FREQUENCY :

    case CMD_GET_INSTANT_L1_Q_PLUS      :
    case CMD_GET_INSTANT_L1_Q_MINUS     :
    case CMD_GET_INSTANT_L1_I           :
    case CMD_GET_INSTANT_L1_U           :
    case CMD_GET_INSTANT_L1_COSF        :
    case CMD_GET_INSTANT_L1_P           :
    case CMD_GET_INSTANT_L1_P_PLUS      :
    case CMD_GET_INSTANT_L1_P_MINUS     :

    case CMD_GET_INSTANT_L2_Q_PLUS      :
    case CMD_GET_INSTANT_L2_Q_MINUS     :
    case CMD_GET_INSTANT_L2_I           :
    case CMD_GET_INSTANT_L2_U           :
    case CMD_GET_INSTANT_L2_COSF        :
    case CMD_GET_INSTANT_L2_P           :
    case CMD_GET_INSTANT_L2_P_PLUS      :
    case CMD_GET_INSTANT_L2_P_MINUS     :

    case CMD_GET_INSTANT_L3_Q_PLUS      :
    case CMD_GET_INSTANT_L3_Q_MINUS     :
    case CMD_GET_INSTANT_L3_I           :
    case CMD_GET_INSTANT_L3_U           :
    case CMD_GET_INSTANT_L3_COSF        :
    case CMD_GET_INSTANT_L3_P           :
    case CMD_GET_INSTANT_L3_P_PLUS      :
    case CMD_GET_INSTANT_L3_P_MINUS     :


    case CMD_GET_INSTANT_SUMM_I         :
    case CMD_GET_INSTANT_SUMM_U         :
    case CMD_GET_INSTANT_SUMM_COSF      :
    case CMD_GET_INSTANT_SUMM_P         :

    case CMD_GET_ACTIVE_SUMM            :
    case CMD_GET_ACTIVE_T1              :
    case CMD_GET_ACTIVE_T2              :
    case CMD_GET_ACTIVE_T3              :
    case CMD_GET_ACTIVE_T4              :

    case CMD_GET_ACTIVE_IMPORT_SUMM     :
    case CMD_GET_ACTIVE_IMPORT_T1       :
    case CMD_GET_ACTIVE_IMPORT_T2       :
    case CMD_GET_ACTIVE_IMPORT_T3       :
    case CMD_GET_ACTIVE_IMPORT_T4       :
    case CMD_GET_ACTIVE_EXPORT_SUMM     :
    case CMD_GET_ACTIVE_EXPORT_T1       :
    case CMD_GET_ACTIVE_EXPORT_T2       :
    case CMD_GET_ACTIVE_EXPORT_T3       :
    case CMD_GET_ACTIVE_EXPORT_T4       :
    case CMD_GET_REACTIVE_RIMPORT_SUMM  :
    case CMD_GET_REACTIVE_RIMPORT_T1    :
    case CMD_GET_REACTIVE_RIMPORT_T2    :
    case CMD_GET_REACTIVE_RIMPORT_T3    :
    case CMD_GET_REACTIVE_RIMPORT_T4    :
    case CMD_GET_REACTIVE_REXPORT_SUMM  :
    case CMD_GET_REACTIVE_REXPORT_T1    :
    case CMD_GET_REACTIVE_REXPORT_T2    :
    case CMD_GET_REACTIVE_REXPORT_T3    :
    case CMD_GET_REACTIVE_REXPORT_T4    :

    case CMD_GET_REACTIVE_R1_SUMM       :
    case CMD_GET_REACTIVE_R1_T1         :
    case CMD_GET_REACTIVE_R1_T2         :
    case CMD_GET_REACTIVE_R1_T3         :
    case CMD_GET_REACTIVE_R1_T4         :

    case CMD_GET_REACTIVE_R2_SUMM       :
    case CMD_GET_REACTIVE_R2_T1         :
    case CMD_GET_REACTIVE_R2_T2         :
    case CMD_GET_REACTIVE_R2_T3         :
    case CMD_GET_REACTIVE_R2_T4         :

    case CMD_GET_REACTIVE_R3_SUMM       :
    case CMD_GET_REACTIVE_R3_T1         :
    case CMD_GET_REACTIVE_R3_T2         :
    case CMD_GET_REACTIVE_R3_T3         :
    case CMD_GET_REACTIVE_R3_T4         :

    case CMD_GET_REACTIVE_R4_SUMM       :
    case CMD_GET_REACTIVE_R4_T1         :
    case CMD_GET_REACTIVE_R4_T2         :
    case CMD_GET_REACTIVE_R4_T3         :
    case CMD_GET_REACTIVE_R4_T4         : cid = DLMS_CLASS_ID_REGISTER      ; break;//scaler_unit = 3



    case CMD_GSET_DATETIME              : cid = DLMS_CLASS_ID_CLOCK         ; break;


    case CMD_GET_EV_STANDARD            :
    case CMD_GET_EV_FRAUD_DETECTION     :
    case CMD_GET_EV_FIRMWARE_UPDATE     :
    case CMD_GET_EV_POWER_QUALITY       :
    case CMD_GET_EV_COMMUNICATION_IFACE :
    case CMD_GET_EV_CLOCK               :
    case CMD_GET_EV_POWER_FAILURE       :
    case CMD_GET_BILLING_PROFILE        :
    case CMD_GET_LOAD_PROFILE_2         :

    case CMD_GET_LOAD_PROFILE           : cid = DLMS_CLASS_ID_PROFILE_GENERIC   ; break;

    case CMD_GSET_RELAY                  : cid = DLMS_CLASS_ID_DISCONNECT_CONTROL; break;


    default:{
        cid = obis2classIdsubObis(obis);
        if(cid > 0)
            break;


//        qDebug() << " ";
//        qDebug() << "======================================================================================";
//        qDebug() << "--------------- obis2classId unknown obis " << obis << QByteArray::number(obis, 16);
//        qDebug() << " ";
//        dlmsVersion.append("00");
        break;}
    }

    QByteArray a = QByteArray::number(cid, 16);
    a = a.rightJustified(4, '0');
    return a;
}

//-----------------------------------------------------------------------------------------

quint16 DlmsHelper::obis2classIdsubObis(quint64 obis)
{
    quint16 cid = 0x0;


    QByteArray arr = QByteArray::number(obis, 16);

    if(arr.right(2).toUpper() == "FF"){
//        qDebug() << "obis2classIdsubObis obis " << arr.toUpper();
        return cid;
    }

     arr.chop(2);
     arr.append("00");
    obis = arr.toULongLong(0, 16);


    switch(obis){



    case CMD_GET_EOD_ACTIVE_IMPORT_SUMM     :
    case CMD_GET_EOD_ACTIVE_IMPORT_T1       :
    case CMD_GET_EOD_ACTIVE_IMPORT_T2       :
    case CMD_GET_EOD_ACTIVE_IMPORT_T3       :
    case CMD_GET_EOD_ACTIVE_IMPORT_T4       :


    case CMD_GET_REACTIVE_REXPORT_T4   : cid = DLMS_CLASS_ID_REGISTER      ; break;




    default:{


//        qDebug() << "--------------- obis2classIdsubobis unknown obis " << obis << QByteArray::number(obis, 16);
//        qDebug() << " ";
//        dlmsVersion.append("00");
        break;}
    }

    return cid;
}

//-----------------------------------------------------------------------------------------

QByteArray DlmsHelper::dt2arr(const QDateTime &currDateTime, const QByteArray rightarr)
{
    //yy yy MM dd dow hh mm ss FF FF FF FF
    QByteArray arrh = QByteArray::number(currDateTime.date().year(), 16).rightJustified(4, '0') +
            QByteArray::number(currDateTime.date().month(), 16).rightJustified(2, '0') +
            QByteArray::number(currDateTime.date().day(), 16).rightJustified(2, '0') +
//            "FF" +
            QByteArray::number(/* (currDateTime.date().dayOfWeek() == 7) ? 0 : */currDateTime.date().dayOfWeek() , 16).rightJustified(2, '0') +
            QByteArray::number(currDateTime.time().hour(), 16).rightJustified(2, '0') +
            QByteArray::number(currDateTime.time().minute(), 16).rightJustified(2, '0') +
            QByteArray::number(currDateTime.time().second(), 16).rightJustified(2, '0') + rightarr;
    return arrh;
}

//-----------------------------------------------------------------------------------------

QVariantMap DlmsHelper::arrStructure2map(const QByteArray &arr)
{
    // 02 - len
    // 0F FF - int8 -1
    // 16 1E - enum (unit8) 30 -  Wh
    QVariantMap m;


    quint8 counter = (quint8)arr.at(0);
    if(counter != 2 || arr.length() != 5)
        return m;


    int scaler = ((qint8)arr.at(1) == 0x0F) ? (qint8)arr.at(2) : 0;

    m.insert("scaler", scaler);
    m.insert("unit", (quint8)arr.at(4));

    return m;
}

//-----------------------------------------------------------------------------------------

QString DlmsHelper::calcMeterAddr(const quint64 &meterSn, const int &addVal)
{
    int rpart = QString::number(meterSn).right(4).toInt();
    rpart += addVal;
    return QString::number(rpart);
}

//-----------------------------------------------------------------------------------------

void DlmsHelper::addEmptyIval2listDate(const QVariantHash &hashConstData, const QVariantHash &hashTmpData, const QVariantMap &mapPos2obis, const QStringList &list4pllEnrg, QVariantHash &hash, QStringList &listDate)
{
    //mark all ivl as done
    for(int i = 0, jMax = list4pllEnrg.size(); i < 500; i++){
        if(!hashConstData.contains(QString("pollDate_%1").arg(i)))
            break;
        const QString strDt = hashConstData.value(QString("pollDate_%1").arg(i)).toDateTime().toString("yyyy_MM_dd_hh_mm");

        if(listDate.contains(strDt))
            continue;

        for(int j = 0; j < jMax; j++){
            if(mapPos2obis.contains("T0_" + list4pllEnrg.at(j))){

                const QString kk =  QString("%1_T0_%2").arg(strDt).arg(list4pllEnrg.at(j));

                if(!hashTmpData.value(kk).toString().isEmpty() || !hash.value(kk).toString().isEmpty())
                    break;

                hash.insert(kk, "-");
                break;
            }
        }
        listDate.append(strDt);
    }
}

//-----------------------------------------------------------------------------------------

QDateTime DlmsHelper::fixDstShift(const QDateTime &indt, const bool &isDstNow)
{
    const int utcOffsetDt = indt.offsetFromUtc();


    QDateTime d = QDateTime(QDate(indt.date().year(), isDstNow ? 7 : 1, 1), indt.time());

//    qDebug() << "DlmsGamaHelper::fixDstShift "
//             << indt.toUTC().toString("yyyy/MM/dd hh:mm:ss") << indt.toLocalTime().offsetFromUtc() << indt.toLocalTime().isDaylightTime()
//             << d.toUTC().toString("yyyy/MM/dd hh:mm:ss") << d.toLocalTime().offsetFromUtc() << d.toLocalTime().isDaylightTime();

    const int utcOffset = d.offsetFromUtc();

    QDateTime dt = indt.toLocalTime();
    if(utcOffsetDt != utcOffset){
        dt.setOffsetFromUtc(utcOffset);
    }
    return dt;//UTC time is true, but local can be wrong
}

//-----------------------------------------------------------------------------------------

QDateTime DlmsHelper::fixDstShiftSmart25hour(const QDateTime &indt)
{
    //if indt with DST=1, return as it is
    //if indt with DST=0, check it , if the local time can be shifted

    if(indt.isDaylightTime())//10800
        return indt;

    const int utcOffsetDt = indt.offsetFromUtc(); //7200


    const QDateTime dtfixed = fixDstShift(indt, true); //it changes only utc time


    const int utcOffsetDtOut = dtfixed.offsetFromUtc();//10800


    if(utcOffsetDt == utcOffsetDtOut)
        return indt;

    const int diffsec = utcOffsetDt - utcOffsetDtOut - 1;//7200-10800=-3600 ,

    if(!indt.addSecs(diffsec).isDaylightTime()){//this is only normal time
        return indt;
    }

    return dtfixed;
}

//-----------------------------------------------------------------------------------------
QByteArray DlmsHelper::getValidPassword(const QVariantHash &hashConstData, const bool &retInHex, const QByteArray &defPasswd)
{
    const QByteArray a = hashConstData.value("passwd", "").toByteArray();
    if(a.isEmpty())
        return (retInHex) ? defPasswd.toHex() : defPasswd;
    return (retInHex) ? a.toHex() : a;
}
//----------------------------------------------------------------------------------

bool DlmsHelper::ignoreThisObisCodeTariff(const quint64 &obisCode, bool &codeIsValid, QString &tstr, QString &removeThisKeyStr)
{
    tstr.clear();
    codeIsValid = true;
    bool ignoreCode = false;
    switch(obisCode){

//|A|
    case CMD_GET_ACTIVE_SUMM            : tstr = "T0_A+"     ; break;
    case CMD_GET_ACTIVE_T1              : tstr = "T1_A+"     ; break;
    case CMD_GET_ACTIVE_T2              : tstr = "T2_A+"     ; break;
    case CMD_GET_ACTIVE_T3              : tstr = "T3_A+"     ; break;
    case CMD_GET_ACTIVE_T4              : tstr = "T4_A+"     ; break;

//A+
    case CMD_GET_ACTIVE_IMPORT_SUMM     : tstr = "T0_A+"     ; break;
    case CMD_GET_ACTIVE_IMPORT_T1       : tstr = "T1_A+"     ; break;
    case CMD_GET_ACTIVE_IMPORT_T2       : tstr = "T2_A+"     ; break;
    case CMD_GET_ACTIVE_IMPORT_T3       : tstr = "T3_A+"     ; break;
    case CMD_GET_ACTIVE_IMPORT_T4       : tstr = "T4_A+"     ; break;

//A-
    case CMD_GET_ACTIVE_EXPORT_SUMM     : tstr = "T0_A-"     ; break;
    case CMD_GET_ACTIVE_EXPORT_T1       : tstr = "T1_A-"     ; break;
    case CMD_GET_ACTIVE_EXPORT_T2       : tstr = "T2_A-"     ; break;
    case CMD_GET_ACTIVE_EXPORT_T3       : tstr = "T3_A-"     ; break;
    case CMD_GET_ACTIVE_EXPORT_T4       : tstr = "T4_A-"     ; break;

//R+

//
    case CMD_GET_REACTIVE_RIMPORT_SUMM : tstr = "T0_R+"     ; removeThisKeyStr = QString("DLMS_%1").arg(tstr); break;
    case CMD_GET_REACTIVE_RIMPORT_T1   : tstr = "T1_R+"     ; removeThisKeyStr = QString("DLMS_%1").arg(tstr); break;
    case CMD_GET_REACTIVE_RIMPORT_T2   : tstr = "T2_R+"     ; removeThisKeyStr = QString("DLMS_%1").arg(tstr); break;
    case CMD_GET_REACTIVE_RIMPORT_T3   : tstr = "T3_R+"     ; removeThisKeyStr = QString("DLMS_%1").arg(tstr); break;
    case CMD_GET_REACTIVE_RIMPORT_T4   : tstr = "T4_R+"     ; removeThisKeyStr = QString("DLMS_%1").arg(tstr); break;

    case CMD_GET_REACTIVE_REXPORT_SUMM : tstr = "T0_R-"     ; removeThisKeyStr = QString("DLMS_%1").arg(tstr); break;
    case CMD_GET_REACTIVE_REXPORT_T1   : tstr = "T1_R-"     ; removeThisKeyStr = QString("DLMS_%1").arg(tstr); break;
    case CMD_GET_REACTIVE_REXPORT_T2   : tstr = "T2_R-"     ; removeThisKeyStr = QString("DLMS_%1").arg(tstr); break;
    case CMD_GET_REACTIVE_REXPORT_T3   : tstr = "T3_R-"     ; removeThisKeyStr = QString("DLMS_%1").arg(tstr); break;
    case CMD_GET_REACTIVE_REXPORT_T4   : tstr = "T4_R-"     ; removeThisKeyStr = QString("DLMS_%1").arg(tstr); break;



    case CMD_GET_REACTIVE_R1_SUMM       : tstr = "T0_R+"     ; break;
    case CMD_GET_REACTIVE_R1_T1         : tstr = "T1_R+"     ; break;
    case CMD_GET_REACTIVE_R1_T2         : tstr = "T2_R+"     ; break;
    case CMD_GET_REACTIVE_R1_T3         : tstr = "T3_R+"     ; break;
    case CMD_GET_REACTIVE_R1_T4         : tstr = "T4_R+"     ; break;

    case CMD_GET_REACTIVE_R2_SUMM       : tstr = "DLMS_T0_R+"; break;
    case CMD_GET_REACTIVE_R2_T1         : tstr = "DLMS_T1_R+"; break;
    case CMD_GET_REACTIVE_R2_T2         : tstr = "DLMS_T2_R+"; break;
    case CMD_GET_REACTIVE_R2_T3         : tstr = "DLMS_T3_R+"; break;
    case CMD_GET_REACTIVE_R2_T4         : tstr = "DLMS_T4_R+"; break;


    case CMD_GET_REACTIVE_R3_SUMM       : tstr = "T0_R-"     ; break;
    case CMD_GET_REACTIVE_R3_T1         : tstr = "T1_R-"     ; break;
    case CMD_GET_REACTIVE_R3_T2         : tstr = "T2_R-"     ; break;
    case CMD_GET_REACTIVE_R3_T3         : tstr = "T3_R-"     ; break;
    case CMD_GET_REACTIVE_R3_T4         : tstr = "T4_R-"     ; break;


    case CMD_GET_REACTIVE_R4_SUMM       : tstr = "DLMS_T0_R-"; break;
    case CMD_GET_REACTIVE_R4_T1         : tstr = "DLMS_T1_R-"; break;
    case CMD_GET_REACTIVE_R4_T2         : tstr = "DLMS_T2_R-"; break;
    case CMD_GET_REACTIVE_R4_T3         : tstr = "DLMS_T3_R-"; break;
    case CMD_GET_REACTIVE_R4_T4         : tstr = "DLMS_T4_R-"; break;

    default: ignoreCode = true; codeIsValid = false; break;
    }

    return ignoreCode;
}
//------------------------------------------------------------------------------------------
bool DlmsHelper::ignoreThisObisCodeVoltage(const quint64 &obisCode, const bool &isSinglePhase, bool &codeIsValid, QString &tstr)
{
    tstr.clear();
    codeIsValid = true;
    bool ignoreCode = false;

//    qreal scaler = 1.0;

    if(isSinglePhase){

        switch(obisCode){

        case CMD_GET_INSTANT_SUMM_FREQUENCY : tstr = "F"                         ; break;



        case CMD_GET_INSTANT_SUMM_I         : tstr = "IA"                        ; break;
        case CMD_GET_INSTANT_SUMM_U         : tstr = "UA"                        ; break;
        case CMD_GET_INSTANT_SUMM_COSF      : tstr = "cos_fA"                    ; break;
        case CMD_GET_INSTANT_SUMM_P         : tstr = "PA"       ;  break;//scaler =  0.001;

        case CMD_GET_INSTANT_SUMM_Q         : tstr = "QA"                         ; break;

        default: ignoreCode = true; codeIsValid = false; break;
        }

    }else{

        switch(obisCode){

        case CMD_GET_INSTANT_SUMM_FREQUENCY : tstr = "F"                         ; break;

        case CMD_GET_INSTANT_L1_Q_PLUS      : tstr = "DLMS_QA"  ;  break;//scaler =  0.001; break;
        case CMD_GET_INSTANT_L1_Q_MINUS     : tstr = "DLMS_QA"  ;  break;//scaler = -0.001; break;
        case CMD_GET_INSTANT_L1_I           : tstr = "IA"                        ; break;
        case CMD_GET_INSTANT_L1_U           : tstr = "UA"                        ; break;
        case CMD_GET_INSTANT_L1_COSF        : tstr = "cos_fA"                    ; break;
        case CMD_GET_INSTANT_L1_P           : tstr = "PA"       ;  break;//scaler =  0.001; break;
        case CMD_GET_INSTANT_L1_P_PLUS      : tstr = "DLMS_PA"       ;  break;//scaler =  0.001; break;
        case CMD_GET_INSTANT_L1_P_MINUS     : tstr = "DLMS_PA"       ;  break;//scaler =  0.001; break;

        case CMD_GET_INSTANT_L2_Q_PLUS      : tstr = "DLMS_QB"  ; break;// scaler =  0.001; break;
        case CMD_GET_INSTANT_L2_Q_MINUS     : tstr = "DLMS_QB"  ; break;// scaler = -0.001; break;
        case CMD_GET_INSTANT_L2_I           : tstr = "IB"                        ; break;
        case CMD_GET_INSTANT_L2_U           : tstr = "UB"                        ; break;
        case CMD_GET_INSTANT_L2_COSF        : tstr = "cos_fB"                    ; break;
        case CMD_GET_INSTANT_L2_P           : tstr = "PB"       ; break;// scaler =  0.001; break;
        case CMD_GET_INSTANT_L2_P_PLUS      : tstr = "DLMS_PB"       ;  break;//scaler =  0.001; break;
        case CMD_GET_INSTANT_L2_P_MINUS     : tstr = "DLMS_PB"       ;  break;//scaler =  0.001; break;


        case CMD_GET_INSTANT_L3_Q_PLUS      : tstr = "DLMS_QC"  ; break;// scaler =  0.001; break;
        case CMD_GET_INSTANT_L3_Q_MINUS     : tstr = "DLMS_QC"  ; break;// scaler = -0.001; break;
        case CMD_GET_INSTANT_L3_I           : tstr = "IC"                        ; break;
        case CMD_GET_INSTANT_L3_U           : tstr = "UC"                        ; break;
        case CMD_GET_INSTANT_L3_COSF        : tstr = "cos_fC"                    ; break;
        case CMD_GET_INSTANT_L3_P           : tstr = "PC"       ; break;// scaler =  0.001; break;
        case CMD_GET_INSTANT_L3_P_PLUS      : tstr = "DLMS_PC"       ;  break;//scaler =  0.001; break;
        case CMD_GET_INSTANT_L3_P_MINUS     : tstr = "DLMS_PC"       ;  break;//scaler =  0.001; break;

        default: ignoreCode = true; codeIsValid = false; break;
        }

    }

    return ignoreCode;


}
//------------------------------------------------------------------------------------------
bool DlmsHelper::ignoreThisObisCodeLoadProfile(const quint64 &obisCode, bool &codeIsValid, QString &tstr)
{
    tstr.clear();
    codeIsValid = true;
    bool ignoreCode = false;

    switch(obisCode){


    case CMD_GET_PWR_ACTIVE_SUMM_7         :
    case CMD_GET_PWR_ACTIVE_SUMM            :

//    case CMD_GET_PWR_ACTIVE_IMPORT_SUMM_SN  :
    case CMD_GET_PWR_ACTIVE_IMPORT_SUMM     : tstr = "A+";;break;

//    case CMD_GET_PWR_ACTIVE_EXPORT_SUMM_SN  :
    case CMD_GET_PWR_ACTIVE_EXPORT_SUMM     : tstr = "A-"; break;

    case CMD_GET_PWR_REACTIVE_SUMM_7:
    case CMD_GET_PWR_REACTIVE_AXIMPORT_SUMM : tstr = "R+"; break;

//    case CMD_GET_PWR_REACTIVE_REXPORT_SUMM_SN:
    case CMD_GET_PWR_REACTIVE_AYIMPORT_SUMM : tstr = "R-"; break;

    default: ignoreCode = true; codeIsValid = false; break;

    }
    return ignoreCode;
}

//------------------------------------------------------------------------------------------
QByteArray DlmsHelper::addObis4writeDtExt(ObisList &lastObisList, const quint64 &obisln, const quint16 &obissn, const bool &lastMeterIsShortDlms, const QByteArray &rightarr)
{

    //    quint64 obis, quint16 &attr, QByteArray &arrh

//    const quint64 obis = CMD_GSET_DATETIME;
    const quint16 attr = 2;

    //yy yy MM dd dow hh mm ss FF FF FF FF
    const QByteArray arrh = "09 0C" + dt2arr(QDateTime::currentDateTime().addSecs(4), rightarr);


    if(lastMeterIsShortDlms){

//        const qint16 obissn = CMD_GSET_DATETIME_SN;
        return arrMessageWriteSN(lastObisList, obisln, obissn, arrh);
    }

    return arrMessageWrite(lastObisList, obisln, attr, arrh);
}
//------------------------------------------------------------------------------------------
