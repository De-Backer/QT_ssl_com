QT += network
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/tcp_server.h \
    $$PWD/ssl_server_socket.h

SOURCES += \
    $$PWD/tcp_server.cpp \
    $$PWD/ssl_server_socket.cpp

