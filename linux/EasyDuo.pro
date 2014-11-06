TEMPLATE = app
TARGET = EasyDuo
QT += core \
    gui
HEADERS += easyplayer.h \
    config.h \
    network.h \
    easyduo.h
SOURCES += easyplayer.cpp \
    config.cpp \
    network.cpp \
    main.cpp \
    easyduo.cpp
FORMS += easyplayer.ui \
    easyduo.ui
RESOURCES += pictures.qrc
LIBS += -lconfig++
