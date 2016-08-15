#include "CfunctionLink.h"

CfunctionLink::CfunctionLink(QObject *parent) : CallApi(parent)
{
    callSession();
}

CfunctionLink::~CfunctionLink()
{

}

QString CfunctionLink::callSession()
{

    QString sRe=CONNECT_ERROR;
    QString sSession=g_sql.getOtherData(SqlOtherDataKey::sSession);
    if(sSession=="")
    {
        m_sSession="0";
    }
    else
    {
        m_sSession=sSession;
    }

    sRe=getApi(API_SESSION,m_sSession);

    if(sRe=="1")
        g_sql.setOtherData(SqlOtherDataKey::sSession,m_sSession);

    return sRe;
}

int CfunctionLink::callAd()
{
    int iRe=JB_CONNECT_ERROR;
    QString sRe="";
    QList<QStringList> dData;


    if(g_sql.checkHaveAdData())
    {
        qDebug()<<"have ad";
        sRe=g_sql.getAdData(dData);
        if(sRe!="")
            iRe=0;
    }
    else
    {
        qDebug()<<"no ad";
        sRe="";
        sRe=getApi(API_AD,dData,"",5000);
        if(sRe!="")
        {
            g_sql.addAdData(dData);
            iRe=0;
        }
    }

    if(iRe!=JB_CONNECT_ERROR)
    {
        g_data.g_dAd=dData;
        qDebug()<<"call AD";
    }
    return iRe;
}

//int CfunctionLink::callHeader()
//{
//    int iRe=JB_CONNECT_ERROR;
//    QList<QStringList> dData;


//    if(g_sql.checkHaveHeaderData())
//    {
//        qDebug()<<"have header";
//        dData=g_sql.getHeaderData();
//    }
//    else
//    {
//        qDebug()<<"no header";
//        QString sTmp=getApi(API_HEADER,dData,"",5000);
//        if(sTmp!="")
//        {
//            g_sql.addHeaderData(dData);
//            iRe=0;
//        }

//    }

//    //  getApi(API_HEADER,dOut,"",3000);
//    g_data.g_dMenu=dData;

//    QStringList listMenuNameH1;
//    foreach (QStringList listData, dData)
//    {
//        QString sName=listData.at(_Menu::_headerNameH1);
//        if(listMenuNameH1.indexOf(sName)==-1)
//            listMenuNameH1.append(sName);
//        g_data.g_listMenuH1=listMenuNameH1;
//    }

//    return iRe;
//}

QString CfunctionLink::getHeader()
{
    QString sRe=CONNECT_ERROR;
    QList<QStringList> dData;

#if 1
    if(g_sql.checkHaveHeaderData())
    {
        qDebug()<<"have header";
        dData=g_sql.getHeaderData();
    }
    else
    {
        qDebug()<<"no header";
        sRe=getApi(API_HEADER,dData,"",5000);
        if(sRe=="1")
        {
            g_sql.addHeaderData(dData);
        }

    }
#else
    sRe=getApi(API_HEADER,dData,"",5000);
#endif
    // QString sTmp=getApi(API_HEADER,dData,"",5000);
    g_data.g_header.setData(dData);
    return sRe;
}

int CfunctionLink::getLastUpdateDate(QStringList &list)
{
    int iRe=JB_CONNECT_ERROR;
    QList<QStringList> dOut;
    QString sTmp=getApi(API_LAST_UPDATE,dOut);
    if(sTmp!="")
        iRe=0;

    while (dOut.length()<1)
    {
        QStringList list;
        list<<""<<""<<"";
        dOut.append(list);
    }

    while (dOut[0].length()<3)
    {
        dOut[0].append("");
    }

    list=dOut[0];
    return iRe;
}


