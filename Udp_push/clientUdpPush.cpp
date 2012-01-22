#include <QDebug>
#include <QHostAddress>
#include <QTimerEvent>
#include "clientUdpPush.h"

ClientUdpPush::ClientUdpPush( const QHostAddress& addr, quint16 portClient,
                              QList<QByteArray> &video, int tmpsParImage):
    address(addr), portControle(portClient),tpi(tmpsParImage),
    images(video), imgCourante(-1)


{}


void ClientUdpPush::traiterRequete( const QByteArray& paquet )
{

    if ( paquet.startsWith("ALIVE") ){

    }else if ( paquet.startsWith("START") )
    {
        envoieImage();
        sendTimer = startTimer(tpi);

    }else if( paquet.startsWith("PAUSE") ){
        killTimer(sendTimer);
    }
    else if( paquet.contains("LISTEN") )
    {

        portDonnees = paquet.split('\n')[1].trimmed().
                      split(' ')[1].trimmed().toInt();

        fragmentSize = paquet.split('\n')[2].trimmed().
                       split(' ')[1].trimmed().toInt();

    }

    killTimer(endTimer);
    endTimer = startTimer(60 * 1000);


}


void ClientUdpPush::envoieImage()
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

void ClientUdpPush::finConnection()
{
    emit connexionTermine(this);
}

void ClientUdpPush::timerEvent(QTimerEvent *event) {

    if( event->timerId() == endTimer ){
        finConnection();

    }else if( event->timerId() == sendTimer ){
        envoieImage();
    }
}
