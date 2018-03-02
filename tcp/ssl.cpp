#include "ssl.h"

ssl::ssl(QObject *parent) : QObject(parent)
{
    qDebug()<<this<<"created";
    socket = new QSslSocket(this);
    if (!socket) {
       qWarning("not enough memory to create new QSslSocket");
       return;
    }

}

bool ssl::Connect(QString IP, int port, QString sslPeerName)
{
    qDebug() << this <<"transmiter Connect: "<<IP<<" at port: "<<port << "CN" << sslPeerName;
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

void ssl::Connect(QString IP, int port, QString sslPeerName, QByteArray data)
{
    qDebug() << this << "Connect" << IP << port << data;
    if(!Connect(IP,port,sslPeerName)) return;
    if (!socket) return;                 // might have disconnected already
    sent_message(socket->socketDescriptor(),data);
}

void ssl::SetSocket(qintptr Descriptor)
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

void ssl::SetCaCertificates(QString file)
{
    qDebug() << this << "SetCaCertificates" << file;
    QList<QSslCertificate> trustedCas;
    foreach (const QSslCertificate &cert, QSslCertificate::fromPath(file+"*.crt", QSsl::Pem,
                                                             QRegExp::Wildcard)) {
        trustedCas.append(cert);
        qDebug()<<this<<cert;
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

void ssl::SetLocalCertificate(QString file)
{
    qDebug() << this << "SetLocalCertificate" << file;
    /* Set the certificate */
    socket->setLocalCertificate(file);


}

void ssl::SetPrivateKey(QString file)
{
    qDebug() << this << "SetPrivateKey" << file;
    /* Set the private key. */
    socket->setPrivateKey(file);

}

void ssl::sent_message(qintptr Descriptor, QByteArray data)
{
    qDebug() << this << "sent_message"<< Descriptor;
    if(socket->socketDescriptor()!=Descriptor) return;
    if(!socket->isEncrypted()) return;
    if(!socket->isWritable()) return;
    socket->write(data);
    socket->waitForBytesWritten();
}

void ssl::disconnect(qintptr Descriptor)
{
    qDebug() << this << "disconnect"<< Descriptor;
    if(socket->socketDescriptor()!=Descriptor) return;
    socket->close();
}

void ssl::readyRead()
{
    qDebug() << "readyRead";
    emit message(socket->socketDescriptor(),socket->readAll());
}

void ssl::Encrypted()
{
    qDebug() << this << "Encrypted";
    if (!socket) return;                 // might have disconnected already

    QSslCipher ciph = socket->sessionCipher();
    qDebug()<<QString("%1, %2 (%3/%4) %5").arg(ciph.authenticationMethod())
                     .arg(ciph.name()).arg(ciph.usedBits()).arg(ciph.supportedBits()).arg(ciph.protocolString());
}

void ssl::disconnected()
{
    qDebug() << this << "disconnected";
    qDebug() <<socket->socketDescriptor()<< "disconnected:"<<socket->errorString();
    /* Close the connection once the data is written. */
    socket->disconnectFromHost();
    deleteLater();
}

void ssl::sslErrors(const QList<QSslError> &errors)
{

    qDebug()<<"sslErrors:"<<errors;
    foreach (const QSslError &error, errors)
    {
        qDebug()<<error.errorString();
    }
    qDebug()<<"end sslErrors";
}
