# Version=0.0.1
#include(../../matilda-base/type-converter/type-converter.pri)
#Dependencies -
# tasks-types
# type-conerter

INCLUDEPATH  += $$PWD\
                $$PWD/../../defines/defines\
                $$PWD/../../defines/define-types

HEADERS += \
    $$PWD/src/zbyrator-v2/zbyratordatatypehelper.h \
    $$PWD/src/zbyrator-v2/zbyratorsharedtypes.h \
    $$PWD/src/meter/zbyratortypes4poll.h \
    $$PWD/src/zbyrator-v2/zbyratortypesv2.h \
    $$PWD/src/zbyrator-v2/zbyratortypesv2defs.h \
    $$PWD/src/zbyrator-v2/meterschedulertypes.h \
    $$PWD/src/conversion/converttasktypes.h \
    $$PWD/src/dbg/dbgaboutsourcetype.h

SOURCES += \
    $$PWD/src/zbyrator-v2/zbyratordatatypehelper.cpp \
    $$PWD/src/conversion/converttasktypes.cpp


