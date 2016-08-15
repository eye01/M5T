#include "StageFirst.h"
#include "ui_StageFirst.h"

StageFirst::StageFirst(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageFirst)
{
    ui->setupUi(this);

    resize(GLOBAL().g_sizeWindow);
    ui->vTitle->setMinimumHeight(TOP_MENU_H);
    ui->vTitle->setMaximumHeight(TOP_MENU_H);
    ui->wContent->setMinimumSize(QSize(width(),height()-TOP_MENU_H));
    m_wScrollV=new CScrollWidgetV(ui->wContent);
    m_wScrollV->resize(ui->wContent->size());
    connect(ui->vTitle,SIGNAL(signalClickedLeft()),this,SLOT(slotShowOption()));
    connect(m_wScrollV,SIGNAL(signalClick(int)),this,SLOT(btnClicked(int)));
    ui->vTitle->setCentFlag(_NO_ICON);
    ui->vTitle->m_btnRight->hide();


    m_btnTest=new ItemButton(ui->wContent);
    m_btnTest->resize(200,200);
    m_btnTest->connect(m_btnTest,SIGNAL(clicked()),this,SLOT(slotTest()));
}

StageFirst::~StageFirst()
{
    delete ui;
}

void StageFirst::setAd()
{

     QList<QStringList> dData;//=FUNC().g_data.g_dAd;

     dData=dData.mid(0,3);

     float h=(float)WINDOW_W/640*337;

     m_wScrollV->setContent(dData.length(),h);
     QLabel *lb;

     m_listImage.clear();

     for(int i=0;i<m_wScrollV->m_listBtn.length();i++)
     {
         QWidget *w=m_wScrollV->m_listBtn[i];
         lb=new QLabel(w);
         lb->resize(w->size());
         lb->show();
         m_listImage.append(lb);

        // getImage(dData[i][_Ad::_imageUrl],lb);
     }



}

void StageFirst::showEvent(QShowEvent *)
{
    m_btnTest->raise();
    m_btnTest->move(ui->wContent->width()-m_btnTest->width(),0);
    //  setAd();
}

void StageFirst::keyPressEvent(QKeyEvent *e)
{
    if(GLOBAL().isBlock())
        return;
    if(e->key()==Qt::Key_Back)
    {
        if(GLOBAL().isShowMsg())
            GLOBAL().cancelMsg();
        else
            slotShowOption();
    }
}


void StageFirst::getImage(QString sUrl,QLabel *lb)
{
//    QUrl url(sUrl);
//    QNetworkAccessManager manager;
//    QEventLoop loop;
//    QNetworkReply *reply = manager.get(QNetworkRequest(url));
//    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
//    loop.exec();
//    QByteArray jpegData = reply->readAll();
//    QPixmap pixmap;
//    pixmap.loadFromData(jpegData);
//    lb->setPixmap(pixmap);
}





void StageFirst::btnClicked(int iIdx)
{
   // QStringList d=FUNC().g_data.g_dAd.at(iIdx);
     //  DataHeader *dataHeader=&FUNC().g_data.g_header;
  //  QString st="WOMEN_Popular_NEW ARRIVAL";
  //  GLOBAL().goTargetProductList(st);

}

void StageFirst::slotShowOption()
{
    GLOBAL().goTargetStage(_StageIdx::_option,_StageItemIdx::_option_show);
}

void StageFirst::slotTest()
{
    // GLOBAL().goTargetStage(_StageIdx::_test);
}
