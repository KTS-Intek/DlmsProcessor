#ifndef GLOBAL_DLMS_DEFINES_H
#define GLOBAL_DLMS_DEFINES_H


//defaults
#define DEF_TARIFF_NUMB     3
#define DEF_THREE_PHASE     true
#define DEF_ONLY_ACTIVE     false

#define HDLC_FRAME_SNRM     0x93
#define HDLC_FRAME_UA       0x73


#define HDLC_FRAME_RR       0x01
#define HDLC_FRAME_I        0x10


//#define HDLC_FRAME_DM       0x1F

//#define HDLC_FRAME_DISC     0x53
//#define HDLC_FRAME_AARQ     0x10
#define HDLC_FRAME_AARE     0x30

//#define HDLC_FRAME_DLMS_SN  0x32
//#define HDLC_FRAME_DLMS_VR  0x54
//#define HDLC_FRAME_DLMS_DT  0xBA


#define ERR_ALL_GOOD            0x00
#define ERR_BAD_PASSWORD        0x01
#define ERR_BAD_PASSWORD2       0x02
#define ERR_READ_WRITE          0x03
#define ERR_NO_DATA_NIK         0x04
#define ERR_BAD_OBIS            0x09
#define ERR_DATA_OUT_OF_RANGE   0x0D
#define ERR_DATA_BUSY           0x0F
#define ERR_NO_AUTHORIZE        0xFA
#define ERR_UNKNOWN_ERR         0xFF

#define ERR_CHECK_AUTHORIZE     0x55
#define ERR_WRITE_DONE          0x56



#define DLMS_CLASS_ID_DATA                      0x1//v0 4.3.1       class_id = 1
#define DLMS_CLASS_ID_REGISTER                  0x3//v0 4.3.2       class_id = 3
#define DLMS_CLASS_ID_EXTENDED_REGISTER         0x4//v0 4.3.3       class_id = 4
#define DLMS_CLASS_ID_DEMAND_REGISTER           0x5//v0 4.3.4       class_id = 5
#define DLMS_CLASS_ID_REGISTER_ACTIVATION       0x6//v0 4.3.5       class_id = 6
#define DLMS_CLASS_ID_PROFILE_GENERIC           0x7//v1 4.3.6       class_id = 7
#define DLMS_CLASS_ID_UTILITY_TABLES            0x1A//v0 4.3.7      class_id = 26
#define DLMS_CLASS_ID_REGISTER_TABLE            0x3D//v0 4.3.8      class_id = 61
#define DLMS_CLASS_ID_STATUS_MAPPING            0x3F//v0 4.3.9      class_id = 63
#define DLMS_CLASS_ID_COMPACT_DATA              0x3E//v0 4.3.10.1   class_id = 62
#define DLMS_CLASS_ID_ASSOCIATION_SN            0x0C//v4 4.4.3      class_id = 12
#define DLMS_CLASS_ID_ASSOCIATION_LN            0x0F//v3 4.4.4      class_id = 15
#define DLMS_CLASS_ID_SAP_ASSIGNMENT            0x11//v0 4.4.5      class_id = 17
#define DLMS_CLASS_ID_IMAGE_TRANSFER            0x12//v0 4.4.6.3    class_id = 18

#define DLMS_CLASS_ID_SECURITY_SETUP            0x40//v1 4.4.7      class_id = 64
#define DLMS_CLASS_ID_PUSH_SETUP                0x28//v0 4.4.8.2    class_id = 40
#define DLMS_CLASS_ID_DATA_PROTECTION           0x1E//v0 4.4.9.2    class_id = 30

#define DLMS_CLASS_ID_CLOCK                     0x08//v0 4.5.1      class_id = 8
#define DLMS_CLASS_ID_SCRIPT_TABLE              0x09//v0 4.5.2      class_id = 9
#define DLMS_CLASS_ID_SCHEDULE                  0x0A//v0 4.5.3      class_id = 10
#define DLMS_CLASS_ID_SPECIAL_DAYS_TABLE        0x0B//v0 4.5.4      class_id = 11
#define DLMS_CLASS_ID_ACTIVITY_CALENDAR         0x14//v0 4.5.5      class_id = 20
#define DLMS_CLASS_ID_REGISTER_MONITOR          0x15//v0 4.5.6      class_id = 21
#define DLMS_CLASS_ID_SINGLE_ACTION_SCHEDULE    0x16//v0 4.5.7      class_id = 22

#define DLMS_CLASS_ID_DISCONNECT_CONTROL        0x46//v0 4.5.8      class_id = 70
#define DLMS_CLASS_ID_LIMITER                   0x47//v0 4.5.9      class_id = 71
#define DLMS_CLASS_ID_PARAMETER_MONITOR         0x41//v0 4.5.10     class_id = 65

