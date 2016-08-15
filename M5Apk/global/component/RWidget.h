#ifndef RWIDGET_H
#define RWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QShowEvent>
#include <QPushButton>
namespace RWidgetItem
{
class RWtopWing : public QWidget
{
    Q_OBJECT
public:
    explicit RWtopWing(QWidget *parent=0):QWidget(parent)
    {
       resize(500,60);
       setStyleSheet("background-color:rgb(0,250,25)");
       QPushButton *btn=new QPushButton(this);
       btn->setGeometry(rect());
    }

};
}

using namespace RWidgetItem;
class RWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RWidget(QWidget *parent = 0);
     void setVscrollItem(QWidget *wVscrollItem);
     void setAnimation(int iMillSec,int iMargin=50,const QEasingCurve &easing=QEasingCurve::Linear);
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void showEvent(QShowEvent *);
private:
    QWidget *m_wRollContent;

    QPropertyAnimation m_ani;

    RWtopWing *m_wTopWing;
    int m_iOldPressY;

    int m_iOldContentY;

    int m_iMargin;

    bool m_bIsVscroll;
signals:

public slots:
};

#endif // RWIDGET_H
