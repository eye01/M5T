#include "DialogSelector.h"
#include "ui_DialogSelector.h"

DialogSelector::DialogSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogSelector)
{
    ui->setupUi(this);
    m_listCheck.append(ui->wCheck0);
    m_listCheck.append(ui->wCheck1);
    m_listCheck.append(ui->wCheck2);
    m_listCheck.append(ui->wCheck3);
    m_listCheck.append(ui->wCheck4);
    m_listCheck.append(ui->wCheck5);
    m_listCheck.append(ui->wCheck6);

    m_listBtn.append(ui->w0);
    m_listBtn.append(ui->w1);
    m_listBtn.append(ui->w2);
    m_listBtn.append(ui->w3);
    m_listBtn.append(ui->w4);
    m_listBtn.append(ui->w5);
    m_listBtn.append(ui->w6);

    m_listContent.append(ui->wContent0);
    m_listContent.append(ui->wContent1);
    m_listContent.append(ui->wContent2);
    m_listContent.append(ui->wContent3);
    m_listContent.append(ui->wContent4);
    m_listContent.append(ui->wContent5);
    m_listContent.append(ui->wContent6);
    m_iIdx=0;
    connect(ui->wMask,SIGNAL(clicked()),this,SLOT(slotClicked()));

    foreach (ItemButton *btn, m_listBtn)
    {
        connect(btn,SIGNAL(clicked()),this,SLOT(slotClicked()));
    }
    m_iType=-1;
    resize(GLOBAL().g_sizeWindow);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    ui->wMask->setGeometry(ui->wBg->rect());
    ui->wWindow->setMinimumWidth(ui->wBg->width()-200);
    ui->wWindow->setMaximumWidth(ui->wBg->width()-200);
    ui->wWindow->move(100,(ui->wBg->height()-ui->wWindow->height())/2);
    hide();
}

DialogSelector::~DialogSelector()
{
    delete ui;
}

void DialogSelector::showDialog(int iType, QString sTitleName, int iNowIdx, QList<QWidget*> &listContent, QList<bool> isEndable)
{
    if(listContent.length()<=1)
        return;
    m_iType=iType;
    ui->label->setText(sTitleName);

    int iWindowHeight=ui->wTop->height()+ui->wBottom->height()+150*listContent.length();

    for(int i=0;i<m_listBtn.length();i++)
    {
        if(i<listContent.length())
        {
            m_listBtn[i]->setVisible(true);
            listContent[i]->setParent(m_listContent[i]);
            listContent[i]->show();
        }
        else
        {
            m_listBtn[i]->setVisible(false);
        }

    }
    ui->wWindow->setMinimumHeight(iWindowHeight);
    ui->wWindow->setMaximumHeight(iWindowHeight);
    ui->wWindow->move(ui->wWindow->x(),(ui->wBg->height()-ui->wWindow->height())/2);
    visiableCheckIcon(iNowIdx);

    show();
}

void DialogSelector::visiableCheckIcon(int iIdx)
{
    if(iIdx< 0 || iIdx>=m_listCheck.length())
    {
        qDebug()<<"error dialog idx" ;
        iIdx=0;
    }
    for(int i=0;i<m_listCheck.length();i++)
    {
        m_listCheck[i]->setVisible(i==iIdx);
    }
    m_iIdx=iIdx;
}

void DialogSelector::resizeEvent(QResizeEvent *)
{
    ui->wMask->setGeometry(ui->wBg->rect());
    ui->wWindow->setMinimumWidth(ui->wBg->width()-200);
    ui->wWindow->setMaximumWidth(ui->wBg->width()-200);
    ui->wWindow->move(100,(ui->wBg->height()-ui->wWindow->height())/2);
}

void DialogSelector::slotClicked()
{
    ItemButton *btn=dynamic_cast<ItemButton*>(sender());
    int iIdx=m_listBtn.indexOf(btn);

    if(iIdx<0)
    {
        iIdx=m_iIdx;
    }

    visiableCheckIcon(iIdx);

    hide();
    emit signalClose(m_iType,iIdx);
}
