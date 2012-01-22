#ifndef SERVEURTCPPUSH_H
#define SERVEURTCPPUSH_H

#include <QTcpServer>
#include <QList>
#include "clientTcpPush.h"

class ServeurTcpPush: public QTcpServer
{
        Q_OBJECT

    public:
        ServeurTcpPush( const QString& pathFlux, int port );

    protected slots:
        void connexionAuServeur();
        void deleteSock( ClientTcpPush* );

    protected:
        QList<QByteArray> mesImages;
        QList<ClientTcpPush* > socks;
        int tpi;
        void chargerVideo( const QString& pathFlux );

};

#endif // SERVEURTCPPULL_H
