#ifndef SSL_H
#define SSL_H

#include <QObject>
#include <QDebug>

#include <QSslSocket>
#include <QSslCipher>
#include <QSslConfiguration>

#include <QHostAddress>

class ssl_socket : public QObject
{
    Q_OBJECT
public:
    // all
    explicit ssl_socket(QObject *parent = nullptr);

    // client of all(-en server?)
    bool Connect(QString IP, int port,QString sslPeerName);
    void SetCaCertificates(QString file);

    // server
    void SetSocket(qintptr Descriptor);
    void SetLocalCertificate(QString file);
    void SetPrivateKey(QString file);

signals:
    // all
    void message(qintptr Descriptor,QByteArray data);

    // client
    void Connect_Descriptor(qintptr Descriptor);

public slots:
    // all
    virtual void sent_message(qintptr Descriptor,QByteArray data);
    // client of all(-en server?)
    virtual void disconnect(qintptr Descriptor);

private:
    // all
    QSslSocket *socket;

private slots:
    void readyRead();
    void Encrypted();
    void disconnected();
    void sslErrors(const QList<QSslError> &errors);

};

#endif // SSL_H
