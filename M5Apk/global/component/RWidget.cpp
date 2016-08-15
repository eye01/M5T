#include "RWidget.h"

RWidget::RWidget(QWidget *parent) : QWidget(parent)
{
    m_wRollContent=NULL;
    m_bIsVscroll=false;
    m_iMargin=50;

    m_ani.setPropertyName("pos");
    m_ani.setDuration(100);
    m_ani.setEasingCurve(QEasingCurve::OutInBounce);

    m_wTopWing=new RWtopWing(this);
    //m_wTopWing->setGeometry(0,0,width(),m_iMargin);
    m_wTopWing->setGeometry(0,0,500,50);
    m_wTopWing->hide();

}


void RWidget::mousePressEvent(QMouseEvent *e)
{
    if(m_wRollContent && m_bIsVscroll)
    {
        m_iOldPressY=e->y();
        m_iOldContentY=m_wRollContent->y();
    }
}

void RWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(m_wRollContent && m_bIsVscroll)
    {
        int iDiffY=e->pos().y()-m_iOldPressY;
        int iMoveValue=qBound( -(m_wRollContent->height()-height())-m_iMargin,m_iOldContentY+iDiffY,0+m_iMargin);
        m_wRollContent->move(0,iMoveValue);
    }
}

void RWidget::mouseReleaseEvent(QMouseEvent *)
{
    if(m_wRollContent)
    {
        int iY=m_wRollContent->y();
        if(iY>0)
        {
//            m_wTopWing->move(0,0);
//            m_wTopWing->raise();
//            m_wTopWing->show();
            m_ani.setStartValue(QPoint(m_wRollContent->pos()));
            m_ani.setEndValue(QPoint(0,0));
            m_ani.start();
        }
        else if(iY<-(m_wRollContent->height()-height()))
        {
            m_ani.setStartValue(QPoint(m_wRollContent->pos()));
            m_ani.setEndValue(QPoint(0,-(m_wRollContent->height()-height())));
            m_ani.start();
        }
        else{}
    }
}

void RWidget::showEvent(QShowEvent *)
{

}

void RWidget::setVscrollItem(QWidget *wVscrollItem)
{
    m_wRollContent=wVscrollItem;
    m_ani.setTargetObject(m_wRollContent);
    m_bIsVscroll=true;

}

void RWidget::setAnimation(int iMillSec, int iMargin, const QEasingCurve &easing)
{
    m_iMargin=iMargin;
    m_ani.setDuration(iMillSec);
    m_ani.setEasingCurve(easing);
}
