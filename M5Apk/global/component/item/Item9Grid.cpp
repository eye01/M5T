#include "Item9Grid.h"
#include "ui_Item9Grid.h"

Item9Grid::Item9Grid(QWidget *parent) :
    ItemButton(parent),
    ui(new Ui::Item9Grid)
{
    ui->setupUi(this);
    m_lb->setStyleSheet("background-color:rgb(0,0,0,0)");
    m_lb->setAttribute(Qt::WA_TranslucentBackground, true);
    m_lb->raise();
    m_lb->setStyleSheet("color:rgb(255,255,255)");
    ui->wMask->hide();

}

Item9Grid::~Item9Grid()
{
    delete ui;
}

void Item9Grid::mousePressEvent(QMouseEvent *e)
{

    ui->wMask->show();
    ItemButton::mousePressEvent(e);
}

void Item9Grid::mouseReleaseEvent(QMouseEvent *e)
{
    ui->wMask->hide();
    ItemButton::mouseReleaseEvent(e);
}



void Item9Grid::showEvent(QShowEvent *)
{

}

void Item9Grid::resizeEvent(QResizeEvent *)
{


    ui->wBg->resize(size());
    ui->wBg->move(0,0);
    //ui->wBg->setGeometry(rect());

    //ui->wMask->setGeometry(rect());
    ui->wMask->resize(size());
    ui->wMask->move(0,0);
    m_lb->setGeometry(rect());
}
