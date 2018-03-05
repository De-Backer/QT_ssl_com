#include "client.h"

client::client(QWidget *parent) : QWidget(parent)
{
    qDebug()<<this<<"created";
    setWindowTitle(tr("client"));

    connect_to_server =new QPushButton(tr("&Connect"),this);
    connect_to_server->setCheckable(true);
    connect(connect_to_server, SIGNAL(toggled(bool)),this,SLOT(on_PB_connect_to_server_toggled(bool)));

    port=new QSpinBox(this);

    port->setMinimum(0);
    port->setMaximum(60000);
    port->setValue(1234);

    IP=new QLineEdit(this);
    IP->setInputMask("000.000.000.000;");
    IP->setText("127.0.0.1");

    CN=new QLineEdit(this);
    CN->setText("test");


    verzenden=new QTextEdit(this);
    verzenden->setText("hallo server hoor je mij?");

    zend_to_server =new QPushButton(tr("&zend"),this);
    zend_to_server->setEnabled(false);
    connect(zend_to_server, SIGNAL(clicked(bool)),this,SLOT(on_PB_zend_to_server()));

    ontvangen=new QTextEdit(this);
    ontvangen->setReadOnly(true);

    QPointer<QFormLayout> FL=new QFormLayout(this);
    FL->addRow(tr("ip"),IP);
    FL->addRow(tr("port"),port);
    FL->addRow(tr("Algemene_naam"),CN);
    FL->addRow(connect_to_server);
    FL->addRow(verzenden);
    FL->addRow(zend_to_server);
    FL->addRow(ontvangen);
    setLayout(FL);

    hide();

}

void client::set_Descriptor(qintptr Descriptor)
{
    descriptor=Descriptor;
}

void client::get_message(qintptr Descriptor, QByteArray data)
{
    descriptor=Descriptor;
    ontvangen->setText("Descriptor "+QString::number(Descriptor)+": "+QString().fromUtf8(data)+"\n"+ontvangen->toPlainText());
}

void client::set_folder_crt()
{
    folder_crt=QFileDialog::getExistingDirectory(this,
                                                 tr("laad *.crt File's"),
                                                 QDir::currentPath(),
                                                 QFileDialog::ShowDirsOnly);
}

void client::on_PB_connect_to_server_toggled(bool is)
{
    qDebug()<<this<<"on_PB_connect_to_server_toggled"<<is;
    if(is)
    {
        my_ssl = new ssl_client_socket(this);
        connect(this, &client::disconnect,my_ssl,&ssl_client_socket::disconnect);
        connect(my_ssl, &ssl_client_socket::Connect_Descriptor, this, &client::set_Descriptor);
        connect(my_ssl, &ssl_client_socket::message, this, &client::get_message);
        connect(this, &client::sent_message, my_ssl, &ssl_client_socket::sent_message);
        //start de com
        my_ssl->SetCaCertificates(folder_crt);
        if(my_ssl->Connect(IP->text(),port->value(),CN->text()))
        {
            //Connect
            connect_to_server->setText(tr("&disconnect"));
            zend_to_server->setEnabled(true);
            IP->setEnabled(false);
            port->setEnabled(false);
            CN->setEnabled(false);
        } else {
            connect_to_server->setText(tr("&Connect failed"));

            qDebug()<<this<<"on_PB_connect_to_server_toggled"<<is<<"0 emit disconnect"<<descriptor;
            emit disconnect(descriptor);
            delete my_ssl;
        }

    } else {
        connect_to_server->setText(tr("&Connect"));
        zend_to_server->setEnabled(false);
        IP->setEnabled(true);
        port->setEnabled(true);
        CN->setEnabled(true);

        qDebug()<<this<<"on_PB_connect_to_server_toggled"<<is<<"1 emit disconnect"<<descriptor;
        emit disconnect(descriptor);
        delete my_ssl;
    }

}

void client::on_PB_zend_to_server()
{
    qDebug()<<this<<"on_PB_zend_to_server";
    // zend data
    emit sent_message(descriptor,verzenden->toPlainText().toLocal8Bit());
    // clear
    verzenden->clear();

}
