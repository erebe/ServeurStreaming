#include <QDebug>
#include <QHostAddress>
#include "clientTcpPush.h"

ClientTcpPush::ClientTcpPush( QTcpSocket *sock,
                              QList<QByteArray> &video, int time ):
    sockControle(sock), images(video), imgCourante(-1), tpi(time)

{
    connect(sockControle, SIGNAL(readyRead()),
            this, SLOT(requeteRecu()));
    connect(this, SIGNAL(requeteComplete()),
            this, SLOT(traiterRequete()));
}

void ClientTcpPush::requeteRecu()
{
    requeteClient.append(sockControle->readAll());

    if ( requeteClient.endsWith("\r\n\r\n") )
    {
        emit requeteComplete();
    }
}


void ClientTcpPush::traiterRequete()
{

    if ( requeteClient.contains("LISTEN") )
    {
        connecteSockDonnee();
    }

    if( requeteClient.contains("START") )
    {
        timerId = startTimer(tpi);
    }
    else if (  requeteClient.startsWith("END") )
    {
        finConnection();
    }
    else if( requeteClient.startsWith("PAUSE") )
    {
        killTimer(timerId);
    }

    requeteClient.clear();
}

void ClientTcpPush::connecteSockDonnee()
{

    quint64 clientPort = requeteClient.split('\n')[1].trimmed().
                         split(' ')[1].trimmed().toInt();

    sockDonnees.connectToHost(sockControle->peerAddress(),clientPort);
    sockDonnees.waitForConnected(-1 );

}

void ClientTcpPush::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    imgCourante = (imgCourante + 1) % images.size();

    QByteArray packet;

    packet =  QByteArray::number(imgCourante + 1) + "\r\n"
              + QByteArray::number(images.at(imgCourante).size()) + "\r\n"
              + images.at(imgCourante);

    sockDonnees.write( packet );

}

void ClientTcpPush::finConnection()
{
    delete sockControle;
    emit connexionTermine(this);
}
