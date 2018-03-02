#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QFormLayout>
#include <QDebug>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QPointer>

#include <QDir>
#include <QFileDialog>
#include <QLabel>

#include "ssl.h"

class client : public QWidget
{
    Q_OBJECT
public:
    explicit client(QWidget *parent = nullptr);

signals:
    void sent_message(qintptr Descriptor,QByteArray data);

public slots:
    void set_Descriptor(qintptr Descriptor);
    void get_message(qintptr Descriptor,QByteArray data);

private:
    QPushButton *connect_to_server;
    QPushButton *zend_to_server;
    QTextEdit *ontvangen;
    QTextEdit *verzenden;
    QLineEdit *IP;
    QSpinBox *port;
    QLineEdit *CN;

    QString folder_crt=QDir::currentPath();
    ssl *my_ssl;
    qintptr descriptor;

private slots:
    void set_folder_crt();
    void on_PB_connect_to_server_toggled(bool is);
    void on_PB_zend_to_server();
};

#endif // CLIENT_H
