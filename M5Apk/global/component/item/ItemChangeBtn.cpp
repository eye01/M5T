#include "ItemChangeBtn.h"

ItemChangeBtn::ItemChangeBtn(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    m_lb=new QLabel(this);
    m_iSec=-1;
    QObject::startTimer(35);
    m_bLock=false;

    m_bIsEnable=true;
}

void ItemChangeBtn::mouseReleaseEvent(QMouseEvent *)
{
    if(!m_bLock && m_iSec<0)
    {
        m_bLock=true;
        m_iSec=0;
    }
}

void ItemChangeBtn::timerEvent(QTimerEvent *)
{
    if(m_iSec<0)
        return;

    int iCurrentIcon=0;

    if(m_bIsEnable)
    {
        iCurrentIcon=m_iSec;
    }
    else
    {
        iCurrentIcon=m_listRes.length()-1-m_iSec;
    }

    m_lb->setStyleSheet("border-image:url("+m_listRes[iCurrentIcon]+")");

    m_iSec++;

    if(m_iSec>=m_listRes.length())
    {
        m_iSec=-1;
        m_bLock=false;
        m_bIsEnable=!m_bIsEnable;
        emit clicked(m_bIsEnable);
    }

}

void ItemChangeBtn::setIconRes(QSize sz, QStringList listRes)
{
    if(listRes.length()<1)
        return;
    resize(sz);
    m_lb->setGeometry(rect());
    m_listRes=listRes;
    m_lb->setStyleSheet("border-image:url("+m_listRes[0]+")");

}

void ItemChangeBtn::setIdxEnable(bool bIsEnable)
{
   int iIdx=0;
   m_bIsEnable=bIsEnable;
   if(!m_bIsEnable)
       iIdx=m_listRes.length()-1;

   m_lb->setStyleSheet("border-image:url("+m_listRes[iIdx]+")");
}

