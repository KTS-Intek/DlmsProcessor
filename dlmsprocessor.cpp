#include "dlmsprocessor.h"

#include "dlmshelper.h"


//----------------------------------------------------------------------------------

DlmsProcessor::DlmsProcessor(QObject *parent) : QObject(parent)
{
    verboseMode = false;

}

//----------------------------------------------------------------------------------

bool DlmsProcessor::isItTime2getShortNames2obisTotalFromVHsmart(const QVariantHash &hashConstData, QVariantHash &hashTmpData)
{
    const bool isDone = isItMarkedAsDoneSn2obis(hashTmpData);// hashTmpData.value("DLMS_shortNamesReadingDone", false).toBool();
    if(isDone)//it was already received
        return false;

    if(!isItTime2getShortNames2obisTotalFromVH(hashConstData)){
        markThisMeterAsDoneSn2obis(hashTmpData);
        return false;
    }
    return true;//get the obis list

}

//----------------------------------------------------------------------------------

bool DlmsProcessor::isItTime2getShortNames2obisVoltageFromVHsmart(const QVariantHash &hashConstData, QVariantHash &hashTmpData)
{
    const bool isDone = isItMarkedAsDoneSn2obis(hashTmpData);// hashTmpData.value("DLMS_shortNamesReadingDone", false).toBool();
    if(isDone)//it was already received
        return false;

    if(!isItTime2getShortNames2obisVoltageFromVH(hashConstData)){
        markThisMeterAsDoneSn2obis(hashTmpData);
        return false;
    }
    return true;//get the obis list
}

//----------------------------------------------------------------------------------

bool DlmsProcessor::isItTime2getShortNames2obisLoadProfileFromVHsmart(const QVariantHash &hashConstData, QVariantHash &hashTmpData)
{
    const bool isDone = isItMarkedAsDoneSn2obis(hashTmpData);// hashTmpData.value("DLMS_shortNamesReadingDone", false).toBool();
    if(isDone)//it was already received
        return false;

    if(!isItTime2getShortNames2obisLoadProfileFromVH(hashConstData)){
        markThisMeterAsDoneSn2obis(hashTmpData);
        return false;
    }
    return true;//get the obis list
}

//----------------------------------------------------------------------------------

bool DlmsProcessor::isItMarkedAsDoneSn2obis(const QVariantHash &hashTmpData)
{
    return hashTmpData.value("DLMS_shortNamesReadingDone", false).toBool();

}

//----------------------------------------------------------------------------------

void DlmsProcessor::markThisMeterAsDoneSn2obis(QVariantHash &hashTmpData)
{
    hashTmpData.insert("DLMS_shortNamesReadingDone", true);
}

//----------------------------------------------------------------------------------

bool DlmsProcessor::isItTime2getShortNames2obisTotalFromVH(const QVariantHash &hashConstData)
{
    return isItTime2getShortNames2obisTotal(hashConstData.value("NI").toString());
}

//----------------------------------------------------------------------------------

bool DlmsProcessor::isItTime2getShortNames2obisTotal(const QString &ni)
{
    return isItTime2getShortNames2obisExt(ni, hNi2obis2ShortNamesTotal);
}

//----------------------------------------------------------------------------------

bool DlmsProcessor::isItTime2getShortNames2obisVoltageFromVH(const QVariantHash &hashConstData)
{
    return isItTime2getShortNames2obisVoltage(hashConstData.value("NI").toString());
}

//----------------------------------------------------------------------------------

bool DlmsProcessor::isItTime2getShortNames2obisVoltage(const QString &ni)
{   
    return isItTime2getShortNames2obisExt(ni, hNi2obis2ShortNamesVoltage);
}

//----------------------------------------------------------------------------------

bool DlmsProcessor::isItTime2getShortNames2obisLoadProfileFromVH(const QVariantHash &hashConstData)
{
    return isItTime2getShortNames2obisLoadProfile(hashConstData.value("NI").toString());
}

//----------------------------------------------------------------------------------

bool DlmsProcessor::isItTime2getShortNames2obisLoadProfile(const QString &ni)
{
    return isItTime2getShortNames2obisExt(ni, hNi2obis2ShortNamesLoadProfile);
}

//----------------------------------------------------------------------------------

bool DlmsProcessor::isItTime2getShortNames2obisExt(const QString &ni, const QHash<QString, DlmsProcessor::DLMSShortNamesParams> &h)
{

    lastShortNames.ni = ni;
    lastShortNames.lastObis2shortNames = h.value(ni);
    lastShortNames.lastShortNames2get.clear();

    return lastShortNames.lastObis2shortNames.obis2shortNames.isEmpty();//it has no data
}

//----------------------------------------------------------------------------------

