#ifndef CERTIFICAAT_H
#define CERTIFICAAT_H

#include <QWidget>
#include <QFormLayout>
#include <QProcess>
#include <QDebug>
#include <QPushButton>
#include <QLineEdit>
#include <QPointer>
#include <QDir>
#include <QFileDialog>

class certificaat : public QWidget
{
    Q_OBJECT
public:
    explicit certificaat(QWidget *parent = nullptr);

signals:

public slots:
private:
    QPushButton *PB_setup_certificaat;
    QLineEdit *LE_Land;
    QLineEdit *LE_Staat;
    QLineEdit *LE_Gebied;
    QLineEdit *LE_Organisatie;
    QLineEdit *LE_Organisatieonderdeel;
    QLineEdit *LE_Algemene_naam;
    QProcess *run_openssl;

    QString Land="";
    QString Staat="";
    QString Gebied="";
    QString Organisatie="";
    QString Organisatieonderdeel="";
    QString Algemene_naam="test";

    QString File_crt="test.crt";
    QString File_key="test.key";

private slots:
    void setup_certificaat();
    void ProcesstateChanged();
    void set_File_crt();
    void set_File_key();

};

#endif // CERTIFICAAT_H