#define DLMS_CLASS_ID_SENSOR_MANAGER            0x43//v0 4.5.11.2   class_id = 67
#define DLMS_CLASS_ID_ARBITRATOR                0x44//v0 4.5.12.2   class_id = 68
#define DLMS_CLASS_ID_ACCOUNT                   0x6F//v0 4.6.2      class_id = 111
#define DLMS_CLASS_ID_IEC_LOCAL_PORT_SETUP      0x13//v1 4.7.1      class_id = 19
#define DLMS_CLASS_ID_IEC_HDLC_SETUP            0x15//v1 4.7.2      class_id = 23
#define DLMS_CLASS_ID_IEC_TWISTED_PAIR          0x16//v1 4.7.3      class_id = 24
#define DLMS_CLASS_ID_MODEM_CONFIGURATION       0x1B//v1 4.7.4      class_id = 27
#define DLMS_CLASS_ID_AUTO_ANSWER               0x1C//v2 4.7.5      class_id = 28
#define DLMS_CLASS_ID_AUTO_CONNECT              0x1D//v2 4.7.6      class_id = 29
#define DLMS_CLASS_ID_GPRS_MODEM_SETUP          0x2D//v1 4.7.7      class_id = 45
#define DLMS_CLASS_ID_GSM_DIAGNOSTIC            0x2F//v0 4.7.8      class_id = 47
//M_BUS...TCP...


#define DLMS_DATA_TYPE_NULL_DATA        0x0
#define DLMS_DATA_TYPE_BOOLEAN          0x3 //TRUE OR FALSE
#define DLMS_DATA_TYPE_BIT_STRING       0x4 //An ordered sequence of boolean values
#define DLMS_DATA_TYPE_DOUBLE_LONG      0x5 //int32 -2 147 483 648...2 147 483 647
#define DLMS_DATA_TYPE_DOUBLE_LONG_UNS  0x6 //uint32 0...4 294 967 295

#define DLMS_DATA_TYPE_OCTET_STRING     0x9 //An ordered sequence of octets (8 bit bytes)
#define DLMS_DATA_TYPE_VISIBLE_STRING   0x0A //An ordered sequence of ASCII characters
#define DLMS_DATA_TYPE_UTF_STRING       0x0C //An ordered sequence of characters encoded as UTF-8
#define DLMS_DATA_TYPE_BCD              0x0D //binary coded decimal
#define DLMS_DATA_TYPE_INTEGER          0x0F //int8
#define DLMS_DATA_TYPE_LONG             0x10 //int16
#define DLMS_DATA_TYPE_UNSIGNED         0x11 //uint8
#define DLMS_DATA_TYPE_LONG_UNSIGNED    0x12 //uint16
#define DLMS_DATA_TYPE_LONG64           0x14 //int64
#define DLMS_DATA_TYPE_LONG64_UNSIGNED  0x15 //uint64
#define DLMS_DATA_TYPE_ENUM             0x16 //enum 0...255
#define DLMS_DATA_TYPE_FLOAT32          0x17 //OCTET STRING (SIZE(4))
#define DLMS_DATA_TYPE_FLOAT64          0x18 //OCTET STRING (SIZE(8))
#define DLMS_DATA_TYPE_DATE_TIME        0x19 //OCTET STRING (SIZE(12))
#define DLMS_DATA_TYPE_DATE             0x1A //OCTET STRING (SIZE(5))
#define DLMS_DATA_TYPE_TIME             0x1B //OCTET STRING (SIZE(4))

#define DLMS_DATA_FUCKING_UNKDATA       0x010B
#define DLMS_DATA_RELAY_FCKN_OK         0x0100

#define DLMS_DATA_TYPE_ARRAY            0x01 //???
#define DLMS_DATA_TYPE_STRUCTURE        0x02
#define DLMS_DATA_TYPE_COMPACT_ARRAY    0x13

//#define DLMS_UNIT_A


#define CMD_PING                                0x0
#define CMD_SEND_PSSWD                          0x1



#define CMD_GSET_DATETIME                       0x0000010000FF// 0000010000FF //class_id: 8, attr: 2


#define CMD_GET_DATA_STTS                       0x0000600A07FF
#define CMD_GET_DATA_STTS_SN                    0x0100603E01FF

#define CMD_GSET_METER_NUMBER                   0x00002A0000FF// 000060010400 //class_id: 3, attr: 2
#define CMD_GET_FIRMWARE_VERSION                0x0000600101FF //000060010300
#define CMD_GET_MODIFICATION                    0x0000600102FF //000060010300

#define CMD_SET_METER_ADDR_HI_LO                0x000016000001

#define CMD_GSET_DST_ARRAY                      0x000065000001


