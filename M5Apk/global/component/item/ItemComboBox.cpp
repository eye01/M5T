#include "ItemComboBox.h"
#include "ui_ItemComboBox.h"

ItemComboBox::ItemComboBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemComboBox)
{
    ui->setupUi(this);

//    ui->comboBox->setStyleSheet("QComboBox QAbstractItemView {"
//                            "    min-height: 200px;"
//                            "    min-width: 100px;"
//                            "}"
//                            "QComboBox QAbstractItemView::item {"
//                            "    min-height: 200px;"
//                            "    min-width: 100px;"
//                            "}");




    QListView *listView=new QListView(this);
    QFont f;
    f.setPointSize(24);
    listView->setFont(f);
    ui->comboBox->setView(listView);
    m_cb=ui->comboBox;

    //m_cb->setInsertPolicy(QComboBox::InsertAfterCurrent);


}

ItemComboBox::~ItemComboBox()
{
    delete ui;
}

void ItemComboBox::setTitleName(QString sText)
{
    ui->lb->setText(sText);
}

QString ItemComboBox::text()
{
    QString sRe="";
    sRe=ui->comboBox->currentText();
    return sRe;
}


