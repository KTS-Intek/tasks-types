#ifndef ZBYRATORTYPESV2_H
#define ZBYRATORTYPESV2_H

#include <QStringList>
#include <QDateTime>
#include <QVariantMap>
#include <QVariantHash>
#include "zbyratortypesv2defs.h"
//#include "src/emb/ifaceexchangeserializedtypes.h"


//from meteroperations.h
struct MeterTransformer{
    bool hasTransformer;
    bool only4display;
    quint32 ucDividend;
    quint32 ucDivisor;
    quint32 icDividend;
    quint32 icDivisor;

    qreal endUcoefitient;
    qreal endIcoefitient;
    qreal endCoefitient;

    MeterTransformer() : hasTransformer(false) {}

    MeterTransformer(const bool &hasTransformer) :
        hasTransformer(hasTransformer), only4display(true), ucDividend(1), ucDivisor(1), icDividend(1), icDivisor(1), endCoefitient(1) {}

    MeterTransformer(const bool &hasTransformer, const bool &only4display, const quint32 &ucDividend, const quint32 &ucDivisor, const quint32 &icDividend, const quint32 &icDivisor) :
    hasTransformer(hasTransformer), only4display(only4display), ucDividend(ucDividend), ucDivisor(ucDivisor), icDividend(icDividend), icDivisor(icDivisor),
      endUcoefitient(hasTransformer ? (qreal)((qreal)ucDividend/(qreal)ucDivisor) : 1.0 ), endIcoefitient(hasTransformer ? (qreal)((qreal)icDividend/(qreal)icDivisor) : 1.0 ),
      endCoefitient( hasTransformer ? (endUcoefitient * endIcoefitient) : 1.0 ) {}
};


struct UniverslaMeterOnlyCache
{
//    QString enrg4vrsn;//coma separeted list, cached info about energy that meter support
    QMap<quint8,QString> enrg4vrsn;
    UniverslaMeterOnlyCache() {}
};


struct UniversalMeterSett
{

    quint8 deviceType;//readOnly  // deviceType;
    QString model;//write if Auto
    QString sn;//write

    QString ni;//readOnly
    QString memo;//readOnly
    QString passwd;//readOnly
    bool pollEnbl;//readOnly

    QString enrg; //readOnly coma separated line, this is a sleep profile to water meters
    quint8 tariff;//readOnly

    QString coordinate;//readOnly
    QString version;//write

    QString powerin;//readOnly
    MeterTransformer transformer;//readOnly
    bool disableTimeCorrection;//readOnly


    UniverslaMeterOnlyCache cache;

    UniversalMeterSett() {}

    UniversalMeterSett(const quint8 &deviceType, const QString &model, const QString &sn, const QString &ni, const QString &memo, const QString &passwd, const bool &pollEnbl, const QString enrg,
                       const quint8 tariff, const QString coordinate, const QString &version, const QString &powerin, const MeterTransformer &transformer, const bool &disableTimeCorrection) :
        deviceType(deviceType), model(model), sn(sn), ni(ni), memo(memo), passwd(passwd), pollEnbl(pollEnbl), enrg(enrg),
        tariff(tariff), coordinate(coordinate), version(version), powerin(powerin), transformer(transformer), disableTimeCorrection(disableTimeCorrection) {}


    UniversalMeterSett(const QString &model, const QString &sn, const QString &ni, const QString &memo, const QString &passwd, const bool &pollEnbl, const QString enrg,
                       const quint8 tariff, const QString coordinate, const QString &version, const QString &powerin, const MeterTransformer &transformer, const bool &disableTimeCorrection) :
        deviceType(0xFF), model(model), sn(sn), ni(ni), memo(memo), passwd(passwd), pollEnbl(pollEnbl), enrg(enrg),
        tariff(tariff), coordinate(coordinate), version(version), powerin(powerin), transformer(transformer), disableTimeCorrection(disableTimeCorrection) {}

};


typedef QList<UniversalMeterSett> UniversalMeterSettList;

