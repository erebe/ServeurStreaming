#include <QDebug>
#include <QHostAddress>
#include "demandetcppull.h"

DemandeTcpPull::DemandeTcpPull( QTcpSocket *sock,
                                QList<QByteArray> &video):
    sockControle(sock), images(video), imgCourante(-1)

{
    connect(sockControle, SIGNAL(readyRead()),
            this, SLOT(requeteRecu()));
    connect(this, SIGNAL(requeteComplete()),
            this, SLOT(traiterRequete()));
}

void DemandeTcpPull::requeteRecu()
{
    requeteClient.append(sockControle->readAll());

    if ( requeteClient.endsWith("\r\n\r\n") )
    {

        emit requeteComplete();
    }
}


void DemandeTcpPull::traiterRequete()
{

    if ( requeteClient.at(4) == '-' && requeteClient.at(5) == '1' )
    {
        envoieImage();
    }
    else if (  requeteClient.startsWith("END") )
    {
        finConnection();
    }
    else if ( requeteClient.contains("LISTEN") )
    {
        connecteSockDonnee();
    }

    requeteClient.clear();
}

void DemandeTcpPull::connecteSockDonnee()
{

    quint16 clientPort = requeteClient.split('\n')[1].trimmed().
                         split(' ')[1].trimmed().toInt();

    sockDonnees.connectToHost(sockControle->peerAddress(),clientPort);
    sockDonnees.waitForConnected(-1);

}

void DemandeTcpPull::envoieImage()
{
    imgCourante = (imgCourante + 1) % images.size();

    QByteArray packet;

    packet =  QByteArray::number(imgCourante + 1) + "\r\n"
              + QByteArray::number(images.at(imgCourante).size()) + "\r\n"
              + images.at(imgCourante);

    sockDonnees.write( packet );

}

void DemandeTcpPull::finConnection()
{
    delete sockControle;
    emit connexionTermine(this);
}
