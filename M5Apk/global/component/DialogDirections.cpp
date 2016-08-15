#include "DialogDirections.h"
#include "ui_DialogDirections.h"

DialogDirections::DialogDirections(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogDirections)
{
    ui->setupUi(this);

    ui->wTitle->setMaximumHeight(TOP_MENU_H);
    ui->wTitle->setMinimumHeight(TOP_MENU_H);
    resize(GLOBAL().g_sizeWindow);

    ui->textEdit->setFrameStyle(QFrame::NoFrame);
    ui->textEdit_2->setFrameStyle(QFrame::NoFrame);

    m_listIcon.append(ui->wColorIcon0);
    m_listIcon.append(ui->wColorIcon1);
    m_listIcon.append(ui->wColorIcon2);
    m_listIcon.append(ui->wColorIcon3);

    for(int i=1;i<m_listIcon.length();i++)
    {
        m_listIcon[i]->hide();
    }

    m_listBtn.append(ui->btn0);
    m_listBtn.append(ui->btn1);
    m_listBtn.append(ui->btn2);
    m_listBtn.append(ui->btn3);

    connect(m_listBtn[0],SIGNAL(clicked()),this,SLOT(slotClicked()));
    connect(m_listBtn[1],SIGNAL(clicked()),this,SLOT(slotClicked()));
    connect(ui->btnClose,SIGNAL(clicked()),this,SLOT(slotClose()));
    changePage(0);
    hide();



}

DialogDirections::~DialogDirections()
{
    delete ui;
}

void DialogDirections::showDialog(QString sInfo, QList<QStringList> dSIzeTable)
{

    ui->textEdit->setText(sInfo);

    if(dSIzeTable.length()>2)
    {
        m_listTableColHeader=dSIzeTable.at(0);
        m_listTableRowHeader=dSIzeTable.at(1);

        QList<QStringList> dData;

        int iSortLen=m_listTableColHeader.length();

         int iArrLen=dSIzeTable.at(2).length()/iSortLen;

        QList<QStringList> list;
        while(list.length()<iArrLen)
        {
            QStringList tmp;
            list.append(tmp);
        }

      //  QStringList list[];

        for(int i=0;i<dSIzeTable.at(2).length();i++)
        {
            list[i/iSortLen].append(dSIzeTable.at(2).at(i));
        }

        for(int j=0;j<dSIzeTable.at(2).length()/iSortLen;j++)
        {
            dData.append(list[j]);
        }

        m_dTableData=dData;

    }

   // QStandardItemModel  *model = new QStandardItemModel();
    Cmodel  *model = new Cmodel();
    model->setColumnCount(m_listTableColHeader.length());

    for(int j=0;j<m_listTableColHeader.length();j++)
    {
        model->setHeaderData(j,Qt::Horizontal,m_listTableColHeader.at(j));
    }

    model->setRowCount(m_listTableRowHeader.length());
    for(int k=0;k<m_listTableRowHeader.length();k++)
    {
        model->setHeaderData(k,Qt::Vertical,m_listTableRowHeader.at(k));
    }


    for(int i=0;i<m_dTableData.length();i++)
    {

        for(int j=0;j<m_dTableData.at(i).length();j++)
        {

            model->setItem(i,j,new QStandardItem(m_dTableData.at(i).at(j)));
            // ->item(0,2)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    //    ui->tableView->horizontalHeader()->setResizeMode(1,QHeaderView::Fixed);
    show();
}

void DialogDirections::changePage(int iIdx)
{

    QFont fontOld;
    fontOld.setBold(false);
    fontOld.setPointSize(12);

    QFont fontNow;
    fontNow.setBold(true);
    fontNow.setPointSize(14);

    foreach (QWidget *w, m_listIcon)
    {
        w->hide();
    }

    if(iIdx==0)
    {
        m_listIcon[0]->show();
        ui->lb0->setFont(fontNow);
        ui->lb1->setFont(fontOld);

    }
    else if(iIdx==1)
    {
        m_listIcon[1]->show();
        ui->lb0->setFont(fontOld);
        ui->lb1->setFont(fontNow);
    }
    ui->stackedWidget->setCurrentIndex(iIdx);
}

void DialogDirections::slotClicked()
{

    ItemButton *btn=dynamic_cast<ItemButton*>(sender());

    if(btn==m_listBtn[1] && ui->lb1->text().length()<1)
    {
        return;
    }

    if(btn==m_listBtn[0] && ui->lb0->text().length()<1)
    {
        return;
    }


    if(btn==m_listBtn[0])
    {
        changePage(0);

    }
    else if(btn==m_listBtn[1])
    {
        changePage(1);
    }


}

void DialogDirections::slotClose()
{
    hide();
}
