#include "StageProductList.h"
#include "ui_StageProductList.h"

StageProductList::StageProductList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageProductList)
{
    ui->setupUi(this);
    // ui->wBody->resize(WINDOW_W,WIDONW_H-ui->vTitle->height());



    resize(GLOBAL().g_sizeWindow);
    m_sKey="";
    m_iSec=-1;

    // ui->vTitle->resize(WINDOW_W,TOP_MENU_H);
    ui->wBody->resize(WINDOW_W,WIDONW_H-ui->vTitle->height());
    ui->wBody->move(0,ui->vTitle->height());

    ui->wSubMenu->resize(WINDOW_W,TOP_MENU_H);
    //ui->line->setMaximumHeight(TOP_MENU_H*0.6);
    //ui->line2->setMaximumHeight(TOP_MENU_H*0.6);
    //    ui->wCol1->setMinimumSize(QSize(TOP_MENU_H,TOP_MENU_H));
    //    ui->wCol1->setMaximumSize(QSize(TOP_MENU_H,TOP_MENU_H));
    //    ui->wCol2->setMinimumSize(QSize(TOP_MENU_H,TOP_MENU_H));
    //    ui->wCol2->setMaximumSize(QSize(TOP_MENU_H,TOP_MENU_H));
    ui->wClass->setBorder(BorderType::_type_whrite);
    ui->wClass->setMinimumSize(QSize(WINDOW_W*0.235,TOP_MENU_H*0.546));
    ui->wClass->setMaximumSize(QSize(WINDOW_W*0.235,TOP_MENU_H*0.546));
    ui->wClass->setText("單一商品");
    ui->vTitle->setCentFlag(_HAS_ICON);
    connect(ui->vTitle,SIGNAL(signalClickedLeft()),this,SLOT(slotClickedLeft()));
    connect(ui->vTitle,SIGNAL(signalClickedCent()),this,SLOT(slotClickedCent()));
    connect(ui->vTitle,SIGNAL(signalClickedRight()),this,SLOT(slotClickedRight()));
    m_btnOptionMask=new ItemButton(ui->wBody);
    m_btnOptionMask->setGeometry(ui->wBody->rect());
    m_btnOptionMask->setStyleSheet("background-color:rgb(0,0,0,50)");
    m_btnOptionMask->connect(m_btnOptionMask,SIGNAL(clicked()),this,SLOT(slotClickedCent()));
    m_btnOptionMask->hide();
    m_LayerTitleOption=new LayerOption(ui->wBody);
    m_LayerTitleOption->resize(ui->wBody->size());
    m_LayerTitleOption->hide();
    // m_LayerTitleOption->connect(m_LayerTitleOption,SIGNAL(sendClick(int)),this,SLOT(slotTitleOptionClicked(int)));
    m_LayerTitleOption->connect(m_LayerTitleOption,SIGNAL(sendClickedKey(QString)),this,SLOT(slotTitleOptionClickedKey(QString)));



    LayerZoomView *zoomView=new LayerZoomView(ui->wBody);
    zoomView->setBackground("background-color:rgb(51,51,51)");
    zoomView->setSlice(TOP_MENU_H,"border-image:url(:/slice/res/images/slight/slight_top.png)","border-image:url(:/slice/res/images/slight/slight_bottom.png)");

    zoomView->connect(zoomView,SIGNAL(clicked(int)),this,SLOT(slotItemZoomClicked(int)));
    zoomView->resize(ui->wBody->size());
    zoomView->hide();
    m_view[_zoomView]=zoomView;

    Layer4View *c4View=new Layer4View(ui->wBody);
    c4View->setBackground("background-color:rgb(51,51,51)");
    c4View->setSlice(TOP_MENU_H,"border-image:url(:/slice/res/images/slight/slight_top.png)","border-image:url(:/slice/res/images/slight/slight_bottom.png)");
    c4View->connect(c4View,SIGNAL(clicked(int)),this,SLOT(slotItemZoomClicked(int)));
    c4View->resize(ui->wBody->size());
    c4View->hide();
    m_view[_4View]=c4View;

    m_viewMode=_zoomView;
    m_preViewMode=_zoomView;
    m_view[m_viewMode]->show();

    m_btnTop=new ItemButton(ui->wBody);
    m_btnTop->resize(QSize(TOP_MENU_H,TOP_MENU_H));
    m_btnTop->move(ui->wBody->width(),ui->wBody->height());
    m_btnTop->setStyleSheet("border-image:url(:/image/res/images/icon/icon_arrow4_1.png)");
    m_btnTop->connect(m_btnTop,SIGNAL(clicked()),this,SLOT(slotBtnTopClicked()));
    m_btnTop->connect(m_view[_zoomView],SIGNAL(changeIdx(int)),this,SLOT(slotBtnTopAniShow(int)));
    m_btnTop->connect(m_view[_4View],SIGNAL(changeIdx(int)),this,SLOT(slotBtnTopAniShow(int)));
    // m_btnChangeView=new ItemChangeBtn(ui->wBody);
    // m_btnChangeView->move(WINDOW_W-TOP_MENU_H,0);
    m_btnChangeView=ui->btnChangeMode;
    ui->wSubMenu->move(0,0);

    QStringList list;
    list.append(":/animation/res/images/animation/icon_col1_01.png");
    list.append(":/animation/res/images/animation/icon_col1_02.png");
    list.append(":/animation/res/images/animation/icon_col1_03.png");
    list.append(":/animation/res/images/animation/icon_col1_04.png");
    list.append(":/animation/res/images/animation/icon_col1_05.png");
    list.append(":/animation/res/images/animation/icon_col1_06.png");
    list.append(":/animation/res/images/animation/icon_col1_07.png");

    m_btnChangeView->setIconRes(QSize(TOP_MENU_H,TOP_MENU_H),list);
    m_btnChangeView->setMaximumSize(TOP_MENU_H,TOP_MENU_H);
    m_btnChangeView->setMinimumSize(TOP_MENU_H,TOP_MENU_H);
    m_btnChangeView->connect(m_btnChangeView,SIGNAL(clicked(bool)),this,SLOT(slotChangeView(bool)));


    m_ani.setTargetObject(m_LayerTitleOption);
    m_ani.setDuration(ANI_MINISEC);
    m_ani.setEasingCurve(ANI_EASING);
    m_ani.setPropertyName("pos");

    m_aniBtnTop.setTargetObject(m_btnTop);
    m_aniBtnTop.setDuration(ANI_MINISEC);
    m_aniBtnTop.setEasingCurve(ANI_EASING);
    m_aniBtnTop.setPropertyName("pos");

    m_aniSubMenu.setTargetObject(ui->wSubMenu);
    m_aniSubMenu.setDuration(ANI_MINISEC);
    m_aniSubMenu.setEasingCurve(ANI_EASING);
    m_aniSubMenu.setPropertyName("pos");

    m_bIsBanner=false;

    QObject::startTimer(300);

}

