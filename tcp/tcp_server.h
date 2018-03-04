#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QTcpServer>
#include <QDebug>

#include "ssl_socket.h"

class tcp_server : public QTcpServer
{
    Q_OBJECT
public:
    explicit tcp_server(QObject *parent = 0);
    void StartServer(int port,QString file_crt,QString file_key);

signals:
    void message(qintptr Descriptor,QByteArray data);
    void sent_message(qintptr Descriptor,QByteArray data);

public slots:

protected:
    void incomingConnection(qintptr handle);

private:
    QString File_crt="test.crt";
    QString File_key="test.key";


};

#endif // TCP_SERVER_H
