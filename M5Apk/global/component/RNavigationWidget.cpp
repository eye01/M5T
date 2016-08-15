#include "RNavigationWidget.h"



RNavigationWidget::RNavigationWidget(QWidget *parent) :
    QWidget(parent)
{

    m_bDriveToPre=false;
    m_wViewContent=new QWidget(this);
    m_wViewContent->move(0,0);
    m_wIndexGroup=new QWidget(this);
    m_wIndexGroup->setStyleSheet("background-color:rgb(0,30,60,0)");
    m_posOld=QPoint(0,0);

    m_iPageIdx=0;
    m_bAniLock=false;
    reSet(4,50,50);
    this->setMouseTracking(false);
    m_ani.setTargetObject(m_wViewContent);
    m_ani.setDuration(ANI_MSEC);
    m_ani.setEasingCurve(QEasingCurve::OutQuart);
    m_ani.setPropertyName("pos");
    m_ani.connect(&m_ani,SIGNAL(finished()),this,SLOT(slotAniFinished()));

}

void RNavigationWidget::reSet(int iNums, int iIconSize, int iIconMargin)
{
    //resize(widgetSize);
    m_wViewContent->resize(width()*iNums,height());
    int iCentX=(width()-iIconSize)/2;
    if(iNums%2==0)
        iCentX+=(iIconSize+iIconMargin)/2;

    foreach (QWidget *w, m_listWidget)
    {
        w->deleteLater();
    }

    foreach (ItemBtn *item, m_listBtn)
    {
        item->deleteLater();
    }

    m_listWidget.clear();
    m_listBtn.clear();
    for(int i=0;i<iNums;i++)
    {
        QWidget *w=new QWidget(m_wViewContent);

        //   w->setStyleSheet("background-color:rgb(100,"+QString::number(i*20)+","+QString::number(i*10)+")");
        w->setGeometry(i*width(),0,width(),height());
        m_listWidget.append(w);

        ItemBtn *item=new ItemBtn(QSize(iIconSize,iIconSize),m_wIndexGroup);
        m_listBtn.append(item);
        item->move(i*(iIconSize+iIconMargin),0);
        item->raise();
    }


    m_wIndexGroup->resize((iIconSize+iIconMargin)*iNums-iIconMargin,iIconSize);
    // m_wIndexGroup->setStyleSheet("background-color:yellow");
    m_wIndexGroup->move((width()-m_wIndexGroup->width())/2,height()-iIconSize*2);

    m_listBtn[0]->setTargetFocus(true);
}


//-------------------------------------------------------------------------------------------------
//
RNavigationWidget::~RNavigationWidget()
{

}

//-------------------------------------------------------------------------------------------------
//
void RNavigationWidget::setIconColor(QColor colorBorder,QColor colorBody)
{
    foreach (ItemBtn *btn, m_listBtn)
    {
        btn->setIconColor(colorBorder,colorBody);
    }
}

//-------------------------------------------------------------------------------------------------
//
void RNavigationWidget::setCurrentIconColor(QColor colorBorder,QColor colorBody)
{
    foreach (ItemBtn *btn, m_listBtn)
    {
        btn->setCurrentIconColor(colorBorder,colorBody);
    }
}

//-------------------------------------------------------------------------------------------------
//
void RNavigationWidget::setWidget(QList<QLabel*> m_listPage)
{
    for(int i=0;i<m_listWidget.length();i++)
    {
        if(m_listPage.length()-1>=i)
        {
            //   m_listWidget.append(m_listPage.at(i));
            m_listPage[i]->setParent(m_listWidget[i]);
            //  m_listPage[i]->resize(m_listWidget[i]->size());
            m_listPage[i]->show();

        }
    }

    m_wIndexGroup->setVisible(m_listPage.length()>1);

}

void RNavigationWidget::goPage(int iIdx)
{
    if(m_listBtn.count()<=1)
        return;
    int iTmp=-iIdx*m_listWidget[0]->width();
    QPoint posEnd(iTmp,0);
    m_ani.setStartValue(m_wViewContent->pos());
    m_ani.setEndValue(posEnd);
    m_bAniLock=true;
    m_ani.start();
}

void RNavigationWidget::showEvent(QShowEvent *)
{
    m_bIsSendEnd=false;



}

//-------------------------------------------------------------------------------------------------
//
void RNavigationWidget::mousePressEvent(QMouseEvent *e)
{
#if USE_ANI_LOCK
    // 動畫補間鎖(放開時自動補位到該頁)，拒絕被按下移動，有鎖比較安全；不鎖比較符合常見app操作，看你要不要用囉  roger 0406
    if(m_bAniLock)
        return;
#endif
    m_posOld = e->pos();
    m_posContentOld=m_wViewContent->pos();

}

//-------------------------------------------------------------------------------------------------
//
void RNavigationWidget::mouseReleaseEvent(QMouseEvent *e)
{

#if USE_ANI_LOCK
    if(m_bAniLock)
        return;
#endif

    if(qAbs(m_posOld.x()-e->pos().x())<10)
    {

        emit signaClicked(m_iPageIdx);
    }
    else
    {
        QPoint posEnd(m_iPageIdx*-width(),0);
        m_ani.setStartValue(m_wViewContent->pos());
        m_ani.setEndValue(posEnd);
        m_bAniLock=true;
        m_ani.start();
    }
}

