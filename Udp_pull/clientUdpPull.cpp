#include <QDebug>
#include <QHostAddress>
#include "clientUdpPull.h"

ClientUdpPull::ClientUdpPull( const QHostAddress& addr, quint16 portClient,
                              QList<QByteArray> &video):
    address(addr), portControle(portClient),
    images(video), imgCourante(-1)


{}


void ClientUdpPull::traiterRequete( const QByteArray& paquet )
{

    if ( paquet.contains("GET -1") )
    {
        envoieImage();
    }else if (  paquet.startsWith("END") )
    {
        finConnection();
    }else if( paquet.contains("LISTEN") )
    {

        portDonnees = paquet.split('\n')[1].trimmed().
                      split(' ')[1].trimmed().toInt();

        fragmentSize = paquet.split('\n')[2].trimmed().
                       split(' ')[1].trimmed().toInt();

    }

}


void ClientUdpPull::envoieImage()
{

    quint64 pos = 0;
    imgCourante = (imgCourante + 1) % images.size();

    while( pos < images.at(imgCourante).size() ) {

        QByteArray packet;
        packet.resize(fragmentSize);


        packet =  QByteArray::number(imgCourante + 1) + "\r\n"
                  + QByteArray::number(images.at(imgCourante).size()) + "\r\n"
                  + QByteArray::number(pos) + "\r\n";

        QByteArray data = images.at(imgCourante).mid( pos, fragmentSize
                                                      - packet.size() - 5 );

        packet += QByteArray::number(data.size()) + "\r\n"
                  + data;


        sock.writeDatagram( packet, address, portDonnees );

        pos += data.size();
    }

}

void ClientUdpPull::finConnection()
{
    emit connexionTermine(this);
}
