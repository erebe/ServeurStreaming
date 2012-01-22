#ifndef SERVEURTCPPULL_H
#define SERVEURTCPPULL_H

#include <QTcpServer>
#include <QList>
#include "demandetcppull.h"

class ServeurTcpPull: public QTcpServer
{
        Q_OBJECT

    public:
        ServeurTcpPull( const QString& pathFlux, int port );

    protected:

    protected slots:
        void connexionAuServeur();
        void deleteSock( DemandeTcpPull* );

    protected:
        QList<QByteArray> mesImages;
        QList<DemandeTcpPull* > socks;

        void chargerVideo( const QString& pathFlux );

};

#endif // SERVEURTCPPULL_H
