#include "ItemShoppingCar.h"
#include "ui_ItemShoppingCar.h"


ItemShoppingCar::ItemShoppingCar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemShoppingCar)
{
    ui->setupUi(this);
    float f=(float)WINDOW_W*0.2625;
    resize(WINDOW_W*0.85,f+40+ui->line->height());

    ui->wImage->setMinimumSize(QSize(f,f));
    ui->wImage->setMaximumSize(QSize(f,f));

    float fBtn=(float)TOP_MENU_H*0.7;
    ui->wContrl->setMaximumHeight(fBtn);
    ui->wContrl->setMinimumHeight(fBtn);
    ui->wContrl->setMaximumWidth(TOP_MENU_H*3.5);
    ui->wContrl->setMinimumWidth(TOP_MENU_H*3.5);
    ui->btnAdd->setMinimumSize(fBtn,fBtn);
    ui->btnAdd->setMaximumSize(fBtn,fBtn);
    ui->btnSub->setMinimumSize(fBtn,fBtn);
    ui->btnSub->setMaximumSize(fBtn,fBtn);
    ui->lbNums->setMinimumWidth(TOP_MENU_H*1.5);
    ui->lbNums->setMaximumWidth(TOP_MENU_H*1.5);
    m_sCarItemId="";
    m_iNowCount=1;
    m_iCost=0;
//    ui->textEdit->setFrameStyle(QFrame::NoFrame);
//    ui->textEdit->setReadOnly(true);


    ui->lbNums->setText("1");
    connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(slotClickedAdd()));
    connect(ui->btnSub,SIGNAL(clicked()),this,SLOT(slotClickedSub()));

}

ItemShoppingCar::~ItemShoppingCar()
{
    delete ui;
}



void ItemShoppingCar::setCarItem(DataGetCar cData)
{
    m_sId=cData.sProductId;
    m_sCarItemId=cData.sCarItemID;

    ui->lbName->setText(cData.sName);
    ui->lbSize->setText(cData.sPp1Name+"/"+cData.sPp2Name);
    ui->lbCost->setText(cData.sSellPrice);
    //QString sShowText=cData.sName+"\n"+cData.sPp1Name+"/"+cData.sPp2Name+"\n"+cData.sSellPrice;
    //ui->textEdit->setText(sShowText);
    m_iCost=cData.sSellPrice.replace("TWD","").replace("$","").replace(",","").replace(" ","").toInt();
    m_iMaxCount=cData.sMaxQty.toInt();
    ui->lbNums->setText(cData.sQty);
    ui->wImage->setImageUrl(cData.sImageUrl);
    m_iNowCount=cData.sQty.toInt();
}

int ItemShoppingCar::cost()
{
    return m_iCost;
}



void ItemShoppingCar::slotClickedAdd()
{

    if(m_iNowCount<m_iMaxCount)
    {
        m_iNowCount++;
    }
    else
    {
        qDebug()<<"can't up Max Count : "<<m_iMaxCount;
        GLOBAL().showMsg("超出此款式可購買數量。");
        return;
    }

    QString sRe=FUNC().updateNumsCar(m_sCarItemId,m_iNowCount);


    if(sRe=="1")
    {
        ui->lbNums->setText(QString::number(m_iNowCount));
       emit signalChange(m_iCost);
    }
    else
    {
        m_iNowCount--;
        GLOBAL().showMsg("操作失敗。");
    }





}

void ItemShoppingCar::slotClickedSub()
{
    if(m_iNowCount<=0)
        return;
    m_iNowCount--;
    QString sRe=FUNC().updateNumsCar(m_sCarItemId,m_iNowCount);

    if(sRe=="1")
    {
        ui->lbNums->setText(QString::number(m_iNowCount));
        emit signalChange(-m_iCost);
      //  emit signalGetCar();
    }
    else
    {
        m_iNowCount--;
        GLOBAL().showMsg("操作失敗。");
    }

    if(m_iNowCount==0)
        emit signalGetCar();



}
