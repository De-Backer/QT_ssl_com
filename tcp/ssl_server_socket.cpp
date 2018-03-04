#include "ssl_server_socket.h"

ssl_server_socket::ssl_server_socket(QObject *parent) : QObject(parent)
{
    qDebug() << this << "created";
    socket = new QSslSocket(this);
    if (!socket) {
       qWarning("not enough memory to create new QSslSocket");
       return;
    }
    connect(socket,&QSslSocket::encrypted,this,&ssl_server_socket::Encrypted);
    connect(socket, SIGNAL(sslErrors(QList<QSslError>)),this, SLOT(sslErrors(QList<QSslError>)));
    connect(socket,&QSslSocket::disconnected,this,&ssl_server_socket::disconnected);
    connect(socket,&QSslSocket::readyRead,this,&ssl_server_socket::readyRead);

}

ssl_server_socket::~ssl_server_socket()
{
    qDebug() << this << "destroyed";
}

void ssl_server_socket::SetSocket(qintptr Descriptor)
{
    qDebug() << this << "SetSocket" << Descriptor;
    //reseiver

    /* Emit a message indicating the address of the client. */
    socket->setSocketDescriptor(Descriptor);

    /* Start the server encryption process and wait for it to complete. */
    socket->startServerEncryption();
    if(socket->waitForEncrypted())
    {
        if(socket->isEncrypted())qDebug() <<Descriptor << "Session with client is now encrypted.";
    } else {
        qDebug() << Descriptor<< tr("An error occurred: %1.").arg(socket->errorString()).toLocal8Bit();
    }
}

void ssl_server_socket::SetLocalCertificate(QString file)
{
    qDebug() << this << "SetLocalCertificate" << file;
    /* Set the certificate */
    socket->setLocalCertificate(file);
}

void ssl_server_socket::SetPrivateKey(QString file)
{
    qDebug() << this << "SetPrivateKey" << file;
    /* Set the private key. */
    socket->setPrivateKey(file);
}

void ssl_server_socket::sent_message(qintptr Descriptor, QByteArray data)
{
    qDebug() << this << "sent_message" << Descriptor << data;
    if(socket->socketDescriptor()!=Descriptor) return;
    if(!socket->isEncrypted()) return;
    if(!socket->isWritable()) return;
    socket->write(data);
    socket->waitForBytesWritten();
}

void ssl_server_socket::readyRead()
{
    qDebug() << this << "readyRead";
    emit message(socket->socketDescriptor(),socket->readAll());
}

void ssl_server_socket::Encrypted()
{
    qDebug() << this << "Encrypted";
    if (!socket) return;                 // might have disconnected already

    QSslCipher ciph = socket->sessionCipher();
    qDebug()<<QString("%1, %2 (%3/%4) %5").arg(ciph.authenticationMethod())
              .arg(ciph.name()).arg(ciph.usedBits()).arg(ciph.supportedBits()).arg(ciph.protocolString());
}

void ssl_server_socket::disconnected()
{
    qDebug() << this << "disconnected" <<socket->socketDescriptor()<< "disconnected:"<<socket->errorString();
    /* Close the connection once the data is written. */

    //inform server of disconnected
    emit is_disconnected(socket->socketDescriptor());

    socket->disconnectFromHost();
    socket->close();
    socket->deleteLater();
    deleteLater();
    qDebug() << this << "! TODO: inform server of disconnected";
}

void ssl_server_socket::sslErrors(const QList<QSslError> &errors)
{
    qDebug()<<"sslErrors:"<<errors;
    foreach (const QSslError &error, errors)
    {
        qDebug()<<error.errorString();
    }
    qDebug()<<"end sslErrors";
}
