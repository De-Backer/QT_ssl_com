#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QDebug>

#include "ssl.h"

class server : public QWidget
{
    Q_OBJECT
public:
    explicit server(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // SERVER_H
