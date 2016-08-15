#include "CScrollWidgetV.h"


CScrollWidgetV::CScrollWidgetV(QWidget *parent) :
    QWidget(parent)
{
    resize(parent->size());
    m_wBg=new QWidget(this);
    m_wBg->setObjectName("m_wBg");
    m_wContent=new QWidget(this);
    m_wContent->setObjectName("m_wContent");
    m_wBg->resize(this->size());
    m_wContent->resize(this->size());
    m_iSpace=0;

    startTimer(50);

}

CScrollWidgetV::~CScrollWidgetV()
{

}

void CScrollWidgetV::setContent(int iCount, int  iContentH, int iSpaceH)
{
    m_iSpace=iSpaceH;
    foreach (QWidget *lb, m_listBtn)
    {
        lb->disconnect();
        lb->deleteLater();
    }
    m_listBtn.clear();

    foreach (QWidget *w, m_listSpace)
    {
        w->deleteLater();
    }
    m_listSpace.clear();

    m_wContent->resize(m_wContent->width(),(iContentH+m_iSpace)*iCount);

    for(int i=0;i<iCount;i++)
    {
        QWidget *lb=new QWidget(m_wContent);
       // lb->setAttribute(Qt::WA_TransparentForMouseEvents, true);

        // btn->setFlat(false);

        lb->setFocusPolicy(Qt::NoFocus);
        lb->resize(m_wContent->width(),iContentH);
        lb->move(0,m_listBtn.length()*(iContentH+m_iSpace));

        lb->show();
        m_listBtn.append(lb);

        if(m_iSpace>0)
        {
            QWidget *w=new QWidget(m_wContent);
            w->setAttribute(Qt::WA_TransparentForMouseEvents,true);
            w->setStyleSheet("background-color:rgb(0,0,0,120)");
            w->setGeometry(0,lb->y()+lb->height(),lb->width(),m_iSpace);
            m_listSpace.append(w);
        }

    }


}

void CScrollWidgetV::setAutoContent(int iContentH, int iSpaceH, int iDiffCount)
{

    setContent(children().length()-2+iDiffCount,iContentH,iSpaceH);

    for(int i=2+iDiffCount;i<children().length();i++)
    {
        QObject *obj=children()[i];
        if(obj->isWidgetType())
        {
            QWidget *w=dynamic_cast<QWidget*>(obj);
            m_listBtn.append(w);
        }
    }
}



void CScrollWidgetV::resizeEvent(QResizeEvent *)
{
    m_wBg->resize(this->size());
    m_wContent->resize(width(),m_wContent->height());
    for(int i=0;i<m_listBtn.length();i++)
    {
        m_listBtn[i]->resize(width(),m_listBtn.at(i)->height());
    }

    for(int j=0;j<m_listSpace.length();j++)
    {
        m_listSpace[j]->resize(width(),m_listSpace.at(j)->height());
    }
}

void CScrollWidgetV::showEvent(QShowEvent *)
{
    m_wContent->move(0,0);
}

void CScrollWidgetV::mousePressEvent(QMouseEvent *e)
{
    // m_bAutoRun=false;
    m_pressPoint=e->pos();
    m_iOldContentY=m_wContent->y();
    m_iTochTime=0;

}

void CScrollWidgetV::mouseReleaseEvent(QMouseEvent *e)
{

    // autoMove(e->pos());


    if((m_iTochTime<150 || qAbs(e->y()-m_pressPoint.y())<40) && m_listBtn.length()>0)
    {
        int iIdx=(e->pos().y()-m_wContent->y())/(m_listBtn.at(0)->height()+m_iSpace);
        if(iIdx>=0 && iIdx <m_listBtn.length())
            emit signalClick(iIdx);
    }
    m_iTochTime=-1;
}

void CScrollWidgetV::mouseMoveEvent(QMouseEvent *e)
{
    int changeValue=e->pos().y()-m_pressPoint.y();
    int iTargetY=m_iOldContentY+changeValue;

    if(iTargetY>0)
        iTargetY=0;
    //    else if(iTargetY<-m_wContent->height()-m_iSpace*m_iViewCount)
    //        iTargetY=-m_wContent->height()-m_iSpace*m_iViewCount;

    else if(iTargetY<-m_wContent->height()+height()-20)
        iTargetY=-m_wContent->height()+height()-20;

    if(e->pos().y()<m_pressPoint.y())
    {
        //trun up
        // if(!m_bAutoRun)
        m_wContent->move(0,iTargetY);
    }
    else
    {
        //trun down
        // if(!m_bAutoRun)
        m_wContent->move(0,iTargetY);


    }

}

void CScrollWidgetV::timerEvent(QTimerEvent *)
{
    if(m_iTochTime>=0)
        m_iTochTime+=50;
}


