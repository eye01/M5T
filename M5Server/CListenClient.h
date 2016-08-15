#ifndef CLISTENCLIENT_H
#define CLISTENCLIENT_H

#include <QThread>
#include <QObject>
#include <QtNetwork>

#include "../../common/Common.h"
#include "GLOBAL.h"


class CListenClient : public QThread
{
    Q_OBJECT
public:
    explicit CListenClient(QObject *parent = 0);
    void run();

private:
        QTcpServer *m_tcpServer;

        QTcpSocket *m_clientConnection;


signals:
        void signalTest(QString st);
public slots:
        void slotAcceptConnection();
        void slotReadClient();

};

#endif // CLISTENCLIENT_H
