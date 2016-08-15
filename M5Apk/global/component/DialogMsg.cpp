#include "DialogMsg.h"
#include "ui_DialogMsg.h"

DialogMsg::DialogMsg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogMsg)
{
    ui->setupUi(this);
    m_iAfterCloseGoStage=-1;
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    setMaximumSize(GLOBAL().g_sizeWindow);
    setMinimumSize(GLOBAL().g_sizeWindow);

    ui->wFrame->setMinimumHeight((float)WIDONW_H*0.33);
    ui->wFrame->setMaximumHeight((float)WIDONW_H*0.33);
    ui->wFrame->setMinimumWidth((float)WINDOW_W*0.843);
    ui->wFrame->setMaximumWidth((float)WINDOW_W*0.843);
    ui->wTitle->setMinimumHeight((float)WIDONW_H*0.0715);
    ui->wTitle->setMaximumHeight((float)WIDONW_H*0.0715);
    ui->wBottom->setMinimumHeight((float)WIDONW_H*0.0805);
    ui->wBottom->setMaximumHeight((float)WIDONW_H*0.0805);
    ui->btnBottom->setText("確定");
    ui->btnBottom->setMaskStyleSheet("background-color: rgb(238, 238, 238);");
    connect(ui->wMask,SIGNAL(clicked()),this,SLOT(on_btnBottom_clicked()));

    hide();
}

DialogMsg::~DialogMsg()
{
    delete ui;
}

void DialogMsg::on_btnBottom_clicked()
{

    hide();
    if(m_iAfterCloseGoStage!=-1)
        GLOBAL().goTargetStage(m_iAfterCloseGoStage);
}

void DialogMsg::slotShowMsg(bool bIsShow,QString st, int iStageIdx)
{
    if(bIsShow)
    {
        ui->lbBody->setText(st);
        m_iAfterCloseGoStage=iStageIdx;
        if(st.length()<=20)
            ui->lbBody->setAlignment(Qt::AlignCenter);
        else
            ui->lbBody->setAlignment(Qt::AlignLeft);
        show();
    }
    else
    {
        on_btnBottom_clicked();
    }
}
