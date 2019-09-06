#ifndef METERSCHEDULERTYPES_H
#define METERSCHEDULERTYPES_H

//#include "src/meter/zbyratorfilesetthelper.h"
#include "zbyratortypesv2.h"
//#include "zbyratordatatypehelper.h"



//4 electricity meters and other devices without a sleep mode,
//for the devices with a sleep mode variables 'intrvl' and 'kftnt' were ignored

struct OneProfileSett
{
    quint32 intrvl;//величина інтервалу, одиницю інтервалу вказує kftnt     // ignored by the sleep devices
    quint32 kftnt;//вказує на хв, година, доба, місяця                      // ignored by the sleep devices
    bool onTrue;//true - enabled, false - disabled
    quint8 prtt; //priority 0 - is the highest, '>0' lower
    quint32 glbn; //глибина в днях або місяцях (для на кінець доби)

    OneProfileSett() {}

    OneProfileSett(const quint32 &intrvl, const quint32 &kftnt, const bool &onTrue, const quint8 &prtt, const qint32 &glbn) :
        intrvl(intrvl), kftnt(kftnt), onTrue(onTrue), prtt(prtt), glbn(glbn) {}

};

//4 water meters and other devices with a sleep mode   //deprecated
//struct OneProfileSettWtr
//{
//    QString name;
//    QList<quint8> listCodes;

//    QTime timeFrom;
//    QTime timeTo;

//    QStringList dow;
//    QStringList dom;

//    OneProfileSett profileSett;

//    bool ignoreDst;

//    OneProfileSettWtr() {}
//    OneProfileSettWtr(const QString &name, const QList<quint8> &listCodes, const QTime &timeFrom, const QTime &timeTo, const QStringList &dow, const QStringList &dom, const OneProfileSett &profileSett, const bool &ignoreDst) :
//        name(name), listCodes(listCodes), timeFrom(timeFrom), timeTo(timeTo), dow(dow), dom(dom), profileSett(profileSett), ignoreDst(ignoreDst) {}
//};

struct MeterSleepProfile
{
     quint8 dom; //wake up on the day of the month , 0xFF - any day
     quint8 dow;//wake up on the day of the week , 0 - is Sunday, 1 - Monday, 0xFF - any day
     quint8 hour;//wake up in the hour  0-23, 0xFF - any hour
     quint8 minute;//wake up in the minute 0-59, 0xFF any minute
     quint8 actvt;//time of the activity in minutes    from 1 to 254,

    MeterSleepProfile() : dom(0xFF), dow(0xFF), hour(0xFF), minute(0xFF), actvt(0xFE) {}
    MeterSleepProfile(const quint8 &dom, const quint8 &dow, const quint8 &hour, const quint8 &minute, const quint8 &actvt) :
        dom(dom), dow(dow), hour(hour), minute(minute), actvt(actvt) {}
};

typedef QMap<quint8, OneProfileSett> MapMetersProfiles;//key is the poll code
typedef QMap<quint8, quint8> MapMetersPriority2profilePollCode;//prioritt 2 pollCode
typedef QMap<QString, MeterSleepProfile> MapProfLine2sleepProfile;//key is a sleep profile line

//typedef QMap<quint8, OneProfileSettWtr> MapWaterMetersProfilesSequence; //an extension for water, a key is the profile's priority (index in the table) //deprecated

//water settings have a bigger prioriy then settings for electricity meters
struct PollProfileWithPrrt2pollCode
{
    /// begin: section 4 electricity meters
    MapMetersProfiles profileSett;
    MapMetersPriority2profilePollCode prtt2profileCode;
    /// end: section 4 electricity meters

    /// begin: section 4 water meters
    MapMetersProfiles profileSett4wtrMeters;//I need only poll codes, depth, prtt
    MapProfLine2sleepProfile sleepLine2profile;//only schedules that with depended meters
    MapMetersPriority2profilePollCode prtt2profileCode4wtrMeters;
    /// end: section 4 water meters

    PollProfileWithPrrt2pollCode() {}

    PollProfileWithPrrt2pollCode(const MapMetersProfiles &profileSett, const MapMetersPriority2profilePollCode &prtt2profileCode) : profileSett(profileSett), prtt2profileCode(prtt2profileCode) {}

