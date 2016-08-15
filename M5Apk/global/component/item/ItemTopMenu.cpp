#include "ItemTopMenu.h"
#include "ui_ItemTopMenu.h"

ItemTopMenu::ItemTopMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemTopMenu)
{
    ui->setupUi(this);

    resize(WINDOW_W,TOP_MENU_H);
    setMaximumHeight(TOP_MENU_H);
    setMinimumHeight(TOP_MENU_H);
    m_btnLeft=ui->btnLeft;
    m_btnRight=ui->btnRight;
    connect(ui->btnLeft,SIGNAL(clicked()),this,SIGNAL(signalClickedLeft()));


    m_btn=new ItemButton(ui->wCent);
    connect(m_btn,SIGNAL(clicked()),this,SIGNAL(signalClickedCent()));
    connect(ui->btnRight,SIGNAL(clicked()),this,SIGNAL(signalClickedRight()));
    m_btn->setGeometry(ui->wCent->rect());
    m_btn->setStyleSheet("background-color:rgb(255,255,0,0)");


    ui->wLight->setMinimumWidth(TOP_MENU_H);
    ui->wLight->setMaximumWidth(TOP_MENU_H);
    ui->wRight->setMinimumWidth(TOP_MENU_H);
    ui->wRight->setMaximumWidth(TOP_MENU_H);

    ui->stackIcon->setMinimumWidth(TOP_MENU_H);
    ui->stackIcon->setMaximumWidth(TOP_MENU_H);
    // connect(ui->wCent,SIGNAL(clicked()),this,SIGNAL(signalClickedCent()));

//    ui->stackCent->setMinimumHeight(float(TOP_MENU_H)*0.28);
//    ui->stackCent->setMaximumHeight(float(TOP_MENU_H)*0.28);


}

ItemTopMenu::~ItemTopMenu()
{
    delete ui;
}

void ItemTopMenu::setTitleName(QString sName)
{
    ui->label->setText(sName);
    ui->label_2->setText(sName);
}

QString ItemTopMenu::titleName()
{
    return ui->label->text();
}

void ItemTopMenu::setIconFlag(STACK_ICON iType)
{
    ui->stackIcon->setCurrentIndex(iType);
}

STACK_ICON ItemTopMenu::getIconFlag()
{
    return static_cast<STACK_ICON>(ui->stackIcon->currentIndex());
}

void ItemTopMenu::setCentFlag(STACK_CENT iType)
{
    ui->stackCent->setCurrentIndex(iType);
}

STACK_CENT ItemTopMenu::getCentFlag()
{
    return static_cast<STACK_CENT>(ui->stackCent->currentIndex());
}


void ItemTopMenu::showEvent(QShowEvent *)
{
    resize(WINDOW_W,TOP_MENU_H);
    m_btn->setGeometry(ui->wCent->rect());
}





