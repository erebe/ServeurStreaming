#ifndef DEMANDETCPPUSH_H
#define DEMANDETCPPUSH_H

#include <QTcpSocket>
#include <QList>

class ClientTcpPush: public QObject
{
        Q_OBJECT

    public:
        ClientTcpPush( QTcpSocket *sock, QList<QByteArray> &video, int time);


    signals:
        void requeteComplete();
        void connexionTermine( ClientTcpPush*);

    protected:
        QTcpSocket *sockControle;
        QTcpSocket sockDonnees;
        QByteArray requeteClient;
        QList<QByteArray> &images;
        int imgCourante;
        int tpi;
        int timerId;

        void connecteSockDonnee();
        void timerEvent(QTimerEvent *event);
        void finConnection();
        void demandeClient(QByteArray message);


    protected slots:
        void requeteRecu();
        void traiterRequete();
};

#endif // DEMANDETCPPULL_H
