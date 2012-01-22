#ifndef CLIENTUDPPULL_H
#define CLIENTUDPPULL_H

#include <QUdpSocket>
#include <QList>


class ClientUdpPull: public QObject
{
        Q_OBJECT

    public:
        ClientUdpPull( const QHostAddress& address, quint16 port,
                       QList<QByteArray> &video);
        void traiterRequete( const QByteArray& paquet );


    signals:
        void connexionTermine( ClientUdpPull* );

    protected:
        QUdpSocket sock;
        const QHostAddress address;
        quint16 portControle;
        quint16 portDonnees;
        quint16 fragmentSize;

        QList<QByteArray> &images;
        int imgCourante;


        void envoieImage();
        void finConnection();


};

#endif // DEMANDETCPPULL_H
