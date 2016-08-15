#include "LayerOption.h"

LayerOption::LayerOption(QWidget *parent) :
    QWidget(parent)

{
  //  resize(WINDOW_W*0.85,WIDONW_H);
    QWidget *bg=new QWidget(this);
    bg->resize(GLOBAL().g_sizeWindow);
    bg->setStyleSheet("background-color:white");
   // for(int i=0;i<WIDONW_H/TOP_MENU_H;i++)
     for(int i=0;i<11;i++)
    {
        ItemOption *item=new ItemOption(this);
//        item->resize(size().width(),TOP_MENU_H);

        item->move(0,i*TOP_MENU_H);
        item->m_iIdx=i;
        connect(item,SIGNAL(signalClicked()),this,SLOT(slotClicked()));
        item->setUse(false);
        m_listItem.append(item);
    }

    m_iIdx=0;
}

LayerOption::~LayerOption()
{

}

void LayerOption::setTitleIcon(QStringList listUrl)
{
    for(int i=0;i<listUrl.length();i++)
    {
        if(i<m_listItem.length())
        {
            m_listItem[i]->setTitleIcon(listUrl[i]);
        }
    }
}

void LayerOption::setText(QStringList listText)
{

    foreach (ItemOption *option, m_listItem)
    {
        option->setUse(false);
    }

    for(int i=0;i<listText.length();i++)
    {
        m_listItem[i]->setUse(true);
        m_listItem[i]->setText(listText[i]);

    }
    m_iCount=listText.length();

    cutHeight();

}



void LayerOption::setKeyValue(QStringList listKey, QStringList listValue)
{
    m_listKey=listKey;
    m_listValue=listValue;

    while(m_listValue.length()>m_listKey.length())
    {
        m_listKey.append("");
    }

    m_iCount=m_listKey.length();
    foreach (ItemOption *option, m_listItem)
    {
        option->setUse(false);
    }

    for(int i=0;i<m_listValue.length();i++)
    {

        m_listItem[i]->setUse(true);
        m_listItem[i]->setText(m_listValue.at(i));

    }


    cutHeight();
}

QString LayerOption::getCurrentKey()
{
    return m_listKey.at(m_iIdx);
}



//void LayerOption::setTextData(QList<VoHeader> listData)
//{
//    foreach (ItemOption *option, m_listItem)
//    {
//        option->setUse(false);
//    }

//    for(int i=0;i<listData.length();i++)
//    {
//        m_listItem[i]->setUse(true);
//        m_listItem[i]->setText(listData[i].sName);

//    }
//    m_iCount=listData.length();

//    cutHeight();
//}

void LayerOption::setIcon(int iIdx, int iIconType)
{
    m_listItem[iIdx]->setIcon(iIconType);
}

void LayerOption::cutHeight()
{
    resize(width(),m_iCount*TOP_MENU_H);

}

void LayerOption::resizeEvent(QResizeEvent *)
{
    foreach (ItemOption *item, m_listItem)
    {
        item->resize(width(),TOP_MENU_H);
    }
}


void LayerOption::slotClicked()
{
    ItemOption *option=dynamic_cast<ItemOption*>(sender());
    m_iIdx=option->m_iIdx;
    emit sendClick(option->text());
    if(m_iIdx>=m_listKey.length())
    {

        return ;
    }

    emit sendClick(m_iIdx);




    emit sendClickedKey(m_listKey.at(m_iIdx));
    emit sendClickedValue(m_listValue.at(m_iIdx));

}
