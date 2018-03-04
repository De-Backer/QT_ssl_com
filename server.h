#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QFormLayout>
#include <QDebug>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QPointer>
#include <QDir>
#include <QFileDialog>
#include <QLabel>

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>

#include "tcp_server.h"

class server : public QWidget
{
    Q_OBJECT
public:
    explicit server(QWidget *parent = nullptr);

signals:
    void sent_message(qintptr Descriptor,QByteArray data);

public slots:
    virtual void message(qintptr Descriptor,QByteArray data);

private:
    QPushButton *PB_run;
    QPushButton *zend_to_client;
    QTextEdit *ontvangen;
    QTextEdit *verzenden;
    QSpinBox *port;
    QString File_crt="test.crt";
    QString File_key="test.key";
    QLabel *L_File_crt;
    QLabel *L_File_key;

    qintptr descriptor;

private slots:
    void set_File_crt();
    void set_File_key();
    void on_PB_run_toggled(bool is);
    void on_PB_zend_to_client();
};

#endif // SERVER_H
