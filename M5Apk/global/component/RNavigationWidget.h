

#ifndef ITEMBTN_H
#define ITEMBTN_H


#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QColor>
#include <QShowEvent>
#include <QMouseEvent>
#include <QPropertyAnimation>
//#include "Global.h"



class ItemBtn :public QWidget
{
    Q_OBJECT
public:
    explicit ItemBtn(QSize size,QWidget *parent=0);
    ~ItemBtn();
    void setIconColor(QColor colorBorder,QColor colorBody);
    void setCurrentIconColor(QColor colorBorder,QColor colorBody);
    void setTargetFocus(bool bIsFocus);
private:
    void paintEvent(QPaintEvent *);

    void mouseReleaseEvent(QMouseEvent *);
    void drawSpace(QPainter *p);
    QColor m_colorBorder;
    QColor m_colorBody;

    QColor m_colorCurrentBorder;
    QColor m_colorCurrentBody;
    bool m_bIsFocus;

signals:
    void clicked();

};
#endif


#ifndef CNAVIGATIONWIDGET_H
#define CNAVIGATIONWIDGET_H



#define ANI_MSEC 200
#define USE_ANI_LOCK 0





//=================================================================================================




class RNavigationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RNavigationWidget(QWidget *parent=0);
    void reSet(int iNums, int iIconSize, int iIconMargin);
    ~RNavigationWidget();
    void setIconColor(QColor colorBorder, QColor colorBody);
    void setCurrentIconColor(QColor colorBorder, QColor colorBody);
    void setWidget(QList<QLabel *> m_listPage);
    void goPage(int iIdx);
private:
    void showEvent(QShowEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    QPoint m_posOld;
    QPoint m_posContentOld;
    void checkPageIdx();
    bool m_bAniLock;
    int m_iPageIdx;
    QPropertyAnimation m_ani;

    //因為 signal透過mouse even去送，會順間送很多次，故加flag
    bool m_bIsSendEnd;

        bool m_bDriveToPre;
    QWidget *m_wViewContent;
    QWidget *m_wIndexGroup;
    QList<ItemBtn*> m_listBtn;
    QList<QWidget*> m_listWidget;
private slots:
    void slotAniFinished();
signals:
    //滑到最後一頁，再往下一頁滑時發出的訊號
    void signalEndToNext();
    //滑到第一頁時，再往上一頁滑
    void signalEndToPre();
    void signaClicked(int);
};

#endif // CNAVIGATIONWIDGET_H



