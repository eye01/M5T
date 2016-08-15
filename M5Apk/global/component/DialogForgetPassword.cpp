#include "DialogForgetPassword.h"
#include "ui_DialogForgetPassword.h"

DialogForgetPassword::DialogForgetPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogForgetPassword)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    setMaximumSize(GLOBAL().g_sizeWindow);
    setMinimumSize(GLOBAL().g_sizeWindow);

    ui->wFrame->setMinimumHeight((float)TOP_MENU_H*3.5);
    ui->wFrame->setMaximumHeight((float)TOP_MENU_H*3.5);
    ui->wFrame->setMinimumWidth((float)WINDOW_W*0.843);
    ui->wFrame->setMaximumWidth((float)WINDOW_W*0.843);

    ui->wTitle->setMinimumHeight((float)WIDONW_H*0.0715);
    ui->wTitle->setMaximumHeight((float)WIDONW_H*0.0715);

    ui->wBottom->setMinimumHeight((float)WIDONW_H*0.0805);
    ui->wBottom->setMaximumHeight((float)WIDONW_H*0.0805);


    ui->vTxtEmail->setMinimumHeight((float)TOP_MENU_H);
    ui->vTxtEmail->setMaximumHeight((float)TOP_MENU_H);
    ui->btnCheck->setText("確定");
    ui->btnCheck->setMaskStyleSheet("background-color: rgb(238, 238, 238);");
    connect(ui->btnCheck,SIGNAL(clicked()),this,SLOT(slotCheck()));
    ui->btnCancel->setText("取消");
    ui->btnCancel->setMaskStyleSheet("background-color: rgb(238, 238, 238);");
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(slotCancel()));

    ui->vTxtEmail->setTitleName("Email");

    hide();
}

DialogForgetPassword::~DialogForgetPassword()
{
    delete ui;
}

void DialogForgetPassword::slotCheck()
{
    QString sReturnCode;//=FUNC().fogetPassword(ui->vTxtEmail->text());

    if(sReturnCode=="1")
    {
        GLOBAL().showMsg("密碼已寄至信箱。");
    }
    else if(sReturnCode=="-1")
    {
        GLOBAL().showMsg("缺少參數。");
    }
    else if(sReturnCode=="-2")
    {
        GLOBAL().showMsg("帳號不存在。");
    }
    else if(sReturnCode=="-3")
    {
        GLOBAL().showMsg("寄送信箱錯誤。");
    }

    hide();

}

void DialogForgetPassword::slotCancel()
{
    hide();
}