#define CMD_GET_LOAD_PROFILE                    0x0100630100FF//class_id: 7, attr: 3 - struct, 4 - interval, 5 - ?, 6 - ?, 7 - cells in use , 8 - total cells
#define CMD_GET_LOAD_PROFILE_2                  0x0100630200FF//class_id: 7, attr: 3 - struct, 4 - interval, 5 - ?, 6 - ?, 7 - cells in use , 8 - total cells

///short name load Profile
#define CMD_GET_LOAD_PROFILE_DATA_ARR_SN        0xC008   //- Short Name Load Profile
#define CMD_GET_LOAD_PROFILE_CAPT_OBJ_SN        0xC010   //
#define CMD_GET_LOAD_PROFILE_CAPT_PER_SN        0xC018  //in seconds   must be 30 hvlyn
#define CMD_GET_LOAD_PROFILE_SORT_MET_SN        0xC020  //sort method
#define CMD_GET_LOAD_PROFILE_SORT_OBJ_SN        0xC028  //sort object
#define CMD_GET_LOAD_PROFILE_USED_ENT_SN        0xC030  //used count
#define CMD_GET_LOAD_PROFILE_PROF_ENT_SN        0xC038 //total count


#define CMD_GET_PWR_ACTIVE_SCLR_UNT_SN          0x3018    //Load |P| scale & enum
#define CMD_GET_PWR_ACTIVE_IMPORT_SCLR_UNT_SN   0x3118   //Load P+ scale & enum
#define CMD_GET_PWR_ACTIVE_EXPORT_SCLR_UNT_SN   0x3218   // Load P- scale & enum
#define CMD_GET_PWR_REACTIVE_RIMPORT_SCLR_UNT_SN 0x3318  //Load Q+ scale & enum
#define CMD_GET_PWR_REACTIVE_REXPORT_SCLR_UNT_SN 0x3418 //  Load Q- scale & enum
//35 18   Load R1 scale & enum
//36 18   Load R2 scale & enum
//37 18   Load R3 scale & enum
//38 18   Load R4 scale & enum



#define CMD_GET_BILLING_PROFILE                 0x0000620100FF//class_id: 7, attr: 3 - struct, 4 - interval, 5 - ?, 6 - ?, 7 - cells in use , 8 - total cells
#define CMD_GET_BILLING_PROFILE_STTS            0x0100603E03FF//

#define CMD_GET_BILLING_PROF_READ_ARC_SN        0xC108// - Billing Profile Archive
#define CMD_GET_BILLING_PROF_CAPT_OBJ_SN        0xC110 //- Billing Profile Capture Objects
#define CMD_GET_BILLING_PROF_CAPT_PER_SN        0xC118// - Billing Profile Capture Period
#define CMD_GET_BILLING_PROF_SORT_MET_SN        0xC120// - Billing Profile Sort Method
#define CMD_GET_BILLING_PROF_SORT_OBJ_SN        0xC128// - Billing Profile Sort Object
#define CMD_GET_BILLING_PROF_ENTR_USE_SN        0xC130 // - Billing Profile entries in use
#define CMD_GET_BILLING_PROF_ENTR_CNT_SN        0xC138// - Billing Profile Profile entries //total count


#define CMD_GET_EV_STANDARD                     0x0000636200FF //99.98.0
#define CMD_GET_EV_FRAUD_DETECTION              0x0000636201FF //99.98.1
#define CMD_GET_EV_FIRMWARE_UPDATE              0x0000636204FF //99.98.4
#define CMD_GET_EV_POWER_QUALITY                0x0000636205FF //99.98.5
#define CMD_GET_EV_COMMUNICATION_IFACE          0x0000636207FF //99.98.7
#define CMD_GET_EV_CLOCK                        0x0000636208FF //99.98.8
#define CMD_GET_EV_POWER_FAILURE                0x0000636209FF //99.98.9




#define CMD_GET_EV_POWER_FAILURE_SN             0xC200 // 99.97.0  0x0000636209FF //99.98.9  power failure event log
#define CMD_GET_EV_CHANGE_IN_PHASES_SN          0xC300 // 99.98.11  change in number of phases event log
#define CMD_GET_EV_OVER_VOLTAGE_SN              0xCC00 // 99.98.12 over-voltage event log
#define CMD_GET_EV_UNDER_VOLTAGE_SN             0xCD00 // 99.98.13 under voltage event log
#define CMD_GET_EV_POWEROVERLIMIT_SN            0xCE00 // 99.98.20 power over limit
#define CMD_GET_EV_REVERSECURRENT_SN            0xCA00 // 99.98.21 reverse current
#define CMD_GET_EV_OVERCURRENT_SN               0xCB00 // 99.98.22 over current
#define CMD_GET_EV_MAGNETICFIELD_SN             0xC600 // 99.98.30 magnetic field influence log
#define CMD_GET_EV_CASEOPENED_SN                0xC700 // 99.98.31 case opened
#define CMD_GET_EV_TERMINALOPENED_SN            0xC900 // 99.98.32 terminal cover opened
#define CMD_GET_EV_CLOCK_SN                     0xC800 //   0x0000636208FF //99.98.8
#define CMD_GET_EV_PARAMETRIZATION_SN           0xC500 // 99.98.41 parametrization log
#define CMD_GET_EV_ERRORLOG_SN                  0xC400 //  99.98.50 error event log

