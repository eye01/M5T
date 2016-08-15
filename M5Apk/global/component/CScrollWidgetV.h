#ifndef CSCROLLWIDGETV_H
#define CSCROLLWIDGETV_H

#include <QWidget>
#include <QDebug>
#include <QLabel>

#include <QShowEvent>
#include <QResizeEvent>
#include <QMouseEvent>



class CScrollWidgetV : public QWidget
{
    Q_OBJECT

public:
    explicit CScrollWidgetV(QWidget *parent = 0);
    ~CScrollWidgetV();

    void setContent(int iCount,int iContentH,int iSpaceH=0);
    void setAutoContent(int iContentH, int iSpaceH=0,int iDiffCount=0);
    QList<QWidget*> m_listBtn;
private:

    QList<QWidget*> m_listSpace;
    QWidget *m_wBg;
    QWidget *m_wContent;
    int m_iOldContentY;
    int m_iSpace;
    int m_iViewCount;
    bool m_bAutoRun;
    bool m_bIsMoveDown;
    int m_iMoveValue;
    int m_iTochTime;
    QPoint m_pressPoint;

    void resizeEvent(QResizeEvent *);
    void showEvent(QShowEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void timerEvent(QTimerEvent *);
signals:
    void signalClick(int iIdx);


};

#endif // CSCROLLWIDGETV_H
