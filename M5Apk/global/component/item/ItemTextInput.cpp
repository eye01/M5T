#include "ItemTextInput.h"
#include "ui_ItemTextInput.h"

ItemTextInput::ItemTextInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemTextInput)
{
    ui->setupUi(this);
    g_lineEidt=ui->vLineEdit->g_edit;

}

ItemTextInput::~ItemTextInput()
{
    delete ui;
}

void ItemTextInput::setTitleName(QString sText)
{
    ui->lbTitle->setText(sText);
}

void ItemTextInput::setErrorText(QString sText)
{
    ui->lbError->setText(sText);
}

void ItemTextInput::setPlaceholderText(QString sText)
{
    ui->vLineEdit->setPlaceholderText(sText);
}

void ItemTextInput::setOnlyRead(bool bOnlyRead)
{

    ui->vLineEdit->m_cLineEdit->m_bOnlyRead =bOnlyRead;
    ui->vLineEdit->g_edit->setReadOnly(bOnlyRead);
}

void ItemTextInput::setText(QString sText)
{
    ui->vLineEdit->g_edit->setText(sText);
}

QString ItemTextInput::text()
{
    return ui->vLineEdit->text();
}
