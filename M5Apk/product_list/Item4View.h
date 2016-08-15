#ifndef ITEM4VIEW_H
#define ITEM4VIEW_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QDebug>
#include "Global.h"
namespace Ui {
class Item4View;
}


namespace Item4ViewComponent
{
enum {_left=0,_right};
enum {_productName=0,_productCost};

class Button:public QWidget
{
    Q_OBJECT
public:
    explicit Button(QWidget *parent=0):QWidget(parent)
    {
        QObject::startTimer(200);
    }

    void mousePressEvent(QMouseEvent *e)
    {
        m_iSec=0;
        m_iPressY=mapToGlobal(e->pos()).y();
        e->ignore();
    }

    void mouseReleaseEvent(QMouseEvent *e)
    {
        if(qAbs(m_iPressY-mapToGlobal(e->pos()).y())<30  && m_iSec<=400)
        {
           // m_wMask->show();
            emit clicked();
        }
        e->ignore();

        m_iSec=-1;
    }

    void timerEvent(QTimerEvent *)
    {
        if(m_iSec<0)
            return;
        m_iSec+=200;
    }

    int m_iSec;
    int m_iPressY;
signals:
    void clicked();

};

}

using namespace Item4ViewComponent;

class Item4View : public QWidget
{
    Q_OBJECT

public:

    explicit Item4View(QWidget *parent = 0);

    ~Item4View();

    void setData(QList<int> listIdx, QStringList listName, QStringList listUrl);

private:

    Ui::Item4View *ui;

    int m_iIdxLeft;

    int m_iIdxRight;

    Button *m_btn0;

    Button *m_btn1;

    void resizeEvent(QResizeEvent *);

signals:

    void clicked(int);

private slots:

    void slotItemClicked();

};

#endif // ITEM4VIEW_H