//    sAlt="alt/1/0/"     :從第1個開始，共取0個(0個代表全部)
QList<QStringList> CfunctionLink::getProductList(QString sHeaderId,int iStartIdx,int iCount)
{

    QString sKey=sHeaderId;
    QList<QStringList> dData;

    QString st=sKey+"/%1/%2/";
    st=st.arg(iStartIdx).arg(iCount);


    if(g_sql.checkHaveProductList(sKey))
    {
        qDebug()<<"db has the list data : "<<sHeaderId;
        dData=g_sql.getProductList(sKey);
    }
    else
    {
        qDebug()<<"list data none in db: "<<sHeaderId;
        getApi(API_PRODUCT_LIST,dData,st,5000);
        g_sql.addProductList(sKey,dData);
    }

    return dData;
}

void CfunctionLink::getAllProductList()
{
    QList<QStringList> dData;
    getApi(API_PRODUCT_LIST,dData);

    qDebug()<<"get all product list ok";
    foreach(QStringList list,dData)
    {

            g_sql.addProductList(list[_productList::_headerId],list);
    }

    qDebug()<<"product update db ok";


}

//DataProductDetail CfunctionLink::getProductDetail(QString sId)
//{
//    DataProductDetail re;

//    QList<QStringList> dData;

//#if 1
//    qDebug()<<"db have detail : "<<g_sql.checkHaveProductDetail(sId);
//    if(g_sql.checkHaveProductDetail(sId))
//    {
//        dData=g_sql.getProductDetail(sId);
//    }
//    else
//    {
//        getApi(API_PRODUCT_DETAIL,dData,sId,5000);
//        g_sql.addProductDetail(sId,dData);
//    }

//#else
//    getApi(API_PRODUCT_DETAIL,dData,sId,5000);
//#endif


//    QString sTmp="";
//    if(dData.length()>0 && dData.at(0).length()>0)
//        sTmp=dData.at(0).at(0);
//    re.setData(sTmp);

//    return re;
//}

QString CfunctionLink::getProductDetail(QString sId, DataProductDetail &cData)
{
    QString sRe=QString::number(JB_CONNECT_ERROR);
    QList<QStringList> dData;

#if 1
    qDebug()<<"db have detail : "<<g_sql.checkHaveProductDetail(sId);
    if(g_sql.checkHaveProductDetail(sId))
    {
        sRe="1";
        dData=g_sql.getProductDetail(sId);
    }
    else
    {
        sRe=getApi(API_PRODUCT_DETAIL,dData,sId,5000);
        if(sRe=="1")
            g_sql.addProductDetail(sId,dData);
    }

#else
    getApi(API_PRODUCT_DETAIL,dData,sId,5000);
#endif


    QString sTmp="";
    if(dData.length()>0 && dData.at(0).length()>0)
        sTmp=dData.at(0).at(0);
    cData.setData(sTmp);

    return sRe;
}

DataOutfitDetail CfunctionLink::getOutfitDetail(QString sId)
{
    DataOutfitDetail re;

    QList<QStringList> dData;

    qDebug()<<"db have outfit detail : "<<g_sql.checkHaveOutfitDetail(sId);
    if(g_sql.checkHaveOutfitDetail(sId))
    {
        dData=g_sql.getOutfitDetail(sId);
    }
    else
    {
        getApi(API_OUTFIT_DETAIL,dData,sId,5000);
        g_sql.addOutfitDetail(sId,dData);
    }


    QString sTmp="";
    if(dData.length()>0 && dData.at(0).length()>0)
        sTmp=dData.at(0).at(0);
    re.setData(sTmp);

    return re;
}

QList<QStringList> CfunctionLink::getSizeTable(QString sId)
{
    QList<QStringList> dRe;
    getApi(API_SIZE_TALBE,dRe,sId,5000);
    return dRe;
}

