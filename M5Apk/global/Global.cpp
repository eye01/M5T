#include "Global.h"



Global *Global::m_pInstance = 0;
Global::Global()
{

    g_bShopToLogin=false;
    m_bIsBlock=false;
    m_bIsShowMsg=false;
    g_iNowStage=0;
#if 0
    StageDebug *debug=new StageDebug();
//    debug->hide();
    debug->show();
    connect(&m_cFunc,SIGNAL(signalDebug(QString)),debug,SLOT(slotDebug(QString)));
#endif

}

void Global::slotBlock(bool bCanView)
{
    m_bIsBlock=true;
    emit signalBlockFlag(true,bCanView);
}

void Global::slotCancelBlock()
{
    m_bIsBlock=false;
    emit signalBlockFlag(false,true);
}


Global& Global::Instance()
{
    if(m_pInstance==0)
        m_pInstance=new Global();
    return *m_pInstance;

}

//CfunctionLink &Global::func()
//{
//    return m_cFunc;
//}

CTcpClient &Global::tcp()
{
    return m_cTcp;
}

Csql &Global::sql()
{
    return m_sql;
}

void Global::goTargetProductList(QString sAlt)
{
     // todo
        sAlt=sAlt;
//    QStringList listData;
//    QString sHeaderName="";
//    QString sType="";
//    foreach (QStringList list, FUNC().g_data.g_dMenu)
//    {
//        if(list[_Menu::_h3Alt]==sAlt)
//        {
//            listData=list;
//            sHeaderName=list[_Menu::_headerNameH3];
//            sType=list[_Menu::_headerType];
//        }
//    }



//    if(listData.length()>0 && sType!="")
//    {

//        FUNC().g_data.g_listNowMenuH3=QStringList(sHeaderName);
//        FUNC().g_data.g_listNowMenuAlt3=QStringList(sAlt);
//        FUNC().g_data.g_listNowAltType=QStringList(sType);
//        emit siganlStageChange(_StageIdx::_productList,0);
//    }
}

void Global::goTargetStage(int iIdx, int iItem)
{
    emit siganlStageChange(iIdx,iItem);
}

void Global::showMsg(QString sText,int iStageIdx)
{
    m_bIsShowMsg=true;
    emit signalMsg(true,sText,iStageIdx);
}

void Global::cancelMsg()
{
    m_bIsShowMsg=false;
    emit signalMsg(false);
}

bool Global::isShowMsg()
{
    return m_bIsShowMsg;
}

void Global::elapsedTimer(int iMsec)
{
    QElapsedTimer t;
    t.start();
    while (t.elapsed()<iMsec)
    {
        QCoreApplication::processEvents();
    }
}

bool Global::isBlock()
{
   return m_bIsBlock;
}



Global::~Global()
{

}

