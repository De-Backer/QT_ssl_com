#ifndef SSL_H
#define SSL_H

#include <QObject>
#include <QDebug>

#include <QSslSocket>
#include <QSslCipher>
#include <QSslConfiguration>

#include <QHostAddress>

class ssl_client_socket : public QObject
{
    Q_OBJECT
public:
    explicit ssl_client_socket(QObject *parent = nullptr);
    ~ssl_client_socket();
    bool Connect(QString IP, int port,QString sslPeerName);
    void SetCaCertificates(QString file);


signals:
    void message(qintptr Descriptor,QByteArray data);
    void Connect_Descriptor(qintptr Descriptor);

public slots:
    virtual void sent_message(qintptr Descriptor,QByteArray data);
    virtual void disconnect(qintptr Descriptor);

protected:
    QSslSocket *socket;

private slots:
    void readyRead();
    void Encrypted();
    void disconnected();
    void sslErrors(const QList<QSslError> &errors);

};

#endif // SSL_H
