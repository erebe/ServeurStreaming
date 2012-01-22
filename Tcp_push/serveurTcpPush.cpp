#include "serveurTcpPush.h"
#include "clientTcpPush.h"
#include <QFile>
#include <QString>
#include <QDebug>
#include <QStringList>

ServeurTcpPush::ServeurTcpPush( const QString& pathFlux, int port )
    : QTcpServer()
{

    chargerVideo( pathFlux );
    connect(this, SIGNAL(newConnection()),
            this, SLOT(connexionAuServeur()) );

    listen( QHostAddress::Any, port );
    waitForNewConnection();
    //attend une connection
}

void ServeurTcpPush::connexionAuServeur()
{
    ClientTcpPush* sock = new ClientTcpPush( nextPendingConnection(), mesImages, tpi);
    socks << sock;
    connect( sock, SIGNAL(connexionTermine(ClientTcpPush*)),
             this, SLOT(deleteSock(ClientTcpPush*))  );

}

void ServeurTcpPush::deleteSock( ClientTcpPush* sender )
{
    socks.removeOne(sender);
    sender->deleteLater();
}

void ServeurTcpPush::chargerVideo( const QString& pathFlux )
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
