#include "ItemImage.h"

ItemImage::ItemImage(QWidget *parent) : QWidget(parent)
{
    m_lbBg=new QLabel(this);
    m_lb=new QLabel(this);
    m_lb->raise();
    m_thread=new CThread(this);

}

ItemImage::~ItemImage()
{

}

void ItemImage::setImageUrl(QString sUrl)
{
    if(sUrl.count()<1)
        return;

    m_lb->clear();
    m_lb->resize(size());

    m_thread->setImage(sUrl,m_lb);
    m_thread->start();
}

void ItemImage::resizeEvent(QResizeEvent *)
{
    m_lbBg->resize(size());
    m_lb->resize(size());
}

