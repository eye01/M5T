#ifndef CTHREAD_H
#define CTHREAD_H

#include <QObject>
#include <QLabel>
#include <QThread>
#include "Global.h"
#include <QDebug>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class CThread :public QThread
{
    Q_OBJECT
public :
    CThread (QObject *parent);
    ~CThread();

    void run();
    void overThread();

    void setImage(QString sUrl,QLabel *lb);
  //  QByteArray m_image;

    QLabel *m_lb;
    QString m_sUrl;
private:
    enum{_image,_other};
    int m_iType;
};



#endif // CTHREAD_H
