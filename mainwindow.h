#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QProcess>
#include <QMenu>
#include <QMenuBar>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QApplication>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
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

    QProcess run_openssl;
    QString Land="";
    QString Staat="";
    QString Gebied="";
    QString Organisatie="";
    QString Organisatieonderdeel="";
    QString Algemene_naam="test";

private slots:
    void setup_Gui_client();
    void setup_Gui_server();
    void setup_Gui_certificaat();
    void setup_certificaat();
};

#endif // MAINWINDOW_H
