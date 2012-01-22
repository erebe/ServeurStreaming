#ifndef SERVEURMULTI_H
#define SERVEURMULTI_H

#include <QUdpSocket>
#include <QMap>

class ServeurMulti: public QObject
{
        Q_OBJECT

    public:
        ServeurMulti( const QString& pathFlux, const QString& address, int port );


    protected:
        QUdpSocket sock;
        int port;
        QHostAddress addr;
        QList<QByteArray> mesImages;
        int tpi;
        int imgCourante;
        int fragmentSize;

        void chargerVideo( const QString& pathFlux);
        void timerEvent(QTimerEvent *event);

};

#endif // SERVEURTCPPULL_H