StageProductList::~StageProductList()
{
    delete ui;
}

void StageProductList::ini(int iKeyIdx)
{
    qDebug()<<"stageProductList Ini";
    DataHeader *dataHeader=&FUNC().g_data.g_header;

//    if(sKey!="")
//        dataHeader->setLastHeader(sKey);

    if(dataHeader->listLastKey.length()<1)
    {
        qDebug()<<"stageProductList Data lenght error";
        currentView()->hide();
        return ;
    }

    iKeyIdx=qBound(0,iKeyIdx,dataHeader->listLastKey.length()-1);
    if(m_sKey!=dataHeader->listLastKey.at(iKeyIdx) || m_viewMode!=m_preViewMode)
    {
        m_sKey=dataHeader->listLastKey.at(iKeyIdx);
        ui->vTitle->setTitleName(dataHeader->listLastValue.at(iKeyIdx));
        ui->vTitle->setIconFlag(_TO_DOWN);
        m_LayerTitleOption->m_iIdx=iKeyIdx;

        if(dataHeader->listLastKey.length()<2)
        {
            ui->vTitle->setIconFlag(_HIDE);

            m_LayerTitleOption->hide();
        }

        m_LayerTitleOption->setKeyValue(dataHeader->listLastKey,dataHeader->listLastValue);

        foreach (ItemOption* item, m_LayerTitleOption->m_listItem)
        {
            item->setIcon(OPTION_ICON_NONE);
        }

        m_LayerTitleOption->m_listItem[iKeyIdx]->setIcon(OPTION_ICON_CHECK);

        getViewData();
        setItemData(m_listName,m_listImageUrl);
    }

    //    if(m_viewMode!=m_preViewMode)
    //        setItemData(m_listName,m_listImageUrl);

    currentView()->setVisible(m_listPid.length()>0);

    if(m_listPid.length()>0)
    {
        slotBtnTopClicked();
    }

    m_LayerTitleOption->move(0,-m_LayerTitleOption->height());
    m_LayerTitleOption->raise();
    m_LayerTitleOption->show();

}

InterfaceView *StageProductList::currentView()
{
    return m_view[m_viewMode];
}



