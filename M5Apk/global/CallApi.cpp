#include "CallApi.h"

CallApi::CallApi(QObject *parent) : QObject(parent)
{
    m_networkManager=NULL;
    m_sNowApi="";
    m_bApiReturn=false;
    //m_sCarId="0";
    m_sReturnValue=API_CONNECT_ERROR;
    m_sOrderId="";
    m_sIsPreTrade="0";
    m_sFreeKey="";
    m_bIsLogin=false;

}

CallApi::~CallApi()
{



}


QString CallApi::getApi(QString sApi,QString sIn,int iTimeout)
{
    qDebug()<<"get Api: "+sApi;
    QList<QStringList> out;
    return getApi(sApi,out,sIn,iTimeout);
}


QString CallApi::getApi(QString sApi, QList<QStringList> &dOut, QString sIn, int iTimeout)
{


    QString sRe="";
    m_sNowApi=sApi;

    QString sUrl=sApi;

    //    if(m_sNowApi==API_GET_CAR || m_sNowApi==API_ADD_CAR)
    //    {
    //        m_sSession="7cksj7b6bhk750icr397ct7qu2";
    //        m_sCarId="346aa367-08b0-452c-9dfb-91f7b1f1cfec";
    //    }

    if(m_sNowApi==API_SET_VALUE || m_sNowApi==API_GET_VALUE)
    {
        m_sFreeKey=sIn;
    }


    if(m_sNowApi==API_LAST_UPDATE||
            m_sNowApi==API_ADD_CAR || m_sNowApi==API_GET_CAR ||  m_sNowApi==API_UPDATE_CAR||
            m_sNowApi==API_LOGIN || m_sNowApi==API_LOGOUT ||
            m_sNowApi==API_CHANGE_PASSWORD || m_sNowApi==API_GET_MEMBER_DATA ||
            m_sNowApi==API_GET_DELIVERY_LIST ||m_sNowApi==API_GET_ORDER_LIST || m_sNowApi==API_GET_ORDER_LIST_DETAIL)
        sUrl+=m_sSession+"/";


    if(sIn!="")
        sUrl+=sIn;

    m_bApiReturn=false;

    qDebug()<<"send API: "<<sUrl;

    emit signalDebug("call(get) api : "+sUrl);
    qDebug()<<"before http";
    doHttpGet(sUrl);
    qDebug()<<"after http";

    QElapsedTimer t;
    t.start();

    while (t.elapsed()<iTimeout && !m_bApiReturn)
    {
        QCoreApplication::processEvents();
    }

     qDebug()<<"after ok timer "<<m_bApiReturn;
    if(m_bApiReturn)
    {
        dOut=m_dOut;
    }


    if(m_sNowApi==API_SESSION)
    {
        qDebug()<<"session : "<<m_sSession;
    }


    sRe=m_sReturnValue;
    return sRe;
}

QString CallApi::postApi(QString sApi, QList<QStringList> &dOut, QJsonObject obj,QString sIn, int iTimeout)
{

    QString sRe="";
    m_sNowApi=sApi;

    QString sUrl=sApi;

    if(m_sNowApi==API_REGISTER || m_sNowApi==API_UPDATE_MEMBER_DATA || m_sNowApi== API_SEND_ORDER ||
            m_sNowApi ==API_UPDATE_DELIVERY_DATA)
        sUrl+=m_sSession+"/";

    if(m_sNowApi==API_SEND_ORDER)
        sUrl+=m_sIsPreTrade;
//    if(m_sNowApi==API_REGISTER || m_sNowApi ==API_SEND_ORDER)
//        sUrl+=m_sCarId+"/";

    if(sIn!="")
        sUrl+=sIn+"/";
    m_bApiReturn=false;

    qDebug()<<"send API: "<<sUrl;
    emit signalDebug("call(post) api : "+sUrl);

    QJsonDocument doc(obj);
    QString strJson2(doc.toJson(QJsonDocument::Compact));
    emit signalDebug("post json : "+strJson2);
    doHttpPost(sUrl,obj);


    QElapsedTimer t;
    t.start();

    while (t.elapsed()<iTimeout && !m_bApiReturn)
    {
        QCoreApplication::processEvents();
    }


    if(m_bApiReturn)
    {
        dOut=m_dOut;
    }

    sRe=m_sReturnValue;
    return sRe;
}


