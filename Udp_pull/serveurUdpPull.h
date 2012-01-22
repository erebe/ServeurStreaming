#ifndef SERVEURUDPPULL_H
#define SERVEURUDPPULL_H

#include <QUdpSocket>
#include <QMap>
#include "clientUdpPull.h"

class ServeurUdpPull: public QObject
{
        Q_OBJECT

    public:
        ServeurUdpPull( const QString& pathFlux, int port );

    protected slots:
        void lecturePaquet();
        void deleteSock( ClientUdpPull* );

    protected:
        typedef QMap< QString, ClientUdpPull*> ClientUdp;

        QUdpSocket sockControle;
        QList<QByteArray> mesImages;
        ClientUdp socks;
        QString client;
        void chargerVideo( const QString& pathFlux);

};

#endif // SERVEURTCPPULL_H
