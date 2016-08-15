#ifndef LAYERZOOMVIEW_H
#define LAYERZOOMVIEW_H

#include <QWidget>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <QEventLoop>
#include <QElapsedTimer>
#include <QCoreApplication>
#include "InterfaceView.h"

namespace CZoomItem
{
class ItemOption : public QWidget
{
    Q_OBJECT

public:
    explicit ItemOption(QWidget *parent = 0);

    void setItem(QWidget *wItem);

    void showOption();

    void hideOpiton();

    ~ItemOption(){}
private :
    QWidget *m_wBg;

    QPropertyAnimation m_ani;

    int m_iVisibleTime;

    void resizeEvent(QResizeEvent *);

    void timerEvent(QTimerEvent *);

};}




class LayerZoomView : public InterfaceView
{
    Q_OBJECT

public:
    explicit LayerZoomView(QWidget *parent = 0);

    ~LayerZoomView();

    void setBackground(QString st);

    void setOption(QWidget *w);

    void setItemWidget(QList<QWidget *> listWidget, int iSpace=-1, int iMinHeight=-1, int iMaxHeight=-1);

    void goIdx(int iIdx);

    void setSlice(int iH,QString sTopStyleSheet,QString sBottomSt);

    int length();

private:

    CZoomItem::ItemOption *m_wOption;

    typedef enum _RollMode{_zoom,_view}RollMode;
    RollMode m_nRollMode;

    typedef enum _RollStatus{_first,_driveUp,_driveDown,_last}RollStatus;
    RollStatus m_nRollStatus;

    bool m_bAniLock;

    int m_iSliceHeight;

    int m_iMinHeight;

    int m_iMaxHeight;

    int m_iSpace;

    int m_iPressMiniSec;

    int m_iReleaseMiniSec;

    int m_iPressContentY;

    int m_iPressPosY;

    bool m_bUseOption;

    int m_iIdx;

    int m_iLineStart;

    int m_iLineValue;

    QWidget *m_wBg;

    QWidget *m_wContent;

    QWidget *m_wMask;

    QList<QWidget*> m_listWidget;

    QSize m_sizeView;

    QWidget *m_wTopSlice;

    QWidget *m_wBottomSlice;

    QPropertyAnimation m_aniHoming;

    QPropertyAnimation m_aniMoveIdx;

    QTimeLine *m_timeLine;

    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

    void mouseMoveEvent(QMouseEvent *e);

    void timerEvent(QTimerEvent *);

    void resizeEvent(QResizeEvent *);

    void checkZoom(int iValue=-1);

    void layoutLoc();

signals:
//    void clicked(int iIdx);
//    void changeIdx(int iIdx);
public slots:

    void slotHoming(int);

private slots:

    void homing();

    void slotAniChange(QVariant);

    void slotAnifinish();

};

#endif // LAYERZOOMVIEW_H
