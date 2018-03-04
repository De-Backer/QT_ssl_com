QT += network
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/ssl_socket.h \
    $$PWD/tcp_server.h

SOURCES += \
    $$PWD/ssl_socket.cpp \
    $$PWD/tcp_server.cpp

