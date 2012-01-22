#include "serveurUdpPush.h"
#include "clientUdpPush.h"
#include <QFile>
#include <QDebug>
#include <QStringList>

ServeurUdpPush::ServeurUdpPush( const QString& pathFlux, int port )
{

    chargerVideo( pathFlux );
    sockControle.bind( QHostAddress::Any, port );

    connect(&sockControle, SIGNAL(readyRead()),
            this, SLOT(lecturePaquet()) );

}

void ServeurUdpPush::lecturePaquet()
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
            it = socks.insert( clef, new ClientUdpPush(address, port, mesImages, tpi) );

            connect(it.value(), SIGNAL(connexionTermine(ClientUdpPush*)),
                    this, SLOT(deleteSock(ClientUdpPush*)));
        }

        it.value()->traiterRequete( paquet );

    }

}

void ServeurUdpPush::deleteSock( ClientUdpPush* sender )
{ 
    socks.remove( socks.key(sender) );
    delete sender;
}

void ServeurUdpPush::chargerVideo( const QString& pathFlux )
{

    QFile flux(pathFlux);
    if (!flux.open(QIODevice::ReadOnly) ) return;

    QString buffer;
    while( !buffer.startsWith("IPS") )
    { buffer = flux.readLine(); }

    tpi = 1 / buffer.split(' ')[1].trimmed().toDouble() * 1000;


    while( !flux.atEnd() ) {
        QFile image( flux.readLine().trimmed().replace('\\', '/') );
        image.open(QIODevice::ReadOnly);
        mesImages.push_back( image.readAll() );
    }

}
