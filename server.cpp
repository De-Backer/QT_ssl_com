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

    PB_run =new QPushButton(tr("&run"),this);
    PB_run->setCheckable(true);
    connect(PB_run, SIGNAL(toggled(bool)),this,SLOT(on_PB_run_toggled(bool)));



    port=new QSpinBox(this);

    port->setMinimum(0);
    port->setMaximum(60000);
    port->setValue(1234);

    verzenden=new QTextEdit(this);
    verzenden->setText("hallo client hoor je mij?");

    zend_to_client =new QPushButton(tr("&zend"),this);
    zend_to_client->setEnabled(false);
    connect(zend_to_client, SIGNAL(clicked(bool)),this,SLOT(on_PB_zend_to_client()));

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
    FL->addRow(verzenden);
    FL->addRow(zend_to_client);
    FL->addRow(ontvangen);
    setLayout(FL);
    hide();

}

void server::message(qintptr Descriptor, QByteArray data)
{
    qDebug()<<this<<"message"<<Descriptor<<data;
    descriptor=Descriptor;
    ontvangen->setText(ontvangen->toPlainText()+"\n"+QString().fromUtf8(data));

}

void server::disconnected(qintptr Descriptor)
{
    qDebug()<<this<<"disconnected"<<Descriptor;
}

void server::set_File_crt()
{
    qDebug()<<this<<"set_File_crt";
    File_crt=QFileDialog::getOpenFileName(this,tr("laad File"),
                                                 QDir::currentPath(),
                                                 tr("data (*crt)"));
    L_File_crt->setText(File_crt);
}

void server::set_File_key()
{
    qDebug()<<this<<"set_File_key";
    File_key=QFileDialog::getOpenFileName(this,tr("laad File"),
                                                 QDir::currentPath(),
                                                 tr("data (*key)"));
    L_File_key->setText(File_key);
}

void server::on_PB_run_toggled(bool is)
{
    qDebug()<<this<<"on_PB_run_toggled"<<is;
    if(is)
    {
        PB_run->setText(tr("&stop"));
        tcp_server *my_tcp_server = new tcp_server();//no parent
        connect(my_tcp_server,&tcp_server::disconnected,this,&server::disconnected,Qt::QueuedConnection);
        connect(my_tcp_server,&tcp_server::message,this,&server::message,Qt::QueuedConnection);
        connect(this,&server::sent_message,my_tcp_server,&tcp_server::sent_message,Qt::QueuedConnection);
        my_tcp_server->StartServer(port->value(),File_crt,File_key);
        QThread *thread_Receiver = new QThread;
        connect(thread_Receiver, SIGNAL(finished()),thread_Receiver, SLOT(deleteLater()));
        my_tcp_server->moveToThread(thread_Receiver);
        thread_Receiver->start();
        zend_to_client->setEnabled(true);

    } else {
        PB_run->setText(tr("&run"));
        zend_to_client->setEnabled(false);

        qDebug()<<this<<"on_PB_run_toggled ToDo stop server";
    }
}

void server::on_PB_zend_to_client()
{
    qDebug()<<this<<"on_PB_zend_to_client";
    // zend data
    emit sent_message(descriptor,verzenden->toPlainText().toLocal8Bit());
    // clear
    verzenden->clear();
}
