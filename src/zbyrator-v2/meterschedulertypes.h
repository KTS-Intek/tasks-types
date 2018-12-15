#ifndef METERSCHEDULERTYPES_H
#define METERSCHEDULERTYPES_H

#include "src/meter/zbyratorfilesetthelper.h"

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
    quint8 meterType;
    QStringList listNi4poll;
    quint32 intrvl;
    quint32 kftnt;

    StartPollStruct() : startPoll(false) {}

    StartPollStruct(const bool &startPoll) : startPoll(startPoll) {}

    StartPollStruct(const bool &startPoll, const PollDateMemoExt &pollDtMemo, const quint8 &pollCode, const quint8 &prtt, const quint8 &meterType, const QStringList &listNi4poll, const quint32 &intrvl, const quint32 &kftnt)
        : startPoll(startPoll), pollDtMemo(pollDtMemo), pollCode(pollCode), prtt(prtt), meterType(meterType), listNi4poll(listNi4poll), intrvl(intrvl), kftnt(kftnt) {}

};

#endif // METERSCHEDULERTYPES_H
