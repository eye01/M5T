#include "LayerZoomView.h"


LayerZoomView::LayerZoomView(QWidget *parent) :
    InterfaceView(parent)
{
    m_iSliceHeight=160;
    resize(parent->size());
    m_wBg=new QWidget(this);
    m_wBg->setObjectName("m_wBg");

    m_wBg->resize(size());

    m_sizeView=size();
    m_wContent=new QWidget(m_wBg);
    m_wContent->resize(size());
    // m_wContent->setStyleSheet("QWidget#m_wContent{background-color:rgb(0,0,0,0)}");
    m_wContent->setStyleSheet("QWidget#m_wContent{background-color:rgb(0,0,0)}");
    m_wOption=new CZoomItem::ItemOption(m_wBg);
    m_wOption->setGeometry(0,0,width(),100);

    m_iMinHeight=height()/5;
    m_iMaxHeight=height()-m_iMinHeight*2;
    m_iSpace=0;
    m_bUseOption=false;
    m_bAniLock=false;
    m_nRollMode=_zoom;
    m_aniHoming.setTargetObject(m_wContent);
    m_aniHoming.setPropertyName("pos");
    m_aniHoming.setDuration(200);


    m_aniMoveIdx.setTargetObject(m_wContent);
    m_aniMoveIdx.setPropertyName("pos");
    m_aniMoveIdx.setDuration(200);
    //connect(&m_aniHoming,SIGNAL(valueChanged(QVariant)),this,SLOT(slotAniChange(QVariant)));
    connect(&m_aniMoveIdx,SIGNAL(finished()),this,SLOT(homing()));

    connect(&m_aniHoming,SIGNAL(valueChanged(QVariant)),this,SLOT(slotAniChange(QVariant)));
    connect(&m_aniHoming,SIGNAL(finished()),this,SLOT(slotAnifinish()));
    m_timeLine = new QTimeLine(200, this);
    m_timeLine->setFrameRange(0,10);
    connect(m_timeLine, SIGNAL(frameChanged(int)), this, SLOT(slotHoming(int)));
    m_iPressMiniSec=-1;
    m_iReleaseMiniSec=-1;
    m_iIdx=-1;
    QObject::startTimer(100);

    m_wOption->raise();
    m_wOption->hide();

    m_wMask=new QWidget(this);
    m_wMask->setStyleSheet("background-color:rgb(0,0,0,46)");
    m_wMask->setWindowFlags(Qt::FramelessWindowHint);
    m_wMask->setAttribute(Qt::WA_TranslucentBackground, true);
    m_wMask->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    m_wMask->setGeometry(0,m_iMinHeight,width(),height());
    m_wMask->hide();

    m_wTopSlice=new QWidget(m_wBg);
    m_wTopSlice->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0 rgba(255, 255, 255, 200), stop:0.965347 rgba(255, 255, 255, 0));");
    m_wTopSlice->hide();
    m_wBottomSlice=new QWidget(m_wBg);
    m_wBottomSlice->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(255, 255, 255, 200), stop:0.965347 rgba(255, 255, 255, 0));");
    m_wBottomSlice->hide();


    /* use example
    //-----------------
    QWidget *wOption=new QWidget(this);
    wOption->setStyleSheet("background-color:rgb(21,94,30)");
    wOption->resize(500,120);

    setOption(wOption);

    float fH=(float)width()*800/640;
    QList<QWidget*> list;
    for(int i=0;i<30;i++)
    {
        QWidget *w=new QWidget(this);
        ItemZoomView *item=new ItemZoomView(w);
        item->setText(QString::number(i));
        item->resize(width(),fH);
        item->show();
        list.append(w);
        w->show();
    }
    setItemWidget(list,0,(height()-fH)/2,fH);
    */

}

LayerZoomView::~LayerZoomView()
{
    //delete ui;
}

