#include "tcp_server.h"

tcp_server::tcp_server(QObject *parent) :
    QTcpServer(parent)
{
    qDebug() << this << "created";
}

tcp_server::~tcp_server()
{
    qDebug() << this << "destroyed";
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

void tcp_server::close()
{
    qDebug() << this << "closing server";
    emit finished();
    QTcpServer::close();
}

void tcp_server::incomingConnection(qintptr handle)
{
    qDebug() << this << "incomingConnection" << handle;
    ssl_server_socket *my_socket = new ssl_server_socket(this);
    connect(my_socket,&ssl_server_socket::message,this,&tcp_server::message);
    connect(this,&tcp_server::sent_message,my_socket,&ssl_server_socket::sent_message);
    connect(my_socket,&ssl_server_socket::is_disconnected,this,&tcp_server::disconnected);
    //todo
    //connect(socket,&ssl_socket::destroyed);
    my_socket->SetLocalCertificate(File_crt);
    my_socket->SetPrivateKey(File_key);
    my_socket->SetSocket(handle);
}
