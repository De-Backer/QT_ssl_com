#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QTcpServer>
#include <QDebug>

#include "ssl_server_socket.h"

class tcp_server : public QTcpServer
{
    Q_OBJECT
public:
    explicit tcp_server(QObject *parent = 0);
    ~tcp_server();
    void StartServer(int port,QString file_crt,QString file_key);
    virtual void close();

signals:
    void message(qintptr Descriptor,QByteArray data);
    void sent_message(qintptr Descriptor,QByteArray data);
    void disconnected(qintptr Descriptor);
    void finished();


public slots:

protected:
    void incomingConnection(qintptr handle);

private:
    QString File_crt="test.crt";
    QString File_key="test.key";


};

#endif // TCP_SERVER_H
