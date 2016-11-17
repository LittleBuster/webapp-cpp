TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS +=-lpthread

SOURCES += main.cpp \
    app.cpp \
    router.cpp \
    webserver.cpp \
    tcpserver.cpp \
    tcpclient.cpp \
    log.cpp \
    clients/termoclient.cpp \
    handlers/termohandler.cpp \
    handlers/unknownhandler.cpp \
    configs.cpp \
    ext.cpp

HEADERS += \
    app.h \
    router.h \
    webserver.h \
    tcpserver.h \
    tcpclient.h \
    log.h \
    clients/termoclient.h \
    handlers/ihandler.h \
    handlers/termohandler.h \
    handlers/unknownhandler.h \
    configs.h \
    ext.h
