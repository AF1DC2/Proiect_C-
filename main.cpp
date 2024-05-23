#include "fereastraprincipala.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FereastraPrincipala w; /*Creare obiect fereastra*/
    w.show(); /*Apelare functie de afisare*/
    w.Default(); /*Apelare functie de configurare default*/
    return a.exec();
}
