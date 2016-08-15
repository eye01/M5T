#ifndef CTCPCLIENT_H
#define CTCPCLIENT_H

#include <QObject>

#include <QStringList>
#include <QDebug>
#include <QString>
#include <QTcpSocket>
#include <QTime>
#include <QCoreApplication>

#define STREAM_PKG "::"
#define STREAM_LIST ";;"
#define STREAM_DATA ",,"

struct TcpData
{
    int iAction;
    int iType;
    QStringList listValue;
    QList<QStringList> dData;
};


class CTcpClient : public QObject
{
    Q_OBJECT
public:
    explicit CTcpClient(QObject *parent = 0);
    int blockTcpSend(const TcpData cIn, TcpData &cOut, QString sIp, int iPort, int iTimeOutMilliSec);
    int blockTcpSend(const QByteArray arrInput, QByteArray &arrOutput, QString sIp, int iPort, int iTimeOutMilliSec);

    int connect(QString sIp, int iPort);
    int nowConnectSend(const TcpData cIn,TcpData &cOut,int iTimeOutMilliSec);

    QTcpSocket *m_socket;
    QString encodeStream(TcpData dData);
    TcpData decodeStream(QString st);
signals:

public slots:
};

#endif // CTCPCLIENT_H