#define CMD_GET_EV_ENTRIES_IN_USE_ADDED_SN      0x30 //  add to obis code to get entries in use
#define CMD_GET_EV_EVENTS_ADDED_SN              0x08 //  add to obis code to get events, do not forget to add dt object


#define CMD_GET_ACTIVE_TARIFF_NUMBER            0x0000640000FF//class_id: 3, attr: 2

//short name
#define CMD_GSET_METER_NUMBER_SN        0x7008
#define CMD_GET_FIRMWARE_VERSION_SN     0x7108
#define CMD_GET_MODIFICATION_SN         0x7208
#define CMD_GSET_DATETIME_SN            0x6808
#define CMD_GSET_DATETIME_DSTFROM_SN    0x6820
#define CMD_GSET_DATETIME_DSTTO_SN      0x6828
#define CMD_GSET_DATETIME_DEVIAT_SN     0x6830
#define CMD_GSET_DATETIME_DSTEN_SN      0x6838


//Total Energy   Поточні //class_id: 3, attr: 2

//|A|
#define CMD_GET_ACTIVE_SUMM                     0x01000F0800FF
#define CMD_GET_ACTIVE_T1                       0x01000F0801FF
#define CMD_GET_ACTIVE_T2                       0x01000F0802FF
#define CMD_GET_ACTIVE_T3                       0x01000F0803FF
#define CMD_GET_ACTIVE_T4                       0x01000F0804FF

///short name
#define CMD_GET_ACTIVE_SUMM_SN                  0x0008
#define CMD_GET_ACTIVE_T1_SN                    0x0020
#define CMD_GET_ACTIVE_T2_SN                    0x0038
#define CMD_GET_ACTIVE_T3_SN                    0x0050
#define CMD_GET_ACTIVE_T4_SN                    0x0068



//A+
#define CMD_GET_ACTIVE_IMPORT_SUMM              0x0100010800FF
#define CMD_GET_ACTIVE_IMPORT_T1                0x0100010801FF
#define CMD_GET_ACTIVE_IMPORT_T2                0x0100010802FF
#define CMD_GET_ACTIVE_IMPORT_T3                0x0100010803FF
#define CMD_GET_ACTIVE_IMPORT_T4                0x0100010804FF

///short name
#define CMD_GET_ACTIVE_IMPORT_SUMM_SN           0x0108
#define CMD_GET_ACTIVE_IMPORT_T1_SN             0x0120
#define CMD_GET_ACTIVE_IMPORT_T2_SN             0x0138
#define CMD_GET_ACTIVE_IMPORT_T3_SN             0x0150
#define CMD_GET_ACTIVE_IMPORT_T4_SN             0x0168


//A-
#define CMD_GET_ACTIVE_EXPORT_SUMM              0x0100020800FF
#define CMD_GET_ACTIVE_EXPORT_T1                0x0100020801FF
#define CMD_GET_ACTIVE_EXPORT_T2                0x0100020802FF
#define CMD_GET_ACTIVE_EXPORT_T3                0x0100020803FF
#define CMD_GET_ACTIVE_EXPORT_T4                0x0100020804FF

///short name
#define CMD_GET_ACTIVE_EXPORT_SUMM_SN           0x0208
#define CMD_GET_ACTIVE_EXPORT_T1_SN             0x0220
#define CMD_GET_ACTIVE_EXPORT_T2_SN             0x0238
#define CMD_GET_ACTIVE_EXPORT_T3_SN             0x0250
#define CMD_GET_ACTIVE_EXPORT_T4_SN             0x0268






//R+Ax, it is only  R+ !!!
#define CMD_GET_REACTIVE_RIMPORT_SUMM          0x0100030800FF
#define CMD_GET_REACTIVE_RIMPORT_T1            0x0100030801FF
#define CMD_GET_REACTIVE_RIMPORT_T2            0x0100030802FF
#define CMD_GET_REACTIVE_RIMPORT_T3            0x0100030803FF
#define CMD_GET_REACTIVE_RIMPORT_T4            0x0100030804FF

