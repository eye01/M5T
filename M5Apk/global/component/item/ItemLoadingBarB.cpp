#include "ItemLoadingBarB.h"
#include "ui_ItemLoadingBarB.h"

ItemLoadingBarB::ItemLoadingBarB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemLoadingBarB)
{
    ui->setupUi(this);
    m_iNowValue=0;
    m_iBarWidthMax=ui->widget_5->width()-ui->wEnd->width();
}

ItemLoadingBarB::~ItemLoadingBarB()
{
    delete ui;
}

void ItemLoadingBarB::showEvent(QShowEvent *)
{
    m_iBarWidthMax=ui->widget_5->width()-ui->wEnd->width();
}

void ItemLoadingBarB::setValue(int i)
{
    int iPer=qBound(0,i,100);
    m_iNowValue=iPer;
    ui->wAdd->setMaximumWidth(iPer*(float)m_iBarWidthMax*0.01);
    ui->wAdd->setMinimumWidth(iPer*(float)m_iBarWidthMax*0.01);

}

int ItemLoadingBarB::value()
{
    return m_iNowValue;
}
