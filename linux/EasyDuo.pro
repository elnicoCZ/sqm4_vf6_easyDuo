TEMPLATE = app
TARGET = easyduo
QT += core \
    gui \
    network
HEADERS += CMcc.h \
    ../common/easyduo_mcc_common.h \
    alsa.h \
    easyplayer.h \
    config.h \
    network.h \
    easyduo.h
SOURCES += CMcc.cpp \
    alsa.cpp \
    easyplayer.cpp \
    config.cpp \
    network.cpp \
    main.cpp \
    easyduo.cpp
FORMS += easyplayer.ui \
    easyduo.ui
RESOURCES += pictures.qrc
LIBS += -lconfig++ \
    -lasound \
    -lmcc
# make install
target.path = /usr/bin
INSTALLS += target
