#ifndef DEMANDETCPPULL_H
#define DEMANDETCPPULL_H

#include <QTcpSocket>
#include <client.h>
#include <QList>

class DemandeTcpPull: public QObject
{
        Q_OBJECT

    public:
        DemandeTcpPull( QTcpSocket *sock, QList<QByteArray> &video);


    signals:
        void requeteComplete();
        void connexionTermine( DemandeTcpPull*);

    protected:
        QTcpSocket *sockControle;
        QTcpSocket sockDonnees;
        QByteArray requeteClient;
        QList<QByteArray> &images;
        int imgCourante;

        void connecteSockDonnee();
        void envoieImage();
        void finConnection();
        void demandeClient(QByteArray message);


    protected slots:
        void requeteRecu();
        void traiterRequete();
};

#endif // DEMANDETCPPULL_H
