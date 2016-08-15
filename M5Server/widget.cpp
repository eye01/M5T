#include "widget.h"
#include "ui_widget.h"

#define CODE_VERSION "ccb_v010_1"


static QString st;
static Widget *instance;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    instance=this;

    this->setWindowTitle("M5Server");

    setting();

}

void Widget::setting()
{

    Global();

    m_sql=new CSqlServer(this);

    listenClient=new CListenClient(this);

    connect(listenClient,SIGNAL(signalTest(QString)),this,SLOT(slotTest(QString)));

    connect(m_sql,SIGNAL(signalLog(QString)),this,SLOT(slotTest(QString)));

     m_sql->openDb();

 //      connect(&Global(),SIGNAL(signalDebug(QString)),this,SLOT(slotDebug(QString)));




    listenClient->run();

    m_timer=new QTimer(this);

    m_timer->connect(m_timer,SIGNAL(timeout()),this,SLOT(slotSchedule()));




}



void Widget::appendDebugMsg(const QString &msg)
{
        ui->textEdit_2->append(msg);
}

void Widget::on_btnClear_clicked()
{
    if(ui->tabWidget->currentIndex()==0)
    {
        ui->textEdit->clear();
    }
    else
    {
        ui->textEdit_2->clear();
    }
}


Widget::~Widget()
{
    delete ui;
}

//-------------------------------------------------------------------------------------------------
//

void Widget::on_checkTargetDate_clicked()
{
    ui->dateEdit->setEnabled(ui->checkTargetDate->isChecked());
}

void Widget::slotTest(QString st)
{
    ui->textEdit->append(st);

}

void Widget::slotDebug(QString st)
{
     ui->textEdit_2->append(st);
}

void Widget::on_btnSendFile_clicked()
{
    //m_ftp->uploadEzCardDir();
}

void Widget::on_btnGetFile_clicked()
{

}

void Widget::on_btnPackFile_clicked()
{

}

//
void Widget::on_checkBoxLock_clicked()
{
    ui->wMask->setVisible(ui->checkBoxLock->isChecked());
}

void Widget::slotSchedule()
{

}
