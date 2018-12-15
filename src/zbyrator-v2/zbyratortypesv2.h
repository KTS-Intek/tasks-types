#ifndef ZBYRATORTYPESV2_H
#define ZBYRATORTYPESV2_H

#include <QStringList>
#include <QDateTime>
#include <QVariantMap>
#include <QVariantHash>
#include "zbyratortypesv2defs.h"
//#include "src/emb/ifaceexchangeserializedtypes.h"


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
    quint8 rez;//exchenge rezult
    quint8 srcId;//
    QString qckType;//коли починаю виконувати завдання, то додаю <Space> вкінці
    qint64 dtCreated;
    qint64 dtFinished;//lastExchange
    quint32 counter;//how many times it started, from a task created/updated
    quint32 counterTotal;//haw many times it started, from a task created

    QString ni;
    quint8 pollCode;
    quint8 prtt4pollCode;//
    quint8 meterType;
    PollDateMemoExt pollDtMemoExt;

    //date and time utc only
    quint32 kftnt;
    quint32 intrvl;
    QStringList dow;
    QStringList dom;
    QTime timtFrom;
    QTime timeTo;

    ZbyratorTask() : stts(0xFF), rez(0xFF), srcId(0), counter(0), counterTotal(0), pollCode(0), prtt4pollCode(0xFF), meterType(0xFF) {}
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