//void CfunctionLink::setHeader1(QString sHeader1)
//{
//    QStringList listMenuNameH2;
//    //go m_layer1  detail page
//    foreach (QStringList listData, g_data.g_dMenu)
//    {
//        QString st=listData[_Menu::_headerNameH2];
//        if(listData[_Menu::_headerNameH1]==sHeader1 && listMenuNameH2.indexOf(st)==-1 && listData[_Menu::_headerType]!="banner")
//        {
//            listMenuNameH2.append(st);
//        }
//    }
//    g_data.g_listMenuH2=listMenuNameH2;
//}

//void CfunctionLink::setHeader2(QString sHeader1, QString sHeader2)
//{
//    QStringList listMenuNameH3;
//    QStringList listMenuAltH3;
//    QStringList listAltType;
//    foreach (QStringList listData, g_data.g_dMenu)
//    {
//        QString st=listData[_Menu::_headerNameH3];
//        QString sAlt=listData[_Menu::_h3Alt];
//        QString sType=listData[_Menu::_headerType];
//        if(listData[_Menu::_headerNameH1] == sHeader1 && listData[_Menu::_headerNameH2]==sHeader2 && listMenuNameH3.indexOf(st)==-1 && listData[_Menu::_headerType]!="banner")
//        {
//            listMenuNameH3.append(st);
//            listMenuAltH3.append(sAlt);
//            listAltType.append(sType);
//        }
//    }
//    g_data.g_listNowMenuH3=listMenuNameH3;
//    g_data.g_listNowMenuAlt3=listMenuAltH3;
//    g_data.g_listNowAltType=listAltType;
//}

QString CfunctionLink::addCar(DataAddCar data, QStringList &listOut)
{
    QList<QStringList> dOut;
    QString sRe;

    sRe=getApi(API_ADD_CAR,dOut,data.getData(),5000);

    if(sRe=="1" && dOut.length()>0 )
    {
        listOut.append(dOut[0]);
    }
    else
    {
        listOut.append("");
    }

    return sRe;
}

QList<DataGetCar> CfunctionLink::getCar(int iFlag)
{
    QList<QStringList> dOut;
    getApi(API_GET_CAR,dOut,QString::number(iFlag),5000);

    QList<DataGetCar> listData;

    QString sData;
    //  if(dOut.length()>0 || dOut.at(0).length()>0)
    sData=dOut.at(0).at(0);

    QJsonDocument jsonResponse = QJsonDocument::fromJson(sData.toUtf8());;
    QJsonArray arr=jsonResponse.array();

    for(int i=0;i<arr.count();i++)
    {
        DataGetCar data;
        data.setData(arr[i].toObject());
        listData.append(data);
    }

    return listData;

}

QString CfunctionLink::updateNumsCar(QString sCarItemId,int iNums)
{
    return getApi(API_UPDATE_CAR,sCarItemId+"/"+QString::number(iNums));
}




QString CfunctionLink::login(QString sName, QString sPassword)
{
    QList<QStringList> dOut;
    QString in=sName+"/"+sPassword+"/";
    QString sReturnCode=getApi(API_LOGIN,dOut,in);

    if(sReturnCode=="1")
    {
        // m_sCarId=dOut[0][1];
        m_bIsLogin=true;
        //        g_sql.setOtherData(SqlOtherDataKey::sSession,m_sSession);
        //        g_sql.setOtherData(SqlOtherDataKey::sCarId,m_sCarId);
    }
    return sReturnCode;
}

QString CfunctionLink::logout()
{


    QString sReturnCode=getApi(API_LOGOUT);
    if(sReturnCode=="1")
    {
        m_bIsLogin=false;
        callSession();
    }
    return sReturnCode;
}

bool CfunctionLink::checkLogin()
{
    return m_bIsLogin;
}

QString CfunctionLink::fogetPassword(QString sEmail)
{
    return getApi(API_FORGET_PASSWORD,sEmail);
}

QString CfunctionLink::memberRegister(QJsonObject obj,QStringList &listOut)
{
    QString sRe;
    QList<QStringList> dOut;
    sRe=postApi(API_REGISTER,dOut,obj);
    while(dOut.length()<1)
    {
        QStringList list;
        list<<""<<""<<"";
        dOut.append(list);
    }
    listOut=dOut[0];
    return sRe;
}

