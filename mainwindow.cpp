#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug()<<this<<"created";
}

MainWindow::~MainWindow()
{
    qDebug()<<this<<"destroyed";

}

void MainWindow::setup_Gui_client()
{
    qDebug()<<this<<"setup_Gui_client";

}

void MainWindow::setup_Gui_server()
{
    qDebug()<<this<<"setup_Gui_server";

}
