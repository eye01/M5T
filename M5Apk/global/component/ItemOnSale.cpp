#include "ItemOnSale.h"
#include "ui_ItemOnSale.h"

ItemOnSale::ItemOnSale(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemOnSale)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

ItemOnSale::~ItemOnSale()
{
    delete ui;
}

void ItemOnSale::setCost(QString sCost, QString sOnSale)
{

    ui->lbCost->setText("TWD$"+sCost);
    ui->btn->setText("TWD$"+sCost);
    ui->lbOnSale->setText("TWD$"+sOnSale);

    if(sOnSale.replace(",","").toInt()<sCost.replace(",","").toInt())
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
        ui->stackedWidget->setCurrentIndex(0);
}

QString ItemOnSale::cost()
{
    return ui->lbOnSale->text();
}
