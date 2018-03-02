#ifndef SSL_H
#define SSL_H

#include <QObject>
#include <QDebug>

#include <QSslSocket>
#include <QSslCipher>
#include <QSslConfiguration>

#include <QHostAddress>

class ssl : public QObject
{
    Q_OBJECT
public:
    explicit ssl(QObject *parent = nullptr);
    bool Connect(QString IP, int port,QString sslPeerName);
    void Connect(QString IP, int port,QString sslPeerName, QByteArray data);
    void SetSocket(qintptr Descriptor);
    void SetCaCertificates(QString file);
    void SetLocalCertificate(QString file);
    void SetPrivateKey(QString file);

signals:
    void message(qintptr Descriptor,QByteArray data);
    void Connect_Descriptor(qintptr Descriptor);

public slots:
    void sent_message(qintptr Descriptor,QByteArray data);
    void disconnect(qintptr Descriptor);

private:
    QSslSocket *socket;

private slots:
    void readyRead();
    void Encrypted();
    void disconnected();
    void sslErrors(const QList<QSslError> &errors);

};

#endif // SSL_H
