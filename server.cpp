#include "server.h"

server::server(QWidget *parent) : QWidget(parent)
{
    qDebug()<<this<<"created";

    L_File_crt = new QLabel(File_crt);
    L_File_key = new QLabel(File_key);

    set_File_crt();
    set_File_key();

    QPointer<QPushButton> PB_crt =new QPushButton(tr("verander &crt"),this);
    connect(PB_crt, SIGNAL(clicked()),this, SLOT(set_File_crt()));

    QPointer<QPushButton> PB_key =new QPushButton(tr("verander &key"),this);
    connect(PB_key, SIGNAL(clicked()),this, SLOT(set_File_key()));

    QPointer<QPushButton> PB_run =new QPushButton(tr("&run"),this);
//    connect(connect_to_server, SIGNAL(clicked()),
//                         this,SLOT(start_transmitter()));

    QPointer<QPushButton> PB_stop =new QPushButton(tr("&stop"),this);
//    connect(Button_disconnect, SIGNAL(clicked()),
//                         this,SLOT(disconnect_transmitter()));


    port=new QSpinBox(this);

    port->setMinimum(0);
    port->setMaximum(60000);
    port->setValue(1234);

    verzenden=new QTextEdit(this);
    verzenden->setText("hallo client hoor je mij?");

    QPointer<QPushButton> zend_to_server =new QPushButton(tr("&zend"),this);
//    connect(zend_to_server, SIGNAL(clicked()),
//                         this,SLOT(zend_transmitter()));

    ontvangen=new QTextEdit(this);
    ontvangen->setReadOnly(true);

    setWindowTitle(tr("server"));

    QPointer<QFormLayout> FL=new QFormLayout(this);
    FL->addRow(L_File_crt);
    FL->addRow(PB_crt);
    FL->addRow(L_File_key);
    FL->addRow(PB_key);
    FL->addRow(tr("port"),port);
    FL->addRow(PB_run);
    FL->addRow(PB_stop);
    FL->addRow(verzenden);
    FL->addRow(zend_to_server);
    FL->addRow(ontvangen);
    setLayout(FL);
    hide();

}

void server::set_File_crt()
{
    File_crt=QFileDialog::getOpenFileName(this,tr("laad File"),
                                                 QDir::currentPath(),
                                                 tr("data (*crt)"));
    L_File_crt->setText(File_crt);
}

void server::set_File_key()
{
    File_key=QFileDialog::getOpenFileName(this,tr("laad File"),
                                                 QDir::currentPath(),
                                                 tr("data (*key)"));
    L_File_key->setText(File_key);
}
