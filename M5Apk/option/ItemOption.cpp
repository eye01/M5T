#include "ItemOption.h"
#include "ui_ItemOption.h"

ItemOption::ItemOption(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemOption)
{
    m_wBg=new QWidget(this);
    m_wBg->setStyleSheet("background-color: rgb(221, 221, 221);");
    m_wBg->resize(size());
    m_wBg->hide();
    ui->setupUi(this);
    resize(WINDOW_W*0.85,TOP_MENU_H);
    ui->stackIcon->setMinimumWidth(TOP_MENU_H);
    ui->stackIcon->setMaximumWidth(TOP_MENU_H);


    m_touch=new ItemTouchCanvas(this);
    m_touch->setGeometry(rect());
    m_wDisable=new QWidget(this);
    m_wDisable->setStyleSheet("background-color:rgb(255,255,255)");
    setIcon(OPTION_ICON_NONE);


}

ItemOption::~ItemOption()
{
    delete ui;
}

void ItemOption::resizeEvent(QResizeEvent *)
{
    m_wBg->resize(size());
    m_touch->resize(size());
    m_touch->raise();
    m_wDisable->resize(width(),150);
    m_wDisable->raise();
    m_wDisable->hide();
}

void ItemOption::press()
{
    //ui->wBg->setStyleSheet("QWidget#wBg{background-color: rgb(221, 221, 221);}");
    m_wBg->show();
}

void ItemOption::release()
{
    // ui->wBg->setStyleSheet("QWidget#wBg{background-color: rgb(221, 221, 221,0);}");
    m_wBg->hide();
    emit signalClicked();
}

void ItemOption::setText(QString sText)
{
    ui->label->setText(sText);
}

QString ItemOption::text()
{
    return ui->label->text();
}

void ItemOption::setUse(bool bIsUse)
{
    bIsUse=true;
    m_wDisable->setHidden(bIsUse);
}

void ItemOption::setIcon(int iEnum)
{
    ui->stackIcon->setCurrentIndex(iEnum);
}

void ItemOption::setTitleIcon(QString sUrl)
{

    ui->wTitleIcon->setMinimumWidth((float)TOP_MENU_H*81/112);
    ui->wTitleIcon->setMaximumWidth((float)TOP_MENU_H*81/112);

    ui->wTitleIcon->setStyleSheet("border-image:url("+sUrl+");");
}


//=============================================================================
//

ItemTouchCanvas::ItemTouchCanvas(QWidget *parent):QWidget(parent)
{


    //   QVBoxLayout *layout=new QVBoxLayout(this);

    m_wBg=new QWidget(this);
    m_wBg->setStyleSheet("background-color: rgb(221, 221, 221,180);");
    setStyleSheet("background-color:rgb(255,255,255,0)");
    // layout->addWidget(m_wBg);

    // this->setLayout(layout);
    m_wBg->hide();
    m_wBg->resize(10,height());
    m_iSec=-1;
   // QObject::startTimer(50);
}

void ItemTouchCanvas::mousePressEvent(QMouseEvent *)
{
    m_iSec=0;
    m_wBg->resize(size());
    m_wBg->move(0,0);
    m_wBg->show();
    ItemOption *w=dynamic_cast<ItemOption*>(parent());
    w->press();
}

void ItemTouchCanvas::mouseReleaseEvent(QMouseEvent *)
{
    m_iSec=-1;
    m_wBg->hide();
    m_wBg->resize(10,height());
    ItemOption *w=dynamic_cast<ItemOption*>(parent());
    w->release();
}

void ItemTouchCanvas::timerEvent(QTimerEvent *)
{
    if(m_iSec>=0)
    {
        m_iSec+=50;
    }
    else
    {

        return;
    }

    float fValue=qBound(width()/2, m_wBg->width()+30,width());
    m_wBg->resize(fValue,height());
    m_wBg->move((width()-m_wBg->width())/2,0);



}






