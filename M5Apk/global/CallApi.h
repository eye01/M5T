#ifndef CALLAPI_H
#define CALLAPI_H

#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QElapsedTimer>
#include <QCoreApplication>



static const QString API_LINK ="https://www.joanbuller.com/";  //正式機
//static const QString API_LINK ="http://test.joanbuller.com/";  //測試機
//static const QString API_LINK ="https://www.joanbuller.com/JB_API_TEST"; //純回傳值而不寫入正式機
//static const QString API_LINK ="http://192.168.3.30:81/JB_API_TEST";  //仿正式機的測試DB

static const QString API_DOMAIN ="JB_API/";
static const QString WEB_DOMAIN ="member/";

//商品api
#define API_SESSION API_LINK+API_DOMAIN+"createSessionID/"
#define API_LAST_UPDATE API_LINK+API_DOMAIN+"getLastUpdateTime/"
#define API_AD API_LINK+API_DOMAIN+"getAd/"
#define API_HEADER API_LINK+API_DOMAIN+"getHeader/"
#define API_PRODUCT_LIST API_LINK+API_DOMAIN+"getProductList/"
#define API_PRODUCT_DETAIL API_LINK+API_DOMAIN+"getProductDetail/"
#define API_OUTFIT_DETAIL API_LINK+API_DOMAIN+"getoutfitProductDetail/"
#define API_SIZE_TALBE API_LINK+API_DOMAIN+"getProductSizeForm/"

#define API_PRODUCT_PRICE API_LINK+API_DOMAIN+"getProductPriceQty/"

//購物
#define API_ADD_CAR API_LINK+API_DOMAIN+"addCart/"
#define API_GET_CAR API_LINK+API_DOMAIN+"getCart/"
#define API_UPDATE_CAR API_LINK+API_DOMAIN+"updateCartItemQty/"
#define API_DELETE_ITEM_CAR API_LINK+API_DOMAIN+"deleteCartItem/"

//會員
#define API_REGISTER API_LINK+API_DOMAIN+"registerMember/"
#define API_CHECK_EMAIL API_LINK+API_DOMAIN+"checkEmailExist/"

#define API_LOGIN API_LINK+API_DOMAIN+"checkLogin/"
#define API_LOGOUT API_LINK+API_DOMAIN+"logout/"
#define API_FORGET_PASSWORD API_LINK+API_DOMAIN+"forgetPassword/"
#define API_CHANGE_PASSWORD API_LINK+API_DOMAIN+"updateMemberPassword/"
#define API_REGISTER API_LINK+API_DOMAIN+"registerMember/"
#define API_UPDATE_MEMBER_DATA API_LINK+API_DOMAIN+"updateMemberData/"
#define API_GET_MEMBER_DATA API_LINK+API_DOMAIN+"getMemberData/"

//訂單
#define API_SEND_ORDER API_LINK+API_DOMAIN+"creatOrder/"
#define API_UPDATE_DELIVERY_DATA API_LINK+API_DOMAIN+"updateDeliveryData/"
#define API_GET_DELIVERY_LIST API_LINK+API_DOMAIN+"getDeliveryList/"
#define API_GET_DELIVERY_DATA API_LINK+API_DOMAIN+"getDeliveryData/"

#define API_GET_ORDER_LIST API_LINK+API_DOMAIN+"getMemberOrderList/"
#define API_GET_ORDER_LIST_DETAIL API_LINK+API_DOMAIN+"getMemberOrderDetail/"
#define API_NCCC API_LINK+WEB_DOMAIN+"NCCC_payment_m/"

#define API_SET_VALUE API_LINK+API_DOMAIN+"defineVariable/"
#define API_GET_VALUE API_LINK+API_DOMAIN+"defineVariable/"


#define PRODUCT_TYPE_NORMAL "1"

#define PRODUCT_TYPE_OUTFIT "2"

#define API_CONNECT_ERROR "-999"

namespace _Ad
{
enum
{
    _linkType,
    _codeName,
    _imageUrl
};
}

namespace _Menu
{
enum
{
    _headerNameH1,
    _headerNameH2,
    _headerNameH3,
    _h2Alt,
    _h3Alt,
    _headerType
    //,_h3Url
};
}

namespace _LastUpdate
{
enum
{
    _productList,
    _headerName,
    _ad
};
}

namespace _productList
{
enum
{

    _id,
    _name,
    _headerId,
    _source,
    _basePrice,
    _sellPrice,
    _image

};
}

namespace _productPrice
{
enum
{

    _PP2ID,
    _sellingPrice,
    _baseRackPrice,
    _QTY

};
}



namespace _register
{
enum
{
    _mlv,
    _cartID
};

}

namespace _addCar
{
enum
{
    _isMaxQty=0

};
}

namespace _memberData
{
enum
{
    _lastName=0,
    _firstName=1,
    _address,
    _sex,
    _mobile,
    _city,
    _province,
    _postalCode,
    _countryCode,
    _countryName,
    _invoiceNo,
    _invoiceTitle
};
}

namespace _deliveryData
{
enum
{
    _lastName,
    _firstName,
    _address,
    _mobile,
    _city,
    _province,
    _postalCode,
    _countryCode,
    _countryName
};
}

namespace _orderListData
{
enum
{
    _orderDate,
    _orderID,
    _paymentStatus,
    _deliveryStatus,

};
}





class CallApi : public QObject
{
    Q_OBJECT
public:
    explicit CallApi(QObject *parent = 0);
    ~CallApi();
   // QString m_sCarId;
    QString m_sSession;
    bool m_bIsLogin;
    QString m_sOrderId;
    QString m_sIsPreTrade;
    QString m_sFreeKey;
protected:



    QString getApi(QString sApi, QString sIn="", int iTimeout=3000);
    QString getApi(QString sApi,QList<QStringList> &dOut,QString sIn="",int iTimeout=3000);
    QString postApi(QString sApi, QList<QStringList> &dOut, QJsonObject obj, QString sIn="", int iTimeout=3000);


private:
    QNetworkAccessManager *m_networkManager;
    void doHttpGet(QString sUrl);
    void doHttpPost(QString sUrl,QJsonObject obj);

    QString m_sNowApi;
    QString m_sReturnValue;
    bool m_bApiReturn;
    QList<QStringList> m_dOut;

    QString jsonArrIntToString(QJsonArray json);
private slots:
    void slotGetFinish(QNetworkReply*reply);

signals:
    void signalDebug(QString st);
public slots:
};

#endif // CALLAPI_H
