#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QDebug>

#include "ssl.h"

class client : public QWidget
{
    Q_OBJECT
public:
    explicit client(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // CLIENT_H