///short name
#define CMD_GET_REACTIVE_RIMPORT_SUMM_SN       0x0308
#define CMD_GET_REACTIVE_RIMPORT_T1_SN         0x0320
#define CMD_GET_REACTIVE_RIMPORT_T2_SN         0x0338
#define CMD_GET_REACTIVE_RIMPORT_T3_SN         0x0350
#define CMD_GET_REACTIVE_RIMPORT_T4_SN         0x0368


//R-Ax  , it is only R- !!!
#define CMD_GET_REACTIVE_REXPORT_SUMM          0x0100040800FF
#define CMD_GET_REACTIVE_REXPORT_T1            0x0100040801FF
#define CMD_GET_REACTIVE_REXPORT_T2            0x0100040802FF
#define CMD_GET_REACTIVE_REXPORT_T3            0x0100040803FF
#define CMD_GET_REACTIVE_REXPORT_T4            0x0100040804FF

///short name
#define CMD_GET_REACTIVE_REXPORT_SUMM_SN       0x0408
#define CMD_GET_REACTIVE_REXPORT_T1_SN         0x0420
#define CMD_GET_REACTIVE_REXPORT_T2_SN         0x0438
#define CMD_GET_REACTIVE_REXPORT_T3_SN         0x0450
#define CMD_GET_REACTIVE_REXPORT_T4_SN         0x0468


//R+A+ or R1
#define CMD_GET_REACTIVE_R1_SUMM                0x0100050800FF
#define CMD_GET_REACTIVE_R1_T1                  0x0100050801FF
#define CMD_GET_REACTIVE_R1_T2                  0x0100050802FF
#define CMD_GET_REACTIVE_R1_T3                  0x0100050803FF
#define CMD_GET_REACTIVE_R1_T4                  0x0100050804FF

///short name
#define CMD_GET_REACTIVE_R1_SUMM_SN             0x0508
#define CMD_GET_REACTIVE_R1_T1_SN               0x0520
#define CMD_GET_REACTIVE_R1_T2_SN               0x0538
#define CMD_GET_REACTIVE_R1_T3_SN               0x0550
#define CMD_GET_REACTIVE_R1_T4_SN               0x0568

//R+A- or R2
#define CMD_GET_REACTIVE_R2_SUMM                0x0100060800FF
#define CMD_GET_REACTIVE_R2_T1                  0x0100060801FF
#define CMD_GET_REACTIVE_R2_T2                  0x0100060802FF
#define CMD_GET_REACTIVE_R2_T3                  0x0100060803FF
#define CMD_GET_REACTIVE_R2_T4                  0x0100060804FF

///short name
#define CMD_GET_REACTIVE_R2_SUMM_SN             0x0608
#define CMD_GET_REACTIVE_R2_T1_SN               0x0620
#define CMD_GET_REACTIVE_R2_T2_SN               0x0638
#define CMD_GET_REACTIVE_R2_T3_SN               0x0650
#define CMD_GET_REACTIVE_R2_T4_SN               0x0668

//R-A-   R3
#define CMD_GET_REACTIVE_R3_SUMM                0x0100070800FF
#define CMD_GET_REACTIVE_R3_T1                  0x0100070801FF
#define CMD_GET_REACTIVE_R3_T2                  0x0100070802FF
#define CMD_GET_REACTIVE_R3_T3                  0x0100070803FF
#define CMD_GET_REACTIVE_R3_T4                  0x0100070804FF

///short name
#define CMD_GET_REACTIVE_R3_SUMM_SN             0x0708
#define CMD_GET_REACTIVE_R3_T1_SN               0x0720
#define CMD_GET_REACTIVE_R3_T2_SN               0x0738
#define CMD_GET_REACTIVE_R3_T3_SN               0x0750
#define CMD_GET_REACTIVE_R3_T4_SN               0x0768


//R-A+    R4
#define CMD_GET_REACTIVE_R4_SUMM                0x0100080800FF
#define CMD_GET_REACTIVE_R4_T1                  0x0100080801FF
#define CMD_GET_REACTIVE_R4_T2                  0x0100080802FF
#define CMD_GET_REACTIVE_R4_T3                  0x0100080803FF
#define CMD_GET_REACTIVE_R4_T4                  0x0100080804FF

///short name
#define CMD_GET_REACTIVE_R4_SUMM_SN             0x0808
#define CMD_GET_REACTIVE_R4_T1_SN               0x0820
#define CMD_GET_REACTIVE_R4_T2_SN               0x0838
#define CMD_GET_REACTIVE_R4_T3_SN               0x0850
#define CMD_GET_REACTIVE_R4_T4_SN               0x0868