void RNavigationWidget::mouseMoveEvent(QMouseEvent *e)
{


    if(m_listBtn.count()<=1)
        return;




#if USE_ANI_LOCK
    if(m_bAniLock)
        return;
#endif

    int  iDiffMoveX=e->pos().x()-m_posOld.x();

    m_bDriveToPre=iDiffMoveX>0;
    bool bIsClicked=qAbs(iDiffMoveX)<10;

    //    if(diffMove.x()<-10 && m_iPageIdx==m_listBtn.count()-1)
    //        return;


    qDebug()<<"x : "<<m_wViewContent->x()<<",diff X: "<<iDiffMoveX<<" , drive : "<<m_bDriveToPre<<" ,bIsclicked: "<<bIsClicked;
    if(m_wViewContent->x()>=0 && m_bDriveToPre)
    {
        emit signalEndToPre();
        qDebug()<<"pre end";
        return;
    }

    if(m_wViewContent->x()<=-((m_listWidget.length()-1)*width()) && !m_bDriveToPre)
    {
        qDebug()<<"next end";
        emit signalEndToNext();
        return;
    }

    //    if( m_wViewContent->x()<=-((m_listWidget.length()-1)*width()) && diffMove.x()<0)
    //    {
    //        emit signalEndToNext();
    //        return;
    //    }


    //    if(!m_bIsSendEnd && m_wViewContent->x()<=-((m_listWidget.length()-1)*width()) && diffMove.x()<0)
    //    {
    //        emit signalEndToNext();
    //        m_bIsSendEnd=true;

    //        return;
    //    }


    m_wViewContent->move(m_posContentOld.x()+iDiffMoveX,0);
   // m_posOld=e->pos();
    checkPageIdx();
}

//-------------------------------------------------------------------------------------------------
//
void RNavigationWidget::checkPageIdx()
{
    int iIdx=-m_wViewContent->x()/ width();



    if(!m_bDriveToPre)
    {
        if(-m_wViewContent->x()% width()> (float)width()*0.25)
            iIdx+=1;
    }
    else
    {
        if(-m_wViewContent->x()% width()> (float)width()*0.75)
            iIdx-=1;
    }


//    if(-m_wViewContent->x()% width()> (float)width()*0.25)
//        iIdx+=1;




    iIdx= qBound(0,iIdx,m_listWidget.length()-1);





    if(iIdx==m_iPageIdx)
    {
        return;
    }

    m_iPageIdx=iIdx;

    for(int i=0;i<m_listBtn.length();i++)
    {
        if(i!=m_iPageIdx)
            m_listBtn[i]->setTargetFocus(false);
        else
            m_listBtn[i]->setTargetFocus(true);
    }

}

//-------------------------------------------------------------------------------------------------
//
void RNavigationWidget::slotAniFinished()
{
    m_bAniLock=false;
}


//=================================================================================================

ItemBtn::ItemBtn(QSize size,QWidget *parent):QWidget(parent)
{
    resize(size);
    m_colorBorder.setRgb(119,119,119);
    m_colorBody.setRgb(136,136,136);

    m_colorCurrentBorder.setRgb(85,85,85);
    //m_colorCurrentBorder.setAlpha(180);
    m_colorCurrentBody.setRgb(85,85,85);
   // m_colorCurrentBody.setAlpha(180);
    m_bIsFocus=false;
}

//-------------------------------------------------------------------------------------------------
//
ItemBtn::~ItemBtn()
{

}

//-------------------------------------------------------------------------------------------------
//
void ItemBtn::setIconColor(QColor colorBorder,QColor colorBody)
{
    m_colorBorder=colorBorder;
    m_colorBody=colorBody;
}

//-------------------------------------------------------------------------------------------------
//
void ItemBtn::setCurrentIconColor(QColor colorBorder,QColor colorBody)
{
    m_colorCurrentBorder=colorBorder;
    m_colorCurrentBody=colorBody;
    update();
}

//-------------------------------------------------------------------------------------------------
//
void ItemBtn::setTargetFocus(bool bIsFocus)
{
    m_bIsFocus=bIsFocus;
}

//-------------------------------------------------------------------------------------------------
//
void ItemBtn::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    drawSpace(&p);
}


//-------------------------------------------------------------------------------------------------
//
void ItemBtn::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked();

}

//-------------------------------------------------------------------------------------------------
//
void ItemBtn::drawSpace(QPainter *p)
{
    int x = 1, y = 1;
    int w = width()-2, h = height()-2;
    // p->save();  // 儲存繪圖裝置狀態
    QColor borderColor=m_colorBorder;
    QColor bodyColor=m_colorBody;
    if(m_bIsFocus)
    {
        borderColor=m_colorCurrentBorder;
        bodyColor=m_colorCurrentBody;
    }
    p->setPen(QPen(borderColor, 1, Qt::SolidLine));  // 藍色、4pixel大的點狀畫筆
    p->setBrush(bodyColor); // 實心黃色畫刷
    p->drawEllipse(x, y, w, h); // 以方塊為範圍的橢圓形

}
