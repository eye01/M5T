#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);

    //ui->stackedWidget->setCurrentIndex(_StageIdx::_test);
    //ui->stackedWidget->setCurrentIndex(_StageIdx::_start);
    m_wMask=new BtnMask(ui->widget);
    connect(m_wMask,SIGNAL(clicked()),this,SLOT(slotBacktoStage()));

    m_wMask->raise();
    m_wMask->hide();

    m_layerBlock=new LayerBlock(this);
    m_layerBlock->resize(GLOBAL().g_sizeWindow);
    connect(&GLOBAL(),SIGNAL(signalBlockFlag(bool,bool)),m_layerBlock,SLOT(slotBlockFlag(bool,bool)));
    connect(&GLOBAL(),SIGNAL(siganlStageChange(int,int)),this,SLOT(slotToStage(int,int)));
    connect(ui->vStart,SIGNAL(signalIntoFinish()),this,SLOT(slotFinish()));
    connect(ui->vNavigation,SIGNAL(signalEndToNext()),this,SLOT(slotNavigationFinish()));
    connect(ui->vNavigation,SIGNAL(signaClicked(int)),this,SLOT(slotNavigationClicked(int)));


    ui->vNavigation->resize(GLOBAL().g_sizeWindow);
    ui->vNavigation->reSet(4,50,50);

    QStringList listUrl;
    listUrl<<"border-image:url(:/image/res/images/image_1.png)";
    listUrl<<"border-image:url(:/image/res/images/image_2.png)";
    listUrl<<"border-image:url(:/image/res/images/image_1.png)";
    listUrl<<"border-image:url(:/image/res/images/image_2.png)";
    QList<QLabel*> list;
    for(int i=0;i<listUrl.length();i++)
    {
        QLabel *w0=new  QLabel();
        w0->resize(GLOBAL().g_sizeWindow);
        w0->setStyleSheet(listUrl.at(i));
        list.append(w0);
    }
    ui->vNavigation->setWidget(list);
    m_bNeedNavigation=false;
    connect(&m_ani,SIGNAL(finished()),this,SLOT(slotAniFinished()));
    m_ani.setTargetObject(ui->stackedWidget);
    m_ani.setPropertyName("pos");
    m_ani.setDuration(ANI_MINISEC);
    m_ani.setEasingCurve(ANI_EASING);
    m_pageStatus=_stage;
    setSize();
    m_layerBlock->raise();
    m_layerBlock->hide();
    m_msg=new DialogMsg(this);
    m_msg->connect(&GLOBAL(),SIGNAL(signalMsg(bool,QString,int)),m_msg,SLOT(slotShowMsg(bool,QString,int)));
    m_msg->move(0,0);

    qDebug()<<"create ui OK";
    slotToStage(_StageIdx::_start,-1);
    qDebug()<<"stage start";
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setSize()
{
    ui->stackedWidget->move(0,0);
    ui->widget->resize(width()*1.85,WIDONW_H);
    ui->vOption->setGeometry(0,0,WINDOW_W*0.85,WIDONW_H);
    ui->vShoppingCar->resize(ui->vOption->size());
    ui->vShoppingCar->move(WINDOW_W*0.15,0);
    ui->vNavigation->resize(GLOBAL().g_sizeWindow);
    ui->stackedWidget->resize(GLOBAL().g_sizeWindow);
    ui->stackedWidget->move(0,0);
    m_wMask->resize(ui->stackedWidget->size());
    m_wMask->move(ui->vOption->width(),0);
    ui->vShoppingCar->hide();
    ui->vOption->hide();
}

void Widget::slotNavigationFinish()
{
    ui->stackedWidget->setCurrentIndex(_StageIdx::_login);
}

void Widget::slotFinish()
{

    int iIdx=ui->stackedWidget->currentIndex()+1;

//    if(iIdx==_StageIdx::_navigation)
//    {
//        ui->vFirst->setAd();
//    }

//    if(iIdx==_StageIdx::_navigation && ! m_bNeedNavigation)
//    {
//        iIdx+=1;
//    }

    if(iIdx<ui->stackedWidget->count())
    {
        slotToStage(iIdx,0);
    }

}

void Widget::slotBacktoStage()
{

    GLOBAL().g_iNowStage=GLOBAL().g_iPreStage;
    if(m_pageStatus==_option)
    {
        slotOption(false);
        GLOBAL().g_iPreStage=_StageIdx::_option;
    }
    else if(m_pageStatus==_shoppingCar)
    {
        slotCar(false);
        GLOBAL().g_iPreStage=_StageIdx::_car;
    }

}

