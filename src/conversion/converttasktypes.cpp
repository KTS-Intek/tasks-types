#include "converttasktypes.h"

#include "definedpollcodes.h"
#include "defparams4zbyratordefs.h"

///[!] type-conerter
#include "src/base/prettyvalues.h"


///[!] tasks-shared
#include "src/task/pollcodeshelper.h"



//-----------------------------------------------------------------------------------------------------------------------------------------------


PollDateMemoExt ConvertTaskTypes::getDateTimeMemo4poll(const QDateTime &dtPoll, const quint8 &pollCode, const quint32 &kftnt, const quint32 &intrvl, const qint32 &glybokoIntrvl, const bool &ignorePrevData, const QDateTime &pollDtFrom)
{
    //electricity meter ready
    PollDateMemoExt d;
    d.fullTableName = PrettyValues::getFullTableName4poll(dtPoll, pollCode);
    d.dtLastStartPoll = QDateTime::currentDateTimeUtc();

#ifdef HASGUI4USR
    if(PollCodesHelper::isAlogBookPollCode(pollCode) && d.depth == 1 && d.dtLastStartPoll.addDays(-1).toString("yyyyMMdd") == PrettyValues::tableName2DateTime(d.fullTableName).toString("yyyyMMdd")){
        d.fullTableName = PrettyValues::getFullTableName4poll(dtPoll.addDays(1), pollCode);
    }
#endif

    d.pollDateTime = PrettyValues::tableName2DateTime(d.fullTableName);
    d.depth = glybokoIntrvl;

    d.tableName = d.fullTableName.mid(4);
    d.pollCode = pollCode;
    d.ignorePrevData = ignorePrevData;//

    if(PollCodesHelper::isOneMonthStep(pollCode)){
        d.pollDateTimeFirstIntrvl = d.pollDateTime.addMonths((-1) * glybokoIntrvl).addDays(5);
        d.pollDateTimeNextIntrvl = d.pollDateTime.addMonths(glybokoIntrvl);
    }else if(PollCodesHelper::isOneDayStep(pollCode)){
        d.pollDateTimeFirstIntrvl = d.pollDateTime.addDays((-1) * glybokoIntrvl).addSecs(500);
        d.pollDateTimeNextIntrvl = d.pollDateTime.addDays(glybokoIntrvl);
    }else{
        d.pollDateTime = d.pollDateTime.toUTC();

        const qint64 intrvlMinus = (qint64)intrvl;
        switch(kftnt){

        case POLL_KFTNT_HOURS:{ //hour
            d.pollDateTimeFirstIntrvl = d.pollDateTime.addSecs((-1) * intrvlMinus * (60 * 60));
            d.pollDateTimeNextIntrvl = d.pollDateTime.addSecs(intrvlMinus * (60 * 60));
            break;  }

        case POLL_KFTNT_MINUTES:{ //minute
            d.pollDateTimeFirstIntrvl = d.pollDateTime.addSecs((-1) * intrvlMinus * ( 60));
            d.pollDateTimeNextIntrvl = d.pollDateTime.addSecs(intrvlMinus * (60));
            break;}

        case POLL_KFTNT_DAYS:{
            d.pollDateTimeFirstIntrvl = d.pollDateTime.addDays((-1) * glybokoIntrvl).addSecs(500);
            d.pollDateTimeNextIntrvl = d.pollDateTime.addDays(intrvl);
            break;}

        case POLL_KFTNT_WEEK:{
            d.pollDateTimeFirstIntrvl = d.pollDateTime.addDays((-7) * glybokoIntrvl).addSecs(500);
            d.pollDateTimeNextIntrvl = d.pollDateTime.addDays(intrvl * 7);
            break;}

        case POLL_KFTNT_MONTH:{
            d.pollDateTimeFirstIntrvl = d.pollDateTime.addMonths((-1) * glybokoIntrvl).addDays(5);
            d.pollDateTimeNextIntrvl = d.pollDateTime.addMonths(intrvl);
            break;}

        case POLL_KFTNT_SECONDS:{ //
            d.pollDateTimeFirstIntrvl = d.pollDateTime.addSecs((-1) * intrvlMinus);
            d.pollDateTimeNextIntrvl = d.pollDateTime.addSecs(intrvlMinus);
            break;}


        default:{
            d.pollDateTimeNextIntrvl = d.pollDateTime;
            d.pollDateTimeFirstIntrvl = d.pollDateTime.addDays((-1) * glybokoIntrvl).addSecs(500);
            break;}

        }
    }

    if(pollDtFrom.isValid())//only for Quick Collect and command poll
        d.pollDateTimeFirstIntrvl = pollDtFrom.toUTC();

    return d;
}