    PollProfileWithPrrt2pollCode(const MapMetersProfiles &profileSett4wtrMeters, const MapProfLine2sleepProfile &sleepLine2profile, const MapMetersPriority2profilePollCode &prtt2profileCode4wtrMeters) :
        profileSett4wtrMeters(profileSett4wtrMeters), sleepLine2profile(sleepLine2profile), prtt2profileCode4wtrMeters(prtt2profileCode4wtrMeters) {}

    PollProfileWithPrrt2pollCode(const MapMetersProfiles &profileSett, const MapMetersPriority2profilePollCode &prtt2profileCode,
                                 const MapMetersProfiles &profileSett4wtrMeters, const MapProfLine2sleepProfile &sleepLine2profile, const MapMetersPriority2profilePollCode &prtt2profileCode4wtrMeters) :
        profileSett(profileSett), prtt2profileCode(prtt2profileCode),
        profileSett4wtrMeters(profileSett4wtrMeters), sleepLine2profile(sleepLine2profile), prtt2profileCode4wtrMeters(prtt2profileCode4wtrMeters) {}

};


struct PollDateTimeLimitation
{
    QStringList listEnableDoW;//days of the week , 1-Mon, 7-Sun, if empty all days
    QStringList listEnableDoM;//days of the month, 1-27,  28-31 {check if the date is the end of the month}

    QTime pollTimeFrom;
    QTime pollTimeTo;

    PollDateTimeLimitation() {}

    PollDateTimeLimitation(const QStringList &listEnableDoW, const QTime &pollTimeFrom, const QTime &pollTimeTo) : listEnableDoW(listEnableDoW), pollTimeFrom(pollTimeFrom), pollTimeTo(pollTimeTo) {}

    PollDateTimeLimitation(const QStringList &listEnableDoW, const QStringList &listEnableDoM, const QTime &pollTimeFrom, const QTime &pollTimeTo) :
        listEnableDoW(listEnableDoW), listEnableDoM(listEnableDoM), pollTimeFrom(pollTimeFrom), pollTimeTo(pollTimeTo) {}

};


struct PollSchedule4meters
{
    MapMetersPriority2profilePollCode hashPrttPollCode;//QMap<quint8, quint8> MapMetersPriority2profilePollCode;
    PollDateTimeLimitation pdtlim;

    MapMetersProfiles hashProfiles;//QMap<quint8, OneProfileSett> MapMetersProfiles;//key: for electricity meter - pollCode, for water - the index in the list,
    quint8 deviceType;
    quint16 schedulePrtt;
//    qint32 zatrymkaDoZapuskuSek;

    PollSchedule4meters() {}

    PollSchedule4meters(const MapMetersPriority2profilePollCode &hashPrttPollCode, const QStringList &listEnableDoW, const QTime &pollTimeFrom, const QTime &pollTimeTo, const MapMetersProfiles &hashProfiles) :
        hashPrttPollCode(hashPrttPollCode), pdtlim(listEnableDoW, pollTimeFrom, pollTimeTo), hashProfiles(hashProfiles) {}

    PollSchedule4meters(const MapMetersPriority2profilePollCode &hashPrttPollCode, const QStringList &listEnableDoW, const QTime &pollTimeFrom, const QTime &pollTimeTo, const MapMetersProfiles &hashProfiles, const quint16 &deviceType, const quint8 &schedulePrtt) :
        hashPrttPollCode(hashPrttPollCode), pdtlim(listEnableDoW, pollTimeFrom, pollTimeTo), hashProfiles(hashProfiles), deviceType(deviceType), schedulePrtt(schedulePrtt) {}
};


struct UniversalMeter
{
    UniversalMeterSettList activeNi4meters;//NIs of meters that is ready for readout
    QByteArray meterSha256;
    HashNi2MapHistory hashNi2lastPollMeter;//the history of the poll of electricity meters
    bool setIgnoreCounter; //кажу щоб ігнорив повтори по цьому лічильнику один раз при додаванні в чергу якщо true, в іншому випадку керується кешем
    QList<quint8> lastPrttList;

