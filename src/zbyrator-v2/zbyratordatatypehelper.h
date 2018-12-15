#ifndef ZBYRATORDATATYPEHELPER_H
#define ZBYRATORDATATYPEHELPER_H

#include <QHash>
#include <QList>
#include <QPair>

#include <QString>
#include <QByteArray>
#include <QDateTime>
#include <QDataStream>
#include <QDebug>
#include "src/zbyrator-v2/zbyratortypesv2.h"
#include "src/meter/zbyratortypes4poll.h"


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

    quint8 meterType;//readOnly
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

    UniversalMeterSett(const quint8 &meterType, const QString &model, const QString &sn, const QString &ni, const QString &memo, const QString &passwd, const bool &pollEnbl, const QString enrg,
                       const quint8 tariff, const QString coordinate, const QString &version, const QString &powerin, const MeterTransformer &transformer, const bool &disableTimeCorrection) :
        meterType(meterType), model(model), sn(sn), ni(ni), memo(memo), passwd(passwd), pollEnbl(pollEnbl), enrg(enrg),
        tariff(tariff), coordinate(coordinate), version(version), powerin(powerin), transformer(transformer), disableTimeCorrection(disableTimeCorrection) {}


    UniversalMeterSett(const QString &model, const QString &sn, const QString &ni, const QString &memo, const QString &passwd, const bool &pollEnbl, const QString enrg,
                       const quint8 tariff, const QString coordinate, const QString &version, const QString &powerin, const MeterTransformer &transformer, const bool &disableTimeCorrection) :
        meterType(0xFF), model(model), sn(sn), ni(ni), memo(memo), passwd(passwd), pollEnbl(pollEnbl), enrg(enrg),
        tariff(tariff), coordinate(coordinate), version(version), powerin(powerin), transformer(transformer), disableTimeCorrection(disableTimeCorrection) {}

};


typedef QList<UniversalMeterSett> UniversalMeterSettList;


struct ZbyratorTaskTable
{
    QMap<quint32, ZbyratorTask> mapTaskTable;//cache
    QHash<QString,quint32> hashQckType2pid;//кешую qckTyp з прив'язкою до pid завдання

//    QMap<quint8, QList<int> > mapTaskPriority2pids;
    QMap<quint8, QMap<quint8, MyUIntList > > mapMeterTypeAndPriority2pids;


    MyUIntList uconPids;//все що створено через UCon зберігається тут
    UniversalMeterSettList uconMeters;//лічильники що опитуватимуться із-за команди з UCon будуть зберігатися тут

    QMap<quint32, ZbyratorTask> mapTaskTableDone;//фактично історія завершених завдань
    MyUIntList finishedPids;

    quint32 currentTaskId;
    quint32 lastTaskId;
    QDateTime currentTaskStarted;

    QMap<QString,bool> ni2goodAnswer;//якщо отримав відповідь від модему, то відмічаю 1, якщо нема відповіді то 0
    bool enPowerMangement;
    bool enUconPowerManagement;//for quick commands
    ZbyratorTaskTable() : currentTaskId(0), enPowerMangement(true), enUconPowerManagement(false) {}
};


class ZbyratorDataTypeHelper
{
public:
    static void makeRegistration();
};



//must be in a header file, outside the class!!!


QDataStream &operator <<(QDataStream &out, const ZbyratorTask &m);
QDataStream &operator >>(QDataStream &in, ZbyratorTask &m);
QDebug operator<<(QDebug d, const ZbyratorTask &m);



QDataStream &operator <<(QDataStream &out, const ZbyratorTaskTable &m);
QDataStream &operator >>(QDataStream &in, ZbyratorTaskTable &m);
QDebug operator<<(QDebug d, const ZbyratorTaskTable &m);


QDataStream &operator <<(QDataStream &out, const UniversalMeterSett &m);
QDataStream &operator >>(QDataStream &in, UniversalMeterSett &m);
QDebug operator<<(QDebug d, const UniversalMeterSett &m);

QDataStream &operator <<(QDataStream &out, const MeterTransformer &m);
QDataStream &operator >>(QDataStream &in, MeterTransformer &m);
QDebug operator<<(QDebug d, const MeterTransformer &m);

QDataStream &operator <<(QDataStream &out, const UniverslaMeterOnlyCache &m);
QDataStream &operator >>(QDataStream &in, UniverslaMeterOnlyCache &m);
QDebug operator<<(QDebug d, const UniverslaMeterOnlyCache &m);


QDataStream &operator <<(QDataStream &out, const PollDateMemoExt &m);
QDataStream &operator >>(QDataStream &in, PollDateMemoExt &m);
QDebug operator<<(QDebug d, const PollDateMemoExt &m);




bool operator ==(const MeterTransformer &t0, const MeterTransformer &t1);
bool operator ==(const UniversalMeterSett &s, const UniversalMeterSett &s1);


Q_DECLARE_METATYPE(ZbyratorTask)
Q_DECLARE_METATYPE(ZbyratorTaskTable)

Q_DECLARE_METATYPE(UniversalMeterSett)
Q_DECLARE_METATYPE(MeterTransformer)
Q_DECLARE_METATYPE(UniverslaMeterOnlyCache)
Q_DECLARE_METATYPE(PollDateMemoExt)


#endif // ZBYRATORDATATYPEHELPER_H
