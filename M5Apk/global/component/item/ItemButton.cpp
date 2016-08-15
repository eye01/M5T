#include "ItemButton.h"

ItemButton::ItemButton(QWidget *parent) : QWidget(parent)
{

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    m_lb=new QLabel(this);
    m_lb->setStyleSheet("background-color:rgb(0,0,0,0)");
    m_lb->resize(size());
    QFont font;
    font.setPointSize(14);
    m_lb->setFont(font);
    m_lb->setAlignment(Qt::AlignCenter);
    m_lb->setText("");

    m_mask=NULL;
}

ItemButton::~ItemButton()
{

}

void ItemButton::mousePressEvent(QMouseEvent *)
{
    if(m_mask!=NULL)
    {
       // m_mask->setStyleSheet("background-color:rgb(0,0,0,0)");
        m_mask->resize(size()*1.5);
        m_mask->move((width()-m_lb->width())/2,(height()-m_mask->height())/2);
        m_mask->show();
    }
    else
    {
        m_lb->resize(size()*1.5);
        m_lb->move((width()-m_lb->width())/2,(height()-m_lb->height())/2);
    }
}

void ItemButton::mouseReleaseEvent(QMouseEvent *)
{
    m_lb->resize(size());
    m_lb->move(0,0);
    if(m_mask!=NULL)
    {
        m_mask->hide();
    }
    emit clicked();
}

void ItemButton::setStyleSheet(const QString &styleSheet)
{
    m_lb->setStyleSheet(styleSheet);
}

void ItemButton::setMaskStyleSheet(const QString &styleSheet)
{
    if(m_mask!=NULL)
    {
        m_mask->deleteLater();
        m_mask=NULL;
    }

    m_mask=new QLabel(this);
    m_mask->setStyleSheet("background-color:rgb(0,0,0,0)");
    m_mask->resize(size());
    m_mask->setStyleSheet(styleSheet);
    m_mask->raise();
    m_mask->hide();

}

void ItemButton::setText(QString sText)
{
    m_lb->setText(sText);
}

QString ItemButton::text()
{
    return m_lb->text();
}

void ItemButton::setImage(QString sUrl)
{
    m_lb->setStyleSheet("image:url("+sUrl+")");
}

void ItemButton::showEvent(QShowEvent *)
{
    m_lb->resize(size());
    if(m_mask!=NULL)
        m_mask->resize(size());

}

