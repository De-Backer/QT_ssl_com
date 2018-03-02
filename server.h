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

#include "ssl.h"

class server : public QWidget
{
    Q_OBJECT
public:
    explicit server(QWidget *parent = nullptr);

signals:

public slots:

private:
    QTextEdit *ontvangen;
    QTextEdit *verzenden;
    QSpinBox *port;
    QString File_crt="test.crt";
    QString File_key="test.key";
    QLabel *L_File_crt;
    QLabel *L_File_key;

private slots:
    void set_File_crt();
    void set_File_key();
};

#endif // SERVER_H