QString CfunctionLink::updateMemberData(QJsonObject obj)
{
    qDebug()<<"update member : "<<obj;
    QList<QStringList> dOut;
    QString sRe;
    sRe=postApi(API_UPDATE_MEMBER_DATA,dOut,obj);
    while(dOut.length()<1)
    {
        QStringList list;
        list<<""<<"";
        dOut.append(list);
    }

    return sRe;
}


QString CfunctionLink::getMemberData(QStringList &listOut)
{
    QString sRe;
    QList<QStringList> dOut;
    sRe=getApi(API_GET_MEMBER_DATA,dOut);
    listOut=dOut[0];

    return sRe;
}

QString CfunctionLink::changePassword(QString sOld, QString sNew)
{
    return getApi(API_CHANGE_PASSWORD,sOld+"/"+sNew+"/");
}

QString CfunctionLink::sendOrder(QJsonObject obj, QString &sOrderId)
{
    QList<QStringList> dOut;
    QString sRe;
    sRe=postApi(API_SEND_ORDER,dOut,obj);
    sOrderId=dOut[0][0];
    while(dOut.length()<1)
    {
        QStringList list;
        list<<""<<"";
        dOut.append(list);
    }

    return sRe;
}

QString CfunctionLink::getOrderList(QList<QStringList> &dData)
{
    QString sRe;
    sRe=getApi(API_GET_ORDER_LIST,dData);
    return sRe;
}

QString CfunctionLink::getOrderListDetail(QString sId, DataOrderListDetail &cData)
{
    QString sRe=QString::number(JB_CONNECT_ERROR);
    QList<QStringList> dData;

    sRe=getApi(API_GET_ORDER_LIST_DETAIL,dData,sId,5000);

    QString sTmp="";
    if(dData.length()>0 && dData.at(0).length()>0)
        sTmp=dData.at(0).at(0);


    if(sRe=="1")
        cData.setData(sTmp);

    return sRe;
}

QString CfunctionLink::getProductPriceQty(QString sPid,QList<QStringList> &dData)
{
    QString sRe;
    qDebug()<<"PriceQty";
    sRe=getApi(API_PRODUCT_PRICE,dData,sPid,3000);

    if(dData.length()>0)
    {

    }
    else
    {
        qDebug()<<"<0";
    }
    return sRe;
}

QString CfunctionLink::updateDelivery(QString &sDeliveryId,QJsonObject obj)
{

    QList<QStringList> dOut;
    QString sRe;
    sRe=postApi(API_UPDATE_DELIVERY_DATA,dOut,obj,sDeliveryId);
    while(dOut.length()<1)
    {
        QStringList list;
        list<<""<<"";
        dOut.append(list);
    }
    sDeliveryId=dOut[0][0];
    return sRe;
}

QString CfunctionLink::getDeliveryList(QStringList &listDeliveryId, QStringList &listDeliveryName)
{
    QList<QStringList> dOut;
    QString sRe;
    sRe=getApi(API_GET_DELIVERY_LIST,dOut);

    listDeliveryId=dOut[0];
    listDeliveryName=dOut[1];

    return sRe;
}

QString CfunctionLink::getDeliveryData(QString sId,QStringList &listData)
{
    QList<QStringList> dOut;
    QString sRe;
    sRe=getApi(API_GET_DELIVERY_DATA,dOut,sId);
    listData=dOut[0];
    return sRe;

}

QString CfunctionLink::getNccc()
{
    return API_NCCC+m_sOrderId;
}

QString CfunctionLink::getValue(QString sKey)
{
    QString sRe="";
    QList<QStringList> dOut;
    QString sReturn=getApi(API_GET_VALUE,dOut,sKey,3000);

    if(sReturn!=CONNECT_ERROR)
        sRe=dOut[0][1];
    return sRe;
}






