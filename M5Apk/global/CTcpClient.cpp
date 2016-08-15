#include "CTcpClient.h"

CTcpClient::CTcpClient(QObject *parent) : QObject(parent)
{
    m_socket=NULL;
}

int CTcpClient::blockTcpSend(const TcpData cIn, TcpData &cOut, QString sIp, int iPort, int iTimeOutMilliSec)
{
    int iRe=-1;
    QByteArray in;
    in.append(encodeStream(cIn));
    QByteArray out;
    iRe=blockTcpSend(in,out,sIp,iPort,iTimeOutMilliSec);
    QString sOut(out);
    cOut=decodeStream(sOut);
    return iRe;
}

int CTcpClient::blockTcpSend(const QByteArray arrInput, QByteArray &arrOutput, QString sIp, int iPort, int iTimeOutMilliSec)
{
    qDebug()<<"ip "<<sIp;
    qDebug()<<"tcp timeout : "<<iTimeOutMilliSec;
    int iRe=-1;

    qDebug()<<arrInput;

    if(arrInput.length()<1)
        return -1;

    QTcpSocket *socket = new QTcpSocket();




    socket->connectToHost(sIp,iPort);

    if(socket->waitForConnected(iTimeOutMilliSec))
    {
        qDebug() << "Connected!";
        socket->write(arrInput);
        socket->waitForBytesWritten(iTimeOutMilliSec);
        qDebug()<<"socket written ok";
        socket->waitForReadyRead(iTimeOutMilliSec);
        int iTmp=0;

        //第一次先取一部分 ，主要要先拿回長度資訊
        iTmp=socket->bytesAvailable();
        QTime dieTime = QTime::currentTime().addMSecs(1000);
        while( QTime::currentTime() < dieTime && iTmp<15 )
        {
            iTmp=socket->bytesAvailable();
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }

        qDebug() <<"first reading: " << iTmp;
        arrOutput=socket->readAll();

        QString tmp0(arrOutput);

        TcpData data =decodeStream(tmp0);
        // TcpData data=decodeStream(tmp0);

        int iDataLen=0;
        if(data.listValue.length()>0)
            iDataLen=data.listValue.at(0).toInt();
        qDebug()<<"Need lens: "<<iDataLen;


        //未取完第二次給2秒 等待，再補填
        dieTime = QTime::currentTime().addMSecs(2000);
        while( QTime::currentTime() < dieTime && iTmp<iDataLen)
        {
            iTmp=socket->bytesAvailable();
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        qDebug() << "two reading: " << iTmp;
        arrOutput.append(socket->readAll());

        qDebug()<<"get Lens : "<<arrOutput.length();



        qDebug()<<"data: "<<arrOutput;

        if(iTmp>0)
        {
            // transFlag(arrOutput);
        }
        iRe=0;
    }
    else
    {
        qDebug() << "Not connected!";
        iRe=-1;
    }


        socket->close();
        delete socket;

    return iRe;

}
//
int CTcpClient::connect(QString sIp, int iPort)
{
    qDebug()<<"ip "<<sIp<<" iPort : "<<iPort;

    if(m_socket!=NULL)
    {
        m_socket->close();
        delete m_socket;
    }

    m_socket = new QTcpSocket();

    m_socket->connectToHost(sIp,iPort);

    return 0;
}

int CTcpClient::nowConnectSend(const TcpData cIn, TcpData &cOut, int iTimeOutMilliSec)
{
    int iRe=-1;

    QByteArray arrInput;
    QByteArray arrOutput;
    arrInput.append(encodeStream(cIn));

    qDebug()<<"use old connect ";
    if(m_socket->waitForConnected(iTimeOutMilliSec))
    {
        qDebug() << "Connected!";
        m_socket->write(arrInput);
        m_socket->waitForBytesWritten(iTimeOutMilliSec);
        qDebug()<<"socket written ok";
        m_socket->waitForReadyRead(iTimeOutMilliSec);
        int iTmp=0;

        //第一次先取一部分 ，主要要先拿回長度資訊
        iTmp=m_socket->bytesAvailable();
        QTime dieTime = QTime::currentTime().addMSecs(1000);
        while( QTime::currentTime() < dieTime && iTmp<15 )
        {
            iTmp=m_socket->bytesAvailable();
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }

        qDebug() <<"first reading: " << iTmp;
        arrOutput=m_socket->readAll();

        QString tmp0(arrOutput);

        TcpData data =decodeStream(tmp0);
        // TcpData data=decodeStream(tmp0);

        int iDataLen=0;
        if(data.listValue.length()>0)
            iDataLen=data.listValue.at(0).toInt();
        qDebug()<<"Need lens: "<<iDataLen;


        //未取完第二次給2秒 等待，再補填
        dieTime = QTime::currentTime().addMSecs(2000);
        while( QTime::currentTime() < dieTime && iTmp<iDataLen)
        {
            iTmp=m_socket->bytesAvailable();
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        qDebug() << "two reading: " << iTmp;
        arrOutput.append(m_socket->readAll());

        qDebug()<<"get Lens : "<<arrOutput.length();



        qDebug()<<"data: "<<arrOutput;

        if(iTmp>0)
        {
            // transFlag(arrOutput);
        }
        iRe=0;
    }
    else
    {
        qDebug() << "Not connected!";
        iRe=-1;
    }



    return iRe;
}
QString CTcpClient::encodeStream(TcpData dData)
{
    QString sRe;
    sRe.append(QString::number(dData.iAction));
    sRe.append(STREAM_LIST);
    sRe.append(QString::number(dData.iType));
    sRe.append(STREAM_PKG);
    QStringList listValue=dData.listValue;
    for(int i=0;i<listValue.length();i++)
    {
        sRe.append(listValue.at(i));
        if(i!=listValue.length()-1)
            sRe.append(STREAM_LIST);

    }

    sRe.append(STREAM_PKG);

    QList<QStringList> data=dData.dData;


    for(int j=0;j<data.length();j++)
    {

        for(int k=0;k<data.at(j).length();k++)
        {
            sRe.append(data[j][k]);

            if(k!=data[j].length()-1)
            {

                sRe.append(STREAM_DATA);
            }
            else
            {
                sRe.append(STREAM_LIST);
            }
        }

        // sRe.append(STREAM_PKG);

    }

    return sRe;
}

TcpData CTcpClient::decodeStream(QString st)
{
    TcpData dObj;
    dObj.iAction=-1;
    dObj.iType=-1;

    // QList<QStringList> dData;
    QStringList listAll=st.split(STREAM_PKG);
    QStringList listActionDefine=listAll.at(0).split(STREAM_LIST);
    dObj.iAction=listActionDefine.at(0).toInt();

    if(listActionDefine.length()>1)
        dObj.iType=listActionDefine.at(1).toInt();


    if(listAll.length()>1)
        dObj.listValue=listAll.at(1).split(STREAM_LIST);


    if(listAll.length()>2)
    {
        QStringList listTemp=listAll.at(2).split(STREAM_LIST);

        for(int i=0;i<listTemp.length();i++)
        {
            dObj.dData.append(listTemp[i].split(STREAM_DATA));
        }
    }

    return dObj;
}

