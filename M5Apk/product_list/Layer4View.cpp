#include "Layer4View.h"

Layer4View::Layer4View(QWidget *parent) : InterfaceView(parent)
{
    m_flagPowerFull=false;
    m_iIdx=-1;
    m_iReleaseMiniSec=-1;
    m_iPressMiniSec=-1;
    m_iRollTime=-1;
    m_iRollY=0;
    m_iTop=0;
    m_iLength=0;
    m_iSliceHeight=160;
    m_wBg=new QWidget(this);
    m_wBg->setObjectName("m_wBg");
    m_wBg->move(0,0);

    m_wContent=new QWidget(m_wBg);
    //m_wContent=new QOpenGLWidget(m_wBg);
    m_wContent->move(0,0);


    m_wContent->resize(WINDOW_W,WINDOW_W);
    for(int i=0;i<40;i++)
    {
        Item4View *item=new Item4View(m_wContent);
        item->connect(item,SIGNAL(clicked(int)),this,SIGNAL(clicked(int)));
        item->move(0,item->height()*i);
        m_listLocY.append(item->y());
        m_listItem.append(item);
    }
    m_wContent->resize(WINDOW_W,m_listItem[0]->height()*40);

    m_wTopSlice=new QWidget(m_wBg);
    m_wTopSlice->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0 rgba(255, 255, 255, 200), stop:0.965347 rgba(255, 255, 255, 0));");
    m_wTopSlice->hide();
    m_wBottomSlice=new QWidget(m_wBg);
    m_wBottomSlice->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(255, 255, 255, 200), stop:0.965347 rgba(255, 255, 255, 0));");
    m_wBottomSlice->hide();
    m_ani.setTargetObject(m_wContent);
    m_ani.setPropertyName("pos");
    m_ani.setDuration(200);
    QObject::startTimer(TIMER_DURATION);



}

void Layer4View::setBackground(QString st)
{
    m_wBg->setStyleSheet("QWidget#m_wBg{"+st+"}");
}

void Layer4View::setItemWidget(QStringList listName, QStringList listImage)
{
    if(listName.length()%2==1)
    {
        listName.append("");
        listImage.append("");
    }

    m_wContent->resize(width(),m_listItem[0]->height()*listName.length()/2);
    m_iBottom=-m_wContent->height()+m_listItem[0]->height()+20;


    int iTmp=0;
    for(int i=0;i+1<listName.length();i+=2)
    {

        QStringList tmpName;
        tmpName.append(listName.at(i));
        tmpName.append(listName.at(i+1));

        QStringList tmpUrl;
        tmpUrl.append(listImage.at(i));
        tmpUrl.append(listImage.at(i+1));
        QList<int> tmpIdx;
        tmpIdx.append(iTmp*2);
        tmpIdx.append(iTmp*2+1);
        m_listItem[iTmp]->setData(tmpIdx,tmpName,tmpUrl);
        iTmp++;
    }
    m_iLength=iTmp;



}

void Layer4View::goIdx(int iIdx)
{
    QPoint pEnd(m_wContent->x(), m_listItem[0]->height()*-iIdx);
    m_ani.setStartValue(m_wContent->pos());
    m_ani.setEndValue(pEnd);
    m_ani.start();
}

void Layer4View::setSlice(int iH, QString sTopStyleSheet, QString sBottomStyleSheet)
{
    m_iSliceHeight=iH;
    m_wTopSlice->setStyleSheet(sTopStyleSheet);
    m_wBottomSlice->setStyleSheet(sBottomStyleSheet);
}

int Layer4View::length()
{
    return m_iLength;
}

void Layer4View::mousePressEvent(QMouseEvent *e)
{
    m_flagPowerFull=false;
    m_iPressMiniSec=0;
    m_iRollTime=-1;
    if(m_wContent->height()<=height())
        return;
    m_iOldPressY= e->y();
    m_iOldContentY= m_wContent->y();



}

void Layer4View::mouseMoveEvent(QMouseEvent *e)
{

    if(m_wContent->height()<=height())// && m_listItem.length()<1)
        return;
    int iTargetY=m_iOldContentY+(e->y()-m_iOldPressY);
    contentMove(iTargetY);

}

