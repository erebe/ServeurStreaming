#ifndef SERVEUR_H
#define SERVEUR_H

#include <QTcpServer>
#include <QString>
#include "client.h"

class Serveur : public QTcpServer
{
        Q_OBJECT

    public:
        Serveur(const char* path);
        ~Serveur();


    protected:
        QList<Client *> clientsConnectes;
        QByteArray catalogue;
        QString fichierPath;
        int port;
        void chargerCatalogue();
        QList<QObject*> flux;



    protected slots:
        void connexionAuServeur();



};

#endif // SERVEUR_H
