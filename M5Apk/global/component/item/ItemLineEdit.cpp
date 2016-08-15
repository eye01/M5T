#include "ItemLineEdit.h"
#include "ui_ItemLineEdit.h"

ItemLineEdit::ItemLineEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemLineEdit)
{
    ui->setupUi(this);

    m_nContype=_nono;

    m_cLineEdit=new ItemLineComponent::CLineEdit(ui->wText);
    connect(m_cLineEdit,SIGNAL(signalFocus(bool)),this,SLOT(slotFocus(bool)));

//    ui->wIcon->setWindowFlags(Qt::FramelessWindowHint);
//    ui->wIcon->setAttribute(Qt::WA_TranslucentBackground, true);
    //ui->wIcon->hide();

    ui->wBorder->setStyleSheet("QWidget#wBorder{background-color: rgb(170, 170, 255);"
                               "border: 4px solid gray;"
                               "border-radius: 10px;"
                               "padding: 0 8px;"
                               "background: white;"
                               "selection-background-color: darkgray;}");

    g_edit=m_cLineEdit;


}

ItemLineEdit::~ItemLineEdit()
{
    delete ui;
}

void ItemLineEdit::setText(QString sText)
{
    m_cLineEdit->setText(sText);
}

QString ItemLineEdit::text()
{
    return m_cLineEdit->text();
}

void ItemLineEdit::setIconImage(QString sUrl, QString sFocusUrl, _IconType nType=_normal)
{
    m_nContype=nType;
    ui->wIcon->setVisible(m_nContype!=_nono);
    m_sUrl=sUrl;
    m_sFocusUrl=sFocusUrl;
    ui->wIcon->setStyleSheet("border-image:url("+m_sUrl+");");

    if(nType==_password)
        m_cLineEdit->setEchoMode(QLineEdit::Password);

}

void ItemLineEdit::setPlaceholderText(const QString &text)
{
    m_cLineEdit->setPlaceholderText(text);
}



void ItemLineEdit::showEvent(QShowEvent *)
{
    m_cLineEdit->resize(ui->wText->size());
    float fW=20;
    if(m_nContype!=_nono)
    {
        fW=(float)ui->wIcon->height()/1.25;
    }

    ui->wIcon->setMinimumWidth(fW);
    ui->wIcon->setMaximumWidth(fW);

}


void ItemLineEdit::slotFocus(bool bIsFocusIn)
{

    if(bIsFocusIn)
    {

        ui->wBorder->setStyleSheet(ui->wBorder->styleSheet()+"QWidget#wBorder{border: 4px solid rgb(195,50,39);}");
        // ui->wBorder->setStyleSheet(ui->wBorder->styleSheet()+"border: 4px solid red;");
    }
    else
    {


        ui->wBorder->setStyleSheet(ui->wBorder->styleSheet()+"QWidget#wBorder{border: 4px solid darkgray;}");


        // ui->wBorder->setStyleSheet(ui->wBorder->styleSheet()+"border: 4px solid gray;");
    }

    if(ui->wIcon->isVisible())
    {
        if(bIsFocusIn)
            ui->wIcon->setStyleSheet("border-image:url("+m_sFocusUrl+");");
        else
            ui->wIcon->setStyleSheet("border-image:url("+m_sUrl+");");
    }
}

ItemLineComponent::CLineEdit::CLineEdit(QWidget *parent):QLineEdit(parent)
{

    setFrame(false);
    m_bOnlyRead=false;
}

void ItemLineComponent::CLineEdit::focusInEvent(QFocusEvent *e)
{
    if(!m_bOnlyRead)
    {
        QLineEdit::focusInEvent(e);
        emit signalFocus(true);
    }
}

void ItemLineComponent::CLineEdit::focusOutEvent(QFocusEvent *e)
{
    if(!m_bOnlyRead)
    {
        QLineEdit::focusOutEvent(e);
        emit signalFocus(false);
    }
}

void ItemLineComponent::CLineEdit::mousePressEvent(QMouseEvent *e)
{
    if(!m_bOnlyRead)
    {
        QLineEdit::mousePressEvent(e);
    }
    e->ignore();
}

void ItemLineComponent::CLineEdit::mouseMoveEvent(QMouseEvent *e)
{
    if(!m_bOnlyRead)
    {
        QLineEdit::mouseMoveEvent(e);
    }
    e->ignore();

}

void ItemLineComponent::CLineEdit::mouseReleaseEvent(QMouseEvent *e)
{
    QLineEdit::mouseReleaseEvent(e);
    e->ignore();
}