void LayerZoomView::setBackground(QString st)
{
    m_wBg->setStyleSheet("QWidget#m_wBg{"+st+"}");

    //m_wBg->setStyleSheet(QStringLiteral("QWidget#m_wBg{background-color: rgb(0, 0, 0);}"));


}

void LayerZoomView::setOption(QWidget *w)
{
    //w->setParent(m_wOption);
    m_wOption->setItem(w);

}

void LayerZoomView::setItemWidget(QList<QWidget*> listWidget, int iSpace,int iMinHeight, int iMaxHeight)
{

    if(listWidget.length()<1)
        return;


    if(iMinHeight>-1)
        m_iMinHeight=iMinHeight;
    if(iMaxHeight>-1)
        m_iMaxHeight=iMaxHeight;
    if(iSpace>-1)
        m_iSpace=iSpace;

    m_wMask->setGeometry(0,m_iMinHeight,width(),height());

    foreach (QWidget *w, m_listWidget)
    {
        delete w;
    }

    m_listWidget.clear();

    m_listWidget=listWidget;

    m_wContent->resize(m_wContent->width(),(m_listWidget.length()-1)*m_iMinHeight+m_iMaxHeight);

    for(int i=0;i<m_listWidget.length();i++)
    {
        m_listWidget[i]->setParent(m_wContent);
        m_listWidget[i]->setStyleSheet("background-color:rgba(0,0,0,0)");
        m_listWidget[i]->resize(m_wContent->width(),m_iMinHeight);

        m_listWidget[i]->show();
        //        m_listWidget[i]->setMinimumHeight(m_iMinHeight);
        //        m_listWidget[i]->setMaximumHeight(m_iMaxHeight);

        if(i==0)
        {
            m_listWidget[i]->resize(m_wContent->width(),m_iMaxHeight);
            m_listWidget[i]->move(0,0);
        }
        else
        {
            m_listWidget[i]->resize(m_wContent->width(),m_iMinHeight);
            m_listWidget[i]->move(0,m_listWidget[i-1]->y()+m_listWidget[i-1]->height()+m_iSpace);
        }

    }

}

void LayerZoomView::goIdx(int iIdx)
{
    int iTarget=qBound(0,iIdx,m_listWidget.length()-1);

    m_iIdx=iTarget;
    foreach(QWidget *w, m_listWidget)
    {
        w->resize(w->width(),m_iMinHeight);
    }

    layoutLoc();


    m_aniMoveIdx.setStartValue(m_wContent->pos());
    m_aniMoveIdx.setEndValue(QPoint(m_wContent->x(),iTarget*m_iMinHeight));
    m_aniMoveIdx.start();
}

void LayerZoomView::setSlice(int iH, QString sTopStyleSheet, QString sBottomStyleSheet)
{
    m_iSliceHeight=iH;
    m_wTopSlice->setStyleSheet(sTopStyleSheet);
    m_wBottomSlice->setStyleSheet(sBottomStyleSheet);
}

int LayerZoomView::length()
{
    return m_listWidget.length();
}

void LayerZoomView::mousePressEvent(QMouseEvent *e)
{
    m_iPressMiniSec=0;
    m_iPressContentY=m_wContent->y();
    m_iPressPosY=e->y();
}

void LayerZoomView::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_wTopSlice->isVisible() || m_wBottomSlice->isVisible())
        m_iReleaseMiniSec=0;


    if(m_iPressMiniSec<500 && qAbs(m_iPressPosY-e->pos().y())<15
            &&e->pos().y()<=m_iMaxHeight && !m_bAniLock)
    {
        emit clicked(m_iIdx);
    }

    if(m_nRollStatus==_first)
    {
        // m_wOption->showOption();
    }
    homing();

    m_iPressMiniSec=-1;


}

