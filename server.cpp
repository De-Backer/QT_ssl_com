#include "server.h"

server::server(QWidget *parent) : QWidget(parent)
{
    qDebug()<<this<<"created";
    setWindowTitle(tr("server"));
    hide();

}
