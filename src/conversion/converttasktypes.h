#ifndef CONVERTTASKTYPES_H
#define CONVERTTASKTYPES_H

///[!] tasks-types
#include "src/zbyrator-v2/zbyratordatatypehelper.h"




class ConvertTaskTypes
{

public:



    static PollDateMemoExt getDateTimeMemo4poll(const QDateTime &dtPoll, const quint8 &pollCode, const quint32 &kftnt, const quint32 &intrvl, const qint32 &glybokoIntrvl, const bool &ignorePrevData, const QDateTime &pollDtFrom);


};

#endif // CONVERTTASKTYPES_H
