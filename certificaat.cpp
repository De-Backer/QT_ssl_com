#include "certificaat.h"

certificaat::certificaat(QWidget *parent) : QWidget(parent)
{
    qDebug()<<this<<"created";

    run_openssl = new QProcess(this);
    connect(run_openssl,&QProcess::stateChanged,this,&certificaat::ProcesstateChanged);

    //start gui

    QPointer<QPushButton> PB_crt =new QPushButton(tr("verander &crt"),this);
    connect(PB_crt, SIGNAL(clicked()),this, SLOT(set_File_crt()));

    QPointer<QPushButton> PB_key =new QPushButton(tr("verander &key"),this);
    connect(PB_key, SIGNAL(clicked()),this, SLOT(set_File_key()));

    PB_setup_certificaat = new QPushButton(tr("setup certificaat"));
    connect(PB_setup_certificaat,&QPushButton::clicked,this,&certificaat::setup_certificaat);

    LE_Land = new QLineEdit(this);
    LE_Land->setText(Land);
    LE_Staat = new QLineEdit(this);
    LE_Staat->setText(Staat);
    LE_Gebied = new QLineEdit(this);
    LE_Gebied->setText(Gebied);
    LE_Organisatie = new QLineEdit(this);
    LE_Organisatie->setText(Organisatie);
    LE_Organisatieonderdeel = new QLineEdit(this);
    LE_Organisatieonderdeel->setText(Organisatieonderdeel);
    LE_Algemene_naam = new QLineEdit(this);
    LE_Algemene_naam->setText(Algemene_naam);
    QPointer<QFormLayout> FL=new QFormLayout(this);
    FL->addRow(PB_crt);
    FL->addRow(PB_key);
    FL->addRow(tr("Land"),LE_Land);
    FL->addRow(tr("Staat"),LE_Staat);
    FL->addRow(tr("Gebied"),LE_Gebied);
    FL->addRow(tr("Organisatie"),LE_Organisatie);
    FL->addRow(tr("Organisatieonderdeel"),LE_Organisatieonderdeel);
    FL->addRow(tr("Algemene_naam"),LE_Algemene_naam);
    FL->addRow(PB_setup_certificaat);
    setLayout(FL);

    setWindowTitle(tr("setup certificaat"));
    hide();
}

void certificaat::setup_certificaat()
{
    qDebug()<<this<<"setup_certificaat";
    Land=LE_Land->text();
    Staat=LE_Staat->text();
    Gebied=LE_Gebied->text();
    Organisatie=LE_Organisatie->text();
    Organisatieonderdeel=LE_Organisatieonderdeel->text();
    Algemene_naam=LE_Algemene_naam->text();
    run_openssl->start("openssl req -nodes -newkey rsa:4096 -keyout \""+File_key+"\" -x509 -days 365 -out \""+File_crt+"\" -subj \"/C="+Land+"/ST="+Staat+"/L="+Gebied+"/O="+Organisatie+"/OU="+Organisatieonderdeel+"/CN="+Algemene_naam+"\"");
}

void certificaat::ProcesstateChanged()
{
    qDebug()<<this<<"ProcesstateChanged"
           <<run_openssl->state()
           <<run_openssl->readAll()
          <<run_openssl->errorString()
         <<run_openssl->exitStatus();
}

void certificaat::set_File_crt()
{
    File_crt=QFileDialog::getSaveFileName(this,tr("Save File"),
                                                 QDir::currentPath()+"/*.crt",
                                                 tr("data (*.crt)"));
}

void certificaat::set_File_key()
{
    File_key=QFileDialog::getSaveFileName(this,tr("Save File"),
                                                 QDir::currentPath()+"/*.key",
                                                 tr("data (*.key)"));
}