void StageProductList::slotChangeView(bool bIsEnable)
{
    qDebug()<<"change view";
    GLOBAL().slotBlock(true);

    slotBtnTopAniShow(0);
    m_view[_zoomView]->hide();
    m_view[_4View]->hide();


    m_preViewMode=m_viewMode;
    if(bIsEnable)
        m_viewMode=_zoomView;
    else
        m_viewMode=_4View;

    ini(m_LayerTitleOption->m_iIdx);
    GLOBAL().slotCancelBlock();
}





void StageProductList::getViewData()
{
    currentView()->hide();
    ui->vTitle->setTitleName(FUNC().g_data.g_header.listLastValue.at(m_LayerTitleOption->m_iIdx));
    VoHeader objHeader= FUNC().g_data.g_header.getItem(m_LayerTitleOption->getCurrentKey());

    m_dData=FUNC().getProductList(objHeader.sId);
    QStringList listPid;
    QStringList listName;
    QStringList listUrl;
    QStringList listType;
    foreach (QStringList list, m_dData)
    {

        listName.append(list[_productList::_name]+"\n TWD $"+list[_productList::_sellPrice]);

        listUrl.append(list[_productList::_image]);
        listPid.append(list[_productList::_id]);
        listType.append(list[_productList::_source]);
        qDebug()<<list[_productList::_name];

    }


    m_listPid=listPid;
    m_listType=listType;
    m_listName=listName;
    m_listImageUrl=listUrl;
    m_btnOptionMask->raise();
    m_LayerTitleOption->raise();

    setSubMenuView(true);
    m_iSec=0;
}

void StageProductList::keyPressEvent(QKeyEvent *e)
{
    if(GLOBAL().isBlock())
        return;
    if(e->key()==Qt::Key_Back)
    {
        if(GLOBAL().isShowMsg())
            GLOBAL().cancelMsg();
        else if(m_LayerTitleOption->y()==0)
            slotClickedCent();
        else
            slotClickedLeft();

    }
}

void StageProductList::timerEvent(QTimerEvent *)
{
    if(m_iSec<0)
        return;

    m_iSec+=300;

    if(m_iSec>2500 && ui->wSubMenu->y()>=0)
    {
        setSubMenuView(false);
    }
}

void StageProductList::setItemData(QStringList listName,QStringList listUrl)
{

    QList<QWidget*> listWidget;
    qDebug()<<"setItemData : "<<m_viewMode;

    m_listItemZoom.clear();
    int iItemZoomMaxH=WINDOW_W;
    int iItemZoomMinH=(WIDONW_H-iItemZoomMaxH)/2;

    if(m_listType.length()>0 && m_listType[0]==PRODUCT_TYPE_OUTFIT)
    {
        ui->wClass->setText("套裝商品");
        iItemZoomMaxH=WINDOW_W*1.25;
        iItemZoomMinH=iItemZoomMaxH/3;
    }
    else
    {
        ui->wClass->setText("單一商品");
    }


    if(m_viewMode==_zoomView)
    {

        for(int i=0;i<listUrl.length() ;i++)
        {
            ItemZooming *item=new ItemZooming(this);
            m_listItemZoom.append(item);
            m_listItemZoom[i]->resize(WINDOW_W,iItemZoomMaxH);
            m_listItemZoom[i]->setHeightInit(iItemZoomMinH,iItemZoomMaxH);
            m_listItemZoom[i]->setItemText(listName[i]);
            m_listItemZoom[i]->setItemImage(listUrl[i]);

            listWidget.append((QWidget*)m_listItemZoom[i]);
            //m_listItemZoom.append(item);
        }

        m_view[_zoomView]->setItemWidget(listWidget,0,iItemZoomMinH,iItemZoomMaxH);
    }
    else if(m_viewMode==_4View)
    {
        dynamic_cast<Layer4View*>(m_view[_4View])->m_wContent->move(0,0);
        qDebug()<<"listName : "<<listName;
        m_view[_4View]->setItemWidget(listName,listUrl);
    }

    ui->wSubMenu->raise();

    m_LayerTitleOption->raise();
}

void StageProductList::setSubMenuView(bool bIsView)
{
    QPoint pStart(ui->wSubMenu->x(),0);
    QPoint pEnd(ui->wSubMenu->x(),-ui->wSubMenu->height());

    if(bIsView)
    {
        pStart.setY(-ui->wSubMenu->height());
        pEnd.setY(0);
    }

    m_aniSubMenu.setStartValue(pStart);
    m_aniSubMenu.setEndValue(pEnd);
    m_aniSubMenu.start();

}


