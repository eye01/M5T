#ifndef LAYER4VIEW_H
#define LAYER4VIEW_H

#include <QWidget>
#include "InterfaceView.h"
#include "Item4View.h"
#include <QMouseEvent>
#include <QPropertyAnimation>
#include "Global.h"

#define TIMER_DURATION 100

class Layer4View : public InterfaceView
{
    Q_OBJECT
public:
    explicit Layer4View(QWidget *parent = 0);

    void setBackground(QString st);

    void setOption(QWidget *){}

    void setItemWidget(QList<QWidget *>, int , int , int ){}

    void setItemWidget(QStringList listName, QStringList listImage);

    void goIdx(int iIdx);

    void setSlice(int iH,QString sTopStyleSheet ,QString sBottomStyleSheet);

    int length();

    QWidget *m_wContent;

    //QOpenGLWidget *m_wContent;
private:

    void mousePressEvent(QMouseEvent *e);

    void mouseMoveEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

    void timerEvent(QTimerEvent *);

    //=====   一般移動所使用
    QPropertyAnimation m_ani;

    int m_iOldPressY;

    int m_iOldContentY;

    int m_iPressMiniSec;

    int m_iReleaseMiniSec;
    //回傳true 代表位移越界修正
    bool contentMove(int iValue);
    //彈回限制範圍內，並以timer 消除slice
    void correctRange();
    //---------------------------------

    //=====powerful move (指強力滑動補間)
    //滑動位移量
    int m_iRollY;
    //滑動時間
    int m_iRollTime;
    //滑動力道
    //int m_sStrongSpeed;  //#算了 以位移量除以時間計算之
    //強力滑動的旗標
    float m_flagPowerFull;
    //-----------------------------------

    int m_iLength;
    //這個idx是指每二個為一個單位的
    int m_iIdx;
    //
    int m_iTop;

    int m_iBottom;

    int m_iSliceHeight;

    QWidget *m_wBg;

    QWidget *m_wTopSlice;

    QWidget *m_wBottomSlice;

    QList<Item4View*> m_listItem;

    QList<int> m_listLocY;

    void resizeEvent(QResizeEvent *);

    void powerfulMove();

signals:


};

#endif // LAYER4VIEW_H
