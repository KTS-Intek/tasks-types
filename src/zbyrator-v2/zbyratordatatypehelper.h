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


///[!] tasks-types
#include "src/zbyrator-v2/zbyratortypesv2.h"
#include "src/meter/zbyratortypes4poll.h"


//#include "src/emb/ifaceexchangeserializedtypes.h"




struct ZbyratorTaskTable
{
    QMap<quint32, ZbyratorTask> mapTaskTable;//cache
    QHash<QString,quint32> hashQckType2pid;//кешую qckTyp з прив'язкою до pid завдання

//    QMap<quint8, QList<int> > mapTaskPriority2pids;
//    QMap<quint8, QMap<quint8, MyUIntList > > mapMeterTypeAndPriority2pids;//why do I use it, device poll can loop on one device type, and never go to the next if there are no answers
    //it is better to use device groups, than device types to pids

    QMap<quint8, QMap<quint8, MyUIntList > > mapDeviceGroupsAndPriority2pids;

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
