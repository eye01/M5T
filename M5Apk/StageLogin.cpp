#include "StageLogin.h"
#include "ui_StageLogin.h"

StageLogin::StageLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageLogin)
{
    ui->setupUi(this);
    ui->vTitle->setMaximumHeight(TOP_MENU_H);
    ui->vTitle->m_btnRight->hide();
    ui->vTitle->setCentFlag(_NO_ICON);
    ui->vTitle->setTitleName("會員登入");
    ui->vTitle->m_btnLeft->setStyleSheet("border-image: url(:/image/res/images/icon/icon_back_arrow.png);");
    connect(ui->vTitle->m_btnLeft,SIGNAL(clicked()),this,SLOT(slotClickedLeft()));
    
    ui->vTxtLoginId->setIconImage(":/image/res/images/icon/icon_member_s1-1.png",":/image/res/images/icon/icon_member_s1-2.png",LineEdit::_normal);
    ui->vTxtLoginId->setPlaceholderText("請輸入帳號");
    ui->vTxtPassword->setIconImage(":/image/res/images/icon/icon_password_s1-1.png",":/image/res/images/icon/icon_password_s1-2.png",LineEdit::_password);
    ui->vTxtPassword->setPlaceholderText("請輸入密碼");
    ui->vTxtLoginId->setMaximumHeight((float)WIDONW_H*0.08);
    ui->vTxtLoginId->setMinimumHeight((float)WIDONW_H*0.08);
    ui->vTxtPassword->setMaximumHeight((float)WIDONW_H*0.08);
    ui->vTxtPassword->setMinimumHeight((float)WIDONW_H*0.08);
    float f=(float)WINDOW_W*0.6;
    ui->wImage->setMinimumSize(f,f);
    ui->wImage->setMaximumSize(f,f);
    ui->wImage->setStyleSheet("border-image:url(:/image/res/images/login.png)");

    ui->widget_2->setMinimumHeight(ui->wImage->height()+40);
    ui->widget_2->setMaximumHeight(ui->wImage->height()+40);
    ui->btnLogin->setMinimumHeight(TOP_MENU_H);
    ui->btnLogin->setMaximumHeight(TOP_MENU_H);
    ui->btnJoin->setMinimumHeight(TOP_MENU_H);
    ui->btnJoin->setMaximumHeight(TOP_MENU_H);
    
    ui->btnForget->setMinimumHeight(TOP_MENU_H/3);
    ui->btnForget->setMaximumHeight(TOP_MENU_H/3);
    connect(ui->btnForget,SIGNAL(clicked()),this,SLOT(slotForget()));
    ui->btnJoin->setText("加入會員");
    ui->btnLogin->setText("登入");
    connect(ui->btnJoin,SIGNAL(clicked()),this,SLOT(slotClickedJoin()));
    connect(ui->btnLogin,SIGNAL(clicked()),this,SLOT(slotClickedLogin()));
    
    m_layerForgetPassword=new DialogForgetPassword(this);
    m_layerForgetPassword->move(0,0);

    QWidget::setTabOrder(ui->vTxtLoginId->g_edit,ui->vTxtPassword->g_edit);

    
}

StageLogin::~StageLogin()
{
    delete ui;
}

void StageLogin::slotClickedLeft()
{
    GLOBAL().goTargetStage(_StageIdx::_option,_StageItemIdx::_option_show);
}

void StageLogin::slotClickedJoin()
{
    GLOBAL().goTargetStage(_StageIdx::_register);
    
}

void StageLogin::slotClickedLogin()
{
    QString sRe="";//=FUNC().login(ui->vTxtLoginId->text().toLower(),ui->vTxtPassword->text().toLower());
    
    if(ui->vTxtLoginId->text()=="" || ui->vTxtPassword->text()=="")
        sRe="";

    QByteArray in;
    in.append("3001::check");
    QByteArray out;

    int iTcpRe=GLOBAL().tcp().blockTcpSend(in,out,"192.168.0.113",60000,5000) ;

    if(iTcpRe== -1)
    {

        sRe="-1";
    }

    else
    {
        sRe="-2";
        QStringList listUser=QString(out.length()).split(";");

        for(int i=0;i<listUser.length();i++)
        {
        if(ui->vTxtLoginId->text()==listUser[i].split(",").at(0))
            sRe=1;

        }
//        for(int i=0;i<out.length()-2;i+=2)
//        {
//            qDebug()<<out.at(i) <<"  "<<out.at(i+1);
//            if(ui->vTxtLoginId->text()==QString(out.at(i)) && ui->vTxtPassword->text()==QString(out.at(i+1)))
//                sRe="1";
//        }


    }


    if(sRe=="1")
    {
        GLOBAL().goTargetStage(_StageIdx::_first);
        //        if(!GLOBAL().g_bShopToLogin)
        //            GLOBAL().goTargetStage(_StageIdx::_memberCenter);
        //        else
        //        {
        //            // GLOBAL().goTargetStage(_StageIdx::_Delivery);
        //            GLOBAL().goTargetStage(_StageIdx::_memberCenter);
        //            GLOBAL().goTargetStage(_StageIdx::_car,_StageItemIdx::_car_show);
        //        }
    }
    
    else if(sRe=="")
    {
        GLOBAL().showMsg("請輸入帳號和密碼。");
    }
    else if(sRe=="-2" || sRe=="-3")
    {
        GLOBAL().showMsg("帳號或密碼錯誤。");
    }
    else if(sRe=="-1")
    {
        GLOBAL().showMsg("請確認網路連線是否正常。");
    }

    ui->vTxtPassword->m_cLineEdit->setText("");
}

void StageLogin::slotForget()
{
    
    m_layerForgetPassword->show();
    
}

void StageLogin::keyPressEvent(QKeyEvent *e)
{
    if(GLOBAL().isBlock())
        return;
    if(e->key()==Qt::Key_Back)
    {
        if(GLOBAL().isShowMsg())
            GLOBAL().cancelMsg();
        else if(m_layerForgetPassword->isVisible())
            m_layerForgetPassword->hide();
        else
            slotClickedLeft();
    }

}
