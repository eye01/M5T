#include "ItemZooming.h"


ItemZooming::ItemZooming(QWidget *parent) :QWidget(parent)
{
    // m_wContent=new QWidget(this);
    resize(parent->size());
    m_wOldP=QPoint(0,0);
    //m_thread=NULL;
    m_wContent=new ItemImage(this);
    m_wContent->resize(size());
    m_wSlice=new QWidget(this);
    m_wSlice->resize(size());
    m_wSlice->setObjectName("m_wSlice");

    m_wSlice2=new QWidget(this);
    m_wSlice2->resize(size());
    m_wSlice2->setObjectName("m_wSlice2");
    m_wSlice2->setStyleSheet("QWidget#m_wSlice2{border-image:url(:/image/res/images/mask_bottom.png);}");
    m_wBorder=new QWidget(this);
    m_wBorder->resize(size());
    m_lbTitle=new QLabel(m_wSlice2);
    m_lbTitle->resize(WINDOW_W,(float)TOP_MENU_H*1.5);
    //m_lbTitle->resize(600,216);
    m_lbTitle->setAlignment(Qt::AlignCenter);
    QFont f;
    f.setPointSize(16);
    m_lbTitle->setFont(f);
    m_lbTitle->setStyleSheet("color:rgb(255,255,255)");
   // m_lbTitle->setStyleSheet(m_lbTitle->styleSheet()+";border-image:url(:/image/res/images/mask_bottom.png);");
    m_wBorder->setStyleSheet("border-bottom-width: 3px;"
                            "border-bottom-color: rgb(153,153,153);"
                            "border-bottom-style: solid;");
    m_wSlice2->hide();

}

ItemZooming::~ItemZooming()
{

    //    if(m_thread!=NULL)
    //    {
    //        m_thread->quit();
    //        if(!m_thread->wait(100)) //Wait until it actually has terminated (max. 0.1 sec)
    //        {
    //            m_thread->terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
    //            m_thread->wait(); //We have to wait again here!
    //        }
    //    }
}

void ItemZooming::setHeightInit(int iMinH,int iMaxH)
{

    if(iMaxH==-1)
        iMaxH=iMinH*3;
    m_iMinH=iMinH;
    m_iMaxH=iMaxH;
    resize(width(),m_iMinH);
    m_wContent->resize(width(),m_iMaxH);
    m_wContent->setMinimumHeight(m_iMaxH);
    m_wContent->setMaximumHeight(m_iMaxH);
    m_wSlice->resize(width(),m_iMaxH);
    m_wBorder->resize(width(),m_iMaxH);

}

void ItemZooming::setItemText(QString sText)
{
    m_lbTitle->setText(sText);
}

void ItemZooming::setItemImage(QString sUrl)
{
    m_sUrl=sUrl;
    m_wContent->setImageUrl(sUrl);


#if 1
    //other thread
//    if(m_thread!=NULL)
//    {
//        m_thread->setImage(m_sUrl,m_wContent);
//        m_thread->start();
//    }
#else
    QByteArray jpegData ;
    if(!SQL().checkImageData(m_sUrl))
    {

        QUrl url(m_sUrl);
        QNetworkAccessManager manager;
        QEventLoop loop;
        QNetworkReply *reply = manager.get(QNetworkRequest(url));
        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        jpegData=reply->readAll();
        SQL().addImageData(m_sUrl,jpegData);
        qDebug()<<"from net get";
    }
    else
    {
        qDebug()<<"from db get";
        jpegData=SQL().getImageData(m_sUrl);

    }

    QPixmap pixmap;
    pixmap.loadFromData(jpegData);
    m_wContent->setPixmap(pixmap);

#endif

}

void ItemZooming::resizeEvent(QResizeEvent *)
{
    if(m_wSlice->isVisible() && height()<m_iMaxH/2)
    {
        m_wSlice2->hide();
    }
    m_wContent->setGeometry(0,0,width(),height());
    m_wSlice->setGeometry(0,0,width(),height());
    m_wSlice2->setGeometry(0,0,width(),height());
    m_wBorder->setGeometry(0,0,width(),height());
    m_lbTitle->resize(size().width(),m_lbTitle->height());

    float fValue=(m_iMaxH-m_iMinH)/100;
    float iDiff=255-(height()-m_iMinH)/fValue*255/100;


    if(iDiff<0)
        iDiff=0;

    int iFilter=iDiff*0.5;


    //int iFontSize=40-(iDiff*0.7/10)+6;
    //QFont font;
   // font.setBold(true);
  //  font.setPixelSize(iFontSize);
   // m_lbTitle->setFont(font);
    //  m_lbTitle->move((width()-m_lbTitle->width())/2,(height()-m_lbTitle->height())/2);


   // float f=(float)height()/m_iMaxH;

    m_lbTitle->move((width()-m_lbTitle->width())/2,height()-m_lbTitle->height());

    m_wContent->move((width()-m_wContent->width())/2,(height()-m_wContent->height())/2);

    m_wSlice->setStyleSheet("background-color:rgb(0,0,0,"+QString::number(iFilter+25)+")");

}

//void ItemZooming::mousePressEvent(QMouseEvent *)
//{

//}

//void ItemZooming::mouseReleaseEvent(QMouseEvent *)
//{



//}
