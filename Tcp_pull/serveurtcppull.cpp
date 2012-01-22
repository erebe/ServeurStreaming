#include "serveurtcppull.h"
#include "demandetcppull.h"
#include <QFile>
#include <QDebug>

ServeurTcpPull::ServeurTcpPull( const QString& pathFlux, int port):
    QTcpServer()
{
    chargerVideo( pathFlux );
    connect(this, SIGNAL(newConnection()),
            this, SLOT(connexionAuServeur()) );

    listen( QHostAddress::Any, port );
    waitForNewConnection();
    //attend une connection
}

void ServeurTcpPull::connexionAuServeur()
{
    DemandeTcpPull* sock = new DemandeTcpPull( nextPendingConnection(), mesImages);
    socks << sock;
    connect( sock, SIGNAL(connexionTermine(DemandeTcpPull*)),
             this, SLOT(deleteSock(DemandeTcpPull*))  );
}

void ServeurTcpPull::deleteSock( DemandeTcpPull* sender )
{
    socks.removeOne(sender);
    sender->deleteLater();
}

void ServeurTcpPull::chargerVideo( const QString& pathFlux )
{
    QFile flux(pathFlux);
    if (!flux.open(QIODevice::ReadOnly) ) return;

    QString buffer;
    while( !buffer.startsWith("IPS") )
    { buffer = flux.readLine(); }

    while( !flux.atEnd() ) {
        QFile image( flux.readLine().trimmed().replace('\\', '/') );
        image.open(QIODevice::ReadOnly);
        mesImages.push_back( image.readAll() );
    }
}
