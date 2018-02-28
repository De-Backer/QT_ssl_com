#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug()<<this<<"created";

    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{
    qDebug()<<this<<"destroyed";

}

void MainWindow::createActions()
{
    qDebug()<<this<<"createActions";

    action_certificaat = new QAction(tr("&certificaat"), this);
    action_certificaat->setStatusTip(tr("setup certificaat"));
    connect(action_certificaat, &QAction::triggered, this, &MainWindow::setup_Gui_certificaat);

    action_client = new QAction(tr("&client"), this);
    action_client->setStatusTip(tr("setup client"));
    connect(action_client, &QAction::triggered, this, &MainWindow::setup_Gui_client);

    action_server = new QAction(tr("&server"), this);
    action_server->setStatusTip(tr("setup server"));
    connect(action_server, &QAction::triggered, this, &MainWindow::setup_Gui_server);

    action_Exit = new QAction(tr("&Exit"), this);
    action_Exit->setStatusTip(tr("Exit the program"));
    connect(action_Exit, &QAction::triggered, this, &MainWindow::close);


    closeAct = new QAction(tr("Cl&ose"), this);
    closeAct->setStatusTip(tr("Close the active window"));
    connect(closeAct, &QAction::triggered, mdiArea, &QMdiArea::closeActiveSubWindow);

    closeAllAct = new QAction(tr("Close &All"), this);
    closeAllAct->setStatusTip(tr("Close all the windows"));
    connect(closeAllAct, &QAction::triggered, mdiArea, &QMdiArea::closeAllSubWindows);

    tileAct = new QAction(tr("&Tile"), this);
    tileAct->setStatusTip(tr("Tile the windows"));
    connect(tileAct, &QAction::triggered, mdiArea, &QMdiArea::tileSubWindows);

    cascadeAct = new QAction(tr("&Cascade"), this);
    cascadeAct->setStatusTip(tr("Cascade the windows"));
    connect(cascadeAct, &QAction::triggered, mdiArea, &QMdiArea::cascadeSubWindows);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);

}

void MainWindow::createMenus()
{
    qDebug()<<this<<"createMenus";

    QMenu *menu_File = menuBar()->addMenu(tr("&File"));
    menu_File->addAction(action_certificaat);
    menu_File->addAction(action_client);
    menu_File->addAction(action_server);
    menu_File->addAction(action_Exit);

    QMenu *windowMenu = menuBar()->addMenu(tr("&Window"));
    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascadeAct);
    windowMenu->addSeparator();
    windowMenu->addAction(closeAct);
    windowMenu->addAction(closeAllAct);

    QMenu *helpMenu = menuBar()->addMenu(tr("&help"));
    helpMenu->addAction(aboutQtAct);

}

void MainWindow::setup_Gui_client()
{
    qDebug()<<this<<"setup_Gui_client";

}

void MainWindow::setup_Gui_server()
{
    qDebug()<<this<<"setup_Gui_server";

}

void MainWindow::setup_Gui_certificaat()
{
    qDebug()<<this<<"setup_Gui_certificaat";
}

void MainWindow::setup_certificaat()
{
    qDebug()<<this<<"setup_certificaat";

    run_openssl.start("openssl req -nodes -newkey rsa:4096 -keyout test.key -x509 -days 365 -out test.crt -subj \"/C="+Land+"/ST="+Staat+"/L="+Gebied+"/O="+Organisatie+"/OU="+Organisatieonderdeel+"/CN="+Algemene_naam+"\"");
}
