#include "ssl_client_socket.h"

ssl_client_socket::ssl_client_socket(QObject *parent) : QObject(parent)
{
    qDebug() << this << "created";
    socket = new QSslSocket(this);
    if (!socket) {
       qWarning("not enough memory to create new QSslSocket");
       return;
    }
    connect(socket,&QSslSocket::encrypted,this,&ssl_client_socket::Encrypted);
    connect(socket, SIGNAL(sslErrors(QList<QSslError>)),this, SLOT(sslErrors(QList<QSslError>)));
    connect(socket,&QSslSocket::disconnected,this,&ssl_client_socket::disconnected);
    connect(socket,&QSslSocket::readyRead,this,&ssl_client_socket::readyRead);

}

ssl_client_socket::~ssl_client_socket()
{
    qDebug() << this << "destroyed";
}

bool ssl_client_socket::Connect(QString IP, int port, QString sslPeerName)
{
    qDebug() << this << "Connect: " << IP << " at port: " << port << "CN" << sslPeerName;
    //transmiter

    // Note: IP must match the cert CN or alternative name.
    socket->connectToHostEncrypted(IP,port,sslPeerName);

    if(socket->waitForConnected())
    {
        qDebug() <<socket->socketDescriptor() << "connected ip:"+socket->peerAddress().toString().toLocal8Bit();
        emit Connect_Descriptor(socket->socketDescriptor());
        if (socket->waitForEncrypted())
        {
            if(socket->isEncrypted())qDebug() << socket->socketDescriptor() << "Session with server is now encrypted.";
            qDebug() <<"protocol: "<< socket->protocol()<<"=="<<QSsl::SecureProtocols<<"== SecureProtocol";
        } else {
            qDebug() <<"socket->waitForEncrypted()==0"<<socket->errorString();
            qDebug() <<socket->socketDescriptor()<<tr("An error occurred: %1.").arg(socket->errorString()).toLocal8Bit();
        }
    } else {
        qDebug() <<socket->socketDescriptor()<<"Not Connected!";
        return false;
    }
    return true;
}

void ssl_client_socket::SetCaCertificates(QString file)
{
    qDebug() << this << "SetCaCertificates" << file;
    QList<QSslCertificate> trustedCas;
    foreach (const QSslCertificate &cert, QSslCertificate::fromPath(file+"*.crt", QSsl::Pem,
                                                             QRegExp::Wildcard)) {
        trustedCas.append(cert);
        qDebug() << this << cert;
    }
    if (trustedCas.empty()) {
        qFatal("Error: no trusted Cas");
    }

    //socket->setCaCertificates(trustedCas);
    //Use QSslConfiguration::setCaCertificates() instead.

    QSslConfiguration config = socket->sslConfiguration();
    config.setCaCertificates(trustedCas);
    socket->setSslConfiguration(config);

}

void ssl_client_socket::sent_message(qintptr Descriptor, QByteArray data)
{
    qDebug() << this << "sent_message" << Descriptor << data;
    if(socket->socketDescriptor()!=Descriptor) return;
    if(!socket->isEncrypted()) return;
    if(!socket->isWritable()) return;
    socket->write(data);
    socket->waitForBytesWritten();
}

void ssl_client_socket::disconnect(qintptr Descriptor)
{
    qDebug() << this << "disconnect"<< Descriptor;
    if(socket->socketDescriptor()!=Descriptor) return;
    socket->close();
    socket->deleteLater();
    //emit Connect_Descriptor(0);//client
}

void ssl_client_socket::readyRead()
{
    qDebug() << this << "readyRead";
    emit message(socket->socketDescriptor(),socket->readAll());
}

void ssl_client_socket::Encrypted()
{
    qDebug() << this << "Encrypted";
    if (!socket) return;                 // might have disconnected already

    QSslCipher ciph = socket->sessionCipher();
    qDebug()<<QString("%1, %2 (%3/%4) %5").arg(ciph.authenticationMethod())
                     .arg(ciph.name()).arg(ciph.usedBits()).arg(ciph.supportedBits()).arg(ciph.protocolString());
}

void ssl_client_socket::disconnected()
{
    qDebug() << this << "disconnected" <<socket->socketDescriptor()<< "disconnected:"<<socket->errorString();
    /* Close the connection once the data is written. */
    socket->disconnectFromHost();
    socket->close();
    socket->deleteLater();
    deleteLater();
}

void ssl_client_socket::sslErrors(const QList<QSslError> &errors)
{
    qDebug()<<"sslErrors:"<<errors;
    foreach (const QSslError &error, errors)
    {
        qDebug()<<error.errorString();
    }
    qDebug()<<"end sslErrors";
}