void LayerZoomView::mouseMoveEvent(QMouseEvent *e)
{

    int iTargetY=(m_iPressContentY+(e->y()-m_iPressPosY));


    if(iTargetY>m_iSliceHeight/2)
    {

        m_nRollStatus=_first;

        iTargetY=m_iSliceHeight/2;
    }


    else if(iTargetY<-m_wContent->height()+m_iMaxHeight-m_iMinHeight/3)
    {
        m_nRollStatus=_last;
        iTargetY=-m_wContent->height()+m_iMaxHeight-m_iMinHeight/3;
    }
    else
    {
        if(e->pos().y()-m_iPressPosY>0)
            m_nRollStatus=_driveDown;
        else
            m_nRollStatus=_driveUp;

    }


    m_wContent->move(0,iTargetY);

    if(iTargetY>0)
    {
        int  iTmp=qBound(-m_iSliceHeight,iTargetY*2-m_iSliceHeight,0);
        m_wTopSlice->move(m_wTopSlice->x(),iTmp);
        m_wTopSlice->show();
    }
    else if(iTargetY<-m_wContent->height()+m_iMaxHeight)
    {
        m_wBottomSlice->move(0,m_wBg->height()-m_iSliceHeight);
        m_wBottomSlice->show();
    }
    else
    {}


    checkZoom();
    layoutLoc();
}

void LayerZoomView::timerEvent(QTimerEvent *)
{

    if(m_iPressMiniSec>=0)
    {
        m_iPressMiniSec+=100;
    }

    if(m_iReleaseMiniSec>=0)
    {
        m_iReleaseMiniSec+=100;
    }

    if(m_iReleaseMiniSec>=400)
    {
        m_wTopSlice->hide();
        m_wBottomSlice->hide();
        m_iReleaseMiniSec=-1;
    }


#if 0
    bool bChangeMode=false;
    if(m_iPressMiniSec>1000)
    {
        bChangeMode=m_nRollMode==_zoom;
        m_nRollMode=_view;

    }
    else
    {
        bChangeMode=m_nRollMode==_view;
        m_nRollMode=_zoom;
    }


    int i=0;
    while(i<11 && bChangeMode)
    {

        QElapsedTimer t;
        t.start();
        while (t.elapsed()<50)
        {
            QCoreApplication::processEvents();
        }
        checkZoom(m_iMinHeight/2);
        i++;
    }
#endif
}

void LayerZoomView::resizeEvent(QResizeEvent *)
{

    m_sizeView=size();

    m_wBg->resize(size());
    m_wContent->resize(width(),m_wContent->height());

    foreach (QWidget *w, m_listWidget)
    {
        w->resize(width(),w->height());
    }
    m_wMask->setGeometry(0,m_iMinHeight,width(),height());
    m_wTopSlice->setGeometry(0,-m_iSliceHeight,m_wBg->width(),m_iSliceHeight);
    m_wBottomSlice->setGeometry(0,m_wBg->height()-m_iSliceHeight,m_wBg->width(),m_iSliceHeight);
}

void LayerZoomView::checkZoom(int iValue)
{
    if(iValue==-1)
        iValue=m_iMinHeight/8;
    int iY=m_wContent->y();
    int iIdx=-(iY/m_iMinHeight+m_iSpace);
    int iTmp=-(iY%(m_iMinHeight+m_iSpace));
    if(iTmp>0 && iTmp>m_iMinHeight/3)
        iIdx++;

    int iMin=m_iMinHeight;
    int iMax=m_iMaxHeight;

    if(m_nRollMode==_view)
    {
        iMin=m_iMinHeight/3;
        iMax=m_iMinHeight;
    }

    if(iIdx!=m_iIdx || iIdx==0 || iIdx ==m_listWidget.length()-1)
    {
        emit changeIdx(qBound(0,iIdx,m_listWidget.length()-1));
    }

    m_iIdx=iIdx;

    int iChangeValue=iValue;

    for(int i=0;i<m_listWidget.length();i++)
    {
        if(i==iIdx)
        {
            if(m_listWidget[i]->height()<iMax)
            {
                if(m_listWidget[i]->height()+iChangeValue > iMax)
                    m_listWidget[i]->resize(m_listWidget[i]->width(),iMax);
                else
                    m_listWidget[i]->resize(m_listWidget[i]->width(),m_listWidget[i]->height()+iChangeValue);

            }

        }
        else
        {

            if(m_listWidget[i]->height()>iMin)
            {
                if(m_listWidget[i]->height()-iChangeValue < iMin )
                {
                    m_listWidget[i]->resize(m_listWidget[i]->width(),iMin);
                }
                else
                {
                    m_listWidget[i]->resize(m_listWidget[i]->width(),m_listWidget[i]->height()-iChangeValue);
                }
            }
        }
    }





    m_wMask->setVisible(m_nRollMode==_view);
}