bool DlmsProcessor::addShortName2obisCode(const quint16 &shortname, const quint64 &obiscode)
{
    bool ok;
    QString enrgk;
    QString removeThisKeyStr;
    if(!DlmsHelper::ignoreThisObisCodeTariff(obiscode, ok, enrgk, removeThisKeyStr)){
        DLMSShortNames onesett;
        onesett.enrgKey = enrgk;
        onesett.shortname = shortname;
        lastShortNames.lastObis2shortNames.obis2shortNames.insert(obiscode, onesett);


        if(!removeThisKeyStr.isEmpty() && lastShortNames.lastObis2shortNames.enrgKey2obis.contains(removeThisKeyStr)){
            const quint64 obis2remove = lastShortNames.lastObis2shortNames.enrgKey2obis.take(removeThisKeyStr);
//            const DLMSShortNames sett2remove =
                    lastShortNames.lastObis2shortNames.obis2shortNames.remove(obis2remove);


        }
    }
    return ok;
}

//----------------------------------------------------------------------------------

void DlmsProcessor::swapParams(DlmsProcessor::DLMSShortNamesParams &inOut, const DlmsProcessor::DLMSShortNamesParams &in)
{
    const QList<quint64> lk = in.obis2shortNames.keys();

    for(int i = 0, imax = lk.size(); i < imax; i++){
        const auto obis = lk.at(i);
        const auto params = in.obis2shortNames.value(obis);

        inOut.obis2shortNames.insert(obis, params);
        if(!params.enrgKey.isEmpty())
            inOut.enrgKey2obis.insert(params.enrgKey, obis);

    }



}

//----------------------------------------------------------------------------------

void DlmsProcessor::updateLastNiShortNamesVoltage()
{
    if(!lastShortNames.ni.isEmpty())
        hNi2obis2ShortNamesVoltage.insert(lastShortNames.ni, lastShortNames.lastObis2shortNames);
}

//----------------------------------------------------------------------------------

void DlmsProcessor::updateLastNiShortNamesLoadProfile()
{
    if(!lastShortNames.ni.isEmpty())
        hNi2obis2ShortNamesLoadProfile.insert(lastShortNames.ni, lastShortNames.lastObis2shortNames);
}
//----------------------------------------------------------------------------------

void DlmsProcessor::updateLastNiShortNamesTotal()
{
    if(!lastShortNames.ni.isEmpty())
        hNi2obis2ShortNamesTotal.insert(lastShortNames.ni, lastShortNames.lastObis2shortNames);
}

//----------------------------------------------------------------------------------

void DlmsProcessor::addDefaultReadingParams(QVariantHash &hashMessage)
{
    hashMessage.insert("quickCRC", true);
    hashMessage.insert("endSymb", QByteArray::fromHex("7E"));
    hashMessage.insert("data7EPt", false);
}

//----------------------------------------------------------------------------------

