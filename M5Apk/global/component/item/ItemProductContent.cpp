#include "ItemProductContent.h"
#include "ui_ItemProductContent.h"

ItemProductContent::ItemProductContent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemProductContent)
{
    ui->setupUi(this);
}

ItemProductContent::~ItemProductContent()
{
    delete ui;
}



void ItemProductContent::setItemData(QString sUrl,QString sLbTitle, QString sLb0, QString sLb1, QString sLb2)
{
    ui->vImage->setImageUrl(sUrl);
    //ui->vImage->setStyleSheet("background-color:rgb(200,30,60)");
    ui->lbTitle->setText(sLbTitle);
    ui->lb00->setText(sLb0);
    ui->lb01->setText(sLb1);
    ui->lb02->setText(sLb2);
}

void ItemProductContent::resizeEvent(QResizeEvent *)
{
    ui->vImage->setMaximumWidth(ui->vImage->width());
    ui->vImage->setMinimumWidth(ui->vImage->width());
}
