TEMPLATE = app
TARGET = EasyDuo
QT += core \
    gui
HEADERS += config.h \
    network.h \
    easyduo.h
SOURCES += config.cpp \
    network.cpp \
    main.cpp \
    easyduo.cpp
FORMS += easyduo.ui
RESOURCES += 
LIBS += -lconfig++
