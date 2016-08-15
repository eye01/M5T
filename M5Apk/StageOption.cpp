#include "StageOption.h"



StageOption::StageOption(QWidget *parent):QWidget(parent)
{
    resize(WINDOW_W*0.85,WIDONW_H);
    m_wTitle=new QWidget(this);
    m_wTitle->setGeometry(0,0,width(),TOP_MENU_H);
    m_wTitle->setStyleSheet("background-color: rgb(69, 69, 69);");
    m_btnLeft=new ItemButton(m_wTitle);
    connect(m_btnLeft,SIGNAL(clicked()),this,SLOT(changeLayer()));
    m_btnLeft->setGeometry(0,0,TOP_MENU_H,TOP_MENU_H);
    m_btnLeft->setStyleSheet("border-image:url(:/image/res/images/icon/icon_back_arrow.png)");

    m_lbTitle=new QLabel(m_wTitle);
    m_lbTitle->resize(WINDOW_W*0.3,TOP_MENU_H*0.28);
    m_lbTitle->move(40,(m_wTitle->height()-m_lbTitle->height())/2);
    m_lbTitle->setText("Menu");
    QFont f;
    f.setPointSize(16);
    m_lbTitle->setFont(f);

    m_lbTitle->setStyleSheet("color:rgb(255,255,255)");

    m_wContent=new QWidget(this);
    m_wContent->setMinimumSize(QSize(width()*2,WIDONW_H-m_wTitle->height()));
    m_wContent->move(0,0);

    m_layer0=new LayerOption(m_wContent);
    //connect(m_layer0,SIGNAL(sendClick(int)),this,SLOT(slotClicked(int)));
    connect(m_layer0,SIGNAL(sendClickedKey(QString)),this,SLOT(slotClickedKey(QString)));
    m_layer0->move(0,m_wTitle->height());
    m_layer0->resize(m_wContent->size()/2);
    m_layer1=new LayerOption(m_wContent);
    // connect(m_layer1,SIGNAL(sendClick(int)),this,SLOT(slotClicked(int)));
    connect(m_layer1,SIGNAL(sendClickedKey(QString)),this,SLOT(slotClickedKey(QString)));
    m_layer1->resize(m_wContent->size()/2);
    m_layer1->move(m_layer0->width(),m_wTitle->height());


    m_wTitle->raise();
    m_btnLeft->hide();

    m_ani.setTargetObject(m_wContent);
    m_ani.setPropertyName("pos");
    m_ani.setDuration(ANI_MINISEC);
    m_ani.setEasingCurve(ANI_EASING);
    m_ani.connect(&m_ani,SIGNAL(finished()),&GLOBAL(),SLOT(slotCancelBlock()));
    m_sKey="";





}

StageOption::~StageOption()
{

}

void StageOption::setMenu()
{

}

void StageOption::ini()
{

    QStringList listKey;
    QStringList listValue;

    listKey.push_front(HEADER1_KEY_INDEX_PAGE);
    listValue.push_front(HEADER1_VALUE_INDEX_PAGE);

    listKey.push_back(HEADER1_KEY_MEMBER);
    listValue.push_back(HEADER1_VALUE_MEMBER);

//    listKey.push_back(HEADER1_KEY_ABOUT);
//    listValue.push_back(HEADER1_VALUE_ABOUT);


    m_layer0->setKeyValue(listKey,listValue);

    m_layer0->setIcon(1,OPTION_ICON_NEXT);
    m_layer0->setIcon(2,OPTION_ICON_NEXT);

}

void StageOption::leaveStage()
{
    //    m_layer0->move(0,m_wTitle->height());
    //    m_layer1->move(m_layer0->height(),m_wTitle->height());
}




void StageOption::keyPressEvent(QKeyEvent *e)
{
    if(GLOBAL().isBlock())
        return;
    if(e->key()==Qt::Key_Back)
    {
        if(m_lbTitle->text()!="Menu")
            changeLayer(0);
    }
}

void StageOption::mousePressEvent(QMouseEvent *e)
{
    if(m_wContent->height()<WIDONW_H-TOP_MENU_H)
        return;
    m_iOldPressY=e->y();
    m_iOldContentY=m_wContent->y();
}

void StageOption::mouseMoveEvent(QMouseEvent *e)
{
    if(m_wContent->height()<WIDONW_H-TOP_MENU_H)
        return;
    int iDiffY=m_iOldContentY+(e->y()-m_iOldPressY);

    if(iDiffY>0)
        iDiffY=0;

    if(iDiffY<-WIDONW_H/2+height()/2)
        iDiffY=-WIDONW_H/2+height()/2;
    m_wContent->move(m_wContent->x(), iDiffY);

}

void StageOption::mouseReleaseEvent(QMouseEvent *)
{

}


void StageOption::changeLayer(int iIdx)
{

    if(iIdx>1)
        iIdx=1;

    //    m_layer1->show();
    QPoint pStart(-m_wContent->width()/2,0);
    QPoint pEnd(0,0);
    if(iIdx==0)
    {

        m_ani.setStartValue(pStart);
        m_ani.setEndValue(pEnd);
        m_btnLeft->hide();
        m_lbTitle->setText("Menu");
        m_lbTitle->move(40,m_lbTitle->y());

    }
    else
    {
        m_ani.setStartValue(pEnd);
        m_ani.setEndValue(pStart);
        m_btnLeft->show();
        m_lbTitle->setText(m_sTitleKey);
        m_lbTitle->move(m_btnLeft->width()+20,m_lbTitle->y());
    }


    GLOBAL().slotBlock(false);

    m_ani.start();



}



void StageOption::slotClickedKey(QString sKey)
{

//    LayerOption *w=dynamic_cast<LayerOption*>(sender());
//    DataHeader *dataHeader= &FUNC().g_data.g_header;
//    if(w==m_layer0)
//    {
//        if(sKey==HEADER1_KEY_INDEX_PAGE)
//        {
//            GLOBAL().goTargetStage(_StageIdx::_first);
//        }
//        else if(sKey==HEADER1_KEY_MEMBER)
//        {
//            if(FUNC().m_bIsLogin)
//            {
//                GLOBAL().goTargetStage(_StageIdx::_memberCenter);

//            }
//            else
//            {
//                GLOBAL().g_bShopToLogin=false;
//                GLOBAL().goTargetStage(_StageIdx::_login);
//            }
//        }
//        else if(sKey==HEADER1_KEY_ABOUT)
//        {

//        }
//        else
//        {
//            QStringList listKey,listValue;
//            dataHeader->getChildKeyValue(sKey,listKey,listValue);
//            m_layer1->setKeyValue(listKey,listValue);
//            changeLayer(1);
//        }

//    }
//    else
//    {
//        dataHeader->setLastHeader(sKey);
//        if(sKey!=m_sKey)

//            GLOBAL().goTargetStage(_StageIdx::_productList);
//        else
//            GLOBAL().goTargetStage(_StageIdx::_productList,_StageItemIdx::_productList_dont_init_location);

//        m_sKey=sKey;
//    }



}