void StageProductList::slotClickedLeft()
{
    if(m_LayerTitleOption->y()==0)
    {
        slotClickedCent();
    }
    GLOBAL().goTargetStage(_StageIdx::_option,_StageItemIdx::_option_show);

}

void StageProductList::slotClickedRight()
{
    GLOBAL().goTargetStage(_StageIdx::_car,_StageItemIdx::_car_show);
}

void StageProductList::slotClickedCent()
{

    if(ui->vTitle->getCentFlag()!=_HAS_ICON || ui->vTitle->getIconFlag()==_HIDE)
    {
        return;
    }
    QPoint pStart(0,-m_LayerTitleOption->height());
    QPoint pEnd(0,0);

    if(m_LayerTitleOption->y()<0)
    {
        ui->vTitle->setIconFlag(_TO_UP);
        m_ani.setStartValue(pStart);
        m_ani.setEndValue(pEnd);
        m_btnOptionMask->show();
    }
    else
    {
        ui->vTitle->setIconFlag(_TO_DOWN);
        m_ani.setStartValue(pEnd);
        m_ani.setEndValue(pStart);
        m_btnOptionMask->hide();

    }
    //  GLOBAL().slotBlock();
    m_ani.start();



}

void StageProductList::slotTitleOptionClickedKey(QString)
{

    foreach (ItemOption* item, m_LayerTitleOption->m_listItem)
    {
        item->setIcon(OPTION_ICON_NONE);
    }

    int iIdx=m_LayerTitleOption->m_iIdx;
    if(iIdx<=-1 || iIdx>=m_LayerTitleOption->m_listItem.length())
        iIdx=0;
    m_LayerTitleOption->m_listItem[iIdx]->setIcon(OPTION_ICON_CHECK);

    GLOBAL().slotBlock();
    slotClickedCent();
    QEventLoop loop;
    loop.connect(&m_ani,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();

    GLOBAL().elapsedTimer();

    getViewData();
    setItemData(m_listName,m_listImageUrl);

    currentView()->setVisible(m_listPid.length()>0);

    if(m_listPid.length()>0)
    {
        slotBtnTopClicked();
    }

    loop.disconnect();
    GLOBAL().slotCancelBlock();
}

void StageProductList::slotItemZoomClicked(int iIdx)
{
    qDebug()<<"product list clicked : "<<iIdx;
    if(m_viewMode==_zoomView)
    {
        if(m_listItemZoom.length()<1 || iIdx>=m_listItemZoom.length() || iIdx<0 || GLOBAL().g_iNowStage!=_StageIdx::_productList)
            return;

        if(!m_listItemZoom[iIdx]->m_wSlice2->isVisible())
        {
            m_listItemZoom[iIdx]->m_wSlice2->setVisible(true);
            return;
        }

        else
        {


        }
    }

    else if(m_viewMode==_4View)
    {

    }
    FUNC().g_data.g_sNowProductId=m_listPid[iIdx];
    FUNC().g_data.g_sNowProductType=m_listType[iIdx];
    if(FUNC().g_data.g_sNowProductType==PRODUCT_TYPE_OUTFIT)
        GLOBAL().goTargetStage(_StageIdx::_outfitDetail);
    else
        GLOBAL().goTargetStage(_StageIdx::_productDetail);

}



void StageProductList::slotBtnTopClicked()
{

    if(currentView()->length()>0)
    {
        currentView()->goIdx(0);
        m_btnTop->move(ui->wBody->width(),ui->wBody->height());
    }

}

void StageProductList::slotBtnTopAniShow(int iIdx)
{
    m_iSec=0;
    if(ui->wSubMenu->y()<0)
        setSubMenuView(true);

    if(currentView()->length()<3)
    {
        m_btnTop->hide();
        return ;
    }

    m_btnTop->show();
    QPoint pHide(ui->wBody->width()-TOP_MENU_H,ui->wBody->height());
    QPoint pShow(ui->wBody->width()-TOP_MENU_H,ui->wBody->height()-TOP_MENU_H*2);

    if(iIdx<3 && m_btnTop->pos()!=pHide)
    {
        m_aniBtnTop.setStartValue(pShow);
        m_aniBtnTop.setEndValue(pHide);
        m_aniBtnTop.start();
    }
    else if(iIdx>=3 && m_btnTop->pos()!=pShow)
    {
        m_aniBtnTop.setStartValue(pHide);
        m_aniBtnTop.setEndValue(pShow);
        m_aniBtnTop.start();
    }


}
