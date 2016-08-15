#include "ItemBorderLabel.h"
#include "ui_ItemBorderLabel.h"

ItemBorderLabel::ItemBorderLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemBorderLabel)
{
    ui->setupUi(this);
    m_listBorder.append(ui->wBorder01);
    m_listBorder.append(ui->wBorder02);
    m_listBorder.append(ui->wBorder03);
    m_listBorder.append(ui->wBorder04);
    m_listBorder.append(ui->wBorder05);
    m_listBorder.append(ui->wBorder06);
    m_listBorder.append(ui->wBorder07);
    m_listBorder.append(ui->wBorder08);
    m_listBorder.append(ui->wBorder09);
    setAttribute(Qt::WA_TranslucentBackground);
}

ItemBorderLabel::~ItemBorderLabel()
{
    delete ui;
}

void ItemBorderLabel::setBorder(BorderType::_Type type)
{
    int iType=type;
    int iNum=0;

    QString st=":/border/res/images/border/border"+QString::number(iType)+"_0"+QString::number(iNum)+".png";


    QStringList list;

    for(int i=1;i<10;i++)
    {
        iNum=i;
        st=":/border/res/images/border/border"+QString::number(iType)+"_0"+QString::number(iNum)+".png";
        list.append(st);
    }

    if(type==BorderType::_type_black)
    {
        ui->label->setStyleSheet("background-color: rgba(255, 255, 255, 0);color:rgb(51,51,51);");
    }
    else if(type==BorderType::_type_whrite)
    {
        ui->label->setStyleSheet("background-color: rgba(255, 255, 255, 0);color:rgb(255,255,255);");
    }
    else if(type==BorderType::_type_orange)
    {
        ui->label->setStyleSheet("background-color: rgba(255, 255, 255, 0);color:rgb(191,55,39);");
    }

    setBorder(list);

}

void ItemBorderLabel::setBorder(QStringList listRes)
{

    if(listRes.length()<9)
    {

        return;
    }

    for(int i=0;i<9;i++)
    {
      //  wBorder02->setStyleSheet(QStringLiteral("border-image: url(:/border/res/images/border/border1_02.png);"));
        m_listBorder[i]->setStyleSheet("QWidget#"+m_listBorder[i]->objectName()+"{border-image:url("+listRes.at(i)+");}");
    }
    ui->label->raise();

}

void ItemBorderLabel::setText(QString st)
{

    ui->label->setText(st);
}

QString ItemBorderLabel::text()
{
    return ui->label->text();
}