////EOD //class_id: 3, attr: 2
////A+
//#define CMD_GET_EOD_ACTIVE_IMPORT_SUMM              0x0100010800
//#define CMD_GET_EOD_ACTIVE_IMPORT_T1                0x0100010801
//#define CMD_GET_EOD_ACTIVE_IMPORT_T2                0x0100010802
//#define CMD_GET_EOD_ACTIVE_IMPORT_T3                0x0100010803
//#define CMD_GET_EOD_ACTIVE_IMPORT_T4                0x0100010804


//На кінець місяця //class_id: 3, attr: 2
//A+
#define CMD_GET_EOM_ACTIVE_IMPORT_SUMM          0x0100010900//xx, xx = 0-15 month ago
#define CMD_GET_EOM_ACTIVE_IMPORT_T1            0x0100010901//xx, xx = 0-15 month ago
#define CMD_GET_EOM_ACTIVE_IMPORT_T2            0x0100010902//xx, xx = 0-15 month ago
#define CMD_GET_EOM_ACTIVE_IMPORT_T3            0x0100010903//xx, xx = 0-15 month ago
#define CMD_GET_EOM_ACTIVE_IMPORT_T4            0x0100010904//xx, xx = 0-15 month ago
//A-
#define CMD_GET_EOM_ACTIVE_EXPORT_SUMM          0x0100020900//xx, xx = 0-15 month ago
#define CMD_GET_EOM_ACTIVE_EXPORT_T1            0x0100020901//xx, xx = 0-15 month ago
#define CMD_GET_EOM_ACTIVE_EXPORT_T2            0x0100020902//xx, xx = 0-15 month ago
#define CMD_GET_EOM_ACTIVE_EXPORT_T3            0x0100020903//xx, xx = 0-15 month ago
#define CMD_GET_EOM_ACTIVE_EXPORT_T4            0x0100020904//xx, xx = 0-15 month ago
//R+Ax+
#define CMD_GET_EOM_REACTIVE_AXIMPORT_SUMM      0x0100030900//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AXIMPORT_T1        0x0100030901//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AXIMPORT_T2        0x0100030902//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AXIMPORT_T3        0x0100030903//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AXIMPORT_T4        0x0100030904//xx, xx = 0-15 month ago

//R+Ay-
#define CMD_GET_EOM_REACTIVE_AYIMPORT_SUMM      0x0100070900//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AYIMPORT_T1        0x0100070901//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AYIMPORT_T2        0x0100070902//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AYIMPORT_T3        0x0100070903//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AYIMPORT_T4        0x0100070904//xx, xx = 0-15 month ago

//R-Ax+
#define CMD_GET_EOM_REACTIVE_AXEXPORT_SUMM      0x0100040900//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AXEXPORT_T1        0x0100040901//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AXEXPORT_T2        0x0100040902//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AXEXPORT_T3        0x0100040903//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AXEXPORT_T4        0x0100040904//xx, xx = 0-15 month ago
//R-Ay-
#define CMD_GET_EOM_REACTIVE_AYEXPORT_SUMM      0x0100080900//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AYEXPORT_T1        0x0100080901//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AYEXPORT_T2        0x0100080902//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AYEXPORT_T3        0x0100080903//xx, xx = 0-15 month ago
#define CMD_GET_EOM_REACTIVE_AYEXPORT_T4        0x0100080904//xx, xx = 0-15 month ago

//На кінець доби //class_id: 3, attr: 2
//A+
#define CMD_GET_EOD_ACTIVE_IMPORT_SUMM          0x0100010A0000//xx, xx = 1-120 days ago
#define CMD_GET_EOD_ACTIVE_IMPORT_T1            0x0100010A0100//xx, xx = 1-120 days ago
#define CMD_GET_EOD_ACTIVE_IMPORT_T2            0x0100010A0200//xx, xx = 1-120 days ago
#define CMD_GET_EOD_ACTIVE_IMPORT_T3            0x0100010A0300//xx, xx = 1-120 days ago
#define CMD_GET_EOD_ACTIVE_IMPORT_T4            0x0100010A0400//xx, xx = 1-120 days ago
//A-
#define CMD_GET_EOD_ACTIVE_EXPORT_SUMM          0x0100020A00//xx, xx = 1-120 days ago
#define CMD_GET_EOD_ACTIVE_EXPORT_T1            0x0100020A01//xx, xx = 1-120 days ago
#define CMD_GET_EOD_ACTIVE_EXPORT_T2            0x0100020A02//xx, xx = 1-120 days ago
#define CMD_GET_EOD_ACTIVE_EXPORT_T3            0x0100020A03//xx, xx = 1-120 days ago
#define CMD_GET_EOD_ACTIVE_EXPORT_T4            0x0100020A04//xx, xx = 1-120 days ago
//R+Ax
#define CMD_GET_EOD_REACTIVE_AXIMPORT_SUMM      0x0100030A00//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AXIMPORT_T1        0x0100030A01//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AXIMPORT_T2        0x0100030A02//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AXIMPORT_T3        0x0100030A03//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AXIMPORT_T4        0x0100030A04//xx, xx = 1-120 days ago
//R+Ay
#define CMD_GET_EOD_REACTIVE_AYIMPORT_SUMM      0x0100070A00//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AYIMPORT_T1        0x0100070A01//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AYIMPORT_T2        0x0100070A02//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AYIMPORT_T3        0x0100070A03//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AYIMPORT_T4        0x0100070A04//xx, xx = 1-120 days ago
//R-Ax
#define CMD_GET_EOD_REACTIVE_AXEXPORT_SUMM      0x0100040A00//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AXEXPORT_T1        0x0100040A01//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AXEXPORT_T2        0x0100040A02//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AXEXPORT_T3        0x0100040A03//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AXEXPORT_T4        0x0100040A04//xx, xx = 1-120 days ago
//R-Ay
#define CMD_GET_EOD_REACTIVE_AYEXPORT_SUMM      0x0100080A00//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AYEXPORT_T1        0x0100080A01//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AYEXPORT_T2        0x0100080A02//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AYEXPORT_T3        0x0100080A03//xx, xx = 1-120 days ago
#define CMD_GET_EOD_REACTIVE_AYEXPORT_T4        0x0100080A04//xx, xx = 1-120 days ago



