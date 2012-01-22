#include "serveurUdpPull.h"
#include "clientUdpPull.h"
#include <QFile>
#include <QDebug>

ServeurUdpPull::ServeurUdpPull( const QString& pathFlux, int port )
{

    chargerVideo( pathFlux );
    sockControle.bind( QHostAddress::Any, port );

    connect(&sockControle, SIGNAL(readyRead()),
            this, SLOT(lecturePaquet()) );

}

void ServeurUdpPull::lecturePaquet()
{
    QByteArray paquet;
    QHostAddress address;
    quint16 port;

    while (sockControle.hasPendingDatagrams()) {

        paquet.resize(sockControle.pendingDatagramSize());
        sockControle.readDatagram(paquet.data(), paquet.size(),
                                  &address, &port );


        QString clef = address.toString()+port;
        ClientUdp::iterator it = socks.find( clef );

        if( it == socks.end() || it.key() != clef ) {
            it = socks.insert( clef, new ClientUdpPull(address, port, mesImages) );

            connect(it.value(), SIGNAL(connexionTermine(ClientUdpPull*)),
                    this, SLOT(deleteSock(ClientUdpPull*)));
        }

        it.value()->traiterRequete( paquet );

    }

}

void ServeurUdpPull::deleteSock( ClientUdpPull* sender )
{ 
    socks.remove( socks.key(sender) );
    delete sender;
}

void ServeurUdpPull::chargerVideo( const QString& pathFlux )
{
    QFile flux(pathFlux);
    if (!flux.open(QIODevice::ReadOnly) )
        return;

    QString buffer;
    while( !buffer.startsWith("IPS") )
    { buffer = flux.readLine(); }

    while( !flux.atEnd() ) {
        QFile image( flux.readLine().trimmed().replace('\\', '/') );
        image.open(QIODevice::ReadOnly);
        mesImages.push_back( image.readAll() );
    }

}
