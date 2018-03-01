#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QApplication>
#include <QStatusBar>

#include "certificaat.h"
#include "client.h"
#include "server.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
private:
    certificaat *my_certificaat;
    client *my_client;
    server *my_server;
    QMdiArea *mdiArea;

    void createActions();
    void createMenus();
    QAction *action_Exit,
            *closeAct,
            *closeAllAct,
            *tileAct,
            *cascadeAct,
            *action_certificaat,
            *action_client,
            *action_server,
            *aboutQtAct;
    QMenu *windowMenu;
    void add_window_action(QWidget *widget);


private slots:
    void Gui_client();
    void Gui_server();
    void Gui_certificaat();
};

#endif // MAINWINDOW_H
