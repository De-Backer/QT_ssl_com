#ifndef SSL_H
#define SSL_H

#include <QObject>
#include <QDebug>

#include <QSslSocket>
#include <QSslCipher>

#include <QHostAddress>

class ssl : public QObject
{
    Q_OBJECT
public:
    explicit ssl(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SSL_H