void Layer4View::mouseReleaseEvent(QMouseEvent *e)
{

    m_iRollY=e->pos().y()-m_iOldPressY;
    m_iRollTime=m_iPressMiniSec;
    // m_sStrongSpeed=m_iRollY/(m_iRollTime/TIMER_DURATION);

    m_iPressMiniSec=-1;

    m_iReleaseMiniSec=0;

    if(m_wContent->y()>m_iTop || m_wContent->y()<m_iBottom)
    {
        correctRange();
    }
    else
    {
        if(m_iRollTime<=300 && qAbs(m_iRollY)>100)
        {
            m_flagPowerFull=true;
        }
    }

//        if(m_iPressMiniSec<500 && qAbs(m_iOldPressY-e->y())<80)
//        {
//            int iClickIdx=m_iIdx;

//            int iTmpY=m_listItem[0]->height()*m_iIdx - m_wContent->y();

//            if(e->pos().y()> iTmpY)
//                iClickIdx+=1;

//            iClickIdx*=2;
//            if(e->pos().x()>width()/2)
//                iClickIdx+=1;
//            clicked(iClickIdx);
//        }



}

void Layer4View::timerEvent(QTimerEvent *)
{

    if(m_iPressMiniSec>=0)
    {
        m_iPressMiniSec+=TIMER_DURATION;
    }

    if(m_iReleaseMiniSec>=0)
    {
        m_iReleaseMiniSec+=TIMER_DURATION;
    }

    if(m_iReleaseMiniSec>=TIMER_DURATION*3)
    {
        m_wTopSlice->hide();
        m_wBottomSlice->hide();
        m_iReleaseMiniSec=-1;
    }

    if(m_flagPowerFull)
    {
        powerfulMove();
    }


}

bool Layer4View::contentMove(int iValue)
{
    bool bRe=false;

    if(m_listItem.length()<1)
        return bRe;

    int iTargetY=qBound(m_iBottom-m_iSliceHeight,iValue,m_iTop+m_iSliceHeight);

    bRe=iValue!=iTargetY;

    int iIdx=qAbs(iTargetY)/m_listItem[0]->height();
    if(iIdx>=m_listItem.length())
        iIdx=m_listItem.length()-1;

    if(m_iIdx!=iIdx || m_iIdx==0 || m_iIdx==m_listItem.length()-1)
    {
        m_iIdx=iIdx;
        emit changeIdx(m_iIdx);
    }
    m_wContent->move(0,iTargetY);

    if(iTargetY>m_iTop)
    {
        int  iTmp=qBound(-m_iSliceHeight,iTargetY*2-m_iSliceHeight,0);
        m_wTopSlice->move(m_wTopSlice->x(),iTmp);
        m_wTopSlice->show();
    }
    else if(iTargetY<m_iBottom)
    {
        m_wBottomSlice->move(0,m_wBg->height()-m_iSliceHeight);
        m_wBottomSlice->show();
    }
    else
    {}
    if(bRe)
        qDebug()<<"is away range ";
    return bRe;
}

void Layer4View::resizeEvent(QResizeEvent *)
{
    m_wBg->resize(size());
    m_wContent->resize(m_wBg->width(),m_wContent->height());
    m_iBottom=-m_wContent->height()+height()/2;
    m_wTopSlice->setGeometry(0,0,width(),m_iSliceHeight);
    m_wBottomSlice->setGeometry(0,0,width(),m_iSliceHeight);
}

void Layer4View::correctRange()
{
    qDebug()<<"CorrectRange";
    bool bIsTop=m_wContent->y()>m_iTop;
    QPoint pEnd(m_wContent->x(),m_iBottom);
    if(bIsTop)
        pEnd=QPoint(m_wContent->x(),m_iTop);
    m_ani.stop();
    m_ani.setStartValue(m_wContent->pos());
    m_ani.setEndValue(pEnd);
    m_ani.start();
}

void Layer4View::powerfulMove()
{
//    int iTmp=m_iRollTime/TIMER_DURATION;
//    m_iRollY=(float)m_iRollY/iTmp*0.85;

    m_iRollY=(float)m_iRollY*0.7;
    int iTargetY=m_wContent->y()+m_iRollY;
    bool bAwayRange=contentMove(iTargetY);

    //越界位移，即停止位移補間，即使用越界修正
    if(bAwayRange)
    {
        m_flagPowerFull=false;
        correctRange();
    }
    // 正向滑動時，最小位移量到4；逆向滑動時最小位移至-4。則停止位移補間
    if((m_iRollY < 4 && m_iRollY >= 0 ) || (m_iRollY < 0 && m_iRollY > -4))
    {
        m_flagPowerFull=false;
    }
}

