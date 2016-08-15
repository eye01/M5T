#include "Csql.h"
#include <QApplication>


Csql::Csql(QObject *parent) : QObject(parent)
{

    //bool RpkLib::cOpenSql(_SQL_TYPE _type, QString sPath, QString sName)
    QString sPath="";
    QString sName="myfile";
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    m_db=QSqlDatabase::addDatabase("QSQLITE",sName);


    if(sPath.length()>1 && sPath.at(sPath.length()-1)!='/')
        sPath.append("/");
    qDebug()<<"db open: "<<sPath+sName;


    QFile::copy(":/res/images/myfile.db",sPath+sName+".db");
  m_db.setDatabaseName(sPath+sName+".db");
    bool bIsOpenOk=m_db.open();
    qDebug()<<"DB OPEN IS "<<bIsOpenOk;
    QSqlQuery query(m_db);

    QString sCmd="CREATE TABLE updateNo (sid INTEGER ,apiName TEXT NOT NULL,updateNo TEXT,PRIMARY KEY(sid))";
    query.exec(sCmd);
    qDebug()<<"db talbe updateNo";

    sCmd="CREATE TABLE imageData (sid INTEGER ,url TEXT NOT NULL,data BLOB NOT NULL,PRIMARY KEY(sid))";
    query.exec(sCmd);

    sCmd="CREATE TABLE ad (sid INTEGER ,data TEXT,PRIMARY KEY(sid));";
    query.exec(sCmd);
    qDebug()<<"db talbe ad";

    sCmd="CREATE TABLE headerName (sid INTEGER ,data TEXT,PRIMARY KEY(sid));";
    query.exec(sCmd);
    qDebug()<<"db talbe headerName";

    sCmd="CREATE TABLE productList (sid INTEGER ,key TEXT,data TEXT,PRIMARY KEY(sid))";
    query.exec(sCmd);
    qDebug()<<"db talbe productList";

    sCmd="CREATE TABLE productDetail (sid INTEGER ,key TEXT,data TEXT,PRIMARY KEY(sid))";
    query.exec(sCmd);
    qDebug()<<"db talbe productDetail";


    sCmd="CREATE TABLE outfitDetail (sid INTEGER ,key TEXT,data TEXT,PRIMARY KEY(sid))";
    query.exec(sCmd);
    qDebug()<<"db talbe outfitDetail";

    sCmd="CREATE TABLE otherData (sid INTEGER,key TEXT,value TEXT ,PRIMARY KEY(key))";
    query.exec(sCmd);

    QApplication::restoreOverrideCursor();

}

Csql::~Csql()
{
    m_db.close();
}



bool Csql::checkHaveImageData(QString sUrl)
{

    //sUrl=sUrl.replace("\\","/");
    // sUrl=sUrl.replace("\\/","/");
    QSqlQuery query(m_db);
    QString sCmd="select * from imageData where url='%1'";
    sCmd=sCmd.arg(sUrl);
    query.exec(sCmd);
    bool bHave=false;
    while (query.next())
    {
        bHave=true;
    }

    return bHave;
}

bool Csql::addImageData(QString sUrl, QByteArray byteData)
{
    bool bRe=false;
    QSqlQuery query(m_db);
    query.prepare("insert into imageData(url,data) Values(?,?)");
    query.addBindValue(sUrl);
    QVariant var(byteData);
    query.addBindValue(var);
    bRe=query.exec();
    return bRe;
}

QByteArray Csql::getImageData(QString sUrl)
{
    QByteArray re;
    QSqlQuery query(m_db);
    query.prepare("select * from imageData where url=?");
    query.addBindValue(sUrl);
    query.exec();

    while(query.next())
    {
        re=query.value("data").toByteArray();
    }
    return re;
}

bool Csql::checkHaveAdData()
{
    QSqlQuery query(m_db);
    QString sCmd="select * from ad";
    query.exec(sCmd);
    bool bHave=false;
    while (query.next())
    {
        bHave=true;
    }
    return bHave;
}

