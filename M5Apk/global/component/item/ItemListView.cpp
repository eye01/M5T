#include "ItemListView.h"

ItemListView::ItemListView(QWidget *parent) : QWidget(parent)
{

  resize(parent->size());
  m_wBg=new QWidget(this);
  m_wBg->setStyleSheet("background-color:rgb(255,255,255)");
  m_wBg->setGeometry(rect());
  m_wContent=new QWidget(this);
  m_wContent->setGeometry(rect());

}

ItemListView::~ItemListView()
{

}

void ItemListView::setListWidget(QList<QWidget *> list, int iLineH)
{
    m_wContent->resize(width(),1);
    for(int i=0;i<list.length();i++)
    {
        m_wContent->resize(width(),m_wContent->height()+list[i]->height()+iLineH);
        list[i]->setParent(m_wContent);
        list[i]->show();
        if(i==0)
            list[i]->move(0,0);
        else
            list[i]->move(0,list[i-1]->mapTo(m_wContent,QPoint(0,0)).y()+list[i-1]->height()+iLineH);
    }
    int iH=m_wContent->height();
    if(m_wContent->height()<height())
        iH=height();
    m_wBg->setGeometry(0,0,m_wContent->width(),iH);
}

void ItemListView::setBorderStyleSheet(const QString &styleSheet)
{
    m_wBg->setStyleSheet(styleSheet);

}

void ItemListView::resizeEvent(QResizeEvent *)
{

}

void ItemListView::mousePressEvent(QMouseEvent *e)
{

    m_posPress=e->pos();
    m_posOldContent=m_wContent->pos();

}

void ItemListView::mouseReleaseEvent(QMouseEvent *)
{

}

void ItemListView::mouseMoveEvent(QMouseEvent *e)
{

    int iTargetY=e->pos().y()-m_posPress.y()+m_posOldContent.y();
    if(iTargetY>0)
        iTargetY=0;
    else if(iTargetY<-m_wContent->height()+height())
        iTargetY=-m_wContent->height()+height();

    m_wContent->move(0,iTargetY);



}

