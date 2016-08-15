#ifndef GLOBAL_H
#define GLOBAL_H

#include <QSize>
//#include "CfunctionLink.h"
#include "Csql.h"
#include <QElapsedTimer>
#include "CTcpClient.h"


#define GLOBAL Global::Instance
//#define FUNC Global::Instance().func
#define SQL Global::Instance().sql

#define ANI_MINISEC 250
#define ANI_EASING QEasingCurve::OutBack

#define LAYER_MARGIN 20
#define LAYER_SPACE 15

#define TOP_MENU_H Global::Instance().g_iTopMenuHeight
#define WINDOW_W Global::Instance().g_sizeWindow.width()
#define WIDONW_H Global::Instance().g_sizeWindow.height()



namespace _StageIdx
{
enum
{
//    _test=0,
    _start=0,
    _navigation=1,
      _login=2,
    _first=3,
    _productList=4,
    _productDetail=5,
    _outfitDetail=7,
    _memberCenter=8,
    _orderList=9,
    _memberData,
    _Delivery,
    _changePassword,

    _register,
    _about,
    _cardTrade,
    _fullScreenWeb,
    _callApk,
    _option=80,
    _car=81
};
}

namespace _StageItemIdx
{
enum
{
    _StageItem_Nono=0,
    _option_show=1,
    _option_hide=2,
    _car_show=3,
    _car_show_pre_buy,
    _car_hide,
    _trade_show,
    _trade_hide,
    _productList_dont_init_location,
};
}






class Global :public QObject
{
    Q_OBJECT
public:
    ~Global();
    static Global& Instance();
    QSize g_sizeWindow;

    int g_iPreStage;
    int g_iNowStage;
    int g_iNowStageItemIdx;
    //註冊與登入，分為直接登入與購物後登入，後者登入後要繼續購物流程畫面
    bool g_bShopToLogin;
    int g_iTopMenuHeight;

    //CfunctionLink& func();
    CTcpClient &tcp();
    Csql& sql();

    void goTargetProductList(QString sAlt);

    void goTargetStage(int iIdx,int iItem=0);

    void showMsg(QString sText, int iStageIdx=-1);

    void cancelMsg();

    bool isShowMsg();

    void elapsedTimer(int iMsec=20);

    bool isBlock();

private:
    Global();
    //CfunctionLink m_cFunc;
    CTcpClient m_cTcp;
    Csql m_sql;

    static Global* m_pInstance;
    bool m_bIsBlock;
    bool m_bIsShowMsg;
signals:
    void siganlStageChange(int,int);
    void signalBlockFlag(bool bFlag,bool bIsCanView);
    void signalMsg(bool bIsShow,QString st="",int iStageIdx=-1);
public slots:
    void slotBlock(bool bCanView=true);
    void slotCancelBlock();
};

#endif // GLOBAL_H