bool Csql::addAdData(QList<QStringList> dData)
{
    bool bRe=true;
    foreach (QStringList list, dData)
    {
        QSqlQuery query(m_db);
        query.prepare("insert into ad (data) Values(?)");
        query.addBindValue(list.join(",,"));
        bool b=query.exec();
        if(!b)
            bRe=false;
    }
    return bRe;
}

QString Csql::getAdData(QList<QStringList> &dData)
{
    QString sRe="";
    QList<QStringList> dRe;
    QSqlQuery query(m_db);

    query.prepare("select * from ad");
    query.exec();

    while(query.next())
    {
        QStringList list;
        list=query.value("data").toString().split(",,");
        dRe.append(list);
    }

    dData=dRe;

    if(dData.length()>0)
        sRe="1";
    return sRe;
}

bool Csql::checkHaveHeaderData()
{
    QSqlQuery query(m_db);
    QString sCmd="select * from headerName";
    query.exec(sCmd);
    bool bHave=false;
    while (query.next())
    {
        bHave=true;
    }
    return bHave;
}

bool Csql::addHeaderData(QList<QStringList> dData)
{
    bool bRe=true;
    foreach (QStringList list, dData)
    {
        QSqlQuery query(m_db);
        query.prepare("insert into headerName (data) Values(?)");
        query.addBindValue(list.join(",,"));
        bool b=query.exec();
        if(!b)
            bRe=false;
    }
    return bRe;
}

QList<QStringList> Csql::getHeaderData()
{
    QList<QStringList> dRe;
    QSqlQuery query(m_db);

    query.prepare("select * from headerName");
    query.exec();

    while(query.next())
    {
        QStringList list;
        list=query.value("data").toString().split(",,");
        dRe.append(list);
    }

    return dRe;
}



bool Csql::checkHaveProductList(QString sNo)
{
    QSqlQuery query(m_db);
    query.prepare("select * from productList where key=?");
    query.addBindValue(sNo);
    query.exec();
    bool bHave=false;

    while (query.next())
    {
        bHave=true;
    }

    return bHave;
}

bool Csql::addProductList(QString sApiKey,QList<QStringList> dData)
{

    bool bRe=true;
    foreach (QStringList list, dData)
    {
        QSqlQuery query(m_db);
        query.prepare("insert into productList(key,data) Values(?,?)");
        query.addBindValue(sApiKey);
        query.addBindValue(list.join(",,"));
        bool b=query.exec();
        if(!b)
            bRe=false;
    }
    return bRe;
}

bool Csql::addProductList(QString sApiKey, QStringList listData)
{
    bool bRe=true;

    QSqlQuery query(m_db);
    query.prepare("insert into productList(key,data) Values(?,?)");
    query.addBindValue(sApiKey);
    query.addBindValue(listData.join(",,"));
    bool b=query.exec();
    if(!b)
        bRe=false;
    return bRe;
}

QList<QStringList> Csql::getProductList(QString sApiKey)
{

    QList<QStringList> dRe;
    QSqlQuery query(m_db);

    query.prepare("select * from productList where key=?");
    query.addBindValue(sApiKey);
    query.exec();

    while(query.next())
    {
        QStringList list;
        list=query.value("data").toString().split(",,");
        dRe.append(list);
    }

    return dRe;
}

bool Csql::checkHaveProductDetail(QString sNo)
{
    QSqlQuery query(m_db);
    query.prepare("select * from productDetail where key=?");
    query.addBindValue(sNo);
    query.exec();
    bool bHave=false;

    while (query.next())
    {
        bHave=true;
    }

    return bHave;
}

bool Csql::addProductDetail(QString sApiKey, QList<QStringList> dData)
{
    bool bRe=true;
    foreach (QStringList list, dData)
    {
        QSqlQuery query(m_db);
        query.prepare("insert into productDetail(key,data) Values(?,?)");
        query.addBindValue(sApiKey);
        query.addBindValue(list.join(",,"));
        bool b=query.exec();
        if(!b)
            bRe=false;
    }
    return bRe;
}

