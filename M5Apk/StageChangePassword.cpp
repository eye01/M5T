#include "StageChangePassword.h"
#include "ui_StageChangePassword.h"

StageChangePassword::StageChangePassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageChangePassword)
{
    ui->setupUi(this);
    this->resize(GLOBAL().g_sizeWindow);
    ui->vTitle->m_btnRight->hide();
    ui->vTitle->setMinimumHeight(TOP_MENU_H);
    ui->vTitle->setMaximumHeight(TOP_MENU_H);
    ui->vTitle->setCentFlag(_NO_ICON);
    ui->vTitle->setTitleName("修改密碼");
    ui->vTitle->m_btnLeft->setStyleSheet("border-image: url(:/image/res/images/icon/icon_back_arrow.png);");
    connect(ui->vTitle->m_btnLeft,SIGNAL(clicked()),this,SLOT(slotClickedLeft()));
    float f=(float)TOP_MENU_H;
    ui->vTxtOld->setMinimumHeight(f);
    ui->vTxtOld->setMaximumHeight(f);
    ui->vTxtOld->setTitleName("舊密碼");

    ui->vTxtNew->setMinimumHeight(f);
    ui->vTxtNew->setMaximumHeight(f);
    ui->vTxtNew->setTitleName("新密碼");
    ui->vTxtNew->setPlaceholderText("6~12個英數字");
    ui->vTxtNew->g_lineEidt->setMaxLength(12);
    ui->vTxtCheck->setMinimumHeight(f);
    ui->vTxtCheck->setMaximumHeight(f);
    ui->vTxtCheck->setTitleName("確認密碼");
    ui->vTxtCheck->setPlaceholderText("再次輸入新設定密碼");
    ui->vTxtCheck->g_lineEidt->setMaxLength(12);
    ui->btnCheck->setMinimumHeight(f);
    ui->btnCheck->setMaximumHeight(f);

    ui->btnCheck->setText("儲存");
    connect(ui->btnCheck,SIGNAL(clicked()),this,SLOT(slotCheck()));
}

StageChangePassword::~StageChangePassword()
{
    delete ui;
}

void StageChangePassword::showEvent(QShowEvent *)
{
    ui->vTxtOld->g_lineEidt->setText("");
    ui->vTxtNew->g_lineEidt->setText("");
    ui->vTxtCheck->g_lineEidt->setText("");
}

void StageChangePassword::keyPressEvent(QKeyEvent *e)
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

void StageChangePassword::slotClickedLeft()
{
    GLOBAL().goTargetStage(_StageIdx::_memberCenter);
}

void StageChangePassword::slotCheck()
{
    if(ui->vTxtOld->text()=="" || ui->vTxtNew->text()=="" || ui->vTxtCheck->text()=="")
    {
        GLOBAL().showMsg("欄位不能為空白。");
        return ;
    }

    if(ui->vTxtNew->text()!=ui->vTxtCheck->text())
    {
        GLOBAL().showMsg("密碼確認有誤。");
        return ;
    }

    if(ui->vTxtNew->text().length()<6)
    {
        GLOBAL().showMsg("密碼不能小於6個英數字。");
        return;
    }

    QString sRe="-1";//=FUNC().changePassword(ui->vTxtOld->text(),ui->vTxtNew->text());

    if(sRe=="1")
    {
        GLOBAL().showMsg("修改成功。",_StageIdx::_memberCenter);
    }
    else if(sRe=="-1")
    {
        GLOBAL().showMsg("缺少參數。");

    }

    else if(sRe=="-2")
    {
        GLOBAL().showMsg("尚未登入。");

    }

    else if(sRe=="-3")
    {
        GLOBAL().showMsg("錯誤的密碼。");
    }



}
