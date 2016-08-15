#ifndef LAYERLOADING_H
#define LAYERLOADING_H

#include <QWidget>
#include "Global.h"
#include <QThread>
#include <QTimerEvent>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QList>
#include "Csql.h"
#include <QThread>
namespace Ui {
class LayerLoading;
}


class CLoadingThread :public QThread
{
    Q_OBJECT
public:
    CLoadingThread(){}
    void run()
    {
        msleep(100);
        emit milisec();
    }
signals:
    void milisec();
};



class LayerLoading : public QWidget
{
    Q_OBJECT

public:

    explicit LayerLoading(QWidget *parent = 0);

    ~LayerLoading();

    void startLoading();

    bool isFinish();

    void preLoadAd();

    void preLoadHeader();

    void preLoadProductList();

    void preloadProductDetail();

    void setViewWord(QString sText);

    QString getViewWord();

    int getProgressValue();




private:

    Ui::LayerLoading *ui;

    int m_iTimer;

     float m_fNowValue;


    void timerEvent(QTimerEvent *);

    void goAction();



};

#endif // LAYERLOADING_H
