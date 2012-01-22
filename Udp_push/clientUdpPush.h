#ifndef CLIENTUDPPUSH_H
#define CLIENTUDPPUSH_H

#include <QUdpSocket>
#include <QList>


class ClientUdpPush: public QObject
{
        Q_OBJECT

    public:
        ClientUdpPush( const QHostAddress& address, quint16 port,
                       QList<QByteArray> &video, int tmpsParImage);
        void traiterRequete( const QByteArray& paquet );

    signals:
        void connexionTermine( ClientUdpPush* );

    protected:
        QUdpSocket sock;
        const QHostAddress address;
        quint16 portControle;
        quint16 portDonnees;
        quint16 fragmentSize;
        int endTimer;
        int sendTimer;
        int tpi;

        QList<QByteArray> &images;
        int imgCourante;

        void envoieImage();
        void finConnection();
        void timerEvent(QTimerEvent *event);


};

#endif
