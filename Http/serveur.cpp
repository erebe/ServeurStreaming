#include <QTcpSocket>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include "client.h"
#include "serveur.h"

#include "Tcp_pull/serveurtcppull.h"
#include "Tcp_push/serveurTcpPush.h"
#include "Udp_pull/serveurUdpPull.h"
#include "Udp_push/serveurUdpPush.h"
#include "Multi/serveurMulti.h"


Serveur::Serveur( const char* path):
    QTcpServer(), fichierPath(path)
{

    chargerCatalogue();
    connect(this, SIGNAL(newConnection()),
            this, SLOT(connexionAuServeur()) );

    listen( QHostAddress::Any, port );
    waitForNewConnection();
    //attend une connection

}

Serveur::~Serveur() {

    foreach( QObject* serveur, flux )
        delete serveur;
}

//ajoute un client Ã  la liste et attend une requete
void Serveur::connexionAuServeur()
{
       QTcpSocket* sock = nextPendingConnection();
       Client *client = new Client(sock, catalogue);
       clientsConnectes << client;

    //    qDebug() << "Nouvelle connection entrante !";
}

void Serveur::chargerCatalogue()
{
    QFile fichier(fichierPath);

    if ( !fichier.open( QIODevice::ReadOnly))
        { return;  }


     QString portServ, protoServ, address;

     catalogue = fichier.readLine().trimmed();
     catalogue += "\r\n";
     portServ = fichier.readLine().trimmed();
     port = portServ.split(' ')[1].toInt();
     catalogue += portServ;
     catalogue += "\r\n";


     QString ficPath;
     while( fichier.canReadLine() ){
           ficPath = fichier.readLine().trimmed();
           QFile flux( ficPath );


           if( !flux.open( QIODevice::ReadOnly ) )
           { continue;}

           catalogue += "Object ID=";
           catalogue += flux.readLine().split(' ')[1].trimmed();
           catalogue += " name=";
           catalogue += flux.readLine().split(' ')[1].trimmed();
           catalogue += " type=";
           catalogue += flux.readLine().split(' ')[1].trimmed();
           catalogue += " address=";
           address = flux.readLine().split(' ')[1].trimmed();
           catalogue += address;
           catalogue += " port=";
           portServ = flux.readLine().split(' ')[1].trimmed();
           catalogue += portServ;
           catalogue += " protocol=";
           protoServ = flux.readLine().split(' ')[1].trimmed();
           catalogue += protoServ;
           catalogue += " ips=";
           catalogue += flux.readLine().split(' ')[1].trimmed();
           catalogue += "\r\n";

           if( protoServ == "UDP_PUSH"){
               this->flux.append( new ServeurUdpPush(ficPath, portServ.toInt() ));

           }else if( protoServ == "UDP_PULL" ) {
                this->flux.append( new ServeurUdpPull(ficPath, portServ.toInt() ));

           }else if( protoServ == "TCP_PUSH" ) {
               this->flux.append( new ServeurTcpPush(ficPath, portServ.toInt() ));

           }else if( protoServ == "TCP_PULL" ) {
               this->flux.append( new ServeurTcpPull(ficPath, portServ.toInt() ));

           }else if( protoServ == "MCAST_PUSH") {
               this->flux.append( new ServeurMulti(ficPath, address, portServ.toInt() ));

           }
     }
     catalogue += "\r\n";

     int size = catalogue.size();

     catalogue.insert( 0, "\r\n\r\n" );
     catalogue.insert( 0, QString::number( size) );
     catalogue.insert( 0, "Content-Length: " );
     catalogue.insert( 0, "Content-Type: text/txt\r\n" );
     catalogue.insert( 0, "HTTP/1.1 200 OK\r\n" );


}
