#ifndef CSQL_H
#define CSQL_H

#include <QObject>
#include <QDebug>
#include <QtSql/QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>




namespace SqlTable
{
    enum _table{_ad,_headerName,_productList,_productDetail,_imageData};
}

namespace SqlOtherDataKey
{

    static QString sSession="session";
    static QString sCarId="carId";
}



class Csql : public QObject
{
    Q_OBJECT
public:
    explicit Csql(QObject *parent = 0);
    ~Csql();



    //存圖片進db
    bool checkHaveImageData(QString sUrl);
    bool addImageData(QString sUrl, QByteArray byteData);
    QByteArray getImageData(QString sUrl);


    //存AD
    bool checkHaveAdData();
    bool addAdData(QList<QStringList> dData);
    QString getAdData(QList<QStringList> &dData);

    //存header
    bool checkHaveHeaderData();
    bool addHeaderData(QList<QStringList> dData);
    QList<QStringList> getHeaderData();

    //存商品列表
    bool checkHaveProductList(QString sNo);
    bool addProductList(QString sApiKey, QList<QStringList> dData);
    bool addProductList(QString sApiKey,QStringList listData);
    QList<QStringList> getProductList(QString sApiKey);

    //存商品詳細
    bool checkHaveProductDetail(QString sNo);
    bool addProductDetail(QString sApiKey, QList<QStringList> dData);
    QList<QStringList> getProductDetail(QString sApiKey);

    //存套裝詳細
    bool checkHaveOutfitDetail(QString sNo);
    bool addOutfitDetail(QString sApiKey, QList<QStringList> dData);
    QList<QStringList> getOutfitDetail(QString sApiKey);

    bool setUpdateNo(QString sApiName, QString sUpdateNo);
    QString checkLastUpdate(SqlTable::_table nTable);
    void clearTableData(SqlTable::_table nTable);

    bool setOtherData(QString sKey,QString sValue);
    QString getOtherData(QString sKey);


    QSqlDatabase m_db;
signals:

public slots:
};

#endif // CSQL_H
