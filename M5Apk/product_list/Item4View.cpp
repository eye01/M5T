#include "Item4View.h"
#include "ui_Item4View.h"

Item4View::Item4View(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Item4View)
{
    ui->setupUi(this);

    m_iIdxLeft=-1;
    m_iIdxRight=-1;

    setAttribute(Qt::WA_TintedBackground);
    resize(parent->width(),(float)parent->width()/2*1.3);
    QSize sz((parent->width()-20*2-15)/2,(parent->width()-20*2-15)/2);
    ui->wContent0->setMinimumWidth(sz.width());
    ui->wContent1->setMinimumWidth(sz.width());
    ui->vImage0->setMaximumSize(sz);
    ui->vImage0->setMinimumSize(sz);
    ui->vImage1->setMaximumSize(sz);
    ui->vImage1->setMinimumSize(sz);

    //m_btn0=new PushButton(ui->wContent0);
    m_btn0=new Button(ui->wContent0);
    connect(m_btn0,SIGNAL(clicked()),this,SLOT(slotItemClicked()));
    //m_btn1=new PushButton(ui->wContent1);
    m_btn1=new Button(ui->wContent1);
    connect(m_btn1,SIGNAL(clicked()),this,SLOT(slotItemClicked()));
    m_btn0->setStyleSheet("background-color:rgb(0,0,0,0)");
    m_btn1->setStyleSheet("background-color:rgb(0,0,0,0)");

    //m_btn0->setStyleSheet("border-image:url(:/image/res/images/mask_bottom.png);");
    //m_btn1->setStyleSheet("border-image:url(:/image/res/images/mask_bottom.png);");

//    m_btn0->hide();
//    m_btn1->hide();

}

Item4View::~Item4View()
{
    delete ui;
}

void Item4View::setData(QList<int> listIdx,QStringList listName, QStringList listUrl)
{
    ui->wContent1->show();
    if(listName.length()<2 || listName[1]=="")
    {
        ui->wContent1->hide();

    }

    while(listName.length()<2)
        listName.append("");
    while(listUrl.length()<2)
        listUrl.append("");
    while(listIdx.length()<2)
        listIdx.append(-1);

    m_iIdxLeft=listIdx.at(_left);
    m_iIdxRight=listIdx.at(_right);
    ui->vImage0->setImageUrl(listUrl.at(_left));
    ui->vImage1->setImageUrl(listUrl.at(_right));

    QStringList tmpName0=QString(listName.at(_left)).split("\n");
    if(tmpName0.length()<2)
        tmpName0.append("");

    QStringList tmpName1=QString(listName.at(_right)).split("\n");
    if(tmpName1.length()<2)
        tmpName1.append("");

    ui->lbName0->setText(tmpName0.at(_productName));
   // ui->lbCost0->setText(tmpName0.at(_productCost));

    ui->lbName1->setText(tmpName1.at(_productName));
    //ui->lbCost1->setText(tmpName1.at(_productCost));

}

void Item4View::resizeEvent(QResizeEvent *)
{
    m_btn0->setGeometry(0,0,width()/2,ui->vImage0->height());
    m_btn1->setGeometry(0,0,width()/2,ui->vImage0->height());
    QWidget *w0=new QWidget(ui->wContent0);
    w0->setGeometry(m_btn0->rect());
    w0->setStyleSheet(m_btn0->styleSheet());
    QWidget *w1=new QWidget(ui->wContent1);
    w1->setGeometry(m_btn1->rect());
    w1->setStyleSheet(m_btn1->styleSheet());
    w0->hide();
    w1->hide();



}

void Item4View::slotItemClicked()
{

    Button *btn=dynamic_cast<Button*>(sender());

    if(btn==m_btn0)
    {
        if(m_iIdxLeft>=0)
            emit clicked(m_iIdxLeft);
    }
    else
    {
        if(m_iIdxRight>=0)
            emit clicked(m_iIdxRight);
    }

}


