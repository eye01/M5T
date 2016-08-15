#include "LayerBlock.h"
#include "ui_LayerBlock.h"

LayerBlock::LayerBlock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerBlock)
{
    ui->setupUi(this);
    resize(GLOBAL().g_sizeWindow);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);


    QList<QPixmap*> listPix;
    listPix.append(new QPixmap(":/loading/res/images/loading/loading1-1.png"));
    listPix.append(new QPixmap(":/loading/res/images/loading/loading1-2.png"));
    listPix.append(new QPixmap(":/loading/res/images/loading/loading1-3.png"));
    listPix.append(new QPixmap(":/loading/res/images/loading/loading1-4.png"));
    listPix.append(new QPixmap(":/loading/res/images/loading/loading1-5.png"));
    listPix.append(new QPixmap(":/loading/res/images/loading/loading1-6.png"));
    listPix.append(new QPixmap(":/loading/res/images/loading/loading1-7.png"));
    listPix.append(new QPixmap(":/loading/res/images/loading/loading1-8.png"));
    ui->vLoadingBar->setPixmap(listPix);
    // m_iSec=-1;
    hide();
    ui->vLoadingBar->hide();
    // QObject::startTimer(100);

}

LayerBlock::~LayerBlock()
{
    delete ui;
}

void LayerBlock::setCanView(bool bIsCan)
{

    ui->wBg->setVisible(bIsCan);

}

void LayerBlock::showEvent(QShowEvent *)
{
    m_iSec=0;
    ui->vLoadingBar->show();
}

void LayerBlock::hideEvent(QHideEvent *)
{

    m_iSec=-1;
    ui->vLoadingBar->hide();
}

void LayerBlock::timerEvent(QTimerEvent *)
{


    //    if(m_iSec>=0)
    //        m_iSec+=100;

    //    ui->vLoadingBar->setVisible(m_iSec>=200);


}

void LayerBlock::slotBlockFlag(bool bIsBlock, bool bIsCanView)
{

    bIsBlock=bIsBlock;
    setCanView(bIsCanView);
    setVisible(bIsBlock);
}