struct MeterPollHistory
{
//        quint8 pollCode; key of the map
    QDateTime dtPoll;
    QDateTime dtStateChanged;
    quint8 state;
    MeterPollHistory() : state(MPH_INITSTATE) {}
    MeterPollHistory(const QDateTime &dtPoll, const QDateTime &dtStateChanged, const quint8 &state)
        : dtPoll(dtPoll), dtStateChanged(dtStateChanged), state(state) {}
};


struct MissingData
{
    QStringList niWithMissingData;
    QStringList tableNamesWithMissingData;
    QMap<QString, QStringList> tableName2missingNis;
    QStringList messList;
    MissingData() {}
    MissingData(const QStringList &niWithMissingData, const QStringList &tableNamesWithMissingData, const QMap<QString, QStringList> &tableName2missingNis, const QStringList &messList)
        : niWithMissingData(niWithMissingData), tableNamesWithMissingData(tableNamesWithMissingData), tableName2missingNis(tableName2missingNis), messList(messList) {}
};

struct PollDateMemoExt
{
    qint32 depth;
    quint8 pollCode;
    QString tableName;
    QString fullTableName;
    bool ignorePrevData;

    QDateTime pollDateTime;
    QDateTime pollDateTimeFirstIntrvl;
    QDateTime pollDateTimeNextIntrvl;
    QDateTime dtLastStartPoll;

    QString operationArgument;

    PollDateMemoExt() : depth(1), pollCode(0), ignorePrevData(false) {}
};


typedef QList<PollDateMemoExt> PollDateMemoExtList;

typedef QMap<quint8, MeterPollHistory> MapPollcodePollHistory;
typedef QHash<QString, QMap<quint8, MeterPollHistory> > HashNi2MapHistory;//the history of the poll of meters
typedef QList<int> MyIntList;
typedef QList<quint32> MyUIntList;

typedef QList<quint8> MyUInt8List;
typedef QList<quint32> MyUInt32List;
typedef QMap<QString,QString> MyNi2model;

//може бути ситуація коли завдяння створено через розклад або через ЮКОН, і в процесі виконання буде створене нове подібне
//по завершенню першого воно повинно злитися з наступним, при умові
//-що у них однаковий srcId???
//
struct ZbyratorTask
{
//    int id;
    quint8 stts;//add to queue , processing, finished
    quint8 rez;//exchenge result
    quint8 srcId;//
    QString qckType;//коли починаю виконувати завдання, то додаю <Space> вкінці
    qint64 dtCreated;
    qint64 dtFinished;//lastExchange
    quint32 counter;//how many times it started, from a task created/updated
    quint32 counterTotal;//haw many times it started, from a task created

    QString ni;
    quint8 pollCode;
    quint8 prtt4pollCode;//
    quint8 deviceType;// deviceType;
    PollDateMemoExt pollDtMemoExt;

    //date and time utc only
    quint32 kftnt;
    quint32 intrvl;
    QStringList dow;//day of week
    QStringList dom;//day of month
    QTime timtFrom;
    QTime timeTo;

    ZbyratorTask() : stts(0xFF), rez(0xFF), srcId(0), counter(0), counterTotal(0), pollCode(0), prtt4pollCode(0xFF), deviceType(0xFF) {}
};




struct ExchangeGlobalStat
{

    //poll statistic
    QMap<quint8, quint32> pollCode2meterCountAllTmp;//temporary storage


    QMap<quint8, quint32> pollCode2meterCountAll;
    QMap<quint8, quint32> pollCode2meterCountDone;
    QMap<quint8, quint32> pollCode2meterCountErr;
    QMap<quint8, QStringList> pollCode2meterNiErr;

    QMap<quint8, qint64> hashProfileTimeElapsed;
    QMap<quint8, qint64> hashProfileTimeElapsedTotal;
    QMap<quint8,QDateTime> hashLastDateTime;

    QMap<quint8,QString> pollCode2lastTableName;

    QMap<quint8, int> pollCode2depth;

    quint8 lastPollCode;

//    ExchangeGlobalStat() : zbyratorCounter(0)  {}
};




#endif // ZBYRATORTYPESV2_H
