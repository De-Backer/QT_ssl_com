#include "client.h"

client::client(QWidget *parent) : QWidget(parent)
{
    qDebug()<<this<<"created";
    setWindowTitle(tr("client"));
    hide();

}