void Widget::slotToStage(int iPage,int iItem)
{

    qDebug()<<"change stage : "<<iPage<<" : "<<iItem;
    GLOBAL().g_iPreStage=GLOBAL().g_iNowStage;
    GLOBAL().g_iNowStage=iPage;
    GLOBAL().g_iNowStageItemIdx=iItem;
    if(iPage==_StageIdx::_option)
    {
        slotOption(iItem==_StageItemIdx::_option_show);
    }




    else
    {

        if(iPage<0 || iPage>=ui->stackedWidget->count())
            return;
        else if(iPage==_StageIdx::_start)
        {
            ui->vStart->ini();
        }


        else if(iPage==_StageIdx::_memberCenter)
        {}

        else if(iPage==_StageIdx::_login)
        {}

        else if(iPage==_StageIdx::_register)
        {}


        else if(GLOBAL().g_iPreStage==_StageIdx::_fullScreenWeb)
        {
           // ui->vFullScreenWeb->close();
        }

        ui->stackedWidget->setCurrentIndex(iPage);



        slotOption(false);
    }
}


void Widget::slotOption(bool bIsShow)
{

    GLOBAL().slotBlock();
    m_wMask->setVisible(false);
    QPoint pStart(0,0);
    QPoint pEnd(ui->vOption->width(),0);

    if(!bIsShow && ui->stackedWidget->pos()!= pStart)
    {

       // ui->vProductList->setFocus();
        m_ani.setStartValue(ui->stackedWidget->pos());
        m_ani.setEndValue(pStart);
        m_ani.start();
    }
    else if(bIsShow && ui->stackedWidget->pos()!=pEnd)
    {
        ui->vOption->show();
        ui->vOption->setFocus();
        m_ani.setStartValue(pStart);
        m_ani.setEndValue(pEnd);
        ui->vOption->ini();
        m_ani.start();
    }
    else
    {
        GLOBAL().slotCancelBlock();
    }

}


void Widget::slotCar(bool)
{

//    GLOBAL().slotBlock();
//    m_wMask->setVisible(false);
//    QPoint pStart(0,0);
//    QPoint pEnd(ui->vShoppingCar->x()-ui->stackedWidget->width(),0);

//    if(!bIsShow && ui->stackedWidget->pos()!= pStart)
//    {
//        //ui->vProductList->setFocus();
//        m_ani.setStartValue(pEnd);
//        m_ani.setEndValue(pStart);
//        m_ani.start();
//    }
//    else if(bIsShow && ui->stackedWidget->pos()!=pEnd)
//    {
//        ui->vShoppingCar->show();
//        ui->vShoppingCar->setFocus();
//        m_ani.setStartValue(ui->stackedWidget->pos());
//        m_ani.setEndValue(pEnd);
//        //ui->vOption->ini();
//        m_ani.start();
//    }
//    else
//    {
//        GLOBAL().slotCancelBlock();
//    }

}


void Widget::slotAniFinished()
{

    if(ui->stackedWidget->x()>100)
    {
        m_wMask->move(ui->vOption->width(),0);
        m_wMask->setVisible(true);
        m_pageStatus=_option;

    }
    else if(ui->stackedWidget->x()<-100)
    {
        m_wMask->move(ui->vShoppingCar->x()-m_wMask->width(),0);
        m_wMask->setVisible(true);
        m_pageStatus=_shoppingCar;
    }
    else
    {
        m_pageStatus=_stage;
        ui->vShoppingCar->hide();
        ui->vOption->hide();
    }

   // 緩衝: 防止硬體來不及繪制UI
    GLOBAL().elapsedTimer();


    if(GLOBAL().g_iNowStage==_StageIdx::_productList)
    {

        //if(GLOBAL().g_iNowStageItemIdx!=_StageItemIdx::_productList_dont_init_location)
            //ui->vProductList->ini();

    }

    //
    if(GLOBAL().g_iNowStage==_StageIdx::_car)
    {
        ui->vShoppingCar->setFocus();
        //ui->vShoppingCar->slotChangeView(!GLOBAL().g_iNowStageItemIdx==_StageItemIdx::_car_show_pre_buy);

    }
    else if(GLOBAL().g_iNowStage==_StageIdx::_option)
    {
        ui->vOption->setFocus();
    }
    else
    {

        ui->stackedWidget->currentWidget()->setFocus();

    }

    GLOBAL().slotCancelBlock();

}


void Widget::slotNavigationClicked(int iIdx)
{

    iIdx=iIdx;

}


//=================================================================


BtnMask::BtnMask(QWidget *parent):QWidget(parent)
{
    m_wBg=new QWidget(this);
    m_wBg->setGeometry(rect());
    setStyleSheet("background-color:rgb(0,0,0,30)");
}

void BtnMask::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked();
}

void BtnMask::resizeEvent(QResizeEvent *)
{
    m_wBg->setGeometry(rect());
}