//Зріз потужності за 30 хв //class_id:
#define CMD_GET_PWR_ACTIVE_SUMM                 0x01000F0400FF
#define CMD_GET_PWR_ACTIVE_SUMM_SN              0x01000F0500FF

//A+
#define CMD_GET_PWR_ACTIVE_IMPORT_SUMM          0x0100010400FF
#define CMD_GET_PWR_ACTIVE_IMPORT_SUMM_SN       0x0100010500FF

//A-
#define CMD_GET_PWR_ACTIVE_EXPORT_SUMM          0x0100020400FF
#define CMD_GET_PWR_ACTIVE_EXPORT_SUMM_SN       0x0100020500FF


#define CMD_GET_PWR_REACTIVE_RIMPORT_SUMM_SN    0x0100030500FF
#define CMD_GET_PWR_REACTIVE_REXPORT_SUMM_SN    0x0100040500FF

//R+Ax
#define CMD_GET_PWR_REACTIVE_AXIMPORT_SUMM      0x0100030400FF

//R+Ay
#define CMD_GET_PWR_REACTIVE_AYIMPORT_SUMM      0x0100040400FF


//R-Rx
#define CMD_GET_PWR_REACTIVE_AXEXPORT_SUMM      0x0100050400FF

//R-Ry
#define CMD_GET_PWR_REACTIVE_AYEXPORT_SUMM      0x0100060400FF


//25 hour half hour demand
#define CMD_GET_PWR_25_HALF_HOUR_DEMAND_FRST    0x000060010615//QDateTime(2016-10-30 00:00:00.000 UTC Qt::TimeSpec(UTC)))  3:00 EEST
#define CMD_GET_PWR_25_HALF_HOUR_DEMAND_SCND    0x000060010616//QDateTime(2016-10-30 00:30:00.000 UTC Qt::TimeSpec(UTC)))  3:30 EEST


//Миттєві значення calss_id: 3, attr: 2
//#define CMD_GET_ACTIVE_POWER                    0x010001070000//P  visible string xxxxx,xxx kWt
//#define CMD_GET_REACTIVE_POWER                  0x010003070000//Q  visible string xxxxx,xxx kVr
//#define CMD_GET_I_PHS_A                         0x01001F070000//IA visible string xxxxx,xxx A
//#define CMD_GET_I_PHS_B                         0x010033070000//IB visible string xxxxx,xxx A
//#define CMD_GET_I_PHS_C                         0x010047070000//IC visible string xxxxx,xxx A
//#define CMD_GET_U_PHS_A                         0x010020070000//UA visible string xxxxx,xxx V
//#define CMD_GET_U_PHS_B                         0x010034070000//UB visible string xxxxx,xxx V
//#define CMD_GET_U_PHS_C                         0x010048070000//UC visible string xxxxx,xxx V
//#define CMD_GET_COS_FI_PHS_A                    0x010021070000//cos_fA visible string xxxxx,xxx
//#define CMD_GET_COS_FI_PHS_B                    0x010035070000//cos_fB visible string xxxxx,xxx
//#define CMD_GET_COS_FI_PHS_C                    0x010049070000//cos_fC visible string xxxxx,xxx
//#define CMD_GET_ANGLE_A_B                       0x010021070001//angle A & B long unsigned 0 < angle < 360
//#define CMD_GET_ANGLE_A_C                       0x010049070001//angle A & C long unsigned 0 < angle < 360
////#define CMD_GET_ANGLE_B_C                       0x010047070001//angle B & C long unsigned 0 < angle < 360
//#define CMD_GET_ACTIVE_POWER_A                  0x010015070000//PA
//#define CMD_GET_ACTIVE_POWER_B                  0x010029070000//PB
//#define CMD_GET_ACTIVE_POWER_C                  0x01003D070000//PC
//#define CMD_GET_REACTIVE_POWER_A                0x010017070000//QA
//#define CMD_GET_REACTIVE_POWER_B                0x01002B070000//QB
//#define CMD_GET_REACTIVE_POWER_C                0x01003F070000//QC


