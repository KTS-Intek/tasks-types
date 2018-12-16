#include(../../matilda-base/type-converter/type-converter.pri)


INCLUDEPATH  += $$PWD\
                $$PWD/../../defines/defines

HEADERS += \
    $$PWD/src/zbyrator-v2/zbyratordatatypehelper.h \
    $$PWD/src/zbyrator-v2/zbyratorsharedtypes.h \
    $$PWD/src/meter/zbyratortypes4poll.h \
    $$PWD/src/zbyrator-v2/zbyratortypesv2.h \
    $$PWD/src/zbyrator-v2/zbyratortypesv2defs.h \
    $$PWD/src/zbyrator-v2/meterschedulertypes.h \
    $$PWD/src/conversion/converttasktypes.h

SOURCES += \
    $$PWD/src/zbyrator-v2/zbyratordatatypehelper.cpp \
    $$PWD/src/conversion/converttasktypes.cpp

