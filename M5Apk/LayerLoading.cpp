#include "LayerLoading.h"
#include "ui_LayerLoading.h"

int iMinValue=0;
int iMaxValue=99;
int iSec=50;
LayerLoading::LayerLoading(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerLoading)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    ui->progressBar->setValue(0);
    ui->progressBar2->setMaximumSize((float)WINDOW_W*0.70,(float)TOP_MENU_H*0.15);
    ui->progressBar2->setMinimumSize((float)WINDOW_W*0.70,(float)TOP_MENU_H*0.15);

    ui->progressBar2->setValue(0);
    ui->stackedWidget->setCurrentIndex(1);
    m_iTimer=-1;
    m_fNowValue=0;
    QObject::startTimer(15);
    hide();



}

LayerLoading::~LayerLoading()
{
    delete ui;
}

void LayerLoading::startLoading()
{
    show();

    setViewWord("update productList module");

    QStringList listUpdateNo;
//    FUNC().getLastUpdateDate(listUpdateNo);

//    if(listUpdateNo[_LastUpdate::_productList]!="" && listUpdateNo[_LastUpdate::_productList]!=SQL().checkLastUpdate(SqlTable::_productList))
//    {
//        SQL().clearTableData(SqlTable::_productList);
//        SQL().setUpdateNo("productList",listUpdateNo[_LastUpdate::_productList]);
//    }

    setViewWord("update headerName module");
//    if(listUpdateNo[_LastUpdate::_headerName]!="" && listUpdateNo[_LastUpdate::_headerName]!=SQL().checkLastUpdate(SqlTable::_headerName))
//    {
//        SQL().clearTableData(SqlTable::_headerName);
//        SQL().setUpdateNo("headerName",listUpdateNo[_LastUpdate::_headerName]);
//    }

    setViewWord("update ad module");
//    if(listUpdateNo[_LastUpdate::_ad]!="" && listUpdateNo[_LastUpdate::_ad]!=SQL().checkLastUpdate(SqlTable::_ad))
//    {
//        SQL().clearTableData(SqlTable::_ad);
//        SQL().setUpdateNo("ad",listUpdateNo[_LastUpdate::_ad]);
//    }

    m_iTimer=0;


    m_fNowValue=1;
    //  if(MOBILE_MODE)
    //{


    preLoadAd();

    preLoadHeader();

   // preLoadProductList();

//    preloadProductDetail();

    qDebug()<<"pre load Ok";


    m_fNowValue=99;

}

bool LayerLoading::isFinish()
{
    bool bRe=ui->progressBar->value()==iMaxValue;
    if(ui->stackedWidget->currentIndex()==1)
        bRe=ui->progressBar2->value()==iMaxValue;
    return bRe;

}

void LayerLoading::preLoadAd()
{
    setViewWord("loading Ad");
   // FUNC().callAd();
    m_fNowValue+=5;
}

void LayerLoading::preLoadHeader()
{
    setViewWord("loading header");
    //FUNC().callHeader();
    //FUNC().getHeader();
    m_fNowValue+=10;
}

void LayerLoading::preLoadProductList()
{
#if 0
    for(int i=0;i<FUNC().g_data.g_dMenu.length();i++)
    {
        if(m_fNowValue<98)
            m_fNowValue+=0.5;
        QStringList list=FUNC().g_data.g_dMenu.at(i);

        if(list[_Menu::_headerType]=="normal" || list[_Menu::_headerType]=="event" || list[_Menu::_headerType]=="outfit")
        {
            setViewWord("PdList : "+list[_Menu::_h3Alt]);
            QList<QStringList> tmp= FUNC().getProductList(list[_Menu::_h3Alt],list[_Menu::_headerType]);
            //  m_thread->appendData(list[_productList::_id],list[_productList::_type]);
            //            foreach (QStringList list, tmp)
            //            {
            //                if(list[_productList::_type]!="outfit")
            //                {
            //                    if(m_fNowValue<98)
            //                        m_fNowValue+=0.2;
            //                    FUNC().getProductDetail(list[_productList::_id]);
            //                    setViewWord("loading PdDetail : ppid  "+list[_productList::_id]);
            //                }
            //            }
        }
    }
#else

    setViewWord("loading product list");
    //FUNC().getAllProductList();
    m_fNowValue+=10;


#endif

}

void LayerLoading::preloadProductDetail()
{

}

void LayerLoading::setViewWord(QString sText)
{
    if(sText.length()>40)
        sText=sText.left(40)+"...";
    ui->label->setText(sText);
}

QString LayerLoading::getViewWord()
{
    return ui->label->text();
}

void LayerLoading::timerEvent(QTimerEvent *)
{
    goAction();
}



int LayerLoading::getProgressValue()
{
    return m_fNowValue;
}

void LayerLoading::goAction()
{
    if(m_iTimer<0)
        return ;
    if(m_fNowValue<90)
        m_fNowValue++;


    ui->label_2->setText(QString::number(ui->label_2->text().split(" ").at(0).toInt()+1)+" ");
    if(m_iTimer <m_fNowValue)
    {
        m_iTimer++;

        ui->progressBar->setValue(m_iTimer);
        ui->progressBar2->setValue(m_iTimer);

    }
    else if(m_fNowValue==99)
    {
        setViewWord("ui component create ....");
    }
}
