#include <QtCore/QCoreApplication>
#include <QtNetwork>
#include "Http/serveur.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Serveur serveurHttp("startup.txt");


    return a.exec();
}
