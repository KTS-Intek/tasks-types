QT       += core

linux-beagleboard-g++:{
   QT -= gui
}


INCLUDEPATH  += $$PWD\
                $$PWD/../../defines/defines

HEADERS += \
    $$PWD/src/zbyrator-v2/zbyratordatatypehelper.h \
    $$PWD/src/zbyrator-v2/zbyratorsharedtypes.h \
    $$PWD/src/meter/zbyratortypes4poll.h \
    $$PWD/src/zbyrator-v2/zbyratortypesv2.h \
    $$PWD/src/zbyrator-v2/zbyratortypesv2defs.h

SOURCES += \
    $$PWD/src/zbyrator-v2/zbyratordatatypehelper.cpp


