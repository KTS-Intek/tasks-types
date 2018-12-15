#ifndef ZBYRATORSHAREDTYPES_H
#define ZBYRATORSHAREDTYPES_H

#include <QStringList>
//#include <QTime>
//#include <QDateTime>



struct DetectMeterModelState
{
    QList<QString> keys4plgs;
    int listSize;
    int lastIndx;
    DetectMeterModelState() {}
} ;



#endif // ZBYRATORSHAREDTYPES_H
