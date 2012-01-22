#include "serveurMulti.h"
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QAbstractSocket>
#include <QUdpSocket>

ServeurMulti::ServeurMulti( const QString& pathFlux, const QString& address, int port ):
    port(port), addr(address), imgCourante(-1), fragmentSize(512)
{

    chargerVideo( pathFlux );
    startTimer(tpi);


}


void ServeurMulti::chargerVideo( const QString& pathFlux )
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

void ServeurMulti::timerEvent(QTimerEvent *event) {

    Q_UNUSED(event);

    quint64 pos = 0;
    imgCourante = (imgCourante + 1) % mesImages.size();

    while( pos < mesImages.at(imgCourante).size() ) {


        QByteArray packet;
        packet.resize(fragmentSize);


        packet =  QByteArray::number(imgCourante + 1) + "\r\n"
                  + QByteArray::number(mesImages.at(imgCourante).size()) + "\r\n"
                  + QByteArray::number(pos) + "\r\n";

        QByteArray data = mesImages.at(imgCourante).mid( pos, fragmentSize
                                                         - packet.size() - 5 );

        packet += QByteArray::number(data.size()) + "\r\n"
                  + data;


        sock.writeDatagram( packet, addr, port );

        pos += data.size();
    }
}
