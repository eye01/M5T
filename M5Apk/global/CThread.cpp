#include "CThread.h"

CThread::CThread(QObject *parent) : QThread(parent)
{
    m_iType=-1;
}

void CThread::run()
{

    if(m_iType==_image)
    {
        QByteArray jpegData ;
        if(!SQL().checkHaveImageData(m_sUrl))
        {
            QUrl url(m_sUrl);
            QNetworkAccessManager manager;
            QEventLoop loop;
            QNetworkReply *reply = manager.get(QNetworkRequest(url));
            QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();
            jpegData = reply->readAll();
            SQL().addImageData(m_sUrl,jpegData);
        }
        else
        {
            jpegData=SQL().getImageData(m_sUrl);
        }

        if(jpegData.isNull())
        {
            QUrl url(m_sUrl);
            QNetworkAccessManager manager;
            QEventLoop loop;
            QNetworkReply *reply = manager.get(QNetworkRequest(url));
            QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();
            jpegData = reply->readAll();

            SQL().addImageData(m_sUrl,jpegData);
        }

        QPixmap pixmap;
        pixmap.loadFromData(jpegData);
        if(m_lb!=NULL)
        {
            m_lb->setPixmap(pixmap.scaled(m_lb->width(),m_lb->height(),Qt::KeepAspectRatio));
        }

    }


}

void CThread::overThread()
{



}

void CThread::setImage(QString sUrl, QLabel *lb)
{
    m_iType=_image;
    m_sUrl=sUrl;
    m_lb=lb;



}

CThread::~CThread()
{
    quit();
    if(!wait(300)) //Wait until it actually has terminated (max. 0.1 sec)
    {
        terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
        wait(); //We have to wait again here!
    }
}

