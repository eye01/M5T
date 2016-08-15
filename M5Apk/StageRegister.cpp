#include "StageRegister.h"
#include "ui_StageRegister.h"

StageRegister::StageRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageRegister)
{
    ui->setupUi(this);


    ui->vTitle->setMaximumHeight(TOP_MENU_H);

    ui->vTitle->m_btnRight->hide();
    ui->vTitle->setCentFlag(_NO_ICON);
    ui->vTitle->setTitleName("加入會員");
    ui->vTitle->m_btnLeft->setStyleSheet("border-image: url(:/image/res/images/icon/icon_back_arrow.png);");
    connect(ui->vTitle->m_btnLeft,SIGNAL(clicked()),this,SLOT(slotClickedLeft()));

    //float f=(float)WIDONW_H*0.09;
    float f=(float)TOP_MENU_H;
    ui->vTxtLoginId->setMinimumHeight(f);
    ui->vTxtLoginId->setMaximumHeight(f);
    ui->vTxtPassword->setMinimumHeight(f);
    ui->vTxtPassword->setMaximumHeight(f);
    ui->vTxtRePassword->setMinimumHeight(f);
    ui->vTxtRePassword->setMaximumHeight(f);
    ui->vTxtTel->setMinimumHeight(f);
    ui->vTxtTel->setMaximumHeight(f);
//    ui->vCbSex->setMinimumHeight(f);
//    ui->vCbSex->setMaximumHeight(f);
//    ui->vCbSex->setTitleName("姓別");
    ui->btnOk->setMinimumHeight(TOP_MENU_H);
    ui->btnOk->setMaximumHeight(TOP_MENU_H);
    ui->vTxtLoginId->setTitleName("Email");
    ui->vTxtLoginId->setPlaceholderText("此為你日後登入帳號");
    ui->vTxtPassword->setTitleName("設定密碼");
    ui->vTxtPassword->setPlaceholderText("密碼長度6~12位英數字");
    ui->vTxtPassword->g_lineEidt->setMaxLength(12);
    ui->vTxtRePassword->setTitleName("確認密碼");
    ui->vTxtRePassword->setPlaceholderText("再次確認密碼");
    ui->vTxtRePassword->g_lineEidt->setMaxLength(12);
    ui->vTxtTel->setTitleName("聯絡電話");
    ui->vTxtTel->setPlaceholderText("");
    ui->btnOk->setText("確認送出");
    connect(ui->btnOk,SIGNAL(clicked()),this,SLOT(slotClickedSend()));
    //ui->vCbSex->m_cb->insertItems(0,QStringList()<<"男"<<"女");

    QWidget::setTabOrder(ui->vTxtLoginId->g_lineEidt,ui->vTxtPassword->g_lineEidt);
    QWidget::setTabOrder(ui->vTxtPassword->g_lineEidt,ui->vTxtRePassword->g_lineEidt);
    QWidget::setTabOrder(ui->vTxtRePassword->g_lineEidt,ui->vTxtTel->g_lineEidt);



}

StageRegister::~StageRegister()
{
    delete ui;
}


void StageRegister::slotClickedLeft()
{
    GLOBAL().goTargetStage(_StageIdx::_login);
}

void StageRegister::slotClickedSend()
{
    QJsonObject obj;

    obj.insert("email",ui->vTxtLoginId->text().toLower());
    obj.insert("password",ui->vTxtPassword->text().toLower());
    obj.insert("lastName"," ");
    obj.insert("firstName"," ");
    QString sSex="M";
//    if(ui->vCbSex->text()!="男")
//        sSex=="F";
    obj.insert("sex",sSex);
    obj.insert("mobile",ui->vTxtTel->text());
    obj.insert("postalCode"," ");
    obj.insert("address"," ");
    obj.insert("invoiceNo"," ");
    obj.insert("invoiceTitle"," ");
    obj.insert("countryCode","TW");
    obj.insert("countryName","台灣");
    obj.insert("province"," ");
    obj.insert("city"," ");



    if(ui->vTxtLoginId->text()=="" || ui->vTxtPassword->text()=="" || ui->vTxtTel->text()=="")
    {
        GLOBAL().showMsg("欄位不能為空白。");
        return ;
    }

    if(ui->vTxtPassword->text()!=ui->vTxtRePassword->text())
    {
        GLOBAL().showMsg("密碼確認有誤。");
        return ;
    }

    if(ui->vTxtPassword->text().length()<6)
    {
        GLOBAL().showMsg("密碼不能小於6個英數字。");
        return;
    }


    QString sReturn;
    QStringList listOut;
    //sReturn=FUNC().memberRegister(obj,listOut);
    if(sReturn=="-2")
    {
        GLOBAL().showMsg("帳號已存在。");
    }
    else if(sReturn=="1")
    {
      //  FUNC().m_sCarId=listOut[_register::_cartID];
        //FUNC().m_bIsLogin=true;
     //   SQL().setOtherData(SqlOtherDataKey::sSession,FUNC().m_sSession);
        if(!GLOBAL().g_bShopToLogin)
            GLOBAL().showMsg("註冊成功。",_StageIdx::_memberCenter);
        else
            GLOBAL().goTargetStage(_StageIdx::_Delivery);

    }
    else
    {
        GLOBAL().showMsg("輸入錯誤。");
    }
}

void StageRegister::keyPressEvent(QKeyEvent *e)
{
    if(GLOBAL().isBlock())
        return;
    if(e->key()==Qt::Key_Back)
    {
        if(GLOBAL().isShowMsg())
            GLOBAL().cancelMsg();
        else
            slotClickedLeft();
    }
}
