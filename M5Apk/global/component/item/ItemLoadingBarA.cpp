#include "ItemLoadingBarA.h"



#include <QElapsedTimer>
#include <QCoreApplication>

QVector<QPixmap*> ItemLoadingBarA::m_pixArray;

ItemLoadingBarA::ItemLoadingBarA(QWidget *parent) :
    QWidget(parent)
{
    this->setGeometry(525,674,230,36);
    this->setParent(parent);
    QWidget *w=new QWidget(this);
    w->resize(this->size());
    // this->setStyleSheet("background-color: rgb(255, 255, 255);");
    this->raise();

    m_iClip=0;
    m_label= new QLabel(this);//初始化Label容器
    m_label->resize(this->size());
    m_label->setStyleSheet("background-color:rgb(0,0,0,0)");

    m_thread=new ItemThread(this);
    m_thread->connect(m_thread,SIGNAL(signalSec()),this, SLOT(animation()));
//    QElapsedTimer eTimer;
//    eTimer.start();
//    m_thread->start();
//    while(eTimer.elapsed()<10000)// || m_thread->isRunning());
//    {
//        QCoreApplication::processEvents();
//    }


   // showPic();
}

ItemLoadingBarA::~ItemLoadingBarA()
{

}

void ItemLoadingBarA::setPixmap(QList<QPixmap*> listPix)
{
    for(int i=0;i<listPix.length();i++)
    {
        m_pixArray.push_back(listPix[i]);
    }
    m_thread->start();

}



//-----------------------------------------------------------------------------
//
void ItemLoadingBarA::animation()
{
    if(m_pixArray.length()<1 || m_iClip>m_pixArray.length()-1)
        return;
    m_label->setPixmap(m_pixArray[m_iClip]->scaled(m_label->size()));
    m_iClip = (m_iClip+1)%(m_pixArray.size());
}


//-----------------------------------------------------------------------------
//
void ItemLoadingBarA::showPic()
{
    if(m_pixArray.length()<1)
        return;
   m_iClip=0;

}

//-----------------------------------------------------------------------------
//
void ItemLoadingBarA::showEvent(QShowEvent *)
{
    m_iClip=0;
//    if(!m_thread->isRunning())
//    m_thread->start();
    emit signalEventLock(true);

}

//-----------------------------------------------------------------------------
//
void ItemLoadingBarA::hideEvent(QHideEvent *)
{

    emit signalEventLock(false);

}

void ItemLoadingBarA::resizeEvent(QResizeEvent *)
{
    m_label->resize(this->size());

}

//-----------------------------------------------------------------------------
//


//-----------------------------------------------------------------------------
//

void ItemLoadingBarA::releasePixArray()
{
    if (m_pixArray.size() > 0)
    {
        for (int i = 0; i < m_pixArray.size(); ++i)
            delete m_pixArray.at(i);
    }
}



ItemThread::~ItemThread()
{
    quit();
    if(!wait(100)) //Wait until it actually has terminated (max. 0.1 sec)
    {
        terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
        wait(); //We have to wait again here!
    }
}

void ItemThread::run()
{
    while(1)
    {
        QThread::msleep(300);
        emit signalSec();
    }
}
