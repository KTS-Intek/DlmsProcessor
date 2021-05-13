#include "dlmsprocessor.h"

#include "dlmshelper.h"


//----------------------------------------------------------------------------------

DlmsProcessor::DlmsProcessor(QObject *parent) : QObject(parent)
{
    verboseMode = false;

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
}

//----------------------------------------------------------------------------------

QByteArray DlmsProcessor::crcCalc(const QByteArray &destSN, const quint8 &frameType, const quint8 &messCounterRRR, const quint8 &messCounterSSS, const QByteArray &arrMess)
{
    QByteArray arrHeader("");

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

    lastExchangeState.lastHiLoHex = arrAddrHex;
    arrHeader.append(arrAddrHex); //meter (dest) addr
    arrHeader.append("03"); //source addr

    QByteArray byteFrameType;
    switch(frameType){
    case HDLC_FRAME_SNRM: byteFrameType = QByteArray::number(frameType, 16).rightJustified(2, '0'); break;

    case HDLC_FRAME_I:{

        const QBitArray rrr = ConvertAtype::uint8ToBitArray(messCounterRRR);
        const QBitArray sss = ConvertAtype::uint8ToBitArray(messCounterSSS);

        QBitArray bitArr = ConvertAtype::uint8ToBitArray(frameType);//0x10
        bitArr.setBit(4, true);

        for(int i = 0; i < 3; i++){
            bitArr.setBit(i+1, sss.at(i));
            bitArr.setBit(i+5, rrr.at(i));
        }

        byteFrameType = ConvertAtype::bitArrToByteArr(bitArr, true);

        break;}//RRR and SSS

    case HDLC_FRAME_RR:{

        const QBitArray rrr = ConvertAtype::uint8ToBitArray(messCounterRRR);

        QBitArray bitArr = ConvertAtype::uint8ToBitArray(frameType);
        bitArr.setBit(4, true);

        for(int i = 0; i < 3; i++)
            bitArr.setBit(i+5, rrr.at(i));

        byteFrameType = ConvertAtype::bitArrToByteArr(bitArr, true);

        break;}

    default:{
        qDebug() << "unknown frameHdlc " << frameType;
        byteFrameType = QByteArray::number(frameType, 16); break;}

    }

    arrHeader.append(byteFrameType.rightJustified(2, '0'));// QByteArray::number(frameType, 16).rightJustified(2, '0') );


    QByteArray crc16h("");


    if(!arrMess.isEmpty()) //authorize 2 -nd message
        crc16h = "0000";

    arrHeader.prepend( QByteArray::number(QByteArray::fromHex(arrHeader + crc16h + arrMess ).length() + 4 , 16).rightJustified(2, '0') );
    arrHeader.prepend("A0");

    if(!arrMess.isEmpty()){ //HCS розраховується тільки якщо є дані, в іншому випадку обходитись FCS
        crc16h = QByteArray::number( qChecksum(QByteArray::fromHex(arrHeader).constData(), QByteArray::fromHex(arrHeader).length()) , 16).rightJustified(4, '0');
        crc16h = crc16h.right(2) + crc16h.left(2);
    }

    //FCS
    const QByteArray crc16 = QByteArray::number( qChecksum(QByteArray::fromHex(arrHeader + crc16h + arrMess).constData(), QByteArray::fromHex(arrHeader + crc16h + arrMess).length()) , 16).rightJustified(4, '0');
    arrHeader = QByteArray::fromHex(arrHeader + crc16h + arrMess + crc16.right(2) + crc16.left(2));

    if(verboseMode)
        qDebug() << "arrMess=" << arrHeader.toHex();


    return QByteArray::fromHex("7E") + arrHeader + QByteArray::fromHex("7E");
}

//----------------------------------------------------------------------------------

QByteArray DlmsProcessor::crcCalc(const QVariantHash &hashConstData, const quint8 &frameType, const quint8 &messCounterRRR, const quint8 &messCounterSSS, const QByteArray &arrMess)
{
    return crcCalc(hashConstData.value("NI").toByteArray(), frameType, messCounterRRR, messCounterSSS, arrMess);

}

//----------------------------------------------------------------------------------

QByteArray DlmsProcessor::crcCalcFrameI(const QVariantHash &hashConstData, const ObisList &obisList, const AttributeList &attributeList)
{
    return crcCalcFrameIarr(hashConstData, DlmsHelper::arrMessXtend(lastExchangeState.lastObisList, obisList, attributeList, lastExchangeState.lastMeterIsShortDlms));

}

//----------------------------------------------------------------------------------

QByteArray DlmsProcessor::crcCalcFrameIarr(const QVariantHash &hashConstData, const QByteArray &arrMessXtend)
{
    return crcCalc(hashConstData, HDLC_FRAME_I, lastExchangeState.messageCounterRRR, lastExchangeState.messageCounterSSS, arrMessXtend);

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

QVariantHash DlmsProcessor::fullPowerEmptyValsExt(const QVariantHash &hashConstData, const QVariantHash &hashTmpData, const quint32 &pwrIntrvl, const QStringList &list4meterEnrg)
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
