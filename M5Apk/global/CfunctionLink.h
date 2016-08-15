#ifndef CFUNCTIONLINK_H
#define CFUNCTIONLINK_H

#include <QObject>
#include "CallApi.h"
//#include "Dataprovider.h"
#include "Csql.h"


#define JB_CONNECT_ERROR 999
static QString CONNECT_ERROR = "999";


class CfunctionLink : public CallApi
{
    Q_OBJECT
public:
    explicit CfunctionLink(QObject *parent = 0);
    ~CfunctionLink();


    Csql g_sql;


    //===========================================
    QString callSession();

    int callAd();


    QString getHeader();

    int getLastUpdateDate(QStringList &list);

    //===========================================
    QList<QStringList> getProductList(QString sHeaderId, int iStartIdx=1, int iCount=40);

    void getAllProductList();
  //  DataProductDetail getProductDetail(QString sId);
    QString getProductDetail(QString sId,DataProductDetail &cData);
    DataOutfitDetail getOutfitDetail(QString sId);

    QList<QStringList> getSizeTable(QString sId);

    //===========================================

    QString addCar(DataAddCar data,QStringList &listOut);

    QList<DataGetCar> getCar(int iFlag=0);

    QString updateNumsCar(QString sCarItemId, int iNums);

    //===========================================

    QString login(QString sName, QString sPassword);

    QString logout();

    bool checkLogin();

    QString fogetPassword(QString sEmail);

    QString memberRegister(QJsonObject obj, QStringList &listOut);

    QString updateMemberData(QJsonObject obj);

    QString getMemberData(QStringList &listOut);

    QString changePassword(QString sOld,QString sNew);

    //============================================
    QString sendOrder(QJsonObject obj, QString &sOrderId);

    QString getOrderList(QList<QStringList> &dData);

    QString getOrderListDetail(QString sId,DataOrderListDetail &cData);
    QString getProductPriceQty(QString sPid, QList<QStringList> &dData);

    QString updateDelivery(QString &sDeliveryId, QJsonObject obj);
    QString getDeliveryList(QStringList &listDeliveryId,QStringList &listDeliveryName);
    QString getDeliveryData(QString sId, QStringList &listData);
    QString getNccc();

    QString getValue(QString sKey);
signals:

public slots:
};

#endif // CFUNCTIONLINK_H