#define CMD_GET_INSTANT_SUMM_FREQUENCY          0x01000E0700FF
#define CMD_GET_INSTANT_L1_Q_PLUS               0x0100170700FF
#define CMD_GET_INSTANT_L1_Q_MINUS              0x0100180700FF
#define CMD_GET_INSTANT_L1_I                    0x01001F0700FF
#define CMD_GET_INSTANT_L1_U                    0x0100200700FF
#define CMD_GET_INSTANT_L1_COSF                 0x0100210700FF
#define CMD_GET_INSTANT_L1_P                    0x0100240700FF

#define CMD_GET_INSTANT_L2_Q_PLUS               0x01002B0700FF
#define CMD_GET_INSTANT_L2_Q_MINUS              0x01002C0700FF
#define CMD_GET_INSTANT_L2_I                    0x0100330700FF
#define CMD_GET_INSTANT_L2_U                    0x0100340700FF
#define CMD_GET_INSTANT_L2_COSF                 0x0100350700FF
#define CMD_GET_INSTANT_L2_P                    0x0100380700FF

#define CMD_GET_INSTANT_L3_Q_PLUS               0x01003F0700FF
#define CMD_GET_INSTANT_L3_Q_MINUS              0x0100400700FF
#define CMD_GET_INSTANT_L3_I                    0x0100470700FF
#define CMD_GET_INSTANT_L3_U                    0x0100480700FF
#define CMD_GET_INSTANT_L3_COSF                 0x0100490700FF
#define CMD_GET_INSTANT_L3_P                    0x01004C0700FF

#define CMD_GET_INSTANT_SUMM_I                  0x01000B0700FF
#define CMD_GET_INSTANT_SUMM_U                  0x01000C0700FF
#define CMD_GET_INSTANT_SUMM_COSF               0x01000D0700FF
#define CMD_GET_INSTANT_SUMM_P                  0x0100100700FF


///short names
#define CMD_GET_INSTANT_SUMM_FREQUENCY_SN       0x5208 //for scaller and units +2 to obis
#define CMD_GET_INSTANT_L1_Q_PLUS_SN            0x4008
#define CMD_GET_INSTANT_L1_Q_MINUS_SN           0x4108
#define CMD_GET_INSTANT_L1_I_SN                 0x4B08
#define CMD_GET_INSTANT_L1_U_SN                 0x4F08
#define CMD_GET_INSTANT_L1_COSF_SN              0x4208
#define CMD_GET_INSTANT_L1_P_SN                 0x3F08

#define CMD_GET_INSTANT_L2_Q_PLUS_SN            0x4408
#define CMD_GET_INSTANT_L2_Q_MINUS_SN           0x4508
#define CMD_GET_INSTANT_L2_I_SN                 0x4C08
#define CMD_GET_INSTANT_L2_U_SN                 0x5008
#define CMD_GET_INSTANT_L2_COSF_SN              0x4608
#define CMD_GET_INSTANT_L2_P_SN                 0x4308

#define CMD_GET_INSTANT_L3_Q_PLUS_SN            0x4808
#define CMD_GET_INSTANT_L3_Q_MINUS_SN           0x4908
#define CMD_GET_INSTANT_L3_I_SN                 0x4D08
#define CMD_GET_INSTANT_L3_U_SN                 0x5108
#define CMD_GET_INSTANT_L3_COSF_SN              0x4A08
#define CMD_GET_INSTANT_L3_P_SN                 0x4708


#define CMD_GET_INSTANT_SUMM_I_SN               0x4A08// не підтверджено, вирахувано по закономірності
#define CMD_GET_INSTANT_SUMM_U_SN               0x4E08// не підтверджено, вирахувано по закономірності
#define CMD_GET_INSTANT_SUMM_COSF_SN            0x3E08
#define CMD_GET_INSTANT_SUMM_P_SN               0x3B08


//relay
#define CMD_GSET_RELAY                           0x000060030AFF
#define CMD_GSET_RELAY_SN                        0x9F08

//параметризація
#define CMD_SET_ARRAY_1                         0x000065000001// class_id: 3, attr: 2




#endif // GLOBAL_DLMS_DEFINES_H