void LayerZoomView::layoutLoc()
{
    for(int i=0;i<m_listWidget.length();i++)
    {
        if(i==0)
            m_listWidget[i]->move(0,0);
        else
            m_listWidget[i]->move(0,m_listWidget[i-1]->y()+m_listWidget[i-1]->height()+m_iSpace);

    }
}

void LayerZoomView::homing()
{

    int iOdValue=-(m_wContent->y()%(m_iMinHeight+m_iSpace));

    int iTargetValue=m_iMinHeight-iOdValue;

    m_iLineStart=m_wContent->y();

    m_iLineValue=iTargetValue;

    if(m_iIdx==0)
        m_iLineValue=-m_iLineStart;

    QPoint pStart(m_wContent->pos());


    QPoint pEnd(0,-m_iIdx*(m_iMinHeight+m_iSpace));

    m_aniHoming.setStartValue(pStart);

    m_aniHoming.setEndValue(pEnd);

    m_aniHoming.start();
    m_timeLine->stop();
    m_timeLine->start();
    m_bAniLock=true;

}

void LayerZoomView::slotHoming(int)
{
    checkZoom(m_iMaxHeight/4);
    layoutLoc();
}

void LayerZoomView::slotAniChange(QVariant)
{
    checkZoom(m_iMaxHeight/4);
    layoutLoc();
}

void LayerZoomView::slotAnifinish()
{
    m_bAniLock=false;
}

//=============================================================================

CZoomItem::ItemOption::ItemOption(QWidget *parent):QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    m_wBg=new QWidget(this);
    m_wBg->setGeometry(rect());
    // m_wBg->setWindowFlags(Qt::FramelessWindowHint);
    //  m_wBg->setAttribute(Qt::WA_TranslucentBackground, true);
   // m_wBg->setStyleSheet("background-color:rgb(0,0,0,0);");
    m_ani.setTargetObject(m_wBg);
    m_ani.setDuration(500);
    m_ani.setPropertyName("pos");

    m_iVisibleTime=-1;
    QObject::startTimer(100);
    hide();
}

void CZoomItem::ItemOption::setItem(QWidget *wItem)
{
    resize(wItem->size());
    wItem->setParent(m_wBg);
    wItem->move(0,0);
    wItem->show();
}

void CZoomItem::ItemOption::showOption()
{
    if(m_iVisibleTime>=0)
        return;
    m_iVisibleTime=0;
    show();
    m_ani.setStartValue(QPoint(0,-height()));
    m_ani.setEndValue(QPoint(0,0));
    m_ani.start();
}

void CZoomItem::ItemOption::hideOpiton()
{

    m_iVisibleTime=-1;
    m_ani.setEndValue(QPoint(0,-height()));
    m_ani.setStartValue(QPoint(0,0));
    QEventLoop loop;
    loop.connect(&m_ani,SIGNAL(finished()),&loop,SLOT(quit()));
    m_ani.start();
    loop.exec();
    hide();

}

void CZoomItem::ItemOption::resizeEvent(QResizeEvent *)
{
    m_wBg->resize(size());
}

void CZoomItem::ItemOption::timerEvent(QTimerEvent *)
{
    if(m_iVisibleTime>-1)
    {
        m_iVisibleTime+=100;
        if(m_iVisibleTime>3000)
            hideOpiton();
    }
}
