#ifndef SERVEURUDPPUSH_H
#define SERVEURUDPPUSH_H

#include <QUdpSocket>
#include <QMap>
#include "clientUdpPush.h"

class ServeurUdpPush: public QObject
{
        Q_OBJECT

    public:
        ServeurUdpPush( const QString& pathFlux, int port );

    protected slots:
        void lecturePaquet();
        void deleteSock( ClientUdpPush* );

    protected:
        typedef QMap< QString, ClientUdpPush*> ClientUdp;

        QUdpSocket sockControle;
        QList<QByteArray> mesImages;
        ClientUdp socks;
        QString client;
        int tpi;
        void chargerVideo(  const QString& pathFlux );

};

#endif // SERVEURTCPPULL_H
