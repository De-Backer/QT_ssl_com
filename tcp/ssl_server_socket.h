#ifndef SSL_SERVER_SOCKET_H
#define SSL_SERVER_SOCKET_H

#include <QObject>
#include <QDebug>

#include <QSslSocket>
#include <QSslCipher>
#include <QSslConfiguration>

#include <QHostAddress>

class ssl_server_socket : public QObject
{
    Q_OBJECT
public:
    explicit ssl_server_socket(QObject *parent = nullptr);
    ~ssl_server_socket();

    void SetSocket(qintptr Descriptor);
    void SetLocalCertificate(QString file);
    void SetPrivateKey(QString file);

signals:
    void message(qintptr Descriptor,QByteArray data);
    void is_disconnected(qintptr Descriptor);


public slots:
    virtual void sent_message(qintptr Descriptor,QByteArray data);

protected:
    QSslSocket *socket;

private slots:
    void readyRead();
    void Encrypted();
    void disconnected();
    void sslErrors(const QList<QSslError> &errors);
};

#endif // SSL_SERVER_SOCKET_H