void CallApi::slotGetFinish(QNetworkReply *reply)
{
    qDebug()<<"reply : API "<<m_sNowApi;
    QString strReply=QString::fromUtf8(reply->readAll());

    //    //QString AA(reply->readAll());


    //    QString a1 = strReply;
    //    a1 = a1.replace ("\\", "");
    //    a1 = a1.replace ("\"", "");

    //    QJsonDocument doc = QJsonDocument::fromJson (a1.toUtf8 ());


    qDebug()<<"strReply: "<<strReply.toUtf8();

    emit signalDebug("api reply : "+strReply+"'\n'\n");
    m_dOut.clear();
    m_sReturnValue=API_CONNECT_ERROR;
    QJsonDocument jDoc=QJsonDocument::fromJson(strReply.toUtf8());

    QString sReturn=jDoc.object()["return"].toString();
    QJsonObject jObj=jDoc.object()["data"].toObject();
    // QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
    QJsonArray arr=jDoc.object()["data"].toArray();

    qDebug()<<" API : "<<m_sNowApi;
    if(m_sNowApi==API_SESSION)
    {
        m_sSession=jObj["sessionID"].toString();
        QString sLogin=jObj["isLogin"].toString();
        qDebug()<<"check login : "<<sLogin;
        if(sLogin=="1")
            m_bIsLogin=true;


    }

    else if(m_sNowApi==API_LAST_UPDATE)
    {
        QStringList list;
        list.append(jObj["product"].toString());
        list.append(jObj["header"].toString());
        list.append(jObj["ad"].toString());
        m_dOut.append(list);

    }

    else if(m_sNowApi==API_AD)
    {
        for(int i=0;i<arr.count();i++)
        {
            QStringList list;
            QJsonObject jObj =arr.at(i).toObject();
            list.append(jObj["linkType"].toString());
            list.append(jObj["codeName"].toString());
            list.append(jObj["imageUrl"].toString());
            m_dOut.append(list);
        }

    }


    else if(m_sNowApi==API_HEADER)
    {
        for(int i=0;i<arr.count();i++)
        {
            QStringList list;
            QJsonObject jObj =arr.at(i).toObject();

            list.append(jObj["id"].toString());
            list.append(jObj["name"].toString());
            list.append(jsonArrIntToString(jObj["child"].toArray()));
            list.append(jObj["parent"].toString());

            m_dOut.append(list);

        }

    }

    else if(m_sNowApi==API_PRODUCT_LIST)
    {

        for(int i=0;i<arr.count();i++)
        {
            QStringList list;
            QJsonObject jObj =arr.at(i).toObject();

            list.append(jObj["id"].toString());
            list.append(jObj["name"].toString());
            list.append(jObj["headerId"].toString());
            list.append(jObj["source"].toString());
            list.append(jObj["basePrice"].toString());
            list.append(jObj["sellPrice"].toString());
            list.append(jObj["image"].toString());

            m_dOut.append(list);
        }
    }


    else if(m_sNowApi==API_PRODUCT_DETAIL)
    {

        QJsonDocument doc(jObj);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        m_dOut.append(QStringList(strJson));
    }

    else if(m_sNowApi==API_OUTFIT_DETAIL)
    {
        QJsonDocument doc(jObj);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        m_dOut.append(QStringList(strJson));
    }

    else if(m_sNowApi==API_SIZE_TALBE)
    {

        QJsonArray jsonCol= jObj["sizeArray"].toArray();
        QStringList listCol;
        for(int i=0;i<jsonCol.count();i++)
        {
            listCol.append(jsonCol.at(i).toString());
        }

        QJsonArray jsonRow= jObj["partArray"].toArray();
        QStringList listRow;
        for(int i=0;i<jsonRow.count();i++)
        {
            listRow.append(jsonRow.at(i).toString());
        }

        QJsonArray jsonData= jObj["sizeValueArray"].toArray();
        QStringList listData;
        for(int i=0;i<jsonData.count();i++)
        {
            listData.append(jsonData.at(i).toString());
        }

        m_dOut.append(listCol);
        m_dOut.append(listRow);
        m_dOut.append(listData);

    }

    else if(m_sNowApi==API_ADD_CAR)
    {
        QStringList list;
        list.append(jObj["isMaxQty"].toString());
        m_dOut.append(list);
    }

    else if(m_sNowApi==API_GET_CAR)
    {
        QJsonDocument doc(arr);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        m_dOut.append(QStringList(strJson));
    }

    else if(m_sNowApi==API_UPDATE_CAR)
    {
        // m_dOut.append(QStringList(sReturn));
    }

    else if(m_sNowApi==API_LOGIN)
    {
        QStringList list;
        list.append(jObj["mlv"].toString());
        list.append(jObj["cartID"].toString());
        m_dOut.append(list);
    }

    else if(m_sNowApi==API_LOGOUT)
    {
        // m_dOut.append(QStringList(sReturn));
    }

    else if(m_sNowApi==API_REGISTER)
    {
        QStringList list;
        list.append(jObj["mlv"].toString());
        list.append(jObj["cartID"].toString());
        m_dOut.append(list);

    }

    else if(m_sNowApi==API_FORGET_PASSWORD)
    {
        //m_dOut.append(QStringList(sReturn));
    }

    else if(m_sNowApi==API_CHANGE_PASSWORD)
    {
        // m_dOut.append(QStringList(sReturn));
    }

    else if(m_sNowApi==API_GET_MEMBER_DATA)
    {
        QStringList list;
        list.append(jObj["lastName"].toString());
        list.append(jObj["firstName"].toString());
        list.append(jObj["address"].toString());
        list.append(jObj["sex"].toString());
        list.append(jObj["mobile"].toString());
        list.append(jObj["city"].toString());
        list.append(jObj["province"].toString());
        list.append(jObj["postalCode"].toString());
        list.append(jObj["countryCode"].toString());
        list.append(jObj["countryName"].toString());
        list.append(jObj["invoiceNo"].toString());
        list.append(jObj["invoiceTitle"].toString());

        m_dOut.append(list);
    }

    else if(m_sNowApi==API_SEND_ORDER)
    {
        QString sData=jObj["orderID"].toString();
        m_dOut.append(QStringList(sData));
    }

    else if(m_sNowApi==API_UPDATE_DELIVERY_DATA)
    {
        QString sData=jObj["deliveryID"].toString();
        m_dOut.append(QStringList(sData));
    }

    else if(m_sNowApi==API_GET_DELIVERY_LIST)
    {
        QStringList listId;
        QStringList listName;
        for(int i=0;i<arr.count();i++)
        {

            QJsonObject jObj =arr.at(i).toObject();
            listId.append(jObj["deliveryID"].toString());
            listName.append(jObj["lastName"].toString()+jObj["firstName"].toString());
        }

        m_dOut.append(listId);
        m_dOut.append(listName);
    }

    else if(m_sNowApi==API_GET_DELIVERY_DATA)
    {
        QStringList list;
        list.append(jObj["lastName"].toString());
        list.append(jObj["firstName"].toString());
        list.append(jObj["address"].toString());
        list.append(jObj["mobile"].toString());
        list.append(jObj["city"].toString());
        list.append(jObj["province"].toString());
        list.append(jObj["postalCode"].toString());
        list.append(jObj["countryCode"].toString());
        list.append(jObj["countryName"].toString());

        m_dOut.append(list);
    }

    else if(m_sNowApi==API_PRODUCT_PRICE)
    {

        for(int i=0;i<arr.count();i++)
        {
            QStringList list;
            QJsonObject jObj =arr.at(i).toObject();
            list.append(jObj["PP2ID"].toString());
            list.append(jObj["sellingPrice"].toString());
            list.append(jObj["baseRackPrice"].toString());
            list.append(jObj["QTY"].toString());

            m_dOut.append(list);
        }

    }

    else if(m_sNowApi==API_GET_ORDER_LIST)
    {
        for(int i=0;i<arr.count();i++)
        {
            QStringList list;
            QJsonObject jObj =arr.at(i).toObject();
            list.append(jObj["orderDate"].toString());

            list.append(jObj["orderID"].toString());
            list.append(jObj["paymentStatus"].toString());
            list.append(jObj["orderStatus"].toString());

            m_dOut.append(list);
        }
    }

    else if(m_sNowApi==API_GET_ORDER_LIST_DETAIL)
    {
        QJsonDocument doc(jObj);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        m_dOut.append(QStringList(strJson));

    }
    else if(m_sNowApi==API_SET_VALUE+m_sFreeKey)
    {

    }
    else if(m_sNowApi==API_GET_VALUE)
    {
        QString sKey=m_sFreeKey;
        QString st=jObj["value"].toString();

        QStringList list;
        list.append(sKey);
        list.append(st);
        m_dOut.append(list);
    }



    m_sReturnValue=sReturn;
    m_bApiReturn=true;

}



