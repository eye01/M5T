#include "CListenClient.h"

CListenClient::CListenClient(QObject *parent) :
    QThread(parent)
{


}

void CListenClient::run()
{

    m_clientConnection=NULL;

    m_tcpServer = new QTcpServer(this);

    m_tcpServer->listen(QHostAddress::Any, Global().g_config.sTcpListenPort.toInt());

    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(slotAcceptConnection()));

    emit signalTest("TCP SERVER CREAT");

}



void CListenClient::slotAcceptConnection()
{

    qDebug()<<"get link from client";
    emit signalTest("get client link");
    if(m_clientConnection!=NULL)
    {
        m_clientConnection->disconnect();
    }

    m_clientConnection = m_tcpServer->nextPendingConnection();

    connect(m_clientConnection, SIGNAL(readyRead()), this, SLOT(slotReadClient()));


}

void CListenClient::slotReadClient()
{

    QString str = m_clientConnection->readAll();

    emit signalTest(str);

    QStringList listItem=str.split(",");

    if(listItem.length()<1)
        listItem.append("aa");

    QString sReClient;
    //sReClient=M5SqlServer().returnClient();               //     returnClient(listItem.at(0),listItem.at(1));
    emit signalTest(sReClient);

    QByteArray tmp;

    tmp.append(sReClient);

    QTcpSocket *pSenderSocket = qobject_cast<QTcpSocket*>(sender());

    pSenderSocket->write(tmp);

}