    UniversalMeter() {}
    UniversalMeter(const UniversalMeterSettList &activeNi4meters, const QByteArray &meterSha256, const HashNi2MapHistory &hashNi2lastPollMeter) :
        activeNi4meters(activeNi4meters), meterSha256(meterSha256), hashNi2lastPollMeter(hashNi2lastPollMeter) {}

};

struct ElectricityMeters
{
    UniversalMeter ucm;
    PollSchedule4meters schedule4pollMeters;
    ElectricityMeters() {}
    ElectricityMeters(const UniversalMeterSettList &activeNi4electricityMeters, const QByteArray &electricityMeterSha256, const HashNi2MapHistory &hashNi2lastPollElectricityMeter, const PollSchedule4meters &schedule4pollMeters)
        : ucm(UniversalMeter(activeNi4electricityMeters, electricityMeterSha256, hashNi2lastPollElectricityMeter)), schedule4pollMeters(schedule4pollMeters) {}

} ;

struct WaterMeterProfileStamp
{
    quint8 hour;
    quint16 dayOfYear;
    WaterMeterProfileStamp() : hour(0), dayOfYear(0) {}
    WaterMeterProfileStamp(const quint8 &hour, const quint16 &dayOfYear) : hour(hour), dayOfYear(dayOfYear) {}
};

struct WaterMeters
{
    UniversalMeter ucm;

    MapProfLine2sleepProfile schedule4waterMeters;//key is a sleep profile line
    MapProfLine2sleepProfile schedule4waterMetersLastPoll;//key is a sleep profile line, contains only profiles that received from the meters, it contains only profiles that not exists in schedule4waterMeters

    PollSchedule4meters schedule4pollMeters;
    QMap<QString,QString> mapNi2sleepProfile;
    QMap<QString, WaterMeterProfileStamp> schedule2lastHourLocal;//розклад до останньої години використання, щоб активація розкладу була не частіше 1 разу на 1 годину


//    MapMetersProfiles hashProfiles;//QMap<quint8, OneProfileSett> MapMetersProfiles;//key: pollCode
//    PollDateTimeLimitation pdtlim; at hashProfiles

    QStringList checkedLines;
    WaterMeters() {}
    WaterMeters(const UniversalMeterSettList &activeNi4waterMeters, const QByteArray &waterMeterSha256, const HashNi2MapHistory &hashNi2lastPollWaterMeter, const MapProfLine2sleepProfile &schedule4waterMeters, const PollSchedule4meters &schedule4pollMeters) :
        ucm(UniversalMeter(activeNi4waterMeters, waterMeterSha256, hashNi2lastPollWaterMeter)), schedule4waterMeters(schedule4waterMeters), schedule4pollMeters(schedule4pollMeters) {}
} ;


struct MetersGlobal
{
    QMap<quint8,QDateTime> hashLastDateTime;//poll code 2 datetime
    QMap<quint8,QByteArray> mapPollCode2niListSha256;
    MetersGlobal() {}
    MetersGlobal(const QMap<quint8,QDateTime> &hashLastDateTime, const QMap<quint8,QByteArray> &mapPollCode2niListSha256) : hashLastDateTime(hashLastDateTime), mapPollCode2niListSha256(mapPollCode2niListSha256) {}
} ;


struct StartPollStruct
{
    bool startPoll;
    PollDateMemoExt pollDtMemo;
    quint8 pollCode;
    quint8 prtt;
    quint8 deviceType;// deviceType;
    QStringList listNi4poll;
    quint32 intrvl;
    quint32 kftnt;

    StartPollStruct() : startPoll(false) {}

    StartPollStruct(const bool &startPoll) : startPoll(startPoll) {}

    StartPollStruct(const bool &startPoll, const PollDateMemoExt &pollDtMemo, const quint8 &pollCode, const quint8 &prtt, const quint8 &deviceType, const QStringList &listNi4poll, const quint32 &intrvl, const quint32 &kftnt)
        : startPoll(startPoll), pollDtMemo(pollDtMemo), pollCode(pollCode), prtt(prtt), deviceType(deviceType), listNi4poll(listNi4poll), intrvl(intrvl), kftnt(kftnt) {}

};

#endif // METERSCHEDULERTYPES_H
