#include "StageStart.h"
#include "ui_StageStart.h"

#define VER "1.01"
StageStart::StageStart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageStart)
{
    ui->setupUi(this);

    resize(GLOBAL().g_sizeWindow);
    ui->wBg->resize(size());
    ui->wSlice->resize(size());
    ui->wBg->move(0,0);
    ui->wSlice->move(0,0);



    m_wLogo=new QWidget(this);
    m_wLogo->setStyleSheet("border-image:url(:/image/res/images/eye_logo_base_0.png)");
    //剛好這張圖寬高比相同

    m_wLogo->resize(QSize(width()*0.6,width()*0.6));
    m_wLogo->move((width()-m_wLogo->width())/2+30,(height()-m_wLogo->height()*1.3)/2);

    m_wLogoBg=new QWidget(this);
    m_wLogoBg->setStyleSheet("border-image:url(:/image/res/images/eye_logo_base.png)");
    m_wLogoBg->resize(m_wLogo->size());
    m_wLogoBg->move(m_wLogo->x(),-m_wLogo->height());
    //m_wLogoBg->resize(QSize(width()*0.6,width()*0.6));
   // m_wLogoBg->move((width()-m_wLogo->width())/2+30,(height()-m_wLogo->height()*1.3)/2);



    m_wLogo->raise();
    ui->wSlice->raise();

    m_iTimeFlag=-1;
    QObject::startTimer(100);
    GLOBAL();

    m_layeyLoading=new LayerLoading(this);
    m_layeyLoading->resize(WINDOW_W,TOP_MENU_H*0.7);
    m_layeyLoading->move(0,WIDONW_H-m_layeyLoading->height()-40);
    m_layeyLoading->startLoading();

    QLabel *lb=new QLabel(this);
    lb->setStyleSheet("background-color:rgb(0,0,0,0)");
    lb->move(5,size().height()-110);

    lb->setText(VER);

}

StageStart::~StageStart()
{
    delete ui;
}

void StageStart::ini()
{
    qDebug()<<"start ini";
    //checkNetworkAndVer();
}



void StageStart::timerEvent(QTimerEvent *)
{
    if(m_iTimeFlag==-1)
        return;



    if(m_iTimeFlag>=INTO_USE_MSEC)
    {

        if(m_layeyLoading->isFinish())
        {

            m_iTimeFlag=-1;

            emit signalIntoFinish();

        }
        else if(m_layeyLoading->isHidden())
        {
            m_layeyLoading->startLoading();

        }
        return ;
    }





    m_iTimeFlag+=100;

    if(m_wLogoBg->y()<m_wLogo->y())
    {
        int iMove=m_wLogoBg->y()+60;
        if(iMove>m_wLogo->y())
            iMove=m_wLogo->y();
        m_wLogoBg->move(m_wLogoBg->pos().x(),iMove);
    }




    float iFilter=255-255*(float)m_iTimeFlag/INTO_USE_MSEC;
    ui->wSlice->setStyleSheet("background-color:rgb(255,255,255,"+QString::number(iFilter)+")");

}

void StageStart::showEvent(QShowEvent *)
{
    m_iTimeFlag=0;
    qDebug()<<"start show";


}

void StageStart::checkNetworkAndVer()
{

    ui->wSlice->setStyleSheet("background-color:rgb(255,255,255,255)");

    QString sVer;
    sVer="ver 1.01";//FUNC().getValue("ver");
    qDebug()<<"server ver : "<<sVer<<" ,local ver : "<<VER;
    m_iTimeFlag=-1;
    if(sVer=="")
    {

        ui->wSlice->setStyleSheet("background-color:rgb(255,255,255,0)");
        GLOBAL().showMsg("連線失敗，請確認網路連線。",_StageIdx::_start);

    }
    else
    {
//        if(sVer!=VER)
//        {

//            GLOBAL().showMsg("請更新到最新版本。",_StageIdx::_fullScreenWeb);

//        }
//        else
//        {
//            m_iTimeFlag=0;
//        }

        m_iTimeFlag=0;
    }
}