void DlmsProcessor::resetHDLCglobalVariables()
{
    lastExchangeState.messageCounterRRR = 0;
    lastExchangeState.messageCounterSSS = 0;
    lastExchangeState.lastObisCounter = 0;
    lastExchangeState.lastObisList.clear();
    lastExchangeState.lastMeterH.clear();

    lastExchangeState.dlmsFuckingChecksRemoveTypePrefixH.clear();
    lastExchangeState.dlmsFuckingChecksRemoveLen = 0;
    lastExchangeState.dlmsFuckingChecksObisCounterPos = 0;
    lastExchangeState.dlmsFuckingChecksForceDataLen = 0;    
    lastExchangeState.dlmsFuckingIgnoreEndOfRRframes = false;
    lastExchangeState.dlmsFuckingLastReceivedArr.clear();
    lastExchangeState.dlmsFukcingForcedDataPrefixH.clear();

}
//----------------------------------------------------------------------------------
bool DlmsProcessor::messageIsValid(const QByteArray &readArr, QVariantList &listMeterMesageVar, QList<QByteArray> &commandCodeH, const QByteArray &lastAddrH, quint8 &frameType, quint8 &errCode, const QByteArray lastSrcAddr)
{
    //use it only for testing of the incomming data
     auto lastExchange = lastExchangeState;
    return messageIsValidExt(lastExchange, readArr, listMeterMesageVar, commandCodeH, lastAddrH, frameType, errCode, lastSrcAddr);
}
//----------------------------------------------------------------------------------
bool DlmsProcessor::messageIsValidExt(DLMSExchangeState &lastExchangeState, const QByteArray &readArr, QVariantList &listMeterMesageVar, QList<QByteArray> &commandCodeH, const QByteArray &lastAddrH, quint8 &frameType, quint8 &errCode, const QByteArray lastSrcAddr)
{
    //do not use it for testing of incomming data
    const bool hadMoreData = lastExchangeState.dlmsFuckingHasMoreData;

    lastExchangeState.dlmsFuckingHasMoreData = false;
    errCode = ERR_ALL_GOOD;
    listMeterMesageVar.clear();
    commandCodeH.clear();


    bool endOfRRframes = false;// (!lastSrcAddr.isEmpty() && arrHex.left(2) != "A8");

    bool need2useBuffer = false;// (arrHex.left(2) == "A8");


    const QByteArray arrHex = getArrayHex(readArr, lastSrcAddr, lastAddrH, endOfRRframes, need2useBuffer, frameType);

    if(arrHex.isEmpty())
        return false;//Gama had issue here with GPRS, it can't be empty

    const bool hasByteA8 = need2useBuffer;

    QByteArray meterMessageH = arrHex.mid(16);


    if(!isCrcValid(meterMessageH, arrHex, errCode))
        return (errCode == ERR_CHECK_AUTHORIZE);//be careful, if something wrong with authorization, it must return true


    meterMessageH = meterMessageH.mid(4);//remove HCS
    const bool checkTopArr = (!lastExchangeState.lastMeterH.isEmpty() || !endOfRRframes);
    bool ignoreCheckTopArr = false;

    //LLC bytes
    int obisCounter = 1;
    int payloadLen = -1;
    int dataTypeLen = 4;

    if(isItShortDLMSBreak(frameType, lastSrcAddr, meterMessageH))
        return true;



    QByteArray meterMessageHCache ;

    int forcedDataTypeLen = 0; //use default is 0
    bool checkMeterMessageH = false;
    if(lastExchangeState.lastMeterH.isEmpty()){
        const bool r = checkPreparyCache(meterMessageH, errCode, obisCounter, payloadLen, dataTypeLen, lastExchangeState, forcedDataTypeLen);
        meterMessageHCache = meterMessageH;
        checkMeterMessageH = true;
        if(errCode != ERR_ALL_GOOD)
            return r;

    }else{
        obisCounter = lastExchangeState.lastObisCounter;

        if(!lastExchangeState.dlmsFuckingChecksRemoveTypePrefixH.isEmpty() &&
                meterMessageH.mid(6).toUpper().startsWith(lastExchangeState.dlmsFuckingChecksRemoveTypePrefixH.toUpper())){
            meterMessageH = meterMessageH.mid(6);//remove LLC    E6 E7 00 - LLC bytes

            meterMessageHCache = meterMessageH.mid(lastExchangeState.dlmsFuckingChecksRemoveLen);
            meterMessageHCache.prepend(lastExchangeState.lastMeterH);

            checkMeterMessageH = true;


            //removeLen
            //obisCounter
            ignoreCheckTopArr = true;
            lastExchangeState.dlmsFuckingLastReceivedArr = QByteArray::fromHex(meterMessageH);
            if(lastExchangeState.dlmsFuckingChecksForceDataLen > 0){
                dataTypeLen = lastExchangeState.dlmsFuckingChecksForceDataLen;
                forcedDataTypeLen = lastExchangeState.dlmsFuckingChecksForceDataLen;
            }

        //it is necessary, I don't know why, by meterMessageH is always broken if I don't do it
            lastExchangeState.lastMeterH.clear();
            meterMessageH = meterMessageHCache;

        }
    }



    //parse data


    lastExchangeState.lastDataTypeLen = dataTypeLen;
    lastExchangeState.lastObisCounter = obisCounter;

    if(!lastExchangeState.lastMeterH.isEmpty())
        meterMessageH.prepend(lastExchangeState.lastMeterH);



    if(!lastSrcAddr.isEmpty())
        lastExchangeState.lastMeterH.clear();


    int ob = 0;
    QByteArray topType;
    listMeterMesageVar = processCachedData(obisCounter, meterMessageH, dataTypeLen, commandCodeH, need2useBuffer, ob, topType, forcedDataTypeLen);



    if(verboseMode)
    qDebug() << "messageIsValid checkTopArr=" << checkTopArr << topType.isEmpty() << listMeterMesageVar.size()  << obisCounter << ob << need2useBuffer << meterMessageH.isEmpty() << endOfRRframes;


    if(checkTopArr && !ignoreCheckTopArr)
        topArrayChecks(hasByteA8, meterMessageH, topType, listMeterMesageVar, endOfRRframes, need2useBuffer, obisCounter, ob);

    if((lastExchangeState.dlmsFuckingIgnoreEndOfRRframes && need2useBuffer )){
         lastExchangeState.lastMeterH = meterMessageHCache;
        lastExchangeState.dlmsFuckingHasMoreData = true;
        if(verboseMode)
            qDebug() << "messageIsValid dlmsFuckingIgnoreEndOfRRframes lastExchangeState.lastMeterH=" << lastExchangeState.dlmsFuckingIgnoreEndOfRRframes << lastExchangeState.lastMeterH;

        return true;
    }

    if((!endOfRRframes && need2useBuffer && !meterMessageH.isEmpty()) ){
        lastExchangeState.lastMeterH = topType + meterMessageH;
        if(verboseMode) qDebug() << "messageIsValid lastExchangeState.lastMeterH=" << lastExchangeState.lastMeterH ;
        return true;
    }

    if(hadMoreData && !lastExchangeState.dlmsFuckingHasMoreData && verboseMode){
        qDebug() << "messageIsValid hadMoreData " << hadMoreData << need2useBuffer << lastExchangeState.dlmsFuckingHasMoreData ;
        qDebug() << "messageIsValid hadMoreData meterMessageHCache " << meterMessageHCache ;
        qDebug() << "messageIsValid hadMoreData lastExchangeState.lastMeterH " << lastExchangeState.lastMeterH;

    }


    return (!listMeterMesageVar.isEmpty() && (obisCounter == ob));
}
//----------------------------------------------------------------------------------
QByteArray DlmsProcessor::getArrayHex(const QByteArray &readArr, const QByteArray &lastSrcAddr, const QByteArray &lastAddrH, bool &endOfRRframes, bool &need2useBuffer, quint8 &frameType)
{
    QByteArray arrHex = readArr.toHex().toUpper();

    while(!arrHex.isEmpty() && arrHex.left(2) != "7E")
        arrHex = arrHex.mid(2);

    while(!arrHex.isEmpty() && arrHex.right(2) != "7E")
        arrHex.chop(2);


    if(arrHex.left(2) != "7E" || arrHex.right(2) != "7E" || arrHex.isEmpty())
        return QByteArray();

    arrHex.chop(2);
    arrHex = arrHex.mid(2);

    if(arrHex.left(2) != "A0" && arrHex.left(2) != "A8")
        return  QByteArray();

    endOfRRframes = (!lastSrcAddr.isEmpty() && arrHex.left(2) != "A8");

    need2useBuffer = (arrHex.left(2) == "A8");
//    const bool hasByteA8 = need2useBuffer;

    quint16 crc16 = QByteArray(arrHex.right(2) + arrHex.right(4).left(2)).toInt(0,16);
    arrHex.chop(4);

    if( crc16 != qChecksum(QByteArray::fromHex(arrHex).constData() , QByteArray::fromHex(arrHex).length())){
        if(verboseMode) qDebug() << "crc16 FCS is not valid " << crc16 << arrHex << qChecksum(QByteArray::fromHex(arrHex).constData() , QByteArray::fromHex(arrHex).length());
        return  QByteArray();
    }

    const qint32 len = QByteArray::fromHex(arrHex).length() + 2;
    if(len != arrHex.mid(2,2).toInt(0,16)){
        if(verboseMode) qDebug() << "message len not valid [len messLen] " << len << arrHex.mid(2,2).toInt(0,16) << arrHex.mid(2,2);
        return  QByteArray();
    }

    if(!lastSrcAddr.isEmpty() && arrHex.mid(4,2) != lastSrcAddr.toUpper()){ // "03"){
        if(verboseMode) qDebug() << "dest addr not valid " << arrHex.mid(4,2);
        return  QByteArray();
    }

    if(!lastAddrH.isEmpty() && arrHex.mid(6,8) != lastAddrH.toUpper() && !lastAddrH.isEmpty()){
        if(verboseMode) qDebug() << "source addr not valid [addr lastAddr] " <<  arrHex.mid(6,8) << lastAddrH;
        return  QByteArray();
    }

    frameType = arrHex.mid(14,2).toUShort(0,16);
    if(frameType < 1 || frameType > 0xFE ){
        if(verboseMode) qDebug() << "frameType not valid " << frameType << arrHex.mid(14,2).toUShort(0,16) << arrHex.mid(14,2);
        return  QByteArray();
    }
    return arrHex;

}