void CallApi::doHttpGet(QString sUrl)
{

    QNetworkRequest request(sUrl);


    if(m_networkManager!=NULL)
    {
        m_networkManager->deleteLater();
        m_networkManager=NULL;
    }
    if(m_networkManager==NULL)
    {
        m_networkManager = new QNetworkAccessManager(this);
        m_networkManager->connect(m_networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slotGetFinish(QNetworkReply*)));

    }
    m_networkManager->get(request);

}


void CallApi::doHttpPost(QString sUrl, QJsonObject obj)
{
    QByteArray data;
    QJsonDocument document;
    document.setObject(obj);
    //data.append("memberData=");
    data.append(document.toJson(QJsonDocument::Compact));
    QUrl url(sUrl);
    QNetworkRequest request;
    request.setUrl(url);
    //request.setHeader(QNetworkRequest::ContentTypeHeader,  "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if(m_networkManager!=NULL)
    {
        delete m_networkManager;
        m_networkManager=NULL;
    }
    if(m_networkManager==NULL)
    {
        m_networkManager = new QNetworkAccessManager(this);
        m_networkManager->connect(m_networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slotGetFinish(QNetworkReply*)));
    }

    m_networkManager->post(request,data);


}

QString CallApi::jsonArrIntToString(QJsonArray json)
{
    QString sRe="";

    for(int i=0;i<json.count();i++)
    {
        if(i!=0)
        {
            sRe+=",";
        }
        sRe+=QString::number(json[i].toInt());

    }


    return sRe;
}








