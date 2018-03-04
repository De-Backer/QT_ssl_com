#include "tcp_server.h"

tcp_server::tcp_server(QObject *parent) :
    QTcpServer(parent)
{
    qDebug() << this << "created";
}

void tcp_server::StartServer(int port, QString file_crt, QString file_key)
{
    qDebug() << this << "StartServer";
    File_crt=file_crt;
    File_key=file_key;
    if(listen(QHostAddress::AnyIPv4,port))
    {
        qDebug() << this << "started";
    }
    else
    {
        qDebug() << this << "not started!";
    }
}

void tcp_server::incomingConnection(qintptr handle)
{
    qDebug() << this << "incomingConnection" << handle;
    ssl_socket *socket = new ssl_socket(this);
    connect(socket,&ssl_socket::message,this,&tcp_server::message);
    connect(this,&tcp_server::sent_message,socket,&ssl_socket::sent_message);
    //todo
    //connect(socket,&ssl_socket::destroyed);
    socket->SetLocalCertificate(File_crt);
    socket->SetPrivateKey(File_key);
    socket->SetSocket(handle);
}