//----------------------------------------------------------------------------------

bool DlmsProcessor::isCrcValid(const QByteArray &meterMessH, const QByteArray &arrHex, quint8 &errCode)
{
    if(meterMessH.isEmpty()){
//        meterMessH = "";
        errCode = ERR_CHECK_AUTHORIZE;
        return false;// be crareful, it means true // true;//frame 0x1F err???
    }
    //left 4 byte is HCS check this  A0 15 03 00 02 34 E5 73 F2 BD
    const quint16 crc16 = QByteArray(meterMessH.left(4).right(2) + meterMessH.left(2)).toInt(0,16);
    if( crc16 != qChecksum(QByteArray::fromHex(arrHex.left(16)).constData() , QByteArray::fromHex(arrHex.left(16)).length())){
        if(verboseMode)
            qDebug() << "crc16 HCS is not valid " << crc16 << arrHex.left(16)
                     << qChecksum(QByteArray::fromHex(arrHex.left(16)).constData() , QByteArray::fromHex(arrHex.left(16)).length());
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------------
bool DlmsProcessor::isItShortDLMSBreak(const quint8 &frameType, const QByteArray &lastSrcAddr, const QByteArray &meterMessH)
{
    if(frameType == HDLC_FRAME_UA || lastSrcAddr.isEmpty()){
        //81 80 06 - format id / group id / group len

        if(meterMessH.length() == 18 && meterMessH.startsWith("8180060501") && meterMessH.mid(12, 4) == "0601"){//81 80 06 05 01 83 06 01 4D
            bool ok;
            const quint8 tx = meterMessH.mid(10, 2).toUInt(&ok, 16);
            const quint8 rx = meterMessH.mid(16, 2).toUInt(&ok, 16);

            lastExchangeState.lastMeterIsShortDlms = (tx > 0 && rx > 0) ? (tx > rx ) : false;

            if(verboseMode)
                qDebug() << "lastExchangeState.lastMeterIsShortDlms=" << lastExchangeState.lastMeterIsShortDlms << tx << rx;
        }


        return true;
    }
    return false;
}
//----------------------------------------------------------------------------------
bool DlmsProcessor::checkPreparyCache(QByteArray &meterMessH, quint8 &errCode, int &obisCounter, int &payloadLen, int &dataTypeLen, DLMSExchangeState &lastExchangeState, int &forcedDataTypeLen)
{

    //E6 E7 00 - responce
    if(meterMessH.left(6).toUpper() != "E6E700"){
        if(verboseMode) qDebug() << "LLC bytes " << meterMessH.left(6);
        errCode = ERR_CHECK_AUTHORIZE;
        return false;
    }
    meterMessH = meterMessH.mid(6);//remove LLC    E6 E7 00 - LLC bytes

    int removeLen = 0;
    const quint8 cosemType = meterMessH.left(2).toUInt(0, 16); //C4

    QByteArray forcedPrefixH;

    if(cosemType == 0xC4){ //get.response   C4 03 81 06 || C4 01 81

        if(meterMessH.left(4).toUpper() == "C403"){
            obisCounter = meterMessH.mid(6,2).toInt(0, 16);
            removeLen = 8;
        }else{
            if(meterMessH.left(4).toUpper() == "C401" || meterMessH.left(4).toUpper() == "C402"){ //C4 01 81
                removeLen = 6;
            }
            //C4 02 81 01 00 00 00 01 00 45 <len> <data type 2 bytes>

            //C4 02 81 01 00 00 00 01 00 4A <len> <data type 1 byte>

            //load profile comes with
            //C4 02 81 00 00 00 00 01 00 5E 01   30
        }
        payloadLen = -1;//

        if(!lastExchangeState.dlmsFuckingChecksRemoveTypePrefixH.isEmpty() &&
                meterMessH.toUpper().startsWith(lastExchangeState.dlmsFuckingChecksRemoveTypePrefixH.toUpper())){
            //removeLen
            //obisCounter

            obisCounter = meterMessH.mid(lastExchangeState.dlmsFuckingChecksObisCounterPos,2).toInt(0, 16);
            removeLen = lastExchangeState.dlmsFuckingChecksRemoveLen;
            lastExchangeState.dlmsFuckingLastReceivedArr = QByteArray::fromHex(meterMessH);
            if(lastExchangeState.dlmsFuckingChecksForceDataLen > 0){
                dataTypeLen = lastExchangeState.dlmsFuckingChecksForceDataLen;
                forcedDataTypeLen = lastExchangeState.dlmsFuckingChecksForceDataLen;
            }

            if(!lastExchangeState.dlmsFukcingForcedDataPrefixH.isEmpty())
                forcedPrefixH = lastExchangeState.dlmsFukcingForcedDataPrefixH;

        }
//        dataprocessor.lastExchangeState.dlmsFuckingChecks.insert("DLMS_removeTypeLenAdd", 7);
//        dataprocessor.lastExchangeState.dlmsFuckingChecks.insert("DLMS_removeTypePrefixH", "C40281");

    }else{
        if(meterMessH.left(2 * 4).toUpper() == "C5018100"){
            errCode = ERR_WRITE_DONE;
            return true;
        }

        if(cosemType == 0xC0 || (lastExchangeState.lastMeterIsShortDlms && cosemType == 0x0C)){
            //0C 01 00
            obisCounter = meterMessH.mid(2,2).toUInt(0,16);
            removeLen =  (lastExchangeState.lastMeterIsShortDlms && cosemType == 0x0C) ? 4 : 3;
//                if(lastExchangeState.lastMeterIsShortDlms && cosemType == 0x0C)
//                    dataTypeLen = 2; //old version of protocol
            if(meterMessH.mid(4,2).toUInt(0, 16) != 0x0){
                if(verboseMode)
                    qDebug() << "erro messageIsValid " << meterMessH.left(8) << cosemType << obisCounter << payloadLen << dataTypeLen;
                errCode = ERR_CHECK_AUTHORIZE;
                return true;
            }
        }else{

            if(meterMessH.left(6).toUpper() == "D80101"){
                errCode = ERR_BAD_OBIS;
                return true;
            }

            //61 29 - AARE tag and length
            if(cosemType == 0x61)
                dataTypeLen = 2;//authorization

            payloadLen = meterMessH.mid(2,2).toUInt(0,16);
            removeLen = 4;
        }

    }


    if(verboseMode) qDebug() << "err calc len " << meterMessH.left(8) <<  obisCounter << payloadLen << dataTypeLen << cosemType << removeLen << lastExchangeState.lastMeterIsShortDlms;

    meterMessH = forcedPrefixH + meterMessH.mid(removeLen);//remove tag and len
    return true;
}

//----------------------------------------------------------------------------------

QVariantList DlmsProcessor::processCachedData(int &obisCounter, QByteArray &meterMessH, int &dataTypeLen, QList<QByteArray> &commandCodeH, bool &need2useBuffer, int &ob, QByteArray &topType, const int &forcedDataTypeLen)
{
    QVariantList listMeterMesageVar;

    ob = 0;
    for( ; ob < obisCounter; ob++){

//        if(obisCounter == 8)
//            qDebug() << "wait for fucking bug ";

        bool okc, okl;
        const quint16 datatype = meterMessH.left(dataTypeLen).toUInt(&okc, 16);

        int addLen = 0;
        quint32 len = meterMessH.mid(dataTypeLen,2 + addLen).toUInt(&okl, 16);

        if(len > 0x80 && len < 0x84){
            addLen = ((int)len - 0x80) * 2;
            len = meterMessH.mid(dataTypeLen + 2, addLen).toUInt(0, 16);
        }

        int lenFromLine = 2;
        const int altLen = DlmsHelper::datatype2len(datatype);

        QVariant readyVal;
        bool useReadyVal = false;
        bool isNotAll = false;

        if(altLen >= 0){
            len = (quint8)altLen;
            lenFromLine = 0;
            okl = true;
        }else{
            if(datatype == DLMS_DATA_TYPE_ARRAY){
                useReadyVal = true;
                readyVal = DlmsHelper::arr2map(meterMessH.mid(dataTypeLen), addLen, isNotAll, len, verboseMode, forcedDataTypeLen);
            }else{
                if(datatype == DLMS_DATA_TYPE_STRUCTURE){
                    useReadyVal = true;
                    readyVal = DlmsHelper::strct2map(meterMessH.mid(dataTypeLen), addLen, isNotAll, len, verboseMode, forcedDataTypeLen);
                }
            }
        }

        if(!okc || !okl){
            if(verboseMode) qDebug() << "err parse data !ok  " << okc << okl << (int)datatype << (int)len << dataTypeLen << meterMessH.left(10)  ;
            ob = -1;
//            if(meterMessH.left(4).toUpper() == "010B"){//it is processed before,
//                errCode = ERR_BAD_OBIS;
//                listMeterMesageVar.append(readyVal);
//                meterMessH = meterMessH.mid(4);
//               continue;
//            }
            break;
        }

        if(useReadyVal){
            listMeterMesageVar.append(readyVal);
        }else{

            QByteArray a = meterMessH.mid(dataTypeLen + lenFromLine, len * 2);
            if((quint32)a.length() != (len * 2)){
                if(verboseMode) qDebug() << "err parse data data.len() " << okc << okl << (int)datatype << (int)len << dataTypeLen << meterMessH.left(10) << a;
                ob = -1;
                break;
            }
            listMeterMesageVar.append(DlmsHelper::datatype2normal(datatype, a, verboseMode));

        }
        commandCodeH.append(meterMessH.left(dataTypeLen + lenFromLine + len * 2));


        if(topType.isEmpty())
            topType = meterMessH.left(dataTypeLen + lenFromLine + addLen);
        meterMessH = meterMessH.mid(dataTypeLen + addLen + lenFromLine + len * 2);
        if((datatype == 0xA1 || datatype == 0xA2 || datatype == 0xA3 || datatype == 0xBE) && !meterMessH.isEmpty() && dataTypeLen == 2){
            //authorization
            obisCounter++;
        }


        if(isNotAll){
            need2useBuffer = true;
            if(verboseMode)
                qDebug() << "exit for loop " << ob << obisCounter << listMeterMesageVar;
            break;
        }
    }

    return listMeterMesageVar;
}
//----------------------------------------------------------------------------------
void DlmsProcessor::topArrayChecks(const bool &hasByteA8, QByteArray &meterMessH, QByteArray &topType, QVariantList &listMeterMesageVar, bool &endOfRRframes, bool &need2useBuffer, int &obisCounter, int &ob)
{
    if(!topType.isEmpty() && listMeterMesageVar.size() == 1){
        if(listMeterMesageVar.first().type() == QVariant::Map  ){
            const quint32 len = listMeterMesageVar.first().toMap().size();

            const quint8 s = topType.mid(4,2).toUInt(0,16);
            int topTypeLenSize = topType.length() - 4;

            int midFrom = 4;
            if(s > 0x80){
                midFrom = 6;
                topTypeLenSize -= 2;
            }

            quint32 arrlen = topType.mid(midFrom).toUInt(0,16);
            if(verboseMode)
                qDebug() << "messageIsValid arrlen=" << arrlen << len << (arrlen - len) ;
            if(arrlen < len)
                arrlen = 0;
            else
                arrlen -= len;

            if(hasByteA8 && arrlen < 1)
                arrlen = 1;

            if(arrlen == 0){
                if(!listMeterMesageVar.isEmpty())
                    ob = obisCounter;
                need2useBuffer = false;
            }else{

                topType = topType.left(midFrom);
                topType.append(QByteArray::number(arrlen, 16).rightJustified(topTypeLenSize , '0' ));

                if(!need2useBuffer || meterMessH.isEmpty()){
                    meterMessH.prepend(topType);
                    topType.clear();
                }
                if(endOfRRframes)
                    endOfRRframes = false;
                need2useBuffer = true;
            }

        }
    }

}

//----------------------------------------------------------------------------------

QByteArray DlmsProcessor::crcCalcExt(const QByteArray &arrAddrHex, const quint8 &frameType, const quint8 &messageCounterRRR, const quint8 &messageCounterSSS, const QByteArray &arrMessage)
{
    QByteArray arrHeader("");

    lastExchangeState.lastHiLoHex = arrAddrHex;
    arrHeader.append(arrAddrHex); //meter (dest) addr
    arrHeader.append(lastExchangeState.sourceAddressH);// "03"); //source addr

    QByteArray byteFrameType;
    switch(frameType){
    case HDLC_FRAME_SNRM: byteFrameType = QByteArray::number(frameType, 16).rightJustified(2, '0'); break;

    case HDLC_FRAME_I:{

        const QBitArray rrr = ConvertAtype::uint8ToBitArray(messageCounterRRR);
        const QBitArray sss = ConvertAtype::uint8ToBitArray(messageCounterSSS);

        QBitArray bitArr = ConvertAtype::uint8ToBitArray(frameType);//0x10
        bitArr.setBit(4, true);

        for(int i = 0; i < 3; i++){
            bitArr.setBit(i+1, sss.at(i));
            bitArr.setBit(i+5, rrr.at(i));
        }

        byteFrameType = ConvertAtype::bitArrToByteArr(bitArr, true);

        break;}//RRR and SSS

    case HDLC_FRAME_RR:{

        const QBitArray rrr = ConvertAtype::uint8ToBitArray(messageCounterRRR);

        QBitArray bitArr = ConvertAtype::uint8ToBitArray(frameType);
        bitArr.setBit(4, true);

        for(int i = 0; i < 3; i++)
            bitArr.setBit(i+5, rrr.at(i));

        byteFrameType = ConvertAtype::bitArrToByteArr(bitArr, true);

        break;}

    default:{
        if(verboseMode)
            qDebug() << "unknown frameHdlc " << frameType;
        byteFrameType = QByteArray::number(frameType, 16); break;}

    }

    arrHeader.append(byteFrameType.rightJustified(2, '0'));// QByteArray::number(frameType, 16).rightJustified(2, '0') );


    QByteArray crc16h("");


    if(!arrMessage.isEmpty()) //authorize 2 -nd message
        crc16h = "0000";

    arrHeader.prepend( QByteArray::number(QByteArray::fromHex(arrHeader + crc16h + arrMessage ).length() + 4 , 16).rightJustified(2, '0') );
    arrHeader.prepend("A0");

    if(!arrMessage.isEmpty()){ //HCS розраховується тільки якщо є дані, в іншому випадку обходитись FCS
        crc16h = QByteArray::number( qChecksum(QByteArray::fromHex(arrHeader).constData(), QByteArray::fromHex(arrHeader).length()) , 16).rightJustified(4, '0');
        crc16h = crc16h.right(2) + crc16h.left(2);
    }

    //FCS
    const QByteArray crc16 = QByteArray::number( qChecksum(QByteArray::fromHex(arrHeader + crc16h + arrMessage).constData(), QByteArray::fromHex(arrHeader + crc16h + arrMessage).length()) , 16).rightJustified(4, '0');
    arrHeader = QByteArray::fromHex(arrHeader + crc16h + arrMessage + crc16.right(2) + crc16.left(2));

    if(verboseMode)
        qDebug() << "arrMessage=" << arrHeader.toHex();


    return QByteArray::fromHex("7E") + arrHeader + QByteArray::fromHex("7E");
}

//----------------------------------------------------------------------------------

QByteArray DlmsProcessor::crcCalc(const QByteArray &destSN, const quint8 &frameType, const quint8 &messageCounterRRR, const quint8 &messageCounterSSS, const QByteArray &arrMessage)
{

    QByteArray arrAddrHex(QByteArray::fromHex("00 01 FE FF"));

    if(true){// !destSN.isEmpty()){ //02092443
        //destSN = hhhh:llll (dec)
        bool okL;
        quint16 destLow = destSN.toUInt(&okL) + 1000;
        if(destSN.isEmpty()){
            destLow = 0x3FFF;
            okL = true;
        }
        if(!okL || destLow > 0x3FFF)
            return "";

        destLow = destLow << 1;
        destLow |= 1 << 0;

        QByteArray destLowArr = QByteArray::number(destLow, 16).rightJustified(4, '0');

        quint16 destLowLeft = destLowArr.left(2).toUInt(&okL, 16);
        destLowLeft = destLowLeft << 1;
        //logical meter addr = 0x0001 > 0x0002
        arrAddrHex = "0002" + QByteArray::number(destLowLeft, 16).rightJustified(2, '0') + destLowArr.right(2);
    }

    return crcCalcExt(arrAddrHex, frameType, messageCounterRRR, messageCounterSSS, arrMessage);

}

//----------------------------------------------------------------------------------

QByteArray DlmsProcessor::crcCalc(const QVariantHash &hashConstData, const quint8 &frameType, const quint8 &messageCounterRRR, const quint8 &messageCounterSSS, const QByteArray &arrMessage)
{
    return crcCalc(hashConstData.value("NI").toByteArray(), frameType, messageCounterRRR, messageCounterSSS, arrMessage);

}

//----------------------------------------------------------------------------------

QByteArray DlmsProcessor::crcCalcFrameI(const QVariantHash &hashConstData, const ObisList &obisList, const AttributeList &attributeList)
{
    return crcCalcFrameIarr(hashConstData, DlmsHelper::arrMessageXtend(lastExchangeState.lastObisList, obisList, attributeList, lastExchangeState.lastMeterIsShortDlms));

}

//----------------------------------------------------------------------------------

QByteArray DlmsProcessor::crcCalcFrameIarr(const QVariantHash &hashConstData, const QByteArray &arrMessageXtend)
{
    return crcCalc(hashConstData, HDLC_FRAME_I, lastExchangeState.messageCounterRRR, lastExchangeState.messageCounterSSS, arrMessageXtend);

}

//----------------------------------------------------------------------------------

QByteArray DlmsProcessor::crcCalcFrameRR(const QVariantHash &hashConstData)
{
    return crcCalc(hashConstData, HDLC_FRAME_RR, lastExchangeState.messageCounterRRR, lastExchangeState.messageCounterSSS, QByteArray(""));

}

//----------------------------------------------------------------------------------

bool DlmsProcessor::exitCozNAuth(const int &errCode, QVariantHash &hashTmpData)
{
    if(errCode == ERR_NO_AUTHORIZE || (errCode == ERR_CHECK_AUTHORIZE && hashTmpData.value("logined", false).toBool())){
        hashTmpData.insert("logined", false);
           lastExchangeState.lastMeterH.clear();
//        hashTmpData.insert(MeterPluginHelper::errWarnKey(error_counter, true), MeterPluginHelper::prettyMess(tr("Authorize error 0xFA"), MeterPluginHelper::prettyHexDump(meterMessH, commandCodeH, errCode), lastErrorStr, lastWarning, true));
        if(verboseMode) qDebug() << "need authrize " << lastExchangeState.messageCounterRRR << lastExchangeState.messageCounterSSS;

        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------

QVariantHash DlmsProcessor::fullLoadProfileEmptyValsExt(const QVariantHash &hashConstData, const QVariantHash &hashTmpData, const quint32 &pwrIntrvl, const QStringList &list4meterEnrg)
{
    QVariantHash hash;

    const QDateTime dtZero = hashConstData.value("pollDate_0").toDateTime();
    const QDateTime dtLast = hashConstData.value("pollDate").toDateTime();
    QDateTime dtStart = dtZero.toUTC();

    const QStringList list4pllEnrg = hashConstData.value("listEnrg").toStringList();
//    QStringList list4meterEnrg = DlmsGamaHelper::getSupportedEnrg(POLL_CODE_READ_POWER, version);


    QStringList listDate = hashTmpData.value("listDate").toStringList();

    for(int i = 0, jMax = list4pllEnrg.size(); i < 10000 && dtStart <= dtLast; i++, dtStart = dtStart.addSecs(pwrIntrvl * 60)){
         const QString strDt = dtStart.toString("yyyy_MM_dd_hh_mm");

         if(listDate.contains(strDt))
             continue;

         for(int j = 0; j < jMax; j++){

             const QString sttsstr = list4meterEnrg.contains(list4pllEnrg.at(j)) ? "-" : "!";


             hash.insert( QString("%1_%2").arg(strDt).arg(list4pllEnrg.at(j)), sttsstr);

         }
         listDate.append(strDt);
    }



    hash.insert("listDate", listDate);
    hash.insert("messFail", false);

    return hash;
}

//----------------------------------------------------------------------------------

void DlmsProcessor::preparyLoginedHashTmpData(QVariantHash &hashTmpData)
{
    hashTmpData.remove("DLMS_obis2scaller_ready"); //obis2scaller
    lastExchangeState.lastMeterH.clear();

    //these are from DLMS_obis2scaller_ready
    hashTmpData.remove("DLMS_enrgObisList");//reset values
    hashTmpData.remove("DLMS_enrgObisListIndx");
}

//----------------------------------------------------------------------------------

void DlmsProcessor::fullLogined(const QVariantList &meterMessVar, const quint8 &frameType, QVariantHash &hashTmpData)
{
    if(hashTmpData.value("DLMS_SNRM_ready", false).toBool()){//пароль
        if(frameType == HDLC_FRAME_AARE && !meterMessVar.isEmpty()){
            hashTmpData.insert("logined", true);
            hashTmpData.insert("messFail", false);
//                step = 0xFFFF;

        }
        hashTmpData.remove("DLMS_SNRM_ready");


    }else{
        if(frameType == HDLC_FRAME_UA){
            hashTmpData.insert("DLMS_SNRM_ready", true);
            hashTmpData.insert("messFail", false);
            //sometimes meter stop answering, so to prevent time wasting, detect it and stop
            hashTmpData.insert("DLMS_FRAME_UA_COUNTER",
                               hashTmpData.value("DLMS_FRAME_UA_COUNTER", 0).toInt() + 1);

            resetHDLCglobalVariables();

        }
    }
}

//----------------------------------------------------------------------------------
