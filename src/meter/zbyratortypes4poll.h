#ifndef ZBYRATORTYPES4POLL_H
#define ZBYRATORTYPES4POLL_H

#include <QDateTime>
#include <QVariantHash>
#include <QVariantMap>


struct FindEmptyCellCache
{
    QStringList listSelectCols;
    QStringList listEnrg;
    QString whereStr;
    int dataStartFromIndx ;
    int listSize;
    bool updateCache;

    FindEmptyCellCache() : dataStartFromIndx(0), listSize(0), updateCache(true) {}
};




struct DbGetTableListCache
{
    QDateTime fromDT;
    QDateTime toDT;
    quint8 code;
    QStringList list;
    quint8 cacheCounter;
    quint8 maxCacheCounter;
    DbGetTableListCache() : code(0), cacheCounter(0), maxCacheCounter(3) {}
    DbGetTableListCache(const QDateTime &fromDT, const QDateTime &toDT, const quint8 &code, const QStringList &list) : fromDT(fromDT), toDT(toDT), code(code), list(list), cacheCounter(0), maxCacheCounter(3) {}
    DbGetTableListCache(const QDateTime &fromDT, const QDateTime &toDT, const quint8 &code, const QStringList &list, const quint8 &cacheCounter, const quint8 &maxCacheCounter)
        : fromDT(fromDT), toDT(toDT), code(code), list(list), cacheCounter(cacheCounter), maxCacheCounter(maxCacheCounter) {}
} ;


struct ZbyratorLogoutLater
{
    QByteArray meterNIfromList;
    QByteArray meterNIfromTable;
    QVariantHash exitMessageSett;
    QString model;
    QDateTime dtUpdated;
    ZbyratorLogoutLater() {}
};

struct ExchangeStat
{
    QDateTime startPollDate;


    quint32 byte2meter;
    quint32 bytesFromMeter;

    quint32 totalMessageCounter;
    quint32 usflDataLen;

    quint8 apiErrCounter;

    quint8 emptyAnswerCounterStat;//it was empty AnswerCounter

    //poll statistic
    quint32 meterCountAll;
    quint32 meterCountDone;
    quint32 meterCountErr;


    quint32 zbyratorCounter;
    QHash<quint8, qint64> hashProfileTimeElapsed;
    QHash<quint8, qint64> hashProfileTimeElapsedTotal;
    QHash<quint8,QDateTime> hashLastDateTime;
    //plugin message statistic
    QHash<QByteArray,quint32> hashMessRetryCounter;

    QTime timeFromEmptyChanged;//для аналізу порожніх відповідей
    QTime time4poll;//час між новими завданнями
    QTime time4multicast;//час для паузи в обміні, для системи агрегатування

    ExchangeStat() : byte2meter(0), bytesFromMeter(0), totalMessageCounter(0), usflDataLen(0), apiErrCounter(0), emptyAnswerCounterStat(0), meterCountAll(0),
        meterCountDone(0), meterCountErr(0), zbyratorCounter(0)  {}
};




#endif // ZBYRATORTYPES4POLL_H
