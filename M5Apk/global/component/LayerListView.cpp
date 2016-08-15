#include "LayerListView.h"

LayerListView::LayerListView(QWidget *parent) : QWidget(parent)
{
    m_wBg=new QWidget(this);

    m_wBg->setObjectName("m_wBg");

    m_wBg->setStyleSheet("QWidget#m_wBg{background-color:rgb(0,0,0,0)}");

    m_wContent = new QWidget(m_wBg);


}

void LayerListView::setBg(QString sStyleSheet)
{
    m_wBg->setStyleSheet("QWidget#m_wBg{"+sStyleSheet+"}");
}

void LayerListView::addWidget(QWidget *w)
{
    m_wContent->deleteLater();
    m_wContent=w;
    m_wContent->setParent(m_wBg);
    m_wContent->show();
    m_wContent->move(0,0);

}

void LayerListView::resizeEvent(QResizeEvent *)
{
    m_wBg->setGeometry(rect());

}

void LayerListView::mousePressEvent(QMouseEvent *e)
{
    if(m_wContent->height()<=height())
        return;
    m_iOldPressY= e->y();
    m_iOldContentY= m_wContent->y();
}

void LayerListView::mouseMoveEvent(QMouseEvent *e)
{
    if(m_wContent->height()<=height())
        return;

    int iDiffMove=m_iOldContentY+(e->y()-m_iOldPressY);

    if(iDiffMove>0)
        iDiffMove=0;
    if(iDiffMove<-m_wContent->height()+height()/3)
        iDiffMove=-m_wContent->height()+height()/3;
    m_wContent->move(0,iDiffMove);
}

void LayerListView::mouseReleaseEvent(QMouseEvent *)
{

}