QList<QStringList> Csql::getProductDetail(QString sApiKey)
{

    QList<QStringList> dRe;
    QSqlQuery query(m_db);

    query.prepare("select * from productDetail where key=?");
    query.addBindValue(sApiKey);
    query.exec();

    while(query.next())
    {
        QStringList list;
        list=query.value("data").toString().split(",,");
        dRe.append(list);
    }

    return dRe;
}

bool Csql::checkHaveOutfitDetail(QString sNo)
{
    QSqlQuery query(m_db);
    query.prepare("select * from outfitDetail where key=?");
    query.addBindValue(sNo);
    query.exec();
    bool bHave=false;

    while (query.next())
    {
        bHave=true;
    }

    return bHave;
}

bool Csql::addOutfitDetail(QString sApiKey, QList<QStringList> dData)
{
    bool bRe=true;
    foreach (QStringList list, dData)
    {
        QSqlQuery query(m_db);
        query.prepare("insert into outfitDetail(key,data) Values(?,?)");
        query.addBindValue(sApiKey);
        query.addBindValue(list.join(",,"));
        bool b=query.exec();
        if(!b)
            bRe=false;
    }
    return bRe;
}

QList<QStringList> Csql::getOutfitDetail(QString sApiKey)
{
    QList<QStringList> dRe;
    QSqlQuery query(m_db);

    query.prepare("select * from outfitDetail where key=?");
    query.addBindValue(sApiKey);
    query.exec();

    while(query.next())
    {
        QStringList list;
        list=query.value("data").toString().split(",,");
        dRe.append(list);
    }

    return dRe;
}

bool Csql::setUpdateNo(QString sApiName,QString sUpdateNo)
{
    bool bRe=false;
    QSqlQuery query(m_db);
    query.prepare("insert into updateNo(apiName,updateNo) Values(?,?)");
    query.addBindValue(sApiName);
    query.addBindValue(sUpdateNo);
    bRe=query.exec();
    return bRe;
}

QString Csql::checkLastUpdate(SqlTable::_table nTable)
{
    QString sTableName="";

    switch (nTable)
    {
    case SqlTable::_ad:
        sTableName="ad";
        break;
    case SqlTable::_headerName:
        sTableName="headerName";
        break;
    case SqlTable::_productList:
        sTableName="productList";
        break;
    case SqlTable::_productDetail:
        sTableName="productDetail";
        break;
    default:
        break;
    }

    QString sRe="";
    QSqlQuery query(m_db);
    query.prepare("select * from updateNo where apiName=?");
    query.addBindValue(sTableName);
    bool b=query.exec();

    while(query.next() && b)
    {
        sRe=query.value("updateNo").toString();
    }

    return sRe;

}


void Csql::clearTableData(SqlTable::_table nTable)
{
    QString sTableName="";

    switch (nTable)
    {
    case SqlTable::_ad:
        sTableName="ad";
        break;
    case SqlTable::_headerName:
        sTableName="headerName";
        break;
    case SqlTable::_productList:
        sTableName="productList";
        break;
    case SqlTable::_productDetail:
        sTableName="productDetail";
        break;
    default:
        break;
    }


    QSqlQuery query(m_db);
    QString sCmd="Delete from "+sTableName;
    query.exec(sCmd);

}


bool Csql::setOtherData(QString sKey, QString sValue)
{
    bool bRe=false;
    QSqlQuery query(m_db);
    query.prepare("insert into otherData(key,value) Values(?,?)");
    query.addBindValue(sKey);
    query.addBindValue(sValue);
    bRe=query.exec();
    qDebug()<<"otherDb insert : "<<bRe;
    if(!bRe)
    {
        QSqlQuery query2(m_db);
        query2.prepare("update otherData set value=? where key=?");
        query2.addBindValue(sValue);
        query2.addBindValue(sKey);
        bRe=query2.exec();
    }
    qDebug()<<"otherDb update : "<<bRe;
    return bRe;
}

QString Csql::getOtherData(QString sKey)
{

    QString sRe="";
    QSqlQuery query(m_db);
    query.prepare("select * from otherData where key=?");
    query.addBindValue(sKey);
    bool b=query.exec();

    while(query.next() && b)
    {
        sRe=query.value("value").toString();
    }
    qDebug()<<"get other data : "<<sRe;
    return sRe;
}








